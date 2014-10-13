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
    cModule* catcher = this->getParentModule();

    //Signals that this module is emitting
    sigAEAllocReq      = registerSignal(SIG_AE_AllocateRequest);
    sigAEDeallocReq    = registerSignal(SIG_AE_DeallocateRequest);
    sigAESendData      = registerSignal(SIG_AE_DataSend);

    //Signals that this module is processing
    lisAERcvData = new LisAEReceiveData(this);
    catcher->subscribe(SIG_CDAP_DateReceive, lisAERcvData);

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

bool AE::createBinding(Flow& flow) {
    EV << this->getFullPath() << " created bindings and registered a new flow" << endl;
    //Create new gates
    cGate* gIrmIn;
    cGate* gIrmOut;
    Irm->getOrCreateFirstUnconnectedGatePair(GATE_AEIO, false, true, *&gIrmIn, *&gIrmOut);

    //Get AE gates
    cGate* gAeIn;
    cGate* gAeOut;
    this->getParentModule()->getOrCreateFirstUnconnectedGatePair(GATE_DATAIO, false, true, *&gAeIn, *&gAeOut);

    //CDAPParent Module gates
    cGate* gCdapParentIn;
    cGate* gCdapParentOut;
    Cdap->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gCdapParentIn, *&gCdapParentOut);

    //CDAPSplitter gates
    cModule* CdapSplit = Cdap->getSubmodule(MOD_CDAPSPLIT);
    cGate* gSplitIn;
    cGate* gSplitOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gSplitIn, *&gSplitOut);
    cGate* gSplitCaceIn;
    cGate* gSplitCaceOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CACEIO, false, true, *&gSplitCaceIn, *&gSplitCaceOut);
    cGate* gSplitAuthIn;
    cGate* gSplitAuthOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_AUTHIO, false, true, *&gSplitAuthIn, *&gSplitAuthOut);
    cGate* gSplitCdapIn;
    cGate* gSplitCdapOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CDAPIO, false, true, *&gSplitCdapIn, *&gSplitCdapOut);

    //CACE Module gates
    cModule* CdapCace = Cdap->getSubmodule(MOD_CDAPCACE);
    cGate* gCaceIn;
    cGate* gCaceOut;
    CdapCace->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCaceIn, *&gCaceOut);

    //AUTH Module gates
    cModule* CdapAuth = Cdap->getSubmodule(MOD_CDAPAUTH);
    cGate* gAuthIn;
    cGate* gAuthOut;
    CdapAuth->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gAuthIn, *&gAuthOut);

    //CDAP Module gates
    cModule* CdapCdap = Cdap->getSubmodule(MOD_CDAPCDAP);
    cGate* gCdapIn;
    cGate* gCdapOut;
    CdapCdap->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCdapIn, *&gCdapOut);

    //Connect gates together
    gIrmOut->connectTo(gAeIn);
    gAeIn->connectTo(gCdapParentIn);
    gCdapParentIn->connectTo(gSplitIn);


    gSplitOut->connectTo(gCdapParentOut);
    gCdapParentOut->connectTo(gAeOut);
    gAeOut->connectTo(gIrmIn);


    gSplitCaceOut->connectTo(gCaceIn);
    gCaceOut->connectTo(gSplitCaceIn);

    gSplitAuthOut->connectTo(gAuthIn);
    gAuthOut->connectTo(gSplitAuthIn);

    gSplitCdapOut->connectTo(gCdapIn);
    gCdapOut->connectTo(gSplitCdapIn);


    //Set north-half of the routing in ConnectionTable
    ConTab->setNorthGates(&flow, gIrmIn, gIrmOut);

    //Return true if all dynamically created gates have same index
    return gIrmIn->getIndex() == gAeIn->getIndex()
           && gIrmIn->getIndex() == gCdapParentIn->getIndex()
           && gIrmIn->getIndex() == gSplitIn->getIndex()
           && gIrmIn->getIndex() == gSplitCaceIn->getIndex()
           && gIrmIn->getIndex() == gSplitAuthIn->getIndex()
           && gIrmIn->getIndex() == gSplitCdapIn->getIndex();
}

void AE::initPointers() {
    Irm = ModuleAccess<IRM>(MOD_IRM).get();
    ConTab = ModuleAccess<ConnectionTable>(MOD_CONNTABLE).get();
    Cdap = this->getParentModule()->getSubmodule(MOD_CDAP);

    if (!Irm || !ConTab || !Cdap)
        error("Pointers to Irm or ConnectionTable or Cdap is not initialized!");
}

void AE::insertFlow(Flow& flow) {
    //Add a new flow to the end of the Flow list
    flows.push_back(flow);

    //Create a new record in ConnectionTable
    ConTab->insertNew(&flows.back());

    //Interconnect IRM and AE
    bool status = createBinding(flows.back());
    if (!status) {
        throw("Gate inconsistency during creation of a new flow!");
    }
}

void AE::signalizeAllocateRequest(Flow* flow) {
    emit(sigAEAllocReq, flow);
}

void AE::signalizeDeallocateRequest(Flow* flow) {
    emit(sigAEDeallocReq, flow);
}

void AE::receiveData(cObject* obj) {
}

void AE::signalizeSendData(cMessage* msg) {
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigAESendData, msg);
}


void AE::sendData(Flow* flow, CDAPMessage* msg) {
    //Retrieve handle from ConTab record
    ConnectionTableEntry* cte = ConTab->findEntryByFlow(flow);
    msg->setHandle(cte->getNorthGateIn()->getIndex());

    //Pass message to CDAP
    signalizeSendData(msg);
}
