#include "REFwd_Fabric.h"
#include "DC_Defines.h"

namespace REFwdDC {
Register_Class(REFwd_Fabric);

using namespace std;
using namespace NSPSimpleDC;

    void REFwd_Fabric::initializeSubPolicy() {
        nTor = (unsigned char) par("nTor").longValue();
        nSpine = (unsigned char) par("nSpine").longValue();

        if(nTor <= 0) {
            cerr << "Number of Tors per Pod cannot be 0." << endl;
            endSimulation();
            return;
        }
        if(nSpine <= 0) {
            cerr << "Number of Spine per Spine-set cannot be 0." << endl;
            endSimulation();
            return;
        }

        myportsSyze = nTor + nSpine;
        myports = new Port[myportsSyze];
    }

    bool REFwd_Fabric::setNeigh(const DCAddr & n_addr, Port port) {
        bool refreshUp = false;
        bool refreshDown = false;
        bool validNei = false;

        switch(n_addr.type) {
            case TYPEID_ToR:
                if(n_addr.a == Im.a && n_addr.b < nTor) {
                    validNei = true;
                    Port old = myports[n_addr.b];
                    myports[n_addr.b] = port;

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
            case TYPEID_Spine :
                if(n_addr.a == Im.b && n_addr.b < nSpine) {
                    validNei = true;
                    Port old = myports[n_addr.b+nTor];
                    myports[n_addr.b+nTor] = port;

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
            for(unsigned char i = 0; i < nTor; i++) {
                if(myports[i] != nullptr) { downList.push_back(i); }
            }
        }

        if(refreshUp) {
            upList.clear();
            for(unsigned char i = nTor; i < myportsSyze; i++) {
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


    portList REFwd_Fabric::readException(const Exception & e) {
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

        unsigned char min = (hType | EXCEPTION_FLAG_DOWN)? 0 : nTor;
        unsigned char max = (hType | EXCEPTION_FLAG_UP)? nTor : myportsSyze;

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


    portList REFwd_Fabric::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return portList(); }

        set<portId> ports;
        for(const auto n : raw.validNeis) {
            if(n.type == TYPEID_ToR
                    && n.a == Im.a
                    && n.b < nTor
                    && myports[n.b] != nullptr) {
                ports.insert(n.b);
            } else if(n.type == TYPEID_Spine
                    && n.a == Im.b
                    && n.b < nSpine
                    && myports[n.b+nTor] != nullptr) {
                ports.insert(n.b+nTor);
            }
        }

        return portList(ports.begin(), ports.end() );
    }

    portList REFwd_Fabric::executeRule(const DCAddr & n_addr) {
        int k = myportsSyze;
        switch(n_addr.type) {
            case TYPEID_ToR :
                if(n_addr.a == Im.a) {
                    if(n_addr.b < nTor) { k = n_addr.b; }
                } else { return upList; }
                break;
            case TYPEID_Fabric :
                if(n_addr.a == Im.a) { return downList; }
                if(n_addr.b == Im.b) { return upList; }
                else { return bothList; }
                break;
            case TYPEID_Edge :
                if(n_addr.b == Im.b) { return upList; }
                else { return downList; }
                break;
            case TYPEID_Spine :
                if(n_addr.a == Im.b) {
                    if(n_addr.b < nSpine) { k = n_addr.b+nTor; }
                } else { return downList; }
                break;
            case AGID_Pod : return upList;
            case AGID_Spine : return downList;

        }

        if(k < myportsSyze && myports[k] != nullptr) { return directList(k); }
        else { return portList(); }
    }

    Exception REFwd_Fabric::computeException(const RawException & raw) {
        portList list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        unsigned char hType = EXCEPTION_FLAG_NONE;
        if(list[0] < nTor) { hType |= EXCEPTION_FLAG_DOWN; }
        if(list[list.size()-1] >= nTor) { hType |= EXCEPTION_FLAG_UP; }

        switch(hType) {
            case EXCEPTION_FLAG_UP:
                if(list.size()*2 > nSpine) {
                    portList ilist = inverseList(list,nTor,myportsSyze);
                    return createException(EXCEPTION_FLAG_UP | EXCEPTION_FLAG_INVERSE, ilist);
                } else {
                    return createException(EXCEPTION_FLAG_UP, list);
                }
                break;
            case EXCEPTION_FLAG_DOWN:
                if(list.size()*2 > nTor) {
                    portList ilist = inverseList(list,0,nTor);
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
