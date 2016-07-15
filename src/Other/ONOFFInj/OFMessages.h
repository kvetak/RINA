#pragma once

#include <omnetpp.h>
#include "Inj_PDU.h"

using namespace std;

typedef int32_t seq_t;

class ofMsg : public Inj_data {
public:
    int flow;
    seq_t seq;
    simtime_t t0;

    ofMsg(int f, int l, seq_t s):
        Inj_data(l), flow(f), seq(s), t0(simTime()){}
};

class ofAck : public ofMsg {
public:
    seq_t A, B;
    bool isNack;

    ofAck(int f, int l, seq_t s, seq_t _A, seq_t _B, bool in) :
        ofMsg(f, l, s), A(_A), B(_B), isNack(in) {}
};

class ofReq : public ofAck {
public:
    seq_t A, B;

    int request; // Num packets to send
    double rate; // Rate in PDU/s
    ofReq(int f, int l, seq_t s, seq_t _A, seq_t _B, bool in,  int b, double r) :
        ofAck(f, l, s, _A, _B, in),  request(b), rate(r) {}
};

class ofData : public ofMsg {
public:
    seq_t A, B;
    bool isNack;

    ofData(int f, int l, seq_t s, seq_t _A, seq_t _B, bool in) :
        ofMsg(f, l, s), A(_A), B(_B), isNack(in) {}
};

