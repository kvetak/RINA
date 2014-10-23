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
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getParentModule()->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigAEAllocReq      = registerSignal(SIG_AE_AllocateRequest);
    sigAEDeallocReq    = registerSignal(SIG_AE_DeallocateRequest);
    sigAESendData      = registerSignal(SIG_AE_DataSend);
    sigAEAllocResPosi  = registerSignal(SIG_AERIBD_AllocateResponsePositive);
    sigAEAllocResNega  = registerSignal(SIG_AERIBD_AllocateResponseNegative);

    //Signals that this module is processing
    lisAERcvData = new LisAEReceiveData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisAERcvData);

    //  AllocationRequest from FAI
    lisAEAllReqFromFai = new LisAEAllReqFromFai(this);
    catcher2->subscribe(SIG_FAI_AllocateRequest, lisAEAllReqFromFai);

    //  DeallocationRequest from FAI
    lisAEDeallReqFromFai = new LisAEDeallReqFromFai(this);
    catcher2->subscribe(SIG_FAI_DeallocateRequest, lisAEDeallReqFromFai);
    lisAEDeallResFromFai = new LisAEDeallReqFromFai(this);
    catcher2->subscribe(SIG_FAI_DeallocateResponse, lisAEDeallResFromFai);

    lisAEAllResPosi = new LisAEAllResPosi(this);
    catcher2->subscribe(SIG_FAI_AllocateResponsePositive, lisAEAllResPosi);

    lisAEAllResNega = new LisAEAllResNega(this);
    catcher2->subscribe(SIG_FAI_AllocateResponseNegative, lisAEAllResNega);
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

bool AE::createBindings(Flow& flow) {
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

    //Prepare flow
    Irm->newFlow(&flows.back());

    //Interconnect IRM and AE
    bool status = createBindings(flow);
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

void AE::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //M_READ_Request
    if (dynamic_cast<CDAP_M_Read*>(msg)) {
        processMRead(msg);
    }
    //M_READ_Response
    else if (dynamic_cast<CDAP_M_Read_R*>(msg)) {
        processMReadR(msg);
    }

    delete msg;
}

void AE::receiveAllocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveAllocationRequestFromFai()");
    //EV << this->getFullPath() << " received AllocationRequest from FAI" << endl;

    //TODO: Vesely - More sophisticated decission
    if (QoSRequirements.countFeasibilityScore(flow->getQosParameters()) > 0) {
        //Initialize flow within AE
        insertFlow(*flow);
        //EV << "======================" << endl << flow->info() << endl;
        //Interconnect IRM and IPC
        Irm->receiveAllocationResponsePositiveFromIpc(flow);

        this->signalizeAllocateResponsePositive(flow);
    }
    else {
        this->signalizeAllocateResponseNegative(flow);
    }
}

void AE::signalizeSendData(cMessage* msg) {
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigAESendData, msg);
}

void AE::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigAEAllocResPosi, flow);
}

void AE::receiveAllocationResponseNegative(Flow* flow) {
    Enter_Method("receiveAllocationResponseNegative()");
    //Change allocation status
    ConTab->setStatus(flow, ConnectionTableEntry::CON_ERROR);
}

void AE::receiveAllocationResponsePositive(Flow* flow) {
    Enter_Method("receiveAllocationResponsePositive()");
    //Interconnect IRM and IPC
    Irm->receiveAllocationResponsePositiveFromIpc(flow);

    //Change allocation status
    ConTab->setStatus(flow, ConnectionTableEntry::CON_CONNECTPENDING);

    //TODO: Vesely - Work with return value?
}

void AE::sendAllocationRequest(Flow* flow) {
    //TODO: Vesely - Substitute with signal
    Irm->receiveAllocationRequestFromAe(flow);
}

void AE::sendDeallocationRequest(Flow* flow) {
    //TODO: Vesely - Substitute with signal
    Irm->receiveDeallocationRequestFromAe(flow);
}

void AE::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigAEAllocResNega, flow);
}

void AE::sendData(Flow* flow, CDAPMessage* msg) {
    //Retrieve handle from ConTab record
    ConnectionTableEntry* cte = ConTab->findEntryByFlow(flow);
    if (cte && cte->getNorthGateIn()) {
        msg->setHandle(cte->getNorthGateIn()->getIndex());
        //Pass Data to CDAP
        signalizeSendData(msg);
    }
    else {
        EV << "Sending data before flow is allocated!" << endl;
        delete msg;
    }
}

void AE::processMRead(CDAPMessage* msg) {

}

void AE::receiveDeallocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveDeallocationRequestFromFai()");

    bool status;
    status = deleteBindings(*flow);

    status = Irm->deleteBindings(flow);

    EV << "Statusak> " << status;
}

