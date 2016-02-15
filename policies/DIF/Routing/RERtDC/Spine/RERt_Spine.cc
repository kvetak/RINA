#include "RERt_Spine.h"

namespace RERtDC {
Register_Class(RERt_Spine);

using namespace std;
using namespace NSPSimpleDC;


    void RERt_Spine::startMyNeis() {
        myNeisSize = nPod + nEdgeP;
        myNeis = new nodeNeig[myNeisSize];

        for(unsigned int i = 0; i< nPod; i++) {
            auto & n = myNeis[i];
            DCAddr n_addr = DCAddr(TYPEID_Fabric, i, Im.a);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));
        }
        for(unsigned int i = 0; i< nEdgeP; i++) {
            auto & n = myNeis[i+nPod];
            DCAddr n_addr = DCAddr(TYPEID_Edge, i, Im.a);
            n.init(n_addr, Address(n_addr.toString().c_str(), myAddress.getDifName().getName().c_str()));
        }
    }

    portId RERt_Spine::getNeiId(DCAddr addr) {
        switch(addr.type) {
            case TYPEID_Fabric:
                if(addr.b != Im.a) { return myNeisSize; }
                if(addr.a >= nPod) { return myNeisSize; }
                return addr.a;
            case TYPEID_Edge:
                if(addr.b != Im.a) { return myNeisSize; }
                return addr.a + nPod;
        }
        return myNeisSize;
    }

    RawExceptionsList RERt_Spine::getExceptions() {
        return RawExceptionsList();
    }
}
