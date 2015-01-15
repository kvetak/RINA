//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#include "FAI.h"

const char*     TIM_CREREQ          = "CreateRequestTimer";

Define_Module(FAI);

FAI::FAI() : FAIBase() {
}

FAI::~FAI() {
    this->FaModule = NULL;
    this->FlowObject = NULL;
}

void FAI::initialize() {
    portId = par(PAR_PORTID);
    cepId  = par(PAR_CEPID);

    creReqTimeout = par(PAR_CREREQTIMEOUT).doubleValue();
    creReqTimer = new cMessage(TIM_CREREQ);

    initSignalsAndListeners();

//    this->efcp = (EFCP*)(getParentModule()->getParentModule()->getSubmodule("efcp"));
}

void FAI::postInitialize(FABase* fa, Flow* fl, EFCP* efcp) {
    //Initialize pointers! It cannot be done during model creation :(
    this->FaModule = fa;
    this->FlowObject = fl;
    this->efcp = efcp;
    //this->sigFAIAllocReq = sigAlReq;
}

bool FAI::receiveAllocateRequest() {
    Enter_Method("receiveAllocateRequest()");
    //Invoke NewFlowReqPolicy
    bool status = this->FaModule->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createEFCPI();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    //EV << "!!!!!!" << FlowObject->info() << endl << FlowObject->getDstNeighbor() << endl;

    // bind this flow to a suitable (N-1)-flow
    RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");
    status = raModule->bindNFlowToNM1Flow(FlowObject);
    //IF flow is already available then schedule M_Create(Flow)
    if (status) {
        this->signalizeCreateFlowRequest();
    }
    //Everything went fine
    return true;
}

bool FAI::processDegenerateDataTransfer() {
    return true;
}

bool FAI::receiveAllocateResponsePositive() {
    Enter_Method("receiveAllocateResponsePositive()");

    //Instantiate EFCPi
    bool status = this->createEFCPI();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        //Schedule negative M_Create_R(Flow)
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    //Interconnect IPC <-> EFCPi <-> RMT
    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        //Schedule M_Create_R(Flow-)
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    // bind this flow to a suitable (N-1)-flow
    RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");
    raModule->bindNFlowToNM1Flow(FlowObject);

    //Signalizes M_Create_R(flow)
    this->signalizeCreateFlowResponsePositive();
    return true;
}

void FAI::receiveAllocateResponseNegative() {
    this->signalizeCreateFlowResponseNegative();
}

bool FAI::receiveCreateRequest() {
    Enter_Method("receiveCreateRequest()");
    //Invoke NewFlowReqPolicy
    bool status = this->FaModule->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        //Schedule negative M_Create_R(Flow)
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    //Create IPC north gates
    createNorthGates();

    //Pass AllocationRequest to AP or RMT
    this->signalizeAllocationRequestFromFai();

    //Everything went fine
    return true;
}

bool FAI::receiveDeallocateRequest() {
    Enter_Method("receiveDeallocateRequest()");

    //deleteBindings
    bool status = this->deleteBindings();

    //Signalize M_Delete(Flow)
    this->signalizeDeleteFlowRequest();

    return status;
}

void FAI::receiveDeleteRequest() {
    Enter_Method("receiveDeleteRequest()");
    FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::DEALLOC_PEND);

    //Notify application
    signalizeDeallocateRequestFromFai();

    //DeleteBindings
    this->deleteBindings();

    //Signalizes M_Delete_R(Flow)
    this->signalizeDeleteFlowResponse();

    FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::DEALLOCATED);
}

bool FAI::receiveCreateResponseNegative() {
    Enter_Method("receiveCreResNegative()");

    //invokeAllocateRetryPolicy
    bool status = this->invokeAllocateRetryPolicy();

    //If number of retries IS NOT reached THEN ...
    if (status) {
        signalizeCreateFlowRequest();
    }
    //...otherwise signalize to AE or RIBd failure
    else  {
        EV << "invokeAllocateRetryPolicy() failed"  << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
    }

    return status;
}

bool FAI::receiveCreateResponsePositive(Flow* flow) {
    Enter_Method("receiveCreResPositive()");
    //XXX: Vesely - D-Base-2011-015.pdf, p.9
    //              Create bindings. WTF? Bindings should be already created!''

    cancelEvent(creReqTimer);

    //Change dstCep-Id and dstPortId according to new information
    FlowObject->getConnectionId().setDstCepId(flow->getConId().getDstCepId());
    FlowObject->setDstPortId(flow->getDstPortId());

    //Change status
    FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_POSI);

    //Pass Allocate Response to AE or RIBd
    this->signalizeAllocateResponsePositive();

    //FIXME: Vesely - always true
    return true;
}

