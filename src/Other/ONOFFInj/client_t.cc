#include "client_t.h"
#include "ONOFInj.h"

#include "InjListener.h"

pduReq client_t::act(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;
    if(fin || thend) { return ret; }

    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, getPDUSize(), ++seq, A, B, nacking, until, interval);
        InjListener::instance->dataRequestStarted(parent->src, dstAddr, flowId);

        if(! rt.isScheduled()) {
            nextRet = simTime().dbl() + retT;
            parent->scheduleAt(nextRet, &rt);
        }

        if(kt.isScheduled()) { parent->cancelEvent(&kt); }
    } else { parent->scheduleAt(simTime() + ackT, &at); }

    return ret;
}
pduReq client_t::ret(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;
    if(fin || thend) { return ret; }

    nextRet = simTime().dbl() + retT;

    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, getPDUSize(), seq, A, B, nacking, until, interval);
        if(kt.isScheduled()) { parent->cancelEvent(&kt); }
    }
    parent->scheduleAt(nextRet, &rt);
    return ret;
}

pduReq client_t::ack(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;
    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, 0, -1, A, B, nacking, until, interval);
    } else { parent->scheduleAt(simTime()+ackT, &kt); }

    return ret;
}

void client_t::receive(ONOFInj * parent, shared_ptr<server_d> d, bool fin) {
    retT = ackT + 3 * (simTime().dbl() - d->t0.dbl());

    if(d->seq >= 0) { // seq == -1 -> only Ack message
        if(B < 0) {//In "common" state
            if(d->seq == A+1) {
                //All green
                nacking = false;
                A++;
            } else if(d->seq == A+2) {
                //Change to selective nAck
                B = ++A;
                A++;
            } else if(d->seq <= A) {
                //Already Acked...
                nacking = true;
            } else {
                //Now nAcking
                nacking = true;
            }
        } else {// In selective nAck state
            if(d->seq == B) {
                //Change to "common"
                B = -1;
            } else if ( d->seq == A+1) {
                //All yellow
                A++;
            } else  if(d->seq <= A) {
                //Already Acked...
                nacking = true;
            } else {
                //Now nAcking
                nacking = true;
            }
        }

        if(nacking && lastNAck +ackT < simTime().dbl()) {
            if (kt.isScheduled()) { parent->cancelEvent(&kt); }
            parent->scheduleAt(simTime(), &kt);
        } else if (!kt.isScheduled()) { parent->scheduleAt(simTime()+ackT, &kt); }
    }

    if(d->A >= seq) {
        seq = d->A;
        if(rt.isScheduled()) { parent->cancelEvent(&rt); }
    }

    if(!thend && B < 0 && A >= until) {
        //Signal Data received and start new request
        InjListener::instance->dataRequestEnded(parent->src, dstAddr, flowId);

        if(fin) { thend = true; }
        else {
            setNextUntil();
            setNextRate();
            if(at.isScheduled()) { parent->cancelEvent(&at); }
            parent->scheduleAt(getNextOn(simTime()), &at);
        }
    }
}
