#pragma once

//Standard libraries
#include <omnetpp.h>

#include <string>
#include <map>

//RINASim libraries
#include "AE.h"
#include "RA.h"
#include "FA.h"
#include "DA.h"
#include "Directory.h"

using namespace std;

#include "ViFIB/Messages.h"

namespace ViFIB {

class Controller : public AE
{
protected:

    const char* TIM_CONNECT;
    const char* TIM_STARTFLOWS;
    const char* TIM_HELLO;

    const char* PAR_DSTAPNAME;
    const char* PAR_DSTAPINSTANCE;
    const char* PAR_DSTAENAME;
    const char* PAR_DSTAEINSTANCE;

    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    DA * DifAllocator;
    cModule * baseIPC;
    Directory * dir;

    string vifibId;
    string substrateAddr;

    string cloudAddr, cloudDIF, backboneAddr, backboneDIF;
    APNamingInfo cloudAPN, backboneAPN;
    bool imBorder;

    map<string, Flow *> flows;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


    void onConnect();

    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);


    class AddedFlowListener : public cListener {
    protected:
        Controller * parent;
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    public:
        AddedFlowListener(Controller *);
    };

    class RemovedFlowListener : public cListener {
    protected:
        Controller * parent;
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    public:
        RemovedFlowListener(Controller *);
    };

    virtual void action(cMessage *msg, bool del);


    void createVifiBIPC_Simple(string cloudAddr, string cloudDIF);
    void createVifiBIPC_Double(string cloudAddr, string cloudDIF, string backboneAddr, string backboneDIF);

    void connectTo(string dstAddr, string dstLocation, int border);
    void disconnectFrom(string dstAddr);

public:
    Controller();
    void addedFlow(Flow*);
    void removedFlow(Flow*);
};

}
