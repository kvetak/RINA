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

#include "AE.h"

Define_Module(AE);

AE::AE() :
        Irm(NULL), Cdap(NULL)
{
    FlowObject = NULL;
    connectionState = NIL;
}

AE::~AE() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
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
    sigAEConReq        = registerSignal(SIG_AE_ConnectionRequest);
    sigAERelReq        = registerSignal(SIG_AE_ReleaseRequest);


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
    //WATCH_LIST(flows);
    WATCH(FlowObject);
    WATCH(connectionState);
}

void AE::handleMessage(cMessage* msg) {
}

bool AE::createBindings(Flow& flow) {
    EV << this->getFullPath() << " created bindings and registered a new flow" << endl;
    //Create new gates
    cGate* gIrmIn;
    cGate* gIrmOut;
    Irm->getOrCreateFirstUnconnectedGatePair(GATE_AEIO, false, true, *&gIrmIn, *&gIrmOut);

    cModule* IrmMod = Irm->getParentModule();
    cGate* gIrmModIn;
    cGate* gIrmModOut;
    IrmMod->getOrCreateFirstUnconnectedGatePair(GATE_NORTHIO, false, true, *&gIrmModIn, *&gIrmModOut);

    cModule* ApMon = this->getParentModule()->getParentModule();
    cGate* gApIn;
    cGate* gApOut;
    ApMon->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gApIn, *&gApOut);

    //Get AE gates
    cGate* gAeIn = this->getParentModule()->gateHalf(GATE_AEIO, cGate::INPUT);
    cGate* gAeOut = this->getParentModule()->gateHalf(GATE_AEIO, cGate::OUTPUT);

    //CDAPParent Module gates
    cGate* gCdapParentIn = Cdap->gateHalf(GATE_SOUTHIO, cGate::INPUT);
    cGate* gCdapParentOut = Cdap->gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    //Connect gates together
    gIrmOut->connectTo(gIrmModOut);
    gIrmModOut->connectTo(gApIn);
    gApIn->connectTo(gAeIn);
    gAeIn->connectTo(gCdapParentIn);

    gCdapParentOut->connectTo(gAeOut);
    gAeOut->connectTo(gApOut);
    gApOut->connectTo(gIrmModIn);
    gIrmModIn->connectTo(gIrmIn);

    //Set north-half of the routing in ConnectionTable
    Irm->setNorthGates(&flow, gIrmIn, gIrmOut);

    //Return true if all dynamically created gates have same index
    return gIrmIn->isConnected()
           && gAeIn->isConnected()
           && gIrmModIn->isConnected()
           && gApIn->isConnected();
}

void AE::initPointers() {
    Irm = dynamic_cast<IRM*>(this->getParentModule()->getParentModule()->getParentModule()->getSubmodule(MOD_IPCRESMANAGER)->getSubmodule(MOD_IRM));
    Cdap = this->getParentModule()->getSubmodule(MOD_CDAP);

    if (!Irm || !Cdap)
        error("Pointers to Irm or ConnectionTable or Cdap are not initialized!");
}