void FAI::receiveDeleteResponse() {
    //Notify application
    signalizeDeallocateRequestFromFai();

    FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::DEALLOCATED);
}

void FAI::handleMessage(cMessage *msg) {
    //CreateRequest was not delivered in time
    if ( !strcmp(msg->getName(), TIM_CREREQ) ) {
        //Increment and resend
        bool status = receiveCreateResponseNegative();
        if (status)
            signalizeCreateFlowRequest();
    }

}

std::string FAI::info() const {
    std::stringstream os;
    os << "FAI>\tPort-ID: " << this->portId << "\tCEP-ID: " << this->cepId;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai) {
    return os << fai.info();
}

bool FAI::createEFCPI() {
    EV << this->getFullPath() << " attempts to create EFCP instance" << endl;
    EFCPInstance* efcpi = efcp->createEFCPI(this->getFlow(), cepId);
    return efcpi ? true : false;
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << portId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();

    //IF called as consequence of AllocateRequest then createNorthGate
    //ELSE (called as consequence of CreateRequestFlow) skip
    if (!IPCModule->hasGate(nameIpcDown.str().c_str()))
        createNorthGates();

    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << cepId;
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //IPCModule.northIo <--> Efcp.fai
    gateEfcpUpOut->connectTo(gateIpcDownOut);
    gateIpcDownIn->connectTo(gateEfcpUpIn);

    //Create bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".relayAndMux.rmt");
    rmtModule->createEfcpiGate(cepId);

    std::ostringstream nameRmtUp;
    nameRmtUp << GATE_EFCPIO_ << cepId;
    cGate* gateRmtUpIn = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::INPUT);
    cGate* gateRmtUpOut = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpDown;
    nameEfcpDown << GATE_RMT_ << cepId;
    cGate* gateEfcpDownIn = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::INPUT);
    cGate* gateEfcpDownOut = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::OUTPUT);

    //Efcp.rmt <--> Rmt.efcpIo
    gateRmtUpOut->connectTo(gateEfcpDownIn);
    gateEfcpDownOut->connectTo(gateRmtUpIn);

    return gateEfcpDownIn->isConnected() && gateEfcpDownOut->isConnected()
           && gateEfcpUpIn->isConnected() && gateEfcpUpOut->isConnected()
           && gateRmtUpIn->isConnected() && gateRmtUpOut->isConnected();

}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to disconnect bindings between EFCP, IPC and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << portId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << this->getFlow()->getConId().getSrcCepId();
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //Flush All messages in EFCPI
    efcp->deleteEFCPI(this->getFlow());

    //IPCModule.northIo <- XX -> Efcp.fai
    gateEfcpUpIn->disconnect();
    gateEfcpUpOut->disconnect();
    gateIpcDownOut->disconnect();
    gateIpcDownIn->disconnect();

    //Delete bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".relayAndMux.rmt");

    std::ostringstream nameRmtUp;
    nameRmtUp << GATE_EFCPIO_ << this->getFlow()->getConId().getSrcCepId();
    cGate* gateRmtUpIn = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::INPUT);
    cGate* gateRmtUpOut = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpDown;
    nameEfcpDown << GATE_RMT_ << this->getFlow()->getConId().getSrcCepId();
    cGate* gateEfcpDownIn = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::INPUT);
    cGate* gateEfcpDownOut = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::OUTPUT);

    //Efcp.rmt <- XX -> Rmt.efcpIo
    gateRmtUpOut->disconnect();
    gateRmtUpIn->disconnect();
    gateEfcpDownIn->disconnect();
    gateEfcpDownOut->disconnect();

    rmtModule->deleteEfcpiGate(cepId);

    return true;
}

bool FAI::invokeAllocateRetryPolicy() {
    //Increase CreateFlowRetries
    cancelEvent(creReqTimer);
    //int hops = this->getFlow()->getCreateFlowRetries();
    this->getFlow()->setCreateFlowRetries( this->getFlow()->getCreateFlowRetries() + 1 );
    //Compare whether the limit is reached
    return ( this->getFlow()->getCreateFlowRetries() <= this->getFlow()->getMaxCreateFlowRetries() );
}

