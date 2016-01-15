#pragma once

#include <omnetpp.h>

#include "RINASignals.h"
#include "Flow.h"
#include "RA.h"
#include <set>

using namespace std;

class FlowContainer : public cMessage {
    public:
        Flow * f;
        RA * ra;
        FlowContainer(Flow * _f, RA * _ra);

        bool operator<(const FlowContainer &o) const;
        bool operator==(const FlowContainer & o) const;
};

class FlowListener : public cSimpleModule, cListener {
    public:
        void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    protected:
        void initialize();
        void handleMessage(cMessage *msg);

        vector<FlowContainer> flows;
        double killTime;
        int killCount;
};
