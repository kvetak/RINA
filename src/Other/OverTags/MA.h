#pragma once

//Standard libraries
#include <omnetpp.h>
#include "otMessages.h"

#include <map>

using namespace std;


class MA : public cSimpleModule {
public:
    MA();

    void initialize();

    void handleMessage(cMessage *m);

protected:
    map<string, cModule*> agents;
    map<string, cGate*> agentGates;
};
