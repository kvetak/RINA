#pragma once

#include <omnetpp.h>
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Flow_Data.h"

using namespace std;

class sender_d : public Flow_Data {
public:
    sender_d(int f, int l, seq_t s):
        Flow_Data(f, l, s){}
};

class client_d : public Flow_Data {
public:
    seq_t A, B;
    bool isNack;
    int reqSize;
    double reqInterval;
    int pdu_size;

    client_d(int f, int l, seq_t s, seq_t _A, seq_t _B, bool in, int rS, double rI, int pS) :
        Flow_Data(f, l, s), A(_A), B(_B), isNack(in), reqSize(rS), reqInterval(rI), pdu_size(pS) {}
};

class server_d : public Flow_Data {
public:
    seq_t A;
    bool isNack;

    server_d(int f, int l, seq_t s, seq_t _A, bool in) :
        Flow_Data(f, l, s), A(_A), isNack(in) {}
};
