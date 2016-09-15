#include "./sender_t.h"

PDU_Req sender_t::act(Inj_t * parent, bool fin) {
        if(seq < until) {
            parent->scheduleAt(simTime() + getInterval(), &at);
            if(parent->portReady(dstAddr, QoS)){
                return PDU_Req(this, new sender_d(flowId, getPDUSize(), ++seq));
            }
        } else if(!fin) {
            setNextUntil();
            parent->scheduleAt(getNextOn(), &at);
        }
        return PDU_Req();
}
