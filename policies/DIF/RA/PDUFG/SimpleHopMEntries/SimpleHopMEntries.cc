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

#include "DIF/RA/PDUFG/SimpleHopMEntries/SimpleHopMEntries.h"
#include "Common/APN.h"



namespace NSPSimpleHopMEntries {

Register_Class(SimpleHopMEntries);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void SimpleHopMEntries::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){

    string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);

    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "hops", 1);
        routingUpdated();
    }
}
void SimpleHopMEntries::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();

    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "hops");
        neighbours.erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void SimpleHopMEntries::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        for(const auto & entry : qosEntries.second){
            std::vector< RMTPort * > ps;
            for(string nextHop : entry.second.nh){
                if(nextHop != "") {
                    if(!neighbours[nextHop].empty()) {
                        ps.push_back(*neighbours[nextHop].begin());
                    }
                }
            }

            fwd->addReplace(entry.first, ps);
        }
    }
}

// Called after initialize
void SimpleHopMEntries::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<IntMMForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntTSimpleRouting<mType> *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);

    string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
}

}
