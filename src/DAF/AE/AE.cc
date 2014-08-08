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

#include "AE.h"

Define_Module(AE);

AE::AE()  {
}

AE::~AE() {
}

void AE::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigAEAllocReq      = registerSignal(SIG_AE_AllocateRequest);
    sigAEDeallocReq    = registerSignal(SIG_AE_DeallocateRequest);

    //Signals that this module is processing

}

void AE::initialize() {
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init connection
    initConnections();
}

void AE::handleMessage(cMessage* msg) {
}

void AE::initConnections() {
    EV << this->getFullPath() << " registered and created IRM connections" << endl;

    cModule* Irm = this->getParentModule()->getSubmodule("irm");
    //Create new gates
    cGate* g1i;
    cGate* g1o;
    Irm->getOrCreateFirstUnconnectedGatePair("aeIo", true, true, *&g1i, *&g1o);
    //cGate* g0i;
    //cGate* g0o;
    //this->getOrCreateFirstUnconnectedGatePair("southIo", true, true, *&g0i, *&g0o);

    //Get AE gates
    cGate* g2i = this->gate("dataIn");
    cGate* g2o = this->gate("dataOut");

    //Connect gates together
    g1o->connectTo(g2i);
    g2o->connectTo(g1i);
}

void AE::initPointers() {
}

void AE::signalizeAllocateRequest(Flow* flow) {
    emit(sigAEAllocReq, flow);
}

void AE::signalizeDeallocateRequest(Flow* flow) {
    emit(sigAEDeallocReq, flow);
}


