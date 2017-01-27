#pragma once

#include <omnetpp.h>
#include <map>
#include <queue>
#include <memory>

#include "DIF/RMT/RMTPort.h"

#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Flow_Data.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/PDU_Req.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Flow_PDU.h"

class Flow_t;

using namespace std;

class Inj_t : public cSimpleModule {
public :

    //Initialize connections to other modules
    void initialize();

    //Generate PDU
    Flow_PDU * genPDU(const PDU_Req & req);

    //N-1 ports status
    inline void setPort(const string & dst, const string & qos, RMTPort * p) {
        ports[dst][qos] = p;
    }
    inline bool portReady(string dst, string qos) {
        RMTPort * p = ports[dst][qos];
        return (p != nullptr && p->isOutputReady() && p->isInputReady());
    }
    map<string, map<string, RMTPort * > > ports;

    long long pduId;

/** Basic data **/

    //Infected IPCP information
    string src, dif;
    ConnectionId connID;
    Address srcAddr;
    Address dstAddr; // Changed with each call to genPDU

    //PDU extra headers (lower DIFs)
    int headers;

    //Start and End "simulation" times
    double iniT, finT;
    // iniT < 0 -> iniT = 0
    // finT < iniT -> Abort process

/** Extended functionality **/



    //Request finalized
    virtual void requestComplete(Flow_t * app, simtime_t requestedAt) = 0;

    //Receive data from other node
    virtual void receiveData(const string & _src, const string & _qos, shared_ptr<Flow_Data> data) = 0;

    //Receive self messages
    virtual void handleMessage(cMessage *msg) = 0;

    //Prepare flows and more
    virtual void postInitialize() = 0;

    //At the end
    virtual void finish() {};
};

