#pragma once

#include <omnetpp.h>

#include "RINASignals.h"
#include "Flow.h"
#include "RA.h"
#include <set>

using namespace std;

class myListener : public cSimpleModule, cListener {
    public:
        void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    protected:
        void initialize();
        virtual void finish();
    private:
        std::map<std::string, unsigned int> nodes;
        void updateCount(std::string nodeInfo);
};
