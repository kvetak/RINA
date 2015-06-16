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

class AdmCore : public AE, public cListener {
protected:
    simsignal_t sig;

    virtual void initialize();

    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);

    // dif, src, list dst
    map<string, map<string, vector<string> > > data;
};

