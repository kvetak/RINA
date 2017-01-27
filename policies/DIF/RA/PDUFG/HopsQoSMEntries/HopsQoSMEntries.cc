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

#include "DIF/RA/PDUFG/HopsQoSMEntries/HopsQoSMEntries.h"
#include "Common/APN.h"



namespace HopsQoSMEntries {

Register_Class(HopsQoSMEntries);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void HopsQoSMEntries::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    string dst = addr.getIpcAddress().getName();
    string qosId = qos.getQosId();
    portQoS[port] = qosId;
    neighbours[qosId][dst].insert(port);
    if(neighbours[qosId][dst].size() == 1){
        rt->insertFlow(addr, dst, qosId, 1);
        routingUpdated();
    }
}
void HopsQoSMEntries::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    string qosId = portQoS[port];
    neighbours[qosId][dst].erase(port);
    if(neighbours[qosId][dst].size() <= 0){
        rt->removeFlow(addr, dst, qosId);
        neighbours[qosId].erase(dst);
        if(neighbours[qosId].size()<=0) {
            neighbours.erase(qosId);
        }
        routingUpdated();
    }
    portQoS.erase(port);
}

//Routing has processes a routing update
void HopsQoSMEntries::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        string qosId = qosEntries.first;
        for(const auto & entry : qosEntries.second){
            std::vector< RMTPort * > ps;
            for(string nextHop : entry.second.nh){
                RMTPort * p = NULL;
                if(nextHop != "") {
                    auto n = neighbours[qosId].find(nextHop);
                    if(n != neighbours[qosId].end()){
                        if(!n->second.empty()) {
                            p = *(n->second.begin());
                        }
                    }
                }
                if(p != NULL) {
                    ps.push_back(p);
                }
                fwd->addReplace(entry.first, qosId, ps);
            }
        }
    }
}

// Called after initialize
void HopsQoSMEntries::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<IntQoSMForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntTSimpleRouting<mType> *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);
}

}
