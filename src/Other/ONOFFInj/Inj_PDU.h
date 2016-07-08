#pragma once

#include <omnetpp.h>
#include "DataTransferPDU.h"

using namespace std;

class Inj_PDU : public DataTransferPDU {

public:
    bool first;
    simtime_t sTime;
    int hops;

    Inj_PDU() : DataTransferPDU("Injected PDU"), first(false), sTime(simTime()), hops(0) { }
};
