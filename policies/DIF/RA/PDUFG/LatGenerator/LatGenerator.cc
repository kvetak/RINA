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

#include <LatGenerator/LatGenerator.h>
#include "APN.h"

#include <stdio.h>
#include <stdlib.h>


namespace LatGenerator {

Register_Class(LatGenerator);

using namespace std;

portMetric::portMetric(RMTPort* p, unsigned short m) :
    port(p), metric(m){}

bool portMetric::operator < (const portMetric &other) const {
    return port < other.port;
}

// A new flow has been inserted/or removed
void LatGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();

    unsigned short metric = qos.getDelay()/par("redLinkCost").longValue();

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
void LatGenerator::removedFlow(const Address &addr, RMTPort * port){
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
void LatGenerator::routingUpdated(){
    entries2Next changes = rt->getChanges();

    for(entries2NextIt it = changes.begin(); it!= changes.end(); it++){
        qosPaddr dst = it->first;
        std::string nextHop = it->second;
        RMTPort * p = NULL;
        if(nextHop != "") {
            NTableIt n = neighbours.find(nextHop);
            if(n != neighbours.end()){
                if(!n->second.empty()) {
                    p = n->second.begin()->port;
                }
            }
        }
        if(p == NULL) {
            fwd->remove(dst.second);
        } else {
            fwd->insert(dst.second, p);
        }
    }
}

// Called after initialize
void LatGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<MiniTable::MiniTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntSimpleRouting *>
        (getModuleByPath("^.^.routingPolicy"));
}

}
