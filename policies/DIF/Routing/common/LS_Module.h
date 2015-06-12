#pragma once

#include "common/Routing_Alg.h"
#include "common/GraphCL.h"

namespace common_LSModule {

using namespace std;
using namespace common_Routing;
using namespace common_GraphCL;

template<class T>
class LS_Module : public Routing_Alg<T> {
    //Vars and classes
public:
protected:
    int secId;

    struct linksU{
        int sId;
        map<string, T> links;
        linksU() : sId(-1){}
        linksU(const int &_sId) : sId(_sId){}
    };

    class LS_Update : public Routing_Update {
    public:
        LS_Update(){}
        map<string, linksU> entries;
        void addEntry(const string & _addr, linksU _neig) { entries[_addr] = _neig; }
    };

    map<string, linksU> netState;
    set<string> changed;

    map<string, nhLMetric<T>  > currentTable;

    //Functions
public:
    LS_Module() : secId(-1){}
    LS_Module(Routing_Module * p, const Address &_nAddr, const string &_addr, T inf) :
        Routing_Alg<T>(p, _nAddr, _addr, inf), secId(1){}

    virtual void addSynonym(const string syn) {
        Routing_Alg<T>::addSynonym(syn);

        secId++;
        changed.insert(Routing_Alg<T>::myAddr);
        netState[Routing_Alg<T>::myAddr].sId = secId;
        netState[Routing_Alg<T>::myAddr].links[syn] = T();

        Routing_Alg<T>::scheduleUpdate();
    }
    virtual void removeSynonym(const string syn) {
        Routing_Alg<T>::removeSynonym(syn);

        secId++;
        changed.insert(Routing_Alg<T>::myAddr);
        netState[Routing_Alg<T>::myAddr].sId = secId;
        netState[Routing_Alg<T>::myAddr].links.erase(syn);

        Routing_Alg<T>::scheduleUpdate();
    }

    virtual void addFlow(const Address &_nAddr, const string &_addr, const T &_metric){
        Routing_Alg<T>::addFlow(_nAddr, _addr, _metric);

        changed.insert(Routing_Alg<T>::myAddr);
        secId++;
        netState[Routing_Alg<T>::myAddr].sId = secId;
        netState[Routing_Alg<T>::myAddr].links[_addr] = _metric;

        Routing_Alg<T>::scheduleUpdate();
    }

    virtual void removeFlow(const Address &_nAddr, const string &_addr){
        Routing_Alg<T>::removeFlow(_nAddr, _addr);

        changed.insert(Routing_Alg<T>::myAddr);
        secId++;
        netState[Routing_Alg<T>::myAddr].sId = secId;
        netState[Routing_Alg<T>::myAddr].links.erase(_addr);

        Routing_Alg<T>::scheduleUpdate();
    }

    virtual bool processUpdate(Routing_Update * update) {
        if(LS_Update * up = dynamic_cast<LS_Update*>(update)) {
            for(auto & entry : up->entries){
                if(netState[entry.first].sId < entry.second.sId){
                    netState[entry.first] = entry.second;
                    changed.insert(entry.first);
                }
            }
            if(!changed.empty()) {
                Routing_Alg<T>::scheduleUpdate();
                return true;
            }
        }

        return false;
    };

    virtual void sendUpdate() {
        Routing_Alg<T>::sendUpdate();

        map<string, linksU> entries;
        for(string entry : changed){
            entries[entry] = netState[entry];
        }

        for(auto neig : Routing_Alg<T>::invNeigTable){
            LS_Update * update = new LS_Update();
            update->entries = entries;
            Routing_Alg<T>::parent->chSendUpdate(update, neig.first, this);
        }

    }

    virtual map<string, nhLMetric<T>  > getChanges() {
        GraphCL<T> g;

        for(const auto &entry : netState){
            for(const auto & link : entry.second.links){
                g.addLink(entry.first, Link<T>(link.first, link.second));
            }
        }
        map<string, nhLMetric<T>  > t = g.getNextHops(Routing_Alg<T>::myAddr, Routing_Alg<T>::infinite);
        map<string, nhLMetric<T>  > ret = t;

        for(const auto & entry : currentTable){
            if(entry.second.metric == ret[entry.first].metric || entry.second.nh == ret[entry.first].nh) {
                ret.erase(entry.first);
            }

        }

        currentTable = t;
        return ret;
    };

    virtual map<string, nhLMetric<T>  > getAll() {
        GraphCL<T> g;

        for(auto entry : netState){
            for(auto link : entry.second.links){
                g.addLink(entry.first, Link<T>(link.first, link.second));
            }
        }
        currentTable = g.getNextHops(Routing_Alg<T>::myAddr, Routing_Alg<T>::infinite);
        return currentTable;
    };


    virtual void print() {
        GraphCL<T> g;
        for(auto entry : netState){
            for(auto link : entry.second.links){
                g.addLink(entry.first, Link<T>(link.first, link.second));
            }
        }
        g.print(Routing_Alg<T>::myAddr, Routing_Alg<T>::infinite);
    }
};

} /* namespace common_LSModule */
