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

#include <StaticGenerator/StaticGenerator.h>
#include "APN.h"



namespace StaticGenerator {

Register_Class(StaticGenerator);

using namespace std;

// A new flow has been inserted/or removed
void StaticGenerator::insertedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){

    fwd->insert(addr, qos, port);

    const APNList* remoteApps = difA->findNeigborApns(addr.getApname());

    if (remoteApps) {
        for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it) {
            fwd->insert(Address(it->getName()), qos, port);
        }
    }

    EV << "Flow inserted to " << addr << endl;
}
void StaticGenerator::removedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){

    fwd->remove(addr, qos);

    const APNList* remoteApps = difA->findNeigborApns(addr.getApname());

    if (remoteApps) {
        for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it){
            fwd->remove(Address(it->getName()), qos);
        }
    }
}

//Routing has processes a routing update
void StaticGenerator::routingUpdated(){}

// Called after initialize
void StaticGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<SimpleTable::SimpleTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
