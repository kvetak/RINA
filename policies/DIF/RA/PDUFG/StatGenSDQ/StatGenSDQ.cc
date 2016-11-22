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

#include <StatGenSDQ/StatGenSDQ.h>

Register_Class(StatGenSDQ);

using namespace std;

// A new flow has been inserted/or removed
void StatGenSDQ::insertedFlow(const Address &addr, const QoSCube &qos, port_t port){
    string nei = addr.getIpcAddress().getName();
    auto flows = neiTable[nei];

    //cout << "At " << ipcAddr << " added nei "<< nei << endl;
    //cout << "Entries = " << flows.size() << endl;
    for(auto f : flows) {
        fwd->add(f.src, f.dst, f.qos, port);
    //    cout << "\tNext for "<< f.src << " -> " << f.dst <<" / " << f.qos << endl;
    }

}

void StatGenSDQ::removedFlow(const Address &addr, const QoSCube& qos, port_t port){
    error("This policy should not be used in dynamic scenarios");
}

//Routing has processes a routing update
void StatGenSDQ::routingUpdated(){
    error("This policy should not be used in dynamic scenarios");
}

// Called after initialize
void StatGenSDQ::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<FwdSDQ *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    //Read XML
    if (par("TData").xmlValue() == nullptr || !par("TData").xmlValue()->hasChildren()) {
        error("lData parameter not initialized!");
    }
    cXMLElementList Tsets = par("TData").xmlValue()->getChildrenByTagName("entry");

    string myName = ipcAddr.getIpcAddress().getName();

    for(cXMLElement* t : Tsets) {
        string node = t->getAttribute("node");
        string src = t->getAttribute("src");
        string dst = t->getAttribute("dst");
        string qos = t->getAttribute("qos");
        string next = t->getAttribute("next");

        if(node != myName) { continue; }

        auto & flows = neiTable[next];
        flows.push_back(FlowInfo(src, dst, qos));
    }
}
