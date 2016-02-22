#pragma once

#include <omnetpp.h>

#include "RINASignals.h"
#include "Flow.h"
#include "RA.h"
#include <set>

using namespace std;

class myContainer : public cMessage {
    public:
        Flow * f;
        RA * ra;
        myContainer(Flow * _f, RA * _ra);

        bool operator<(const myContainer &o) const;
        bool operator==(const myContainer & o) const;
};

class myListener : public cSimpleModule, cListener {
    public:
        void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    protected:
        void initialize();
        void handleMessage(cMessage *msg);

        vector<myContainer> flows;
        double killTime;
        int killCount;
};
