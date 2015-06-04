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

#include <QoSDomainGenerator/QoSDomainGenerator.h>
#include "APN.h"

#include <stdio.h>
#include <stdlib.h>



namespace QoSDomainGenerator {

Register_Class(QoSDomainGenerator);

using namespace std;

void QoSDomainGenerator::insertedFlow(const Address& addr, const QoSCube & qos, RMTPort* port) {
    std::string dst = addr.getIpcAddress().getName();

    //Iterate through all QoS cubes and check if qos is a valid
    for(QoSCube qosI : cubes) {
        //if(qosI.validNminus(qos)){
            neighbours[qosI.getQosId()][dst].insert(port);
            if (neighbours[qosI.getQosId()][dst].size() == 1) {
                rt->addFlow(addr, qosI.getQosId(), dst, 1);
                routingUpdated();
            }
        //}
    }
}

void QoSDomainGenerator::removedFlow(const Address &addr, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();

    //Iterate through all QoS cubes and remove is inserted
    for(QoSCube qosI : cubes) {
        if(neighbours[qosI.getQosId()].find(dst) != neighbours[qosI.getQosId()].end()){
            neighbours[qosI.getQosId()][dst].erase(port);
            if(neighbours[qosI.getQosId()][dst].size() <= 0){
                rt->removeFlow(addr,qosI.getQosId(), dst);
                neighbours[qosI.getQosId()].erase(dst);
                routingUpdated();
            }
        }
    }
}

//Routing has processes a routing update
void QoSDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){
            std::string dst = eIt->first;
            std::string nextHop = eIt->second.getIpcAddress().getName();

            EV << "Entry ::: "<< dst << " -> " << nextHop << " ("<< eIt->second<<")" <<endl;
            RMTPort * p = NULL;

            NTableIt n = neighbours[it->domain].find(nextHop);
            if(n != neighbours[it->domain].end()){
                p = *(n->second.begin());
            }

            if(p == NULL) {
                fwd->remove(dst, it->domain);
            } else {
                fwd->insert(dst, it->domain, p);
            }
        }
    }
}

// Called after initialize
void QoSDomainGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<QoSTable::QoSTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    rt = check_and_cast<DMRnms::Routing *>
        (getModuleByPath("^.^.routingPolicy"));

    std::string alg = par("alg").stdstringValue();

    fwd = check_and_cast<QoSTable::QoSTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));


    RABase* ResourceAllocator = check_and_cast<RABase*>(getParentModule()->getParentModule()->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA));

    cubes = ResourceAllocator->getQoSCubes();

    if(alg == "LS"){
        for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
            rt->addDomain(it->getQosId(), getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
        }
    } else {
        for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
            rt->addDomain(it->getQosId(), getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
        }
    }

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
