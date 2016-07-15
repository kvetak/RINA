#pragma once

#include <omnetpp.h>
#include <memory>
#include "DataTransferPDU.h"

using namespace std;


class Inj_data {
public:
    int len;
    Inj_data(int l) : len(l){}
    virtual ~Inj_data(){}
};

class Inj_PDU : public DataTransferPDU {

public:
    bool first;
    simtime_t sTime;
    int hops;
    shared_ptr<Inj_data>xdata;

    Inj_PDU() : DataTransferPDU("Injected PDU"), first(false), sTime(simTime()), hops(0) {}

    Inj_PDU(const Inj_PDU& other) : DataTransferPDU(other) {
        xdata = other.xdata;
        setByteLength(other.getByteLength());
    }
    virtual Inj_PDU *dup() const {return new Inj_PDU(*this);}

};

