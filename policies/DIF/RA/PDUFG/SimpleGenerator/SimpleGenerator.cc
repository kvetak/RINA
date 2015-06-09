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

#include <SimpleGenerator/SimpleGenerator.h>
#include "APN.h"



namespace SimpleGenerator {

Register_Class(SimpleGenerator);

using namespace std;

// A new flow has been inserted/or removed
void SimpleGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "", 1);
        routingUpdated();
    }
}
void SimpleGenerator::removedFlow(const Address &addr, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "");
        neighbours.erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void SimpleGenerator::routingUpdated(){
    entries2Next changes = rt->getChanges();

    for(entries2NextIt it = changes.begin(); it!= changes.end(); it++){
        qosPaddr dst = it->first;
        std::string nextHop = "";
        if(!it->second.nh.empty()){
            nextHop = *(it->second.nh.begin());
        }
        RMTPort * p = NULL;
        if(nextHop != "") {
            NTableIt n = neighbours.find(nextHop);
            if(n != neighbours.end()){
                if(!n->second.empty()) {
                    p = *(n->second.begin());
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
void SimpleGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<IntMiniForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntSimpleRouting *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
