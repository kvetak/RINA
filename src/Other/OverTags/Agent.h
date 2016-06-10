#pragma once

//Standard libraries
#include <omnetpp.h>

#include "FAI.h"
#include <map>

using namespace std;

class Agent : public cSimpleModule, public cListener {
public:
    Agent();

    void initialize();

    void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    void handleMessage(cMessage *m);

    map<Flow * , FAI*> flowsFais;
};
