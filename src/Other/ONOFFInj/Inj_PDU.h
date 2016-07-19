#pragma once

#include <omnetpp.h>
#include <memory>
#include "DataTransferPDU.h"

using namespace std;

typedef int32_t seq_t;

class Inj_data {
public:
    int len;
    int flow;
    seq_t seq;
    simtime_t t0;

    virtual ~Inj_data(){}
    Inj_data(int l, int f, seq_t s):
        len(l), flow(f), seq(s), t0(simTime()){}
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

