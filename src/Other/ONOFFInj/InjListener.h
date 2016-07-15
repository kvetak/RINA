#pragma once

#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include <set>
#include <map>

using namespace std;

struct voiceFlowStat {
    double min_lat, max_lat, sum_lat;
    long long count;
    voiceFlowStat();
    void add(simtime_t lat);
};

class InjListener : public cSimpleModule, public cListener {
public:
    void initialize();
    virtual void finish();

    static InjListener * instance;

    void voiceReceived(string src, string dst, int flow, simtime_t lat);
    void dataRequestStarted(string src, string dst, int flow);
    void dataRequestEnded(string src, string dst, int flow);

protected:
    map<string, map<string, map<int, voiceFlowStat> > > voiceStats;
    map<string, map<string, map<int, long long> > > dataStart, dataEnd;

};

