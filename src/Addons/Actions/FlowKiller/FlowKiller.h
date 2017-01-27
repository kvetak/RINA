#pragma once

#include <omnetpp.h>

#include "Common/RINASignals.h"
#include "Common/Flow.h"
#include "DIF/RA/RA.h"
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

class FlowKiller : public cSimpleModule, cListener {
    public:
        void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    protected:
        void initialize();
        void handleMessage(cMessage *msg);

        vector<FlowContainer> flows;
        double killTime;
        int killCount;
};
