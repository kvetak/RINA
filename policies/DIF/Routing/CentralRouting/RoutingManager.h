#pragma once


#include "DIF/Routing/IntRouting.h"
#include "DIF/Routing/CentralRouting/CentralRoutingCommon.h"



using namespace std;

struct master_t {
    Address addr;
    bool status;

    seqId_t last_sent;
    seqId_t last_acked;

    master_t(): status(false), last_sent(0), last_acked(0) {}
};



struct ToR_info_t {
    addr_t a;                       // Node address
    unsigned int problems;          // Dead connections
    bool disconnected;              // Is disconnected?
    vector<bool> v1;                // Forward to inside Pod
    vector<bool> v2;                // Forward to outside Pod

    vector<e_t> ex;                 // Exceptions

    seqId_t lastReceived;

    ToR_info_t() : problems(0), disconnected(false), lastReceived(0) {}
};

struct Fab_info_t {
    addr_t a;
    bool disconnectedUp;            // Is disconnected Up?
    bool disconnectedDown;          // Is disconnected Down?
    vector<bool> v1;                // Forward to inside Pod
    vector<bool> v2;                // Forward to outside Pod
    unsigned int connectedDown;     // Live connections to ToRs
    unsigned int problemsUp;        // Dead connections to ToRs

    vector<e_t> ex;                 // Exceptions

    seqId_t lastReceived;

    Fab_info_t() : disconnectedUp(false), disconnectedDown(false), problemsUp(0), lastReceived(0) {}
};

class RoutingManager: public IntRouting {
public:
    RoutingModule inzone;

    void setMyA(const addr_t & a);

    void addAddr(const addr_t & a);

    void addMasterNei(const addr_t & a, const Address & m);
    void removeMasterNei(const addr_t & a);

    void addNei(const addr_t &a, const Address &addr, const bool &samezone, const elink_t &link);

    void onFlow(addr_t a);
    void offFlow(addr_t a);

    void sendUpdates();
    void handleMessage(cMessage * msg);
    bool processUpdate(IntRoutingUpdate * update);


    unsigned char r_stat;

protected:
    // Called after initialize
    virtual void onPolicyInit();
    virtual void finish();

    void sendInzoneSincro();
    void sendOutzoneSincro();
    void sendtoOut();

    void computeExceptions();
    void computeZone();
    void sendExceptions();

    map<elink_t, neiInfo> neis;

    map<addr_t, status_t> inzone_status;
    map<addr_t, status_t> outzone_status;
    map<addr_t, zone_stat_t> outStats;
    zone_stat_t myZoneStat;
    unsigned char ** DM;

    vector<ToR_info_t> tors;
    vector<Fab_info_t> fabs;

    map<addr_t, master_t> masters;

    seqId_t statusSeq;

    cMessage * in_timer;
    simtime_t in_updateInterval;

    cMessage * start_timer;

    addr_t myA;
    addr_t myZone;

    seqId_t incrementInKnown;

    index_t f, p, s, t;
    map<addr_t, podInfo> externalPods;

    cMessage * in_sincro_timer;
    simtime_t in_sincro_updateInterval;

    cMessage * out_sincro_timer;
    simtime_t out_sincro_updateInterval;

    cMessage * toout_sincro_timer;
    simtime_t toout_sincro_updateInterval;

    cMessage * exceptions_timer;
    simtime_t exceptions_timer_updateInterval;

    seqId_t exception_seq;
    seqId_t last_exception_seq;


    seqId_t current_sent;
    seqId_t exception_in_seq;
};
