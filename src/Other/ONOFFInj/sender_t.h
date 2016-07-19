#pragma once

#include "Flow_t.h"

class ONOFInj;

class sender_t : public Flow_t {
public :
    seq_t seq;
    actTimer at;


    int until;

    ~sender_t(){}
    sender_t(int fid, string dst, string qos):
      Flow_t(fid, dst, qos), seq (0), until(0) {
        seq = -1;
        simTime();
    }

    virtual pduReq act(ONOFInj * parent, bool fin);

protected:
    virtual int getPDUSize() { return 20; }
    virtual double getInterval() { return 0.01; }
    virtual double getNextOn() { return simTime().dbl() + 1.0; }
    virtual void setNextUntil() { until += 1000; }
};


class voice_f : public sender_t {
public :
    static int min_pdu_len, max_pdu_len;
    static double interval, idle_time, burst_time;

    voice_f(int fid, string dst, string qos):
    sender_t(fid, dst, qos){}

    virtual int getPDUSize() { return uniform(voice_f::min_pdu_len, voice_f::max_pdu_len); }
    virtual double getInterval() { return interval; }
    virtual double getNextOn() { return simTime().dbl() + idle_time; }
    virtual void setNextUntil() { until += (int)ceil(burst_time*interval); }
};
