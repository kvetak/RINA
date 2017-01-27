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

#include "DIF/RA/PDUFG/StaticGenerator/StaticGenerator.h"
#include "Common/APN.h"


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
            const APNList* remoteApps = difA->findNeigborApns(addr.getApn());
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
void StaticGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    //Iterate through all QoS cubes and check if exist an entry with qos
    for(QoSCube qosI : cubes) {
        auto res = fwd->lookup(addr, qosI.getQosId());
        if(!res.empty()){
            RMTPort * tp = *res.begin();
            if(tp == port){
                fwd->remove(addr, qosI.getQosId());
            }
            if (const APNList* remoteApps = difA->findNeigborApns(addr.getApn())) {
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
        if (const APNList* remoteApps = difA->findNeigborApns(addr.getApn())) {
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
    fwd = getRINAModule<SimpleTable::SimpleTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});


    RABase* ResourceAllocator = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});
    cubes = ResourceAllocator->getQoSCubes();

    comparer = getRINAModule<MultilevelQoS *>(this, 2, {MOD_FLOWALLOC, MOD_POL_RA_QOSCOMPARER});
}

}
