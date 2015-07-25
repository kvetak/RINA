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

class ManagementAgent : public AE, public cListener
{
protected:
    simsignal_t sig2master;

    std::string clientId;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);
    void processMRead(CDAPMessage* msg);
    void processMReadR(CDAPMessage* msg);

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    virtual void action(cMessage *msg, bool del);
public:
    ManagementAgent();
};

}
