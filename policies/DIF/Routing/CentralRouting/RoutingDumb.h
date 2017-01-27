#pragma once


#include "DIF/Routing/IntRouting.h"
#include "DIF/Routing/CentralRouting/CentralRoutingCommon.h"



using namespace std;

class RoutingDumb: public IntRouting {
public:
    void setMyA(const addr_t & a);

    void addNei(const addr_t &a, const Address &addr, const Address &manager, const elink_t &link);

    void onFlow(addr_t a);
    void offFlow(addr_t a);

    void handleMessage(cMessage * msg);
    bool processUpdate(IntRoutingUpdate * update);

    unsigned char r_stat;

protected:
    // Called after initialize
    virtual void onPolicyInit();
    virtual void finish();

    map<addr_t, neiInfo_dumb> neis;

    cMessage * status_timer;
    simtime_t status_updateInterval;

    cMessage * re_status_timer;
    simtime_t re_status_updateInterval;

    addr_t myA;


    status_t st;


    void informStatus();
    void sendInformStatus();
    void resendInformStatus();
};
