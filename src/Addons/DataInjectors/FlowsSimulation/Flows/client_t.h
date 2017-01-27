#pragma once

#include "./Flow_t.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Data_t.h"

class client_t : public Flow_t {
public :
    double ackT;

    seq_t seq;
    Flow_timer at;
    Flow_timer rt;
    Flow_timer kt;

    double retT;
    seq_t A, B;
    bool nacking;
    double nextRet;

    int until, nextRq; // data asked in current request vs when to perform next request
    double interval;
    bool thend;
    double lastNAck;

    int request_size;
    int data_size;


    ~client_t(){}
    client_t(int fid, string dst, string qos, int _data_size=1000, int _request_size = 20, double _ackT = 0.1):
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
        request_size = _request_size;
        data_size = _data_size;

        ackT = _ackT;

        at.type = action;
        rt.type = retrans;
        kt.type = ackTime;
    }

    virtual void end(Inj_t * parent){};
    virtual void completeRequest(Inj_t * parent){};

    virtual int getPDUSize() { return request_size; }
    virtual simtime_t getNextOn(simtime_t ct) { return ct; }
    virtual void setNextUntil() { until += 2000; nextRq = until; }
    virtual void setNextRate() { interval = 1.0/100.0; }

    virtual PDU_Req act(Inj_t * parent, bool fin);
    virtual PDU_Req ret(Inj_t * parent, bool fin);
    virtual PDU_Req ack(Inj_t * parent, bool fin);

    virtual void receive(Inj_t * parent, shared_ptr<server_d> d, bool fin);

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


class video_c : public client_t {
public :
    int data_len;
    double data_interval;
    double idle_time;

    simtime_t lastTime;

    video_c(int fid, string dst, string qos,
            int _request_size, int _data_size, int _data_len, double _data_interval, double _idle_time ):
        client_t(fid, dst, qos, _data_size, _request_size),
        data_len(_data_len), data_interval(_data_interval), idle_time(_idle_time), lastTime(-500.0) {
     //   setNextUntil();
     //   setNextRate();
    }

    virtual simtime_t getNextOn(simtime_t ct) {
        lastTime += idle_time;
        if(lastTime < ct) { lastTime = ct; }
        return lastTime;
    }
    virtual void setNextUntil() { until += data_len;  nextRq = until; }
    virtual void setNextRate() { interval = data_interval; }

    virtual void end(Inj_t * parent){ };
    virtual void completeRequest(Inj_t * parent){
        parent->requestComplete(this, lastTime);
    };
};

class data_f : public client_t {
public :
    static int request_size;
    static int between_len;
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


class data_c : public client_t {
public :
    double request_interval;
    int request_len;
    int between_len;

    simtime_t lastTime;

    data_c(int fid, string dst, string qos,
            int _request_size, int _data_size, double _request_interval,
            int _request_len, int _between_len):
                client_t(fid, dst, qos, _data_size, _request_size),
                request_interval(_request_interval), request_len(_request_len),
                between_len(_between_len), lastTime(-500.0) {}

    virtual simtime_t getNextOn(simtime_t ct) { return ct; }
    virtual void setNextUntil() { until = A + request_len;  nextRq = A + between_len;}
    virtual void setNextRate() { interval = request_interval; }
};
