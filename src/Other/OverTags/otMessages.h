#pragma once

#include <omnetpp.h>
#include "Flow.h"

class helloMsg : public cMessage {
public:
    std::string id;
    cModule * mod;
    helloMsg():id(""), mod(nullptr){};
    helloMsg(std::string _id, cModule * _mod):id(_id), mod(_mod){};
};

class requestMsg : public cMessage {
public:
    cModule * mod;
    Flow * f;
    requestMsg():mod(nullptr), f(nullptr){};
    requestMsg(cModule * _mod, Flow * _f):mod(_mod), f(_f){};
};

class responseMsg : public cMessage {
public:
    cModule * modA, *modB;
    Flow * f;
    int gateIndex;

    responseMsg():modA(nullptr), modB(nullptr), f(nullptr), gateIndex(-1){};

    responseMsg(cModule * _modA, cModule * _modB, Flow * _f, int _gateIndex):
        modA(_modA), modB(_modB), f(_f), gateIndex(_gateIndex){};
};
