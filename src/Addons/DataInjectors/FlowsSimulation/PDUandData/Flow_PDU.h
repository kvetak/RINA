#pragma once

#include <omnetpp.h>
#include <memory>
#include "DIF/EFCP/DTP/DataTransferPDU.h"
#include "Addons/DataInjectors/FlowsSimulation/PDUandData/Flow_Data.h"

using namespace std;

typedef int32_t seq_t;


class Flow_PDU : public DataTransferPDU {

public:
    bool first;
    simtime_t sTime;
    int hops;
    shared_ptr<Flow_Data>xdata;

    Flow_PDU() : DataTransferPDU("Injected PDU"), first(false), sTime(simTime()), hops(0) {}
    Flow_PDU(string name) :
        DataTransferPDU(name.c_str()),
        first(false), sTime(simTime()), hops(0) {}

    Flow_PDU(const Flow_PDU& other) : DataTransferPDU(other) {
        xdata = other.xdata;
        setByteLength(other.getByteLength());
    }

    virtual Flow_PDU *dup() const {return new Flow_PDU(*this);}

};

