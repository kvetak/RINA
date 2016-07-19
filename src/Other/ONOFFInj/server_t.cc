#include "server_t.h"
#include "ONOFInj.h"

pduReq server_t::act(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;

    if(parent->portReady(dstAddr, QoS)) {
        if(sendSN) {
            sendSN = false;
            ret.data = new server_d(flowId, server_t::pdu_size, sN, A, nacking);
            parent->scheduleAt(simTime() + interval, &at);
        } else if(seq < until) {
            ret.data = new server_d(flowId, server_t::pdu_size, ++seq, A, nacking);
            if(! rt.isScheduled()) {
                nextRet = simTime() + retT;
                //////cout << "A"<<endl;
                parent->scheduleAt(nextRet, &rt);
                //////cout << "nop"<<endl;
            }
            parent->scheduleAt(simTime() + interval, &at);
        }
    } else { parent->scheduleAt(simTime() + interval, &at); }

    if(ret.data != nullptr) { if(kt.isScheduled()) { parent->cancelEvent(&kt); } }

    return ret;
}

pduReq server_t::ret(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;

    //reset last seq to last ack received, and schedule new retransmit
    seq = acked;
    nextRet += retT;
    if(nextRet < simTime()) { nextRet = simTime(); }
    parent->scheduleAt(nextRet, &rt);
    if(!at.isScheduled()) { parent->scheduleAt(simTime(), &at); }

    return ret;
}

pduReq server_t::sret(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;

    if(sN >= 0) {
        //set next sent = selective nAck, and schedule new retransmit
        sendSN = true;
        parent->scheduleAt(simTime() + retT, &st);
        if(!at.isScheduled()) { parent->scheduleAt(simTime(), &at); }
    } else {
        sendSN = false;
    }
    return ret;
}

pduReq server_t::ack(ONOFInj * parent, bool fin) {
    pduReq ret;
    ret.f = this;

    if(parent->portReady(dstAddr, QoS)) {
        ret.data = new server_d(flowId, 0, -1, A, nacking);
    } else { parent->scheduleAt(simTime()+ackT, &kt); }

    return ret;
}

void server_t::receive(ONOFInj * parent, shared_ptr<client_d> d) {
    retT = ackT + 3 * (simTime().dbl() - d->t0.dbl());

    if(d->seq >= 0) { // seq == -1 -> only Ack message
        if(d->seq == A+1) {
            //All green
            nacking = false;
            A++;
        } else if(d->seq <= A) {
            //Already Acked...
            nacking = true;
        } else {
            //Now nAcking
            nacking = true;
        }

        if(nacking && lastNAck +ackT < simTime().dbl()) {
            if (kt.isScheduled()) { parent->cancelEvent(&kt); }
            parent->scheduleAt(simTime(), &kt);
        } else if (!kt.isScheduled()) { parent->scheduleAt(simTime()+ackT, &kt); }

        until = d->reqSize;
        interval = d->reqInterval;
    }

    if(d->B < 0) { // Stop selective nAcking
        sN = -1;
        sendSN = false;
        if(st.isScheduled()) { parent->cancelEvent(&st); }
    } else if(d->B > sN) { // Selective nAck Request seq# > last one being selNAcked
        sN = d->B;
        if(st.isScheduled()) { parent->cancelEvent(&st); }
        parent->scheduleAt(simTime(), &st);
    } else {
        if(!st.isScheduled()) { parent->scheduleAt(simTime(), &st); }
    }


    if(d->A > acked) {
        seq_t delib = d->A - acked;
        acked = d->A;
        if(rt.isScheduled()) { parent->cancelEvent(&rt); }
        if(acked < seq) {
            nextRet += delib * interval;
            if(nextRet < simTime()) { nextRet = simTime(); }
            //////cout << "C"<<endl;
            parent->scheduleAt(nextRet, &rt);
            //////cout << "nop"<<endl;
        }
    }
    if(d->isNack && next_reset  <= simTime() ) {
        next_reset = simTime() + retT;
        seq = acked; nextRet = 0;
    }
    if(until > seq) {

        // More data to send!!
        if(!at.isScheduled()) { parent->scheduleAt(simTime(), &at); }
    }
}
