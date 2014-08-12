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
    //Watchers
    WATCH_LIST(flows);
}

void AE::handleMessage(cMessage* msg) {
}

void AE::createBinding(Flow& flow) {
    EV << this->getFullPath() << " created bindings and registered a new flow" << endl;
    //Create new gates
    cGate* g1i;
    cGate* g1o;
    Irm->getOrCreateFirstUnconnectedGatePair("aeIo", false, true, *&g1i, *&g1o);

    //cGate* g0i;
    //cGate* g0o;
    //this->getOrCreateFirstUnconnectedGatePair("southIo", true, true, *&g0i, *&g0o);

    //Get AE gates
    cGate* g2i;
    cGate* g2o;
    this->getOrCreateFirstUnconnectedGatePair("dataIo", false, true, *&g2i, *&g2o);

    //Connect gates together
    g1o->connectTo(g2i);
    g2o->connectTo(g1i);

    //Set north-half of the routing in ConnectionTable
    ConTab->setNorthGates(&flow, g1i, g1o);
}

void AE::initPointers() {
    Irm = ModuleAccess<IRM>("irm").get();
    ConTab = ModuleAccess<ConnectionTable>("connectionTable").get();
}

void AE::signalizeAllocateRequest(Flow* flow) {
    emit(sigAEAllocReq, flow);
}

void AE::insert(Flow& flow) {
    //Add a new flow to the end of the Flow list
    flows.push_back(flow);

    //Create a new record in ConnectionTable
    ConTab->insertNew(&flows.back());

    //Interconnect IRM and AE
    createBinding(flows.back());
}

void AE::signalizeDeallocateRequest(Flow* flow) {
    emit(sigAEDeallocReq, flow);
}


