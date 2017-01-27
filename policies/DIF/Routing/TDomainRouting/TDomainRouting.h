#pragma once

#include <string>
#include <map>

#include "DIF/Routing/IntRouting.h"

#include "DIF/Routing/common/nhLMetric.h"
#include "DIF/Routing/common/Routing_Module.h"
#include "DIF/Routing/common/LS_Module.h"
#include "DIF/Routing/common/DV_Module.h"

using namespace std;
using namespace common_LSModule;
using namespace common_DVModule;

namespace tDomain {

enum ModuleAlgs { DV, LS };

class updateI {};

template<class T>
class TDomainRouting: public IntRouting, public common_Routing::Routing_Module {
protected:
    map<string, Routing_Alg<T> * > modules;

    T infinite;
    string myAddr;

    class Update : public IntRoutingUpdate {
    public:
        string domId;
        Routing_Update * u;
    };

    class AutoMsg : public cMessage {
    public:
        string domId;
    };

public:
    virtual void addDomain(const string & domId, const string &_addr, T infinite, ModuleAlgs alg) {
        if(modules[domId] == NULL) {
            switch(alg) {
                case DV : modules[domId] = new DV_Module<T>(this, myAddress, _addr, infinite); break;
                case LS : modules[domId] = new LS_Module<T>(this, myAddress, _addr, infinite); break;
            }
            modules[domId]->setDescriptor(domId);
        }
    }
    virtual void removeDomain(const string & domId) {

        if(modules[domId] != NULL) {
            delete modules[domId];
        }
        modules.erase(domId);
    }

    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) {
        if(Update * u = dynamic_cast<Update*>(update)) {
            if(modules[u->domId] != NULL) {
                return modules[u->domId]->processUpdate(u->u);
            }
        }
        return false;
    }

    //Modules connection
    virtual void chSendUpdate(Routing_Update * update, const Address & dst, Routing_Alg_I * module) {
        bool found = false;
        Update * up = new Update();
        up->setDestination(dst);
        up->setSource(myAddress);
        up->u = update;

        for(const auto & md : modules) {
            if(md.second == module) {
                found = true;
                up->domId = md.first;
                break;
            }
        }

        if(found){
            sendUpdate(up);
        }
    }

    virtual void chScheduleAt(Routing_Alg_I * module, const simtime_t & t) {
        Enter_Method_Silent();
        bool found = false;
        AutoMsg * m = new AutoMsg();

        for(const auto & md : modules) {
            if(md.second == module) {
                found = true;
                m->domId = md.first;
                break;
            }
        }

        if(found){
            scheduleAt(simTime()+t, m);
        }
    }


    //Flow inserted/removed
    virtual void insertFlow(const Address &addr, const string &dst, const string& domId, const T &metric) {
        if(modules[domId] != NULL) {
            modules[domId]->addFlow(addr, dst, metric);
        }
    }
    virtual void removeFlow(const Address &addr, const string &dst, const string& domId) {
        if(modules[domId] != NULL) {
            modules[domId]->removeFlow(addr, dst);
        }
    }

    //Get Changes // QoS // Dst // <metric, next hops>
    virtual map<string, map<string, nhLMetric<T>  > > getChanges() {
        map<string, map<string, nhLMetric<T>  > > ret;
        for(auto & md : modules) {
            ret[md.first] = md.second->getChanges();
        }
        return ret;
    }
    virtual map<string, map<string, nhLMetric<T>  > > getAll() {
        map<string, map<string, nhLMetric<T>  > > ret;
        for(auto &  md : modules) {
            ret[md.first] = md.second->getAll();
        }
        return ret;
    }

    virtual void handleMessage(cMessage *msg){
        if(AutoMsg * m = dynamic_cast<AutoMsg*>(msg)) {
            if(modules[m->domId] != NULL) {
                modules[m->domId]->sendUpdate();
            }
        }
        delete msg;
    }

    // Add/Remove secondary addresses
    void addAddr(const std::string &domId, const std::string &syn){
        if(modules[domId] != NULL) {
            modules[domId]->addSynonym(syn);
        }
    }

    void removeAddr(const std::string &domId, const std::string &syn){
        if(modules[domId] != NULL) {
            modules[domId]->removeSynonym(syn);
        }
    }


protected:
    // Called after initialize
    virtual void onPolicyInit() {
        myAddr = par("myAddr").stdstringValue();
        if(myAddr == "") {
            myAddr = myAddress.getIpcAddress().getName();
        }
    };

    void finish(){
        if(par("printAtEnd").boolValue()){
            EV<< "Routing at "<< myAddress <<endl;
            for(auto &  md : modules) {
                EV << "-----With Domain \""  << md.first <<"\"" << endl;
                md.second->print();
            }
        }
    }
};

}
