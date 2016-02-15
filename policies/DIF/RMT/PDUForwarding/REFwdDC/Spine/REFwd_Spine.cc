#include "REFwd_Spine.h"
#include "DC_Defines.h"

namespace REFwdDC {
Register_Class(REFwd_Spine);

using namespace std;
using namespace NSPSimpleDC;

    void REFwd_Spine::initializeSubPolicy() {
        nPod  = (unsigned char) par("nPod").longValue();
        nEdgeP = (unsigned char) par("nEdgeP").longValue();

        if(nPod <= 0) {
            cerr << "Number of Pods cannot be 0." << endl;
            endSimulation();
            return;
        }
        if(nEdgeP <= 0) {
            cerr << "Number of Edge-planed cannot be 0." << endl;
            endSimulation();
            return;
        }

        myportsSyze = nPod + nEdgeP;
        myports = new Port[myportsSyze];
    }

    bool REFwd_Spine::setNeigh(const DCAddr & n_addr, Port port) {
        bool refreshUp = false;
        bool refreshDown = false;
        bool validNei = false;

        switch(n_addr.type) {
            case TYPEID_Fabric:
                if(n_addr.b == Im.a && n_addr.a < nPod) {
                    validNei = true;
                    Port old = myports[n_addr.a];
                    myports[n_addr.a] = port;

                    if(port != nullptr) {
                        if(old != nullptr) {
                            cache.replacePort(old, port);
                        } else {
                            refreshDown = true;
                        }
                    } else if(old != nullptr) {
                        cache.removePort(old);
                        refreshDown = true;
                    }
                }
                break;
            case TYPEID_Edge :
                if(n_addr.b == Im.a && n_addr.a < nEdgeP) {
                    validNei = true;
                    Port old = myports[n_addr.a+nPod];
                    myports[n_addr.a+nPod] = port;

                    if(port != nullptr) {
                        if(old != nullptr) {
                            cache.replacePort(old, port);
                        } else {
                            refreshUp = true;
                        }
                    } else if(old != nullptr) {
                        cache.removePort(old);
                        refreshUp = true;
                    }
                }
                break;
        }

        if(!validNei) {
            cerr << "At "<< Im << " invalid neighbour "<< n_addr << endl;
            endSimulation();
            return false;
        }


        if(refreshDown) {
            downList.clear();
            for(unsigned char i = 0; i < nPod; i++) {
                if(myports[i] != nullptr) { downList.push_back(i); }
            }
        }

        if(refreshUp) {
            upList.clear();
            for(unsigned char i = nPod; i < myportsSyze; i++) {
                if(myports[i] != nullptr) { upList.push_back(i); }
            }
        }

        if(refreshUp || refreshDown) {
            bothList.clear();
            for(unsigned char i = 0; i < myportsSyze; i++) {
                if(myports[i] != nullptr) { bothList.push_back(i); }
            }
            return true;
        }

        return false;
    }


    portList REFwd_Spine::readException(const Exception & e) {
        unsigned char header = e[0];
        if(! (header & EXCEPTION_FLAG_UPDOWN) ) { return portList(); }

        portList ret;
        bool inverse = header | EXCEPTION_FLAG_INVERSE;

        unsigned char hType = header & EXCEPTION_FLAG_UPDOWN;

        if(e[1] == 0) {
            if(!inverse) { return portList(); }
            switch(hType) {
                case EXCEPTION_FLAG_UP : return upList;
                case EXCEPTION_FLAG_DOWN : return downList;
                case EXCEPTION_FLAG_UPDOWN : return bothList;
            }
        }

        unsigned char min = (hType | EXCEPTION_FLAG_DOWN)? 0 : nPod;
        unsigned char max = (hType | EXCEPTION_FLAG_UP)? nPod : myportsSyze;

        unsigned char j = 0;
        unsigned char current = e[j+2];

        for(unsigned char i = min; i < max; i++) {
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < e[1]) { current = e[j+2]; }
                else { current = max; }
            }
        }

        return ret;
    }


    portList REFwd_Spine::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return portList(); }

        set<portId> ports;
        for(const auto n : raw.validNeis) {
            if(n.type == TYPEID_Fabric
                    && n.b == Im.a
                    && n.a < nPod
                    && myports[n.a] != nullptr) {
                ports.insert(n.a);
            } else if(n.type == TYPEID_Edge
                    && n.b == Im.a
                    && n.a < nEdgeP
                    && myports[n.a+nPod] != nullptr) {
                ports.insert(n.a+nPod);
            }
        }

        return portList(ports.begin(), ports.end() );
    }

    portList REFwd_Spine::executeRule(const DCAddr & n_addr) {
        int k = myportsSyze;
        switch(n_addr.type) {
            case TYPEID_ToR :
            case TYPEID_Fabric :
            case AGID_Pod :
                if(n_addr.a < nPod) { k = n_addr.a; }
                break;
            case TYPEID_Edge :
                if(n_addr.b == Im.a) {
                    if(n_addr.a < nEdgeP) { k = n_addr.a+nPod; }
                }
                else { return downList; }
                break;
            case TYPEID_Spine :
            case AGID_Spine :
                return downList;
        }

        if(k < myportsSyze && myports[k] != nullptr) { return directList(k); }
        else { return portList(); }
    }

    Exception REFwd_Spine::computeException(const RawException & raw) {
        portList list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        unsigned char hType = EXCEPTION_FLAG_NONE;
        if(list[0] < nPod) { hType |= EXCEPTION_FLAG_DOWN; }
        if(list[list.size()-1] >= nPod) { hType |= EXCEPTION_FLAG_UP; }

        switch(hType) {
            case EXCEPTION_FLAG_UP:
                if(list.size()*2 > nEdgeP) {
                    portList ilist = inverseList(list,nPod,myportsSyze);
                    return createException(EXCEPTION_FLAG_UP | EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(EXCEPTION_FLAG_UP, list);
                }
                break;
            case EXCEPTION_FLAG_DOWN:
                if(list.size()*2 > nPod) {
                    portList ilist = inverseList(list,0,nPod);
                    return createException(EXCEPTION_FLAG_DOWN | EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(EXCEPTION_FLAG_DOWN, list);
                }
                break;
            case EXCEPTION_FLAG_UPDOWN:
                if(list.size()*2 > myportsSyze) {
                    portList ilist = inverseList(list,0,myportsSyze);
                    return createException(EXCEPTION_FLAG_UPDOWN | EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(EXCEPTION_FLAG_UPDOWN, list);
                }
                break;
        }

        return createEmptyException();
    }

}
