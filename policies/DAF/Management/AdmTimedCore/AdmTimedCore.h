#pragma once

//Standard libraries
#include <omnetpp.h>
#include <string>
#include <map>

//RINASim libraries
#include "AE.h"
#include "RA.h"
#include "DA.h"

#include "AdminMsgs.h"

using namespace std;

class AdmTimedCore : public AE, public cListener {
protected:
    simsignal_t sig;
    const char * TIME2;

    virtual void initialize();

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    virtual void handleMessage(cMessage * msg);

    //time, dif, src, list dst

    map<int, map<string, map<string, vector<string> > > > addL;
    map<int, map<string, map<string, vector<string> > > > rmL;
public:
    AdmTimedCore();
};

