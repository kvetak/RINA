#pragma once

//Standard libraries
#include <omnetpp.h>
#include <string>

//RINASim libraries
#include "AE.h"
#include "RA.h"
#include "DA.h"

using namespace std;

class AdmFlyIPC : public AE
{
    protected:
        string dif, addr, dst;

        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};
