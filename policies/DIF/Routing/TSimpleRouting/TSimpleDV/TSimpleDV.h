#pragma once

#include <string>
#include <map>

#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"
#include "DIF/Routing/common/DV_Module.h"


namespace TSimpleDV {

using namespace common_DVModule;

template<class T>
class TSimpleDV: public IntTSimpleRouting<T> {
protected:
    string myAddr;

    map<string, DV_Module<T> > modules;

    class Update : public IntRoutingUpdate {
    public:
        string qos;
        Routing_Update * u;
    };

    class AutoMsg : public cMessage {
    public:
        string qos;
    };

public:
    TSimpleDV(){}

    //Process a Routing Update, return true => inform FWDG of the update
    bool processUpdate(IntRoutingUpdate * update) {
        if(Update * u = dynamic_cast<Update*>(update)) {
            if(modules.find(u->qos) == modules.end()) {
                modules[u->qos] = DV_Module<T>(this, IntTSimpleRouting<T>::myAddress, myAddr, IntTSimpleRouting<T>::infinite );
            }

            return modules[u->qos].processUpdate(u->u);
        }
        return false;
    }

    //Modules connection
    virtual void chSendUpdate(Routing_Update * update, const Address & dst, Routing_Alg_I * module) {
        bool found = false;
        Update * up = new Update();
        up->setDestination(dst);
        up->setSource(IntTSimpleRouting<T>::myAddress);
        up->u = update;

        for(const auto & md : modules) {
            if(&md.second == module) {
                found = true;
                up->qos = md.first;
                break;
            }
        }

        if(found){
            IntTSimpleRouting<T>::sendUpdate(up);
        }
    }

    virtual void chScheduleAt(Routing_Alg_I * module, const simtime_t & t) {
        Enter_Method_Silent();
        bool found = false;
        AutoMsg * m = new AutoMsg();

        for(const auto & md : modules) {
            if(&md.second == module) {
                found = true;
                m->qos = md.first;
                break;
            }
        }

        if(found){
            IntTSimpleRouting<T>::scheduleAt(simTime()+t, m);
        }
    }

    //Flow inserted/removed
    virtual void insertFlow(const Address &addr, const string &dst, const string& qos, const T &metric) {
        if(modules.find(qos) == modules.end()) {
            modules[qos] = DV_Module<T>(this, IntTSimpleRouting<T>::myAddress, myAddr, IntTSimpleRouting<T>::infinite );
        }
        modules[qos].addFlow(addr, dst, metric);
    }
    virtual void removeFlow(const Address &addr, const string &dst, const string& qos) {
        if(modules.find(qos) == modules.end()) {
            modules[qos] = DV_Module<T>(this, IntTSimpleRouting<T>::myAddress, myAddr, IntTSimpleRouting<T>::infinite );
        }
        modules[qos].removeFlow(addr, dst);
    }

    //Get Changes // QoS // Dst // <metric, next hops>
    virtual map<string, map<string, nhLMetric<T>  > > getChanges() {
        map<string, map<string, nhLMetric<T>  > > ret;
        for(auto & md : modules) {
            ret[md.first] = md.second.getChanges();
        }
        return ret;
    }
    virtual map<string, map<string, nhLMetric<T>  > > getAll() {
        map<string, map<string, nhLMetric<T>  > > ret;
        for(auto &  md : modules) {
            ret[md.first] = md.second.getAll();
        }
        return ret;
    }

    virtual void handleMessage(cMessage *msg){
        if(AutoMsg * m = dynamic_cast<AutoMsg*>(msg)) {
            if(modules.find(m->qos) == modules.end()) {
                modules[m->qos] = DV_Module<T>(this, IntTSimpleRouting<T>::myAddress, myAddr, IntTSimpleRouting<T>::infinite );
            }
            modules[m->qos].sendUpdate();
        }
        delete msg;
    }


protected:
    // Called after initialize
    virtual void onPolicyInit() {
        myAddr = IntTSimpleRouting<T>::par("myAddr").stdstringValue();
        if(myAddr == "") {
            myAddr = IntTSimpleRouting<T>::myAddress.getIpcAddress().getName();
        }
    };

    void finish(){
        if(IntTSimpleRouting<T>::par("printAtEnd").boolValue()){
            EV<< "Routing at "<< IntTSimpleRouting<T>::myAddress <<endl;
            for(auto &  md : modules) {
                EV << "With QoS \""  << md.first <<"\"" << endl;
                md.second.print();
            }
        }
    }
};

}
