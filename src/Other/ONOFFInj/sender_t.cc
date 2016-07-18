#include "sender_t.h"
#include "ONOFInj.h"

pduReq sender_t::act(ONOFInj * parent, bool fin) {
        if(seq < until) {
            parent->scheduleAt(simTime() + getInterval(), &at);
            if(parent->portReady(dstAddr, QoS)){
                return pduReq(this, new sender_d(flowId, getPDUSize(), ++seq));
            }
        } else if(!fin) {
            setNextUntil();
            return act(parent, fin);
        }
        return pduReq();
}
