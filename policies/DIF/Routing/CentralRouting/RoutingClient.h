#pragma once


#include "DIF/Routing/IntRouting.h"
#include "DIF/Routing/CentralRouting/CentralRoutingCommon.h"



using namespace std;

class RoutingClient: public IntRouting {
public:
    RoutingModule inzone;

    void setMyA(const addr_t & a);

    void setMasterAddr(const Address & m);

    void addNei(const addr_t &a, const Address &addr, const bool &samezone, const elink_t &link);

    void onFlow(addr_t a);
    void offFlow(addr_t a);

    void sendUpdates();
    void handleMessage(cMessage * msg);
    bool processUpdate(IntRoutingUpdate * update);

    void informStatus();
    void sendInformStatus();

    unsigned char r_stat;
    //Last exception
    vector<bool> v1;                // Forward to inside Pod
    vector<bool> v2;                // Forward to outside Pod
    vector<e_t> ex;                 // Exceptions


protected:
    // Called after initialize
    virtual void onPolicyInit();
    virtual void finish();

    map<addr_t, neiInfo> neis;

    bool started;
    Address master;

    seqId_t statusSeq;

    cMessage * in_timer;
    simtime_t in_updateInterval;

    cMessage * status_timer;
    simtime_t status_updateInterval;

    cMessage * re_status_timer;
    simtime_t re_status_updateInterval;

    addr_t myA;

    status_t st;
};
