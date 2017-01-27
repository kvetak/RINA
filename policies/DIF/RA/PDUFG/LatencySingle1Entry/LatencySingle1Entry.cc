//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "DIF/RA/PDUFG/LatencySingle1Entry/LatencySingle1Entry.h"
#include "Common/APN.h"



namespace LatencySingle1Entry {

Register_Class(LatencySingle1Entry);

using namespace std;
using namespace common_GraphCL;


portMetric::portMetric(RMTPort* p, unsigned short m) :
    port(p), metric(m){}

bool portMetric::operator < (const portMetric &other) const {
    return port < other.port;
}

// A new flow has been inserted/or removed
void LatencySingle1Entry::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();

    mType metric = qos.getDelay()/par("redLinkCost").longValue();

    if(metric < par("minLinkCost").longValue()) {
        metric = par("minLinkCost").longValue();
    } else if(metric > par("maxLinkCost").longValue()) {
        metric = par("maxLinkCost").longValue();
    }

    if(qos.getQosId() == qos.MANAGEMENT.getQosId() || qos.getQosId() == VAL_UNDEF_QOSID) {
        metric = par("maxLinkCost").longValue();
    }

    neighbours[dst].insert(portMetric(port, metric));
    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "", metric);
        routingUpdated();
    } else {
        bool lower = true;
        for(portMetric mt : neighbours[dst]) {
            if(metric >= mt.metric && port != mt.port) { lower = false; }
        }
        if(lower) {
            rt->insertFlow(addr, dst, "", metric);
            routingUpdated();
        }
    }
}
void LatencySingle1Entry::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(portMetric(port, 0));
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "");
        neighbours.erase(dst);
        routingUpdated();
    } else {
        unsigned short min = par("maxLinkCost").longValue();
        for(portMetric mt : neighbours[dst]) {
            if(min >= mt.metric) { min = mt.metric; }
        }
        rt->insertFlow(addr, dst, "", min);
        routingUpdated();
    }
}

//Routing has processes a routing update
void LatencySingle1Entry::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & entry : changes[""]){
        std::string nextHop = "";
        if(!entry.second.nh.empty()){
            nextHop = *(entry.second.nh.begin());
        }
        RMTPort * p = NULL;
        if(nextHop != "") {
            auto n = neighbours.find(nextHop);
            if(n != neighbours.end()){
                if(!n->second.empty()) {
                    p = n->second.begin()->port;
                }
            }
        }
        if(p == NULL) {
            fwd->remove(entry.first);
        } else {
            fwd->insert(entry.first, p);
        }
    }
}

// Called after initialize
void LatencySingle1Entry::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<IntMiniForwarding *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntTSimpleRouting<mType> *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_ROUTING});

    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);
}

}
