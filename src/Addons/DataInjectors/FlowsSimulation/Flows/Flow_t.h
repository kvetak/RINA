#pragma once

#include <omnetpp.h>
#include <string>
#include "Addons/DataInjectors/FlowsSimulation/Inj_t.h"


using namespace std;


class Flow_t {
public :
    int flowId;
    string dstAddr;
    string QoS;

    Flow_t(int fid, string da, string q) :
        flowId(fid), dstAddr(da), QoS(q) {}
    virtual ~Flow_t(){}

    virtual PDU_Req act(Inj_t * parent, bool fin);
    virtual PDU_Req ret(Inj_t * parent, bool fin);
    virtual PDU_Req sret(Inj_t * parent, bool fin);
    virtual PDU_Req ack(Inj_t * parent, bool fin);
};

enum timerType {nil, action, retrans, selRetrans, ackTime};

class Flow_timer : public cMessage {
public:
    Flow_t * f;
    timerType type;

    Flow_timer() : f ( nullptr ), type(nil) {}
    virtual ~ Flow_timer() {}
};
