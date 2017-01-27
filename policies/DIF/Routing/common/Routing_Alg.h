#pragma once

#include <string>
#include <set>

#include <omnetpp.h>

#include "DIF/Routing/common/Routing_Module.h"
#include "DIF/Routing/common/nhLMetric.h"

namespace common_Routing {

using namespace std;
using namespace common_GraphCL;

template<class T>
class Routing_Alg : public Routing_Alg_I{

protected:
    Routing_Module * parent;
    Address myNAddr;
    string descriptor;
    string myAddr;
    set<string> synonyms;
    T infinite;
    simtime_t updateW;
    bool scheduledUpdate;

    map<string, T> nei;
    map<string, Address> neigTable;
    map<Address, string> invNeigTable;

public:
    Routing_Alg(){};
    virtual ~Routing_Alg(){};

    Routing_Alg(Routing_Module * p, const Address &_nAddr, const string &_addr, T inf) :
        parent(p), myNAddr(_nAddr), myAddr(_addr), infinite(inf), updateW(0.01), scheduledUpdate(false){};

    virtual void addSynonym(const string syn) { synonyms.insert(syn); }
    virtual void removeSynonym(const string syn) { synonyms.erase(syn); }

    virtual void addFlow(const Address &_nAddr, const string &_addr, const T &_metric){
        nei[_addr] = _metric;
        neigTable[_addr] = _nAddr;
        invNeigTable[_nAddr] = _addr;
    }

    virtual void removeFlow(const Address &_nAddr, const string &_addr){
        nei.erase(_addr);
        neigTable.erase(_addr);
        invNeigTable.erase(_nAddr);
    }

    virtual bool processUpdate(Routing_Update * update) = 0;
    virtual map<string, nhLMetric<T>  > getChanges() = 0;
    virtual map<string, nhLMetric<T>  > getAll() = 0;

    void setInfMetric(const T & inf) { infinite = inf; }

    void setUpdateDelay(const simtime_t & t) { updateW = t; }
    void scheduleUpdate(){
        if(!scheduledUpdate){
            scheduledUpdate = true;
            parent->chScheduleAt(this, updateW);
        }
    }
    virtual void sendUpdate() { scheduledUpdate = false; }

    virtual void print() = 0;

    void setDescriptor(const string & des) { descriptor = des; }
};

} /* namespace common_Routing */
