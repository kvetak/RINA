#pragma once

#include <omnetpp.h>
#include <memory>
#include "DIF/EFCP/DTP/DataTransferPDU.h"

using namespace std;

typedef int32_t seq_t;

class CT_data {
public:
    int len;
    int stage;
    simtime_t t0;

    virtual ~CT_data(){}
    CT_data(int l, int s):
        len(l), stage(s), t0(simTime()){}
};

class CT_PDU : public DataTransferPDU {
public:
    shared_ptr<CT_data>xdata;

    CT_PDU() : DataTransferPDU("Connectivity Test") {}

    CT_PDU(const CT_PDU& other) : DataTransferPDU(other) {
        xdata = other.xdata;
        setByteLength(other.getByteLength());
    }
    virtual CT_PDU *dup() const {return new CT_PDU(*this);}

};

