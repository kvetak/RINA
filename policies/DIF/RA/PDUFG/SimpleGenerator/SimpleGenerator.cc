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

#include "DIF/RA/PDUFG/SimpleGenerator/SimpleGenerator.h"
#include "Common/APN.h"



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
void SimpleGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
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
    fwd = getRINAModule<IntMiniForwarding *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntSimpleRouting *>(this, 2, {MOD_POL_ROUTING});

    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});
}

}
