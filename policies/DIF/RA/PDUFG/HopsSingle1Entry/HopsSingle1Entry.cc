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

#include "DIF/RA/PDUFG/HopsSingle1Entry/HopsSingle1Entry.h"
#include "Common/APN.h"



namespace HopsSingle1Entry {

Register_Class(HopsSingle1Entry);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void HopsSingle1Entry::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "", 1);
        routingUpdated();
    }
}
void HopsSingle1Entry::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "");
        neighbours.erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void HopsSingle1Entry::routingUpdated(){
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
                    p = *(n->second.begin());
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
void HopsSingle1Entry::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<IntMiniForwarding *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntTSimpleRouting<mType> *>(this, 2, {MOD_POL_ROUTING});

    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);
}

}
