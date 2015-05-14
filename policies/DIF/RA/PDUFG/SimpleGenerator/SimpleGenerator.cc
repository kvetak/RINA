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
void SimpleGenerator::insertedFlow(const Address &addr, const std::string &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst][qos].insert(port);
    if(neighbours[dst][qos].size() == 1){
        rt->insertFlow(addr, dst, qos, 1);
        routingUpdated();
    }
}
void SimpleGenerator::removedFlow(const Address &addr, const std::string &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst][qos].erase(port);
    if(neighbours[dst][qos].size() <= 0){
        neighbours[dst].erase(qos);
        rt->removeFlow(addr, dst, qos);
        if(neighbours[dst].size() <= 0){
            neighbours.erase(dst);
        }
        routingUpdated();
    }
}

//Routing has processes a routing update
void SimpleGenerator::routingUpdated(){
    entries2Next changes = rt->getChanges();

    for(entries2NextIt it = changes.begin(); it!= changes.end(); it++){
        qosPaddr dst = it->first;
        std::string nextHop = it->second;
        RMTPort * p = NULL;
        if(nextHop != "") {
            NTableIt n = neighbours.find(nextHop);
            if(n != neighbours.end()){
                NentriesIt pit = n->second.find(dst.first);
                if(pit != n->second.end()){
                    if(pit->second.size()>0){
                        p = *(pit->second.begin());
                    }
                }
            }
        }
        if(p == NULL) {
            fwd->remove(dst.second, dst.first);
        } else {
            fwd->insert(dst.second, dst.first, p);
        }
    }
}

// Called after initialize
void SimpleGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<SimpleTable::SimpleTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntSimpleRouting *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
