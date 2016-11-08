#pragma once

#include <omnetpp.h>
using namespace std;

typedef int32_t seq_t;

class Flow_Data {
public:
    int flow;       // Flow Id
    int len;        // SDU size in Bytes (N-1 headers not considered)
    seq_t seq;      // Sequence number
    simtime_t t0;   // Creation time
    long long pduId;// PDU Id

    virtual ~Flow_Data(){}
    Flow_Data(int f, int l, seq_t s):
        flow(f), len(l), seq(s), t0(simTime()), pduId(0) {}
};
