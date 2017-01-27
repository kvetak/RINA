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

#include "DIF/RA/PDUFG/IntPDUFG.h"
#include <vector>

IntPDUFG::IntPDUFG(){}

IntPDUFG::~ IntPDUFG(){}

void IntPDUFG::initialize(){
    // Display active policy name.
    setPolicyDisplayString(this);

    //Set Forwarding policy
    fwd = getRINAModule<IntPDUForwarding *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    onPolicyInit();

    ipcAddr = Address( getModuleByPath("^.^")->par("ipcAddress").stringValue(),
                getModuleByPath("^.^")->par("difName").stringValue());
}

PDUFGNeighbor * IntPDUFG::getNextNeighbor(const Address &destination, const std::string& qos){
    EV << "Search for " << destination << " with QoS "<< qos << endl;
    if(ipcAddr.getDifName().getName() != destination.getDifName().getName()) {
        EV << "Invalid search at "<< ipcAddr << endl;
    } else {
        RMTPorts ports = fwd->lookup(destination, qos);
        //TODO: Vesely : Changed tautological comparison from >=0 to >0
        if(ports.size() > 0){
            for(RMTPorts::iterator it = ports.begin(); it != ports.end(); it++){
                RMTPort * p = (*it);
                for(EIter it2 = neiState.begin(); it2 != neiState.end(); ++it2 ){
                    PDUFGNeighbor * e = (*it2);
                    // Found the port used for the forwarding table; so it's the next neighbor.
                    if(p == e->getPort()){
                        EV<< "Found "<< e->getDestAddr() << " -> "<< e->getPort()->getFullPath()<<endl;
                            return e;
                    }
                }
            }
        }
        EV<< "Not found"<<endl;
    }
    return nullptr;

}

void IntPDUFG::insertFlowInfo(Address addr, QoSCube qos, RMTPort * port) {
    EV << "New flow -> <" << addr << " , " << qos.getQosId() << "> at " << port->getFullPath()<<endl;

    //Insert Flow into neighbour state
    neiState.push_back(new PDUFGNeighbor(addr, qos, port));

    // Inform child policy of changes
    insertedFlow(addr, qos, port);
}

void IntPDUFG::removeFlowInfo(RMTPort * port) {
    for(EIter it = neiState.begin(); it != neiState.end(); ++it )
    {
        PDUFGNeighbor * e = (*it);
        if(port == e->getPort()) {
            Address addr = e->getDestAddr();
            QoSCube& qos = e->getQoSCube();

            // Remove flow from neighbour state
            neiState.erase(it);

            // Inform child policy of changes
            removedFlow(addr, qos, port);
            return;
        }
    }
}
