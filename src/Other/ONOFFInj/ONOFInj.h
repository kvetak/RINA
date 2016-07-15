#pragma once

#include <omnetpp.h>
#include <queue>
#include <ConnectionId.h>
#include <Address.h>
#include "OFMessages.h"
#include "RMTPort.h"

using namespace std;

class ONOFInj;


class Flow_t {
public :
    int flowId;
    string dstAddr;
    string QoS;

    Flow_t(int fid, string da, string q) :
        flowId(fid), dstAddr(da), QoS(q) {}
    virtual ~Flow_t(){}
};

class Flow_timer : public cMessage {
public:
    Flow_t * f;
    Flow_timer() : f ( nullptr ) {}
};
class actTimer : public Flow_timer {};
class retransTimer : public Flow_timer {};
class selretransTimer : public Flow_timer {};
class ackTimer : public Flow_timer {};


class voiceOF : public Flow_t {
public :
    static int min_pdu_len, max_pdu_len;
    static double interval, idle_time, burst_time;

    seq_t seq;
    actTimer * At;
    bool state;
    int remaining;

    ~voiceOF(){}
    voiceOF(int fid, string dst, string qos):
      Flow_t(fid, dst, qos), seq (0), state(false), remaining(0) {
        seq = -1;
        At = new actTimer();
    }

    virtual ofMsg * getData(ONOFInj *);
};



class dtcpOF : public Flow_t {
public :
    static double ackT;

    seq_t sent, acked, sN;
    seq_t A, B;
    seq_t p0, p1, p2;
    double retT;
    seq_t lastNack;
    double last_sent;
    bool nacking;

    actTimer * At;
    retransTimer * rt;
    selretransTimer * srt;
    ackTimer * at;

    ~dtcpOF(){}
    dtcpOF(int fid, string dst, string qos):
      Flow_t(fid, dst, qos) {
        At = new actTimer();
        rt = new retransTimer();
        srt = new selretransTimer();
        at = new ackTimer();
        sent = -1;
        acked = -1;
        sN = 0;
        A = -1;
        B = 0;
        lastNack = -1;
        retT = ackT + 0.1;
        last_sent = 0.0;
        nacking = false;
    }
};

class clientOF : public dtcpOF {
public :
    static int pdu_len;

    int minData, maxData; // in PDU
    double minRate, maxRate; // in PDU/s
    double idle_time;
    double next_time;
    seq_t until;
    double reqRate;

    ~clientOF(){}
    clientOF(int fid, string dst, string qos,
            int md, int Md, double mr, double Mr, double it):
      dtcpOF(fid, dst, qos),
      minData(md), maxData(Md), minRate(mr), maxRate(Mr), idle_time(it), until(0), reqRate(0.0){}

    virtual ofMsg * getRq(ONOFInj *);
    virtual ofMsg * getAck(ONOFInj *);
};

class serverOF : public dtcpOF {
public :
    static int pdu_len;

    double interval;
    seq_t until;
    bool nextSNack;

    serverOF(int fid, string dst, string qos):
      dtcpOF(fid, dst, qos) {
        nextSNack = false;
        until = -1;
        interval = 0.0;
    }

    virtual ofMsg * getData(ONOFInj *);
    virtual ofMsg * getAck(ONOFInj *);
};

class ONOFInj : public cSimpleModule {
public :
    void receiveData(const string & _src, const string & _qos, shared_ptr<Inj_data> data);
    Inj_PDU * getPDU(const Flow_t * f, Inj_data * data);

    void setPort(const string & dst, const string & qos, RMTPort * p) {
        ports[dst][qos] = p;
    }

    long long received, sent;
    long long reqCount, ackCount, dataCount, dataDCount, dataACount;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void finish();


    int header;
    double fin;

    ;
    string src, dif;
    ConnectionId connID;
    Address srcAddr, dstAddr;


    int nextFlowId;
    map<int, voiceOF *> vFlows;
    map<string, map<int, clientOF *> > cFlows;
    map<string, map<int, serverOF *> > sFlows;


    map<string, map<string, RMTPort * > > ports;


    void actVoice(actTimer * m, voiceOF * f);
    void actClient(actTimer * m, clientOF * f);
    void actServer(actTimer * m, serverOF * f);

    void retClient(retransTimer * m, clientOF * f);
    void retServer(retransTimer * m, serverOF * f);

    void selRetServer(selretransTimer * m, serverOF * f);

    void rackClient(ackTimer * m, clientOF * f);
    void rackServer(ackTimer * m, serverOF * f);
};
