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

#include "DIF/RA/PDUFG/NeiGen/NeiGen.h"

Register_Class(NeiGen);

using namespace std;

// A new flow has been inserted/or removed
void NeiGen::insertedFlow(const Address &addr, const QoSCube &qos, port_t port){
    sfwd->insert(addr.getIpcAddress().getName(), qos.getQosId(), port);
}

void NeiGen::removedFlow(const Address &addr, const QoSCube& qos, port_t port){
    sfwd->remove(addr.getIpcAddress().getName(), qos.getQosId());
}

//Routing has processes a routing update
void NeiGen::routingUpdated(){}

// Called after initialize
void NeiGen::onPolicyInit(){
    //Set Forwarding policy
    sfwd = getRINAModule<NeiTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
}
