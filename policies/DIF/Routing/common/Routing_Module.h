#pragma once

#include <omnetpp.h>

#include "Common/Address.h"

namespace common_Routing {

class Routing_Update {
public:
    virtual ~Routing_Update(){}
};
class Routing_Alg_I {
public:
    virtual bool processUpdate(Routing_Update * update) = 0;
};

class Routing_Module {
public:
    virtual void chSendUpdate(Routing_Update * update, const Address & dst, Routing_Alg_I *) = 0;
    virtual void chScheduleAt(Routing_Alg_I * update, const simtime_t & t) = 0;
};

} /* namespace common_Routing */
