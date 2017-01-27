#include "DIF/Routing/CentralRouting/RoutingModule.h"

RoutingModule::RoutingModule() {}

void RoutingModule::setId(const addr_t & i) {
    id = i;
}

void RoutingModule::addAddress(const addr_t & a) {
    shareAddrs.insert(a);
    auto & ns = neiState[a];
    auto res = ns.addEntry(id, 0);

    if(res & CH1OPT) { neiDistance[a] = 0; }
}
void RoutingModule::removeAddress(const addr_t & a) {
    shareAddrs.erase(a);
    auto & ns = neiState[a];
    ns.removeEntry(id);
    if(ns.op1.empty() || ns.m1 > 16) {
        neiDistance[a] = 16;
    } else {
        neiDistance[a] = ns.m1;
    }
}

void RoutingModule::removeFrom(const addr_t &i) {
    for(auto & e : neiState) {
        auto & ns = e.second;
        ns.removeEntry(i);
        if(ns.op1.empty() || ns.m1 > 16) {
            neiDistance[e.first] = 16;
        } else {
            neiDistance[e.first] = ns.m1;
        }
    }
}

bool RoutingModule::receiveChanges(const addr_t &i, const map<addr_t, char>  & entries) {
    bool ret = false;
    for(auto e : entries) {
        auto & ns = neiState[e.first];
        auto res = ns.addEntry(i, e.second+1);
        if(res & CH1OPT) {
            if(ns.op1.empty() || ns.m1 > 16) {
                neiDistance[e.first] = 16;
            } else {
                neiDistance[e.first] = ns.m1;
            }
            ret = true;
        }
    }
    return ret;
}

rt_Entry RoutingModule::getRTUpdate() {
    rt_Entry u(id);
    u.entries = neiDistance;
    return u;
}
