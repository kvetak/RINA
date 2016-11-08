#pragma once

#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include <set>
#include <map>
#include <fstream>

using namespace std;

struct stats {
    double min_lat, max_lat, sum_lat;
    long long countSent, countRecv;
    stats();
    void add();
    void add(simtime_t lat);
};


struct trace_t {
    unsigned char type;
    long long pduId;
    long long globalFlowId;
    int len;
    double time;
};


class VDT_Listener : public cSimpleModule, public cListener {
public:
    void initialize();
    virtual void finish();

    static VDT_Listener * instance;

    void voiceSent          (string src, string dst, string QoS, int flow , long long id, int len);
    void voiceRecv          (string src, string dst, string QoS, int flow, simtime_t lat, long long id, int len);

    void requestEnd         (string src, string dst, string QoS, int flow, simtime_t duration);

    void requestSent           (string src, string dst, string QoS, int flow, long long id, int len);
    void requestRecv           (string src, string dst, string QoS, int flow, simtime_t lat, long long id, int len);

    void dataSent           (string src, string dst, string QoS, int flow, long long id, int len);
    void dataRecv           (string src, string dst, string QoS, int flow, simtime_t lat, long long id, int len);

protected:
    //SRC-DST-QoS-FlowId -> Stats
    map<string, map<string, map<string, map<int, stats> > > >
        voice, fullRequest, request, data;

    void outStats(const map<string, map<string, map<string, map<int, stats> > > > & st, fstream & out);
    void coutStats(const map<string, map<string, map<string, map<int, stats> > > > & st);


    bool recordTrace;
    fstream tracer;
    fstream flowsInfo;

    //SRC-DST-QoS-FlowId -> globalFlowId
    map<string, map<string, map<string, map<int, long long> > > > globalFlowIds;
    long long nextGlobal;
    long long getGlobal(string src, string dst, string qos, int flowId);
};