void AE::insertFlow() {
    //Add a new flow to

    //Prepare flow
    Irm->newFlow(FlowObject);

    //Interconnect IRM and AE
    bool status = createBindings(*FlowObject);
    if (!status) {
        error("Gate inconsistency during creation of a new flow!");
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

    if ( QoSRequirements.compare(flow->getQosRequirements()) ) {
        //Initialize flow within AE
        FlowObject = flow;
        insertFlow();
        //EV << "======================" << endl << flow->info() << endl;
        //Interconnect IRM and IPC

        Irm->receiveAllocationResponsePositiveFromIpc(flow) ?
                Irm->changeStatus(FlowObject, ConnectionTableEntry::CON_CONNECTPENDING)
                :
                Irm->changeStatus(FlowObject, ConnectionTableEntry::CON_ERROR);

        //Change connection status
        changeConStatus(CONNECTION_PENDING);
        this->signalizeAllocateResponsePositive(FlowObject);
    }
    else {
        EV << "QoS Requirement cannot be met, please check AE attributes!" << endl;
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
    Irm->changeStatus(flow, ConnectionTableEntry::CON_ERROR);

    deleteBindings(*FlowObject);

    //Change connection status
    changeConStatus(NIL);
}

void AE::receiveAllocationResponsePositive(Flow* flow) {
    Enter_Method("receiveAllocationResponsePositive()");
    //Interconnect IRM and IPC
    Irm->receiveAllocationResponsePositiveFromIpc(flow);

    //Change allocation status
    Irm->changeStatus(flow, ConnectionTableEntry::CON_CONNECTPENDING);

    //Change connection status
    changeConStatus(CONNECTION_PENDING);
}

void AE::sendAllocationRequest(Flow* flow) {
    //TODO: Vesely - Substitute with signal
    Irm->receiveAllocationRequestFromAe(flow);

    //Change connection status
    changeConStatus(FLOW_PENDING);
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
    int handle = Irm->getIrmGateHandle(flow);
    if (handle != VAL_UNDEF_HANDLE) {
        //Pass Data to CDAP
        //Connection/Release or send data msg
        if (dynamic_cast<CDAP_M_Connect*>(msg) != NULL &&
                getConStatus() == CONNECTION_PENDING){
            signalizeConnectionRequest(msg);
        }
        else if(dynamic_cast<CDAP_M_Release*>(msg) != NULL){
            signalizeReleaseRequest(msg);
            changeConStatus(RELEASING);
        }
        else if(getConStatus() == ESTABLISHED
                //TODO: Vesely - Ugly hack to support old AE wo Establishment. Should be removed sooner or later
                || getConStatus() == CONNECTION_PENDING
                ){
            signalizeSendData(msg);
        }
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
    if (!status) {
        EV << "deleteBindings() failed during DeallocateRequest processing!" << endl;
        return;
    }

    status = Irm->deleteBindings(flow);
    if (!status) {
        EV << "IRM.deleteBindings() failed during DeallocateRequest processing!" << endl;
        return;
    }

    //EV << "Statusak> " << status;
}

bool AE::deleteBindings(Flow& flow) {
    EV << this->getFullPath() << " deleted bindings" << endl;

    int handle1 = Irm->getIrmGateHandle(&flow);
    int handle2 = Irm->getApGateHandle(&flow);
    if (handle1 == VAL_UNDEF_HANDLE)
        error("Delete gates before flow allocation is impossible!");

    //Disconnect gates
    cGate* gIrmIn = Irm->gateHalf(GATE_AEIO, cGate::INPUT, handle1);
    cGate* gIrmOut = Irm->gateHalf(GATE_AEIO, cGate::OUTPUT, handle1);

    cModule* IrmMod = Irm->getParentModule();
    cGate* gIrmModIn = IrmMod->gateHalf(GATE_NORTHIO,cGate::INPUT, handle1);
    cGate* gIrmModOut = IrmMod->gateHalf(GATE_NORTHIO,cGate::OUTPUT, handle1);

    cModule* ApMon = this->getParentModule()->getParentModule();
    cGate* gApIn = ApMon->gateHalf(GATE_SOUTHIO,cGate::INPUT, handle2);
    cGate* gApOut = ApMon->gateHalf(GATE_SOUTHIO,cGate::OUTPUT, handle2);

    //Get AE gates
    cGate* gAeIn = this->getParentModule()->gateHalf(GATE_AEIO, cGate::INPUT);
    cGate* gAeOut = this->getParentModule()->gateHalf(GATE_AEIO, cGate::OUTPUT);

    //CDAPParent Module gates
    cGate* gCdapParentIn = Cdap->gateHalf(GATE_SOUTHIO, cGate::INPUT);
    cGate* gCdapParentOut = Cdap->gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    //Disconnect gates
    gIrmOut->disconnect();
    gIrmModOut->disconnect();
    gApIn->disconnect();
    gAeIn->disconnect();
    gCdapParentIn->disconnect();

    gCdapParentOut->disconnect();
    gAeOut->disconnect();
    gApOut->disconnect();
    gIrmModIn->disconnect();
    gIrmIn->disconnect();

    //Return true if all dynamically created gates are disconnected
    return !gIrmIn->isConnected() && !gIrmOut->isConnected()
            && !gAeIn->isConnected() && !gAeOut->isConnected()
            && !gCdapParentIn->isConnected() && !gCdapParentOut->isConnected();
}

void AE::processMReadR(CDAPMessage* msg) {

}

void AE::signalizeConnectionRequest(CDAPMessage* msg){
    emit(sigAEConReq, msg);
}

void AE::signalizeReleaseRequest(CDAPMessage* msg){
    emit(sigAERelReq, msg);
}
