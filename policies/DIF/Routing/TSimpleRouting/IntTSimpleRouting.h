#pragma once

#include <string>
#include <map>

#include "DIF/Routing/IntRouting.h"

#include "DIF/Routing/common/nhLMetric.h"
#include "DIF/Routing/common/Routing_Module.h"

using namespace std;

class updateI {};

template<class T>
class IntTSimpleRouting: public IntRouting, public common_Routing::Routing_Module {
protected:
    T infinite;

public:
    virtual void setInfinite(const T & inf) { infinite = inf; }

    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;

    //Modules connection
    virtual void chSendUpdate(common_Routing::Routing_Update * update, const Address & dst, common_Routing::Routing_Alg_I *) = 0;
    virtual void chScheduleAt(common_Routing::Routing_Alg_I * update, const simtime_t & t) = 0;


    //Flow inserted/removed
    virtual void insertFlow(const Address &addr, const string &dst, const string& qos, const T &metric) = 0;
    virtual void removeFlow(const Address &addr, const string &dst, const string& qos) = 0;

    //Get Changes // QoS // Dst // <metric, next hops>
    virtual map<string, map<string, common_GraphCL::nhLMetric<T>  > > getChanges() = 0;
    virtual map<string, map<string, common_GraphCL::nhLMetric<T>  > > getAll() = 0;

protected:
    // Called after initialize
    virtual void onPolicyInit() = 0;
};
