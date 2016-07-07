#pragma once

#include <omnetpp.h>
#include <queue>
#include <ConnectionId.h>
#include <Address.h>

using namespace std;

class NetTestInj : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    simsignal_t signal;

    double wait;
    vector<string> destinations, tDest;
    string src, dif;
    ConnectionId connID;
    Address srcAddr, dstAddr;
};
