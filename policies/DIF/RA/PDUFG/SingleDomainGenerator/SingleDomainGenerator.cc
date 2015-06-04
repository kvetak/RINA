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

#include <SingleDomainGenerator/SingleDomainGenerator.h>
#include "APN.h"



namespace SingleDomainGenerator {

Register_Class(SingleDomainGenerator);

using namespace std;

// A new flow has been inserted/or removed
void SingleDomainGenerator::insertedFlow(const Address &addr, const QoSCube & qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    if(neighbours[dst].size() == 1){
        rt->addFlow(addr, "", dst,1);
        routingUpdated();
    }
}
void SingleDomainGenerator::removedFlow(const Address &addr, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr,"", dst);
        neighbours.erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void SingleDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){
            std::string dst = eIt->first;
            std::string nextHop = eIt->second.getIpcAddress().getName();

            EV << "Entry ::: "<< dst << " -> " << nextHop << " ("<< eIt->second<<")" <<endl;
            RMTPort * p = NULL;

            NTableIt n = neighbours.find(nextHop);
            if(n != neighbours.end()){
                p = *(n->second.begin());
            }

            if(p == NULL) {
                fwd->remove(dst);
            } else {
                fwd->insert(dst, p);
            }
        }
    }
}

// Called after initialize
void SingleDomainGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<MiniTable::MiniTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    rt = check_and_cast<DMRnms::Routing *>
        (getModuleByPath("^.^.routingPolicy"));

    std::string alg = par("alg").stdstringValue();

    if(alg == "LS"){
        rt->addDomain("", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
    } else {
        rt->addDomain("", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
    }


    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
