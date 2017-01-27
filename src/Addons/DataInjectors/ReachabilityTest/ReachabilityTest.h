#pragma once

#include <omnetpp.h>
#include <queue>
#include <memory>

#include "Common/ConnectionId.h"
#include "Common/Address.h"
#include "DIF/RMT/RMTPort.h"

#include "Addons/DataInjectors/ReachabilityTest/ReachabilityTest_PDU.h"


using namespace std;

class ReachabilityTest : public cSimpleModule {
public :
    //Receive data from other node
    void receiveData(const string & _src, const string & _qos, const int & srcCep, shared_ptr<CT_data> data);

    //Generate PDU
    CT_PDU * genPDU(const string & dst, const string & _QoS, const int & stage, const int & srcCep);

    //PDU header
    string QoS;
    int header;

    //Infection end time
    double interval;
    cMessage nextSend;

    //Node info
    string src, dif;
    ConnectionId connID;
    Address srcAddr, dstAddr;

    vector<string> remaining;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void finish();

    void startFlows();
};
