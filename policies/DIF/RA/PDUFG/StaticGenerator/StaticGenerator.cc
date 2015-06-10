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
void StaticGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    //Iterate through all QoS cubes and check if qos is a valid
    for(QoSCube qosI : cubes) {
        if(comparer->isValid(qosI, qos)) {
            fwd->insert(addr, qosI.getQosId(), port);
            fwd->insert(addr, port);
            const APNList* remoteApps = difA->findNeigborApns(addr.getApname());
            if (remoteApps) {
                for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it) {
                    fwd->insert(Address(it->getName()), qosI.getQosId(), port);
                    fwd->insert(Address(it->getName()), port);
                }
            }
        }
    }

    if(qos.getQosId() == VAL_UNDEF_QOSID) {
        error("Undef QoS");
    }

}
void StaticGenerator::removedFlow(const Address &addr, RMTPort * port){
    //Iterate through all QoS cubes and check if exist an entry with qos
    for(QoSCube qosI : cubes) {
        auto res = fwd->lookup(addr, qosI.getQosId());
        if(!res.empty()){
            RMTPort * tp = *res.begin();
            if(tp == port){
                fwd->remove(addr, qosI.getQosId());
            }
            if (const APNList* remoteApps = difA->findNeigborApns(addr.getApname())) {
                for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it){
                    res = fwd->lookup(Address(it->getName()), qosI.getQosId());
                    if(!res.empty()) {
                        tp = *res.begin();
                        if(tp == port){
                            fwd->remove(Address(it->getName()), qosI.getQosId());
                        }
                    }
                }
            }
        }
    }

    auto res = fwd->lookup(addr, ANY_QOS);
    if(!res.empty()){
        RMTPort * tp = *res.begin();
        if(tp == port){
            fwd->remove(addr);
        }
        if (const APNList* remoteApps = difA->findNeigborApns(addr.getApname())) {
            for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it){
                res = fwd->lookup(Address(it->getName()), ANY_QOS);
                if(!res.empty()) {
                    tp = *res.begin();
                    if(tp == port){
                        fwd->remove(Address(it->getName()));
                    }
                }
            }
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


    RABase* ResourceAllocator = check_and_cast<RABase*>(getParentModule()->getParentModule()->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA));
    cubes = ResourceAllocator->getQoSCubes();

    comparer = check_and_cast<MultilevelQoS *>
        (getModuleByPath("^.^.flowAllocator.qosComparerPolicy"));
}

}
