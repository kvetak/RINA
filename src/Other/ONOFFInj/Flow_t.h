#pragma once

#include "OFClasses.h"
#include <omnetpp.h>
#include <string>
#include "OFMessages.h"

using namespace std;

class Flow_t {
public :
    int flowId;
    string dstAddr;
    string QoS;

    Flow_t(int fid, string da, string q) :
        flowId(fid), dstAddr(da), QoS(q) {}
    virtual ~Flow_t(){}

    virtual pduReq act(ONOFInj * parent, bool fin);
    virtual pduReq ret(ONOFInj * parent, bool fin);
    virtual pduReq sret(ONOFInj * parent, bool fin);
    virtual pduReq ack(ONOFInj * parent, bool fin);
};


class Flow_timer : public cMessage {
public:
    Flow_t * f;

    Flow_timer() : f ( nullptr ) {}
    virtual ~ Flow_timer() {}
};
class actTimer : public Flow_timer {};
class retransTimer : public Flow_timer {};
class selretransTimer : public Flow_timer {};
class ackTimer : public Flow_timer {};
