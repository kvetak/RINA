#pragma once

#include <omnetpp.h>
#include "Inj_PDU.h"

using namespace std;

class sender_d : public Inj_data {
public:
    sender_d(int f, int l, seq_t s):
        Inj_data(l, f, s){}
};

class client_d : public Inj_data {
public:
    seq_t A, B;
    bool isNack;
    int reqSize;
    double reqInterval;

    client_d(int f, int l, seq_t s, seq_t _A, seq_t _B, bool in, int rS, double rI) :
        Inj_data(l, f, s), A(_A), B(_B), isNack(in), reqSize(rS), reqInterval(rI) {}
};

class server_d : public Inj_data {
public:
    seq_t A;
    bool isNack;

    server_d(int f, int l, seq_t s, seq_t _A, bool in) :
        Inj_data(l, f, s), A(_A), isNack(in) {}
};

/*
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

*/
