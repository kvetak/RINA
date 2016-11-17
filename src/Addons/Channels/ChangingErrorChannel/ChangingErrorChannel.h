#pragma once


#include <omnetpp.h>
//#include "cdataratechannel.h"

//NAMESPACE_BEGIN


class ChangingErrorChannel : public cDatarateChannel {
  protected:
    virtual void initialize();

    void handleMessage(cMessage * msg);

  public:
    ChangingErrorChannel();
};
