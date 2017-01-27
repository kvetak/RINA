// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/RA/PDUFG/QoSDomainGenerator/QoSDomainGenerator.h"
#include "Common/APN.h"

#include <stdio.h>
#include <stdlib.h>



namespace QoSDomainGenerator {

Register_Class(QoSDomainGenerator);

using namespace std;

void QoSDomainGenerator::insertedFlow(const Address& addr, const QoSCube & qos, RMTPort* port) {
    std::string dst = addr.getIpcAddress().getName();

    //Iterate through all QoS cubes and check if qos is a valid
    for(QoSCube qosI : cubes) {
        if(comparer->isValid(qosI, qos)) {
            neighbours[qosI.getQosId()][dst].insert(port);
            if (neighbours[qosI.getQosId()][dst].size() == 1) {
                rt->addFlow(addr, qosI.getQosId(), dst, 1);
                routingUpdated();
            }
        }
    }
}

void QoSDomainGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
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
    fwd = getRINAModule<QoSTable::QoSTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rt = getRINAModule<DMRnms::Routing *>(this, 2, {MOD_POL_ROUTING});

    std::string alg = par("alg").stdstringValue();

    RABase* ResourceAllocator = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});

    cubes = ResourceAllocator->getQoSCubes();

    if(alg == "LS"){
        for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
            rt->addDomain(it->getQosId(), getModuleByPath("^.^")->par("ipcAddress").stringValue(), DMRnms::LS);
        }
    } else {
        for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
            rt->addDomain(it->getQosId(), getModuleByPath("^.^")->par("ipcAddress").stringValue(), DMRnms::DV);
        }
    }

    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});


    comparer = getRINAModule<MultilevelQoS *>(this, 2, {MOD_FLOWALLOC, MOD_POL_RA_QOSCOMPARER});
}

}
