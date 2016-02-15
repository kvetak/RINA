#include "REFwd_Edge.h"
#include "DC_Defines.h"

namespace REFwdDC {

Register_Class(REFwd_Edge);

using namespace std;
using namespace NSPSimpleDC;

    void REFwd_Edge::initializeSubPolicy() {
        nSpine = (unsigned char) par("nSpine").longValue();
        if(nSpine > 0) {
            myports = new Port[nSpine];
            myportsSyze = nSpine;
        } else {
            cerr << "Number of Spine per Spine-set cannot be 0." << endl;
            endSimulation();
        }
    }

    bool REFwd_Edge::setNeigh(const DCAddr & n_addr, Port port) {
        if(n_addr.type != TYPEID_Spine || n_addr.a != Im.b || n_addr.b >= nSpine) {
            cerr << "At "<< Im << " invalid neighbour "<< n_addr << endl;
            endSimulation();
            return false;
        }

        Port old = myports[n_addr.b];
        myports[n_addr.b] = port;

        bool refreshDown = false;
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

        if(refreshDown) {
            downList.clear();
            for(unsigned char i = 0; i < nSpine; i++) {
                if(myports[i] != nullptr) { downList.push_back(i); }
            }
            return true;
        }

        return false;
    }


    portList REFwd_Edge::readException(const Exception & e) {
        if(! (e[0] & EXCEPTION_FLAG_DOWN) ) { return portList(); }

        portList ret;
        bool inverse = e[0] | EXCEPTION_FLAG_INVERSE;

        if(e[1] == 0) {
            if(inverse) { return downList; }
            else { return portList(); }
        }

        unsigned char j = 0;
        unsigned char current = e[j+2];

        for(unsigned char i = 0; i < nSpine; i++) {
            if(myports[i] == nullptr) { continue; }
            if((current == i) != inverse) { ret.push_back(i); }
            if(current == i) {
                j++;
                if(j < e[1]) { current = e[j+2]; }
                else { current = nSpine; }
            }
        }

        return ret;
    }


    portList REFwd_Edge::readRawException(const RawException & raw) {
        if(raw.OK) { return executeRule(raw.addr); }
        if(raw.validNeis.empty()) { return portList(); }

        set<portId> ports;
        for(const auto n : raw.validNeis) {
            if(n.type == TYPEID_Spine
                    && n.a == Im.b
                    && n.b < nSpine
                    && myports[n.b] != nullptr) {
                ports.insert(n.b);
            }
        }

        return portList(ports.begin(), ports.end() );
    }

    portList REFwd_Edge::executeRule(const DCAddr & n_addr) {
        if(n_addr.type != TYPEID_Spine|| n_addr.a != Im.b) {
            return downList;
        } else {
            const portId & k = n_addr.b;
            if(k < nSpine && myports[k] != nullptr) { return directList(k); }
            else { return portList(); }
        }
    }

    Exception REFwd_Edge::computeException(const RawException & raw) {
        portList list = readRawException(raw);
        if(list.empty()) { return createEmptyException(); }

        if(list.size()*2 > nSpine) {
            portList ilist = inverseList(list, 0 , nSpine);
            return createException(EXCEPTION_FLAG_DOWN | EXCEPTION_FLAG_INVERSE, ilist);
        } else {
            return createException(EXCEPTION_FLAG_DOWN, list);
        }
    }

}
