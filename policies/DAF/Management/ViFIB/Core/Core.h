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

class Core : public AE, public cListener
{
protected:
    simsignal_t sig2slaves;

    DA * DifAllocator;
    cModule * baseIPC;

    map<string, vector<miniInfo> > bordersInfo;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);
    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    virtual void action(cMessage *msg, bool del);


    void createVifiBIPC_Simple(string cloudAddr, string cloudDIF);
    void createVifiBIPC_Double(string cloudAddr, string cloudDIF, string backboneAddr, string backboneDIF);

    void connectTo(string dstAddr, string dstLocation, int border);
    void disconnectFrom(string dstAddr);

public:
    Core();
    void addedFlow(Flow*);
    void removedFlow(Flow*);
};

}
