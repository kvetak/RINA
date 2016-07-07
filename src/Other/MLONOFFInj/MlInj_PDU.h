#pragma once

#include <omnetpp.h>
#include "DataTransferPDU.h"

using namespace std;

class MlInj_PDU : public DataTransferPDU {

public:
    bool first;
    simtime_t sTime;
    int hops;

    MlInj_PDU() : DataTransferPDU("Injected PDU"), first(false), sTime(simTime()), hops(0) { }
};
