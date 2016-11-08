#pragma once


#include <omnetpp.h>

//#include "cdataratechannel.h"

//NAMESPACE_BEGIN


class EthChannel : public cDatarateChannel {
  protected:
    virtual void initialize();
    int eheader;
    int eipg;
    double edelay;
    double edatarate;
    simtime_t etxfinishtime;

  public:
    EthChannel();
    virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
    virtual simtime_t getTransmissionFinishTime() const {return etxfinishtime;}
    virtual bool isBusy() const {return simTime() < etxfinishtime;}
};
