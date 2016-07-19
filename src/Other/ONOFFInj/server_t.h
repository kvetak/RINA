#pragma once

#include "Flow_t.h"

class ONOFInj;

class server_t : public Flow_t {
public :
    static double ackT;
    static int pdu_size;

    // Current seq#, last ack received, seq# of selective retransmission
    seq_t seq, acked, sN;
    bool nacking;
    double lastNAck;

    // Last seq# received in order
    seq_t A;
    bool sendSN;

    actTimer at;
    retransTimer rt;
    selretransTimer st;
    ackTimer kt;

    simtime_t nextRet;
    double retT;

    seq_t until;
    double interval;

    simtime_t next_reset;

    ~server_t(){}
    server_t(int fid, string dst, string qos):
      Flow_t(fid, dst, qos), seq (0), until(false), interval(0) {
        seq = -1;
        acked = -1;
        sN = -1;
        A = -1;
        sendSN = false;
        nacking = false;
        nextRet  = 0;
        retT = 0.1;
        lastNAck = -500.0;
        next_reset = 0.0;
    }

    virtual pduReq act(ONOFInj * parent, bool fin);
    virtual pduReq ret(ONOFInj * parent, bool fin);
    virtual pduReq sret(ONOFInj * parent, bool fin);
    virtual pduReq ack(ONOFInj * parent, bool fin);

    virtual void receive(ONOFInj * parent, shared_ptr<client_d> d);
};
