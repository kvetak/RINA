#pragma once

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"
#include "RA.h"
#include "DA.h"

#include "AdmT.h"

class AdmCM : public AdmT,  public cListener
{
protected:
    simsignal_t sig;
    virtual void initialize();

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    virtual void action(cMessage *msg, bool del);

    string src, dif;
};
