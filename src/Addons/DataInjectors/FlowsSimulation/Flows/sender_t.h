#pragma once

#include "./Flow_t.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Data_t.h"

class Inj_t;

class sender_t : public Flow_t {
public :
    seq_t seq;
    Flow_timer at;


    int until;

    ~sender_t(){}
    sender_t(int fid, string dst, string qos):
      Flow_t(fid, dst, qos), seq (0), until(0) {
        seq = -1;
        simTime();
        at.type = action;
    }

    virtual PDU_Req act(Inj_t * parent, bool fin);

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

    virtual int getPDUSize() {  return uniform(omnetpp::getEnvir()->getRNG(0),  voice_f::min_pdu_len, voice_f::max_pdu_len); }
    virtual double getInterval() { return interval; }
    virtual double getNextOn() { return simTime().dbl() + idle_time; }
    virtual void setNextUntil() { until += (int)ceil(burst_time/interval); }
};

class voice_fb : public sender_t {
public :
    static int min_pdu_len, max_pdu_len;
    static double interval, min_idle_time, max_idle_time, min_burst_time, max_burst_time;

    voice_fb(int fid, string dst, string qos):
        sender_t(fid, dst, qos){}

    virtual int getPDUSize() {  return uniform(omnetpp::getEnvir()->getRNG(0),  voice_f::min_pdu_len, voice_f::max_pdu_len); }
    virtual double getInterval() { return interval; }
    virtual double getNextOn() {  return simTime().dbl() + uniform(omnetpp::getEnvir()->getRNG(0),  min_idle_time, max_idle_time); }
    virtual void setNextUntil() {  until += (int)ceil(uniform(omnetpp::getEnvir()->getRNG(0),  min_burst_time, max_burst_time)/interval); }
};

class voice_c : public sender_t {
public :
    int min_pdu_len, max_pdu_len;
    double interval, min_idle_time, max_idle_time, min_burst_time, max_burst_time;

    voice_c(int fid, string dst, string qos, int _min_pdu_len, int _max_pdu_len, double _interval,
            double _min_idle_time, double _max_idle_time, double _min_burst_time, double _max_burst_time):
        sender_t(fid, dst, qos), min_pdu_len(_min_pdu_len), max_pdu_len(_max_pdu_len), interval(_interval),
        min_idle_time(_min_idle_time), max_idle_time(_max_idle_time), min_burst_time(_min_burst_time), max_burst_time(_max_burst_time)
        {}

    virtual int getPDUSize() {  return uniform(omnetpp::getEnvir()->getRNG(0),  min_pdu_len, max_pdu_len); }
    virtual double getInterval() { return interval; }
    virtual double getNextOn() {  return simTime().dbl() + uniform(omnetpp::getEnvir()->getRNG(0),  min_idle_time, max_idle_time); }
    virtual void setNextUntil() {

        until += (int)ceil(uniform(omnetpp::getEnvir()->getRNG(0),  min_burst_time, max_burst_time)/interval);
    }
};
