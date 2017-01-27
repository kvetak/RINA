#pragma once

#include "DIF/Routing/CentralRouting/RoutingModule.h"
#include "DIF/Routing/eRouting/eLink.h"
#include "DIF/RMT/PDUForwarding/GREFWD/GRE_Helpers.h"

#define R_INZONE_CHANGES 1
#define R_EXCEPTIONS_CHANGES 2
#define R_CONFIG_CHANGES 4


typedef unsigned long long seqId_t;

struct neiInfo {
    Address addr;
    bool samezone;
    bool status;
    elink_t link;
    neiInfo() : status(false){}
};
struct neiInfo_dumb {
    Address addr;
    Address master;
    addr_t zone;
    bool started;
    bool status;
    elink_t link;
    seqId_t last_ack;

    neiInfo_dumb() : started(false), status(false), last_ack(0) {}
};

struct podInfo {
    Address addr;
    seqId_t last_ack;

    podInfo() : last_ack(0) {}
};

struct e_t {
    addr_t a;
    unsigned char m;
    vector<index_t> valid;

    e_t(): a(0), m(0){}
};

// In-zone DV routing update
class RUpdate : public IntRoutingUpdate {
public:
    rt_Entry entries;
};


// Start message
class RStart : public IntRoutingUpdate {
public:
    addr_t zone;
};

struct status_t {
    addr_t node_addr;
    seqId_t seqId;
    set<elink_t> fails;

    status_t(): seqId(0){}
};


struct zone_stat_t {
    addr_t zone;
    set<addr_t> downFabs;
    map<addr_t, set<addr_t> > problemsAtFabs;
    map<addr_t, vector<unsigned char> > probToRtoFabDistance;
    seqId_t seqId;

    zone_stat_t(): seqId(0){}
};

// Status message
class RStatus : public IntRoutingUpdate {
public:
    status_t status;
    bool received; // Request or ack
};

// Zone Status message
class RZoneStatus : public IntRoutingUpdate {
public:
    zone_stat_t stat;
    bool received; // Request or ack
};


// Status message sincro
class ROutSincro : public IntRoutingUpdate {
public:
    addr_t sender;
    map<addr_t, zone_stat_t> outStats;

    seqId_t update_seq;
    seqId_t exception_in_seq;

    bool received; // Request or ack
};



// Status message sincro
class RSincro : public IntRoutingUpdate {
public:
    addr_t sender;
    map<addr_t, status_t> inzone_status;
    map<addr_t, status_t> outzone_status;

    seqId_t update_seq;
    seqId_t exception_in_seq;

    bool received; // Request or ack
};

// Exception Message
class RException : public IntRoutingUpdate {
public:
    seqId_t seqId;

    vector<bool> v1;                // Forward to inside Pod
    vector<bool> v2;                // Forward to outside Pod
    vector<e_t> ex;                 // Exceptions

    bool received; // Request or ack
};




