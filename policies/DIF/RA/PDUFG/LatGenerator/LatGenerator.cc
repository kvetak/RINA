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

#include "DIF/RA/PDUFG/LatGenerator/LatGenerator.h"
#include "Common/APN.h"

#include <stdio.h>
#include <stdlib.h>


namespace LatGenerator {

Register_Class(LatGenerator);

using namespace std;

portMetric::portMetric(RMTPort* p, unsigned short m) :
    port(p), metric(m){}

bool portMetric::operator < (const portMetric &other) const {
    return port < other.port;
}

// A new flow has been inserted/or removed
void LatGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();

    unsigned short metric = qos.getDelay()/par("redLinkCost").longValue();

    if(metric < par("minLinkCost").longValue()) {
        metric = par("minLinkCost").longValue();
    } else if(metric > par("maxLinkCost").longValue()) {
        metric = par("maxLinkCost").longValue();
    }

    if(qos.getQosId() == qos.MANAGEMENT.getQosId() || qos.getQosId() == VAL_UNDEF_QOSID) {
        metric = par("maxLinkCost").longValue();
    }

    neighbours[dst].insert(portMetric(port, metric));
    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "", metric);
        routingUpdated();
    } else {
        bool lower = true;
        for(portMetric mt : neighbours[dst]) {
            if(metric >= mt.metric && port != mt.port) { lower = false; }
        }
        if(lower) {
            rt->insertFlow(addr, dst, "", metric);
            routingUpdated();
        }
    }
}
void LatGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(portMetric(port, 0));
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "");
        neighbours.erase(dst);
        routingUpdated();
    } else {
        unsigned short min = par("maxLinkCost").longValue();
        for(portMetric mt : neighbours[dst]) {
            if(min >= mt.metric) { min = mt.metric; }
        }
        rt->insertFlow(addr, dst, "", min);
        routingUpdated();
    }
}

//Routing has processes a routing update
void LatGenerator::routingUpdated(){
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
                    p = n->second.begin()->port;
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
void LatGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<MiniTable::MiniTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntSimpleRouting *>(this, 2, {MOD_POL_ROUTING});
}

}
