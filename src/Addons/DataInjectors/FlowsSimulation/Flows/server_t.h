#pragma once

#include "./Flow_t.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Data_t.h"

class Inj_t;

class server_t : public Flow_t {
public :
    double ackT;

    // Current seq#, last ack received, seq# of selective retransmission
    seq_t seq, acked, sN;
    bool nacking;
    double lastNAck;

    int pdu_size;

    // Last seq# received in order
    seq_t A;
    bool sendSN;

    Flow_timer at;
    Flow_timer rt;
    Flow_timer st;
    Flow_timer kt;

    simtime_t nextRet;
    double retT;

    seq_t until;
    double interval;

    simtime_t next_reset;

    ~server_t(){}
    server_t(int fid, string dst, string qos, double _ackT = 0.1):
      Flow_t(fid, dst, qos), seq (0), until(false), interval(0) {
        seq = -1;
        acked = -1;
        sN = -1;
        A = -1;
        sendSN = false;
        nacking = false;
        nextRet  = 0;
        lastNAck = -500.0;
        next_reset = 0.0;
        pdu_size = 1000;

        ackT = _ackT;
        retT = 1.5*_ackT;

        at.type = action;
        rt.type = retrans;
        st.type = selRetrans;
        kt.type = ackTime;
    }

    virtual PDU_Req act(Inj_t * parent, bool fin);
    virtual PDU_Req ret(Inj_t * parent, bool fin);
    virtual PDU_Req sret(Inj_t * parent, bool fin);
    virtual PDU_Req ack(Inj_t * parent, bool fin);

    virtual void receive(Inj_t * parent, shared_ptr<client_d> d);
    virtual int getPDUSize();
};
