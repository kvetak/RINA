#pragma once

#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include <set>
#include <map>

using namespace std;

struct stats {
    double min_lat, max_lat, sum_lat;
    long long countSent, countRecv;
    stats();
    void add();
    void add(simtime_t lat);
};


class VDT_Listener : public cSimpleModule, public cListener {
public:
    void initialize();
    virtual void finish();

    static VDT_Listener * instance;

    void voiceSent          (string src, string dst, string QoS, int flow);
    void voiceRecv          (string src, string dst, string QoS, int flow, simtime_t lat);

    void requestEnd         (string src, string dst, string QoS, int flow, simtime_t duration);

    void requestSent           (string src, string dst, string QoS, int flow);
    void requestRecv           (string src, string dst, string QoS, int flow, simtime_t lat);

    void dataSent           (string src, string dst, string QoS, int flow);
    void dataRecv           (string src, string dst, string QoS, int flow, simtime_t lat);

protected:
    //SRC-DST-QoS-FlowId -> Stats
    map<string, map<string, map<string, map<int, stats> > > >
        voice, fullRequest, request, data;

    void coutStats(const map<string, map<string, map<string, map<int, stats> > > > & st);
};

