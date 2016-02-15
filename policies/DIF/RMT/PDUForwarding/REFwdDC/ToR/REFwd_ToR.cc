#include "REFwd_ToR.h"
#include "DC_Defines.h"

namespace REFwdDC {
Register_Class(REFwd_ToR);

using namespace std;
using namespace NSPSimpleDC;

    void REFwd_ToR::initializeSubPolicy() {
        nFab = (unsigned char) par("nFab").longValue();
        if(nFab > 0) {
            myports = new Port[nFab];
            myportsSyze = nFab;
        } else {
            cerr << "Number of Fabrics per Pod cannot be 0." << endl;
            endSimulation();
        }
    }

    bool REFwd_ToR::setNeigh(const DCAddr & n_addr, Port port) {
        if(n_addr.type != TYPEID_Fabric || n_addr.a != Im.a || n_addr.b >= nFab) {
            cerr << "At "<< Im << " invalid neighbour "<< n_addr << endl;
            endSimulation();
            return false;
        }

        Port old = myports[n_addr.b];
        myports[n_addr.b] = port;

        bool refreshUp = false;
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

        if(refreshUp) {
            upList.clear();
            for(unsigned char i = 0; i < nFab; i++) {
                if(myports[i] != nullptr) { upList.push_back(i); }
            }
            return true;
        }

        return false;
    }


    portList REFwd_ToR::readException(const Exception & e) {
        if(! (e[0] & EXCEPTION_FLAG_UP) ) { return portList(); }

        portList ret;
        bool inverse = e[0] | EXCEPTION_FLAG_INVERSE;

        if(e[1] == 0) {
            if(inverse) { return upList; }
            else { return portList(); }
        }

        unsigned char j = 0;
        unsigned char current = e[j+2];

        for(unsigned char i = 0; i < nFab; i++) {
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < e[1]) { current = e[j+2]; }
                else { current = nFab; }
            }
        }

        return ret;
    }


    portList REFwd_ToR::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return portList(); }

        set<portId> ports;
        for(const auto n : raw.validNeis) {
            if(n.type == TYPEID_Fabric
                    && n.a == Im.a
                    && n.b < nFab
                    && myports[n.b] != nullptr) {
                ports.insert(n.b);
            }
        }

        return portList(ports.begin(), ports.end() );
    }

    portList REFwd_ToR::executeRule(const DCAddr & n_addr) {
        unsigned int k = nFab;
        switch(n_addr.type) {
            case TYPEID_ToR:
            case AGID_Pod:
                return upList;
            case TYPEID_Fabric :
            case TYPEID_Edge :
                k = n_addr.b;
                break;
            case TYPEID_Spine :
            case AGID_Spine:
                k = n_addr.a;
                break;
        }
        if(k < nFab && myports[k] != nullptr) { return directList(k); }
        else { return portList(); }
    }

    Exception REFwd_ToR::computeException(const RawException & raw) {
        portList list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        if(list.size()*2 > nFab) {
            portList ilist = inverseList(list,0,nFab);
            return createException(EXCEPTION_FLAG_UP | EXCEPTION_FLAG_INVERSE, ilist);
        } else {
            return createException(EXCEPTION_FLAG_UP, list);
        }
    }

}
