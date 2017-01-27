#include "./client_t.h"

#include "Addons/DataInjectors/FlowsSimulation/Implementations/VDT/VDT_Listener.h"

PDU_Req client_t::act(Inj_t * parent, bool fin) {

    PDU_Req ret;
    ret.f = this;
    if(fin || thend) { return ret; }

    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, getPDUSize(), ++seq, A, B, nacking, until, interval, data_size);

        if(! rt.isScheduled()) {
            nextRet = simTime().dbl() + retT;
            parent->scheduleAt(nextRet, &rt);
        }

        if(kt.isScheduled()) { parent->cancelEvent(&kt); }
    } else { parent->scheduleAt(simTime() + ackT/10, &at); }

    return ret;
}
PDU_Req client_t::ret(Inj_t * parent, bool fin) {

    PDU_Req ret;
    ret.f = this;
    if(fin || thend) { return ret; }

    nextRet = simTime().dbl() + retT;

    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, getPDUSize(), seq, A, B, nacking, until, interval, data_size);
        if(kt.isScheduled()) { parent->cancelEvent(&kt); }
    }
    parent->scheduleAt(nextRet, &rt);
    return ret;
}

PDU_Req client_t::ack(Inj_t * parent, bool fin) {

    PDU_Req ret;
    ret.f = this;
    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new client_d(flowId, 0, -1, A, B, nacking, until, interval, data_size);
    } else { parent->scheduleAt(simTime()+ackT, &kt); }

    return ret;
}

void client_t::receive(Inj_t * parent, shared_ptr<server_d> d, bool fin) {
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

        if(nacking && lastNAck + ackT < simTime().dbl()) {
            if (kt.isScheduled()) { parent->cancelEvent(&kt); }
            parent->scheduleAt(simTime(), &kt);
        } else if (!kt.isScheduled()) {
            parent->scheduleAt(simTime()+ackT, &kt);
        }

    }

    if(d->A >= seq) {
        seq = d->A;
        if(rt.isScheduled()) { parent->cancelEvent(&rt); }
    }

    if(!thend && B < 0 && A >= nextRq) {
        if(nextRq > 0) { completeRequest(parent); }
        //Signal Data received and start new request
        if(fin) { thend = true; end(parent); }
        else {
            setNextUntil();
            setNextRate();
            if(at.isScheduled()) { parent->cancelEvent(&at); }
            parent->scheduleAt(getNextOn(simTime()), &at);
        }
    }
}