bool AE::deleteBindings(Flow& flow) {
    EV << this->getFullPath() << " deleted bindings" << endl;

    int handle = -1;
    ConnectionTableEntry* cte = ConTab->findEntryByFlow(&flow);
    if (cte && cte->getNorthGateIn())
        handle = cte->getNorthGateIn()->getIndex();

    //Disconnect gates
    cGate* gIrmIn = Irm->gateHalf(GATE_AEIO, cGate::INPUT, handle);
    cGate* gIrmOut = Irm->gateHalf(GATE_AEIO, cGate::OUTPUT, handle);

    //Get AE gates
    cGate* gAeIn = this->getParentModule()->gateHalf(GATE_DATAIO, cGate::INPUT, handle);
    cGate* gAeOut = this->getParentModule()->gateHalf(GATE_DATAIO, cGate::OUTPUT, handle);;

    //CDAPParent Module gates
    cGate* gCdapParentIn = Cdap->gateHalf(GATE_SOUTHIO, cGate::INPUT, handle);
    cGate* gCdapParentOut = Cdap->gateHalf(GATE_SOUTHIO, cGate::OUTPUT, handle);

    //CDAPSplitter gates
    cModule* CdapSplit = Cdap->getSubmodule(MOD_CDAPSPLIT);
    cGate* gSplitIn = CdapSplit->gateHalf(GATE_SOUTHIO, cGate::INPUT, handle);
    cGate* gSplitOut = CdapSplit->gateHalf(GATE_SOUTHIO, cGate::OUTPUT, handle);

    cGate* gSplitCaceIn = CdapSplit->gateHalf(GATE_CACEIO, cGate::INPUT, handle);
    cGate* gSplitCaceOut = CdapSplit->gateHalf(GATE_CACEIO, cGate::OUTPUT, handle);

    cGate* gSplitAuthIn = CdapSplit->gateHalf(GATE_AUTHIO, cGate::INPUT, handle);
    cGate* gSplitAuthOut = CdapSplit->gateHalf(GATE_AUTHIO, cGate::OUTPUT, handle);

    cGate* gSplitCdapIn = CdapSplit->gateHalf(GATE_CDAPIO, cGate::INPUT, handle);
    cGate* gSplitCdapOut = CdapSplit->gateHalf(GATE_CDAPIO, cGate::OUTPUT, handle);


    //CACE Module gates
    cModule* CdapCace = Cdap->getSubmodule(MOD_CDAPCACE);
    cGate* gCaceIn = CdapCace->gateHalf(GATE_SPLITIO, cGate::INPUT, handle);
    cGate* gCaceOut = CdapCace->gateHalf(GATE_SPLITIO, cGate::OUTPUT, handle);

    //AUTH Module gates
    cModule* CdapAuth = Cdap->getSubmodule(MOD_CDAPAUTH);
    cGate* gAuthIn = CdapAuth->gateHalf(GATE_SPLITIO, cGate::INPUT, handle);
    cGate* gAuthOut = CdapAuth->gateHalf(GATE_SPLITIO, cGate::OUTPUT, handle);

    //CDAP Module gates
    cModule* CdapCdap = Cdap->getSubmodule(MOD_CDAPCDAP);
    cGate* gCdapIn = CdapCdap->gateHalf(GATE_SPLITIO, cGate::INPUT, handle);
    cGate* gCdapOut = CdapCdap->gateHalf(GATE_SPLITIO, cGate::OUTPUT, handle);

    //Disconnect gates
    gIrmOut->disconnect();
    gAeIn->disconnect();
    gCdapParentIn->disconnect();
    gSplitIn->disconnect();

    gSplitOut->disconnect();
    gCdapParentOut->disconnect();
    gAeOut->disconnect();
    gIrmIn->disconnect();

    gSplitCaceOut->disconnect();
    gCaceIn->disconnect();
    gCaceOut->disconnect();
    gSplitCaceIn->disconnect();

    gSplitAuthOut->disconnect();
    gAuthIn->disconnect();
    gAuthOut->disconnect();
    gSplitAuthIn->disconnect();

    gSplitCdapOut->disconnect();
    gCdapIn->disconnect();
    gCdapOut->disconnect();
    gSplitCdapIn->disconnect();

    //Return true if all dynamically created gates are disconnected
    return !gIrmIn->isConnected() && !gIrmOut->isConnected()
            && !gAeIn->isConnected() && !gAeOut->isConnected()
            && !gCdapParentIn->isConnected() && !gCdapParentOut->isConnected()
            && !gSplitIn->isConnected() && !gSplitOut->isConnected()
            && !gSplitCaceIn->isConnected() && !gSplitCaceOut->isConnected()
            && !gSplitAuthIn->isConnected() && !gSplitAuthOut->isConnected()
            && !gSplitCdapIn->isConnected() && !gSplitCdapOut->isConnected();
}

void AE::processMReadR(CDAPMessage* msg) {

}