void FAI::initSignalsAndListeners() {
    cModule* catcher2 = this->getParentModule()->getParentModule();
    cModule* catcher3 = this->getParentModule()->getParentModule()->getParentModule();
    //Signals that module emits
    sigFAIAllocReq      = registerSignal(SIG_FAI_AllocateRequest);
    sigFAIDeallocReq    = registerSignal(SIG_FAI_DeallocateRequest);
    sigFAIDeallocRes    = registerSignal(SIG_FAI_DeallocateResponse);
    sigFAIAllocResPosi  = registerSignal(SIG_FAI_AllocateResponsePositive);
    sigFAIAllocResNega  = registerSignal(SIG_FAI_AllocateResponseNegative);
    sigFAICreReq        = registerSignal(SIG_FAI_CreateFlowRequest);
    sigFAIDelReq        = registerSignal(SIG_FAI_DeleteFlowRequest);
    sigFAIDelRes        = registerSignal(SIG_FAI_DeleteFlowResponse);
    sigFAICreResNega    = registerSignal(SIG_FAI_CreateFlowResponseNegative);
    sigFAICreResPosi    = registerSignal(SIG_FAI_CreateFlowResponsePositive);

    //Signals that module processes
    //  AllocationRequest
    this->lisAllocReq       = new LisFAIAllocReq(this);
    catcher3->subscribe(SIG_toFAI_AllocateRequest, this->lisAllocReq);
    //  AllocationRespNegative
    this->lisAllocResNega   = new LisFAIAllocResNega(this);
    catcher3->subscribe(SIG_toFAI_AllocateResponseNegative, this->lisAllocResNega);
    //  AllocationRespPositive
    this->lisAllocResPosi   = new LisFAIAllocResPosi(this);
    catcher3->subscribe(SIG_AERIBD_AllocateResponsePositive, this->lisAllocResPosi);
//    //  CreateFlowRequest
//    this->lisCreReq         = new LisFAICreReq(this);
//    catcher->subscribe(SIG_FAI_CreateFlowRequest, this->lisCreReq);
    //  CreateFlowResponseNegative
    this->lisCreResNega     = new LisFAICreResNega(this);
    catcher3->subscribe(SIG_RIBD_CreateFlowResponseNegative, this->lisCreResNega);
    // CreateFlowResponsePositive
    this->lisCreResPosi     = new LisFAICreResPosi(this);
    catcher3->subscribe(SIG_RIBD_CreateFlowResponsePositive, this->lisCreResPosi);

    //  CreateFlowResponseNegative
    lisCreResNegaNmO     = new LisFAICreResNegaNminusOne(this);
    catcher3->subscribe(SIG_RIBD_CreateFlowResponseNegative, lisCreResNegaNmO);
    // CreateFlowResponsePositive
    lisCreResPosiNmO     = new LisFAICreResPosiNminusOne(this);
    catcher3->subscribe(SIG_RIBD_CreateFlowResponsePositive, lisCreResPosiNmO);

    //DeleteRequestFlow
    lisDelReq = new LisFAIDelReq(this);
    catcher2->subscribe(SIG_RIBD_DeleteRequestFlow, lisDelReq);

    //DeleteResponseFlow
    lisDelRes = new LisFAIDelRes(this);
    catcher2->subscribe(SIG_RIBD_DeleteResponseFlow, lisDelRes);

}

void FAI::signalizeCreateFlowRequest() {
    //Start timer
    scheduleAt(simTime() + creReqTimeout, creReqTimer);
    //Signalize RIBd to send M_CREATE(flow)
    emit(this->sigFAICreReq, FlowObject);
}

void FAI::signalizeDeleteFlowResponse() {
    emit(this->sigFAIDelRes, this->FlowObject);

}

void FAI::signalizeCreateFlowResponsePositive() {
    emit(this->sigFAICreResPosi, FlowObject);
}

void FAI::signalizeCreateFlowResponseNegative() {
    emit(this->sigFAICreResNega, FlowObject);
}

void FAI::signalizeAllocationRequestFromFai() {
    emit(sigFAIAllocReq, FlowObject);
}

void FAI::signalizeDeleteFlowRequest() {
    emit(this->sigFAIDelReq, this->FlowObject);
}

void FAI::signalizeAllocateResponseNegative() {
    emit(this->sigFAIAllocResNega, this->FlowObject);
}

void FAI::signalizeDeallocateRequestFromFai() {
    emit(this->sigFAIDeallocReq, this->FlowObject);
}

void FAI::signalizeDeallocateResponseFromFai() {
    emit(this->sigFAIDeallocRes, this->FlowObject);
}

void FAI::signalizeAllocateResponsePositive() {
    emit(this->sigFAIAllocResPosi, this->FlowObject);
}

void FAI::createNorthGates() {
    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << portId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    IPCModule->addGate(nameIpcDown.str().c_str(), cGate::INOUT, false);
}

void FAI::receiveCreateFlowResponsePositiveFromNminusOne() {
    //Schedule M_Create(Flow)
    this->signalizeCreateFlowRequest();
}

void FAI::receiveCreateFlowResponseNegativeFromNminusOne() {
    this->signalizeAllocateResponseNegative();
}

