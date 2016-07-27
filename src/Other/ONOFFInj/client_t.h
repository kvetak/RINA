#pragma once

#include "Flow_t.h"

class client_t : public Flow_t {
public :
    static double ackT;

    seq_t seq;
    actTimer at;
    retransTimer rt;
    ackTimer kt;

    double retT;
    seq_t A, B;
    bool nacking;
    double nextRet;

    int until, nextRq; // data asked in current request vs when to perform next request
    double interval;
    bool thend;
    double lastNAck;


    ~client_t(){}
    client_t(int fid, string dst, string qos):
      Flow_t(fid, dst, qos) {
        seq = -1;

        until = 0;
        nextRq = 0;
        interval = 1.0/100.0;
        retT = 1.0;

        A = -1;
        B = -1;
        nacking = false;

        thend = false;
        lastNAck = -1;
        nextRet = 0;
    }

    virtual int getPDUSize() { return 20; }
    virtual simtime_t getNextOn(simtime_t ct) { return ct; }
    virtual void setNextUntil() { until += 2000; nextRq = until; }
    virtual void setNextRate() { interval = 1.0/100.0; }

    virtual pduReq act(ONOFInj * parent, bool fin);
    virtual pduReq ret(ONOFInj * parent, bool fin);
    virtual pduReq ack(ONOFInj * parent, bool fin);

    virtual void receive(ONOFInj * parent, shared_ptr<server_d> d, bool fin);

};

class video_f : public client_t {
public :
    static int request_size;
    static double idle_time;
    static int request_len;
    static double request_interval;

    simtime_t lastTime;

    video_f(int fid, string dst, string qos):
        client_t(fid, dst, qos){
        lastTime = -500.0;
    }

    virtual int getPDUSize() { return video_f::request_size; }
    virtual simtime_t getNextOn(simtime_t ct) {
        lastTime += video_f::idle_time;
        if(lastTime < ct) { lastTime = ct; }
        return lastTime;
    }
    virtual void setNextUntil() { until += video_f::request_len;  nextRq = until; }
    virtual void setNextRate() { interval = video_f::request_interval; }
};


class data_f : public client_t {
public :
    static int request_size;
    static int between_len;
    static double idle_time;
    static int request_len;
    static double request_interval;

    simtime_t lastTime;

    data_f(int fid, string dst, string qos):
        client_t(fid, dst, qos){
        lastTime = -500.0;
    }

    virtual int getPDUSize() { return video_f::request_size; }
    virtual simtime_t getNextOn(simtime_t ct) { return ct; }
    virtual void setNextUntil() { until = A + data_f::request_len;  nextRq = A + data_f::between_len; }
    virtual void setNextRate() { interval = data_f::request_interval; }
};
