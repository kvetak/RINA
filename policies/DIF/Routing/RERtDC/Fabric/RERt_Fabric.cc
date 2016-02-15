#include "RERt_Fabric.h"

namespace RERtDC {
Register_Class(RERt_Fabric);

using namespace std;
using namespace NSPSimpleDC;
using namespace REFwdDC;


    void RERt_Fabric::startMyNeis() {
        myNeisSize = nTor + nSpine;
        myNeis = new nodeNeig[myNeisSize];

        for(unsigned int i = 0; i< nTor; i++) {
            auto & n = myNeis[i];
            DCAddr n_addr = DCAddr(TYPEID_ToR, Im.a, i);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));
        }
        for(unsigned int i = 0; i< nSpine; i++) {
            auto & n = myNeis[i+nTor];
            DCAddr n_addr = DCAddr(TYPEID_Spine, Im.b, i);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));
        }
    }

    portId RERt_Fabric::getNeiId(DCAddr addr) {
        switch(addr.type) {
            case TYPEID_ToR:
                if(addr.a != Im.a) { return myNeisSize; }
                if(addr.b >= nTor) { return myNeisSize; }
                return addr.b;
            case TYPEID_Spine:
                if(addr.a != Im.b) { return myNeisSize; }
                return addr.b + nTor;
        }
        return myNeisSize;
    }

    RawExceptionsList RERt_Fabric::getExceptions() {
        return RawExceptionsList();
    }
}
