//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file FAI.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */
#include "FAI.h"

Define_Module(FAI);

FAI::FAI() : FAIBase() {
}

FAI::~FAI() {
    this->FaModule = NULL;
    this->FlowObject = NULL;
}

void FAI::initialize() {
    this->portId = par("portId");
    this->cepId  = par("cepId");
    this->initSignalsAndListeners();

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
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_POSI);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createEFCP();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_POSI);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_POSI);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    //Schedule M_Create(Flow)
    this->signalizeCreateFlowRequest();

    //Everything went fine
    return true;
}

bool FAI::processDegenerateDataTransfer() {
    return true;
}

bool FAI::receiveAllocateResponsePositive() {
    Enter_Method("receiveAllocateResponsePositive()");

    //Instantiate EFCPi
    bool status = this->createEFCP();
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
    this->signalizeAllocationRequestFromFAI();

    //Everything went fine
    return true;
}

void FAI::receiveDeallocateRequest() {
    Enter_Method("receiveDeallocateRequest()");
    //deleteBindings
    this->deleteBindings();
    //Signalize M_Delete(Flow)
    this->signalizeDeleteFlowRequest();
}

void FAI::receiveDeleteRequest() {
    Enter_Method("receiveDeleteRequest()");
    //Notify application
    //TODO: Vesely
    //DeleteBindings
    this->deleteBindings();
    //Signalizes M_Delete(Flow)
    this->signalizeDeleteFlowResponse();
}

bool FAI::receiveCreateResponseNegative(Flow* flow) {
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
    //              Create bindings. WTF? Bindings should be already created!

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
    this->FaModule->deinstantiateFai(this->FlowObject);
}

void FAI::handleMessage(cMessage *msg) {

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

bool FAI::createEFCP() {
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
    //FIXME: Vesely @Marek -> How come that I cannot replace this->getFlow()->getConId().getSrcCepId() with cepID???!!!!
    //XXX:   Vesely @Marek -> 15.10.2014, stale tady ta sracka je :-) ... uklidit!
    nameEfcpNorth << GATE_APPIO_ << cepId;
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //IPCModule.northIo <--> Efcp.fai
    gateEfcpUpOut->connectTo(gateIpcDownOut);
    gateIpcDownIn->connectTo(gateEfcpUpIn);

    //Create bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".rmt.rmt");
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

    //FIXME: Vesely - IPC gate checks are failing. Why?
    //return gateIpcDownIn->isConnected() && gateIpcDownOut->isConnected()
    return gateEfcpDownIn->isConnected() && gateEfcpDownOut->isConnected()
           && gateEfcpUpIn->isConnected() && gateEfcpUpOut->isConnected()
           && gateRmtUpIn->isConnected() && gateRmtUpOut->isConnected();

}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to delete bindings between EFCP, IPC and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << portId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    IPCModule->addGate(nameIpcDown.str().c_str(), cGate::INOUT, false);
    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << this->getFlow()->getConId().getSrcCepId();
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //IPCModule.northIo <- XX -> Efcp.fai
    gateEfcpUpOut->disconnect();
    gateIpcDownOut->disconnect();
    gateIpcDownIn->disconnect();
    gateEfcpUpIn->disconnect();

    //Create bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".rmt.rmt");

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
    gateEfcpDownIn->disconnect();
    gateEfcpDownOut->disconnect();
    gateRmtUpIn->disconnect();

    return true;
}

bool FAI::invokeAllocateRetryPolicy() {
    //Increase CreateFlowRetries
    //int hops = this->getFlow()->getCreateFlowRetries();
    this->getFlow()->setCreateFlowRetries( this->getFlow()->getCreateFlowRetries() + 1 );
    //Compare whether the limit is reached
    return ( this->getFlow()->getCreateFlowRetries() <= this->getFlow()->getMaxCreateFlowRetries() );
}

void FAI::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule()->getParentModule();
    //Signals that module emits
    sigFAIAllocReq      = registerSignal(SIG_FAI_AllocateRequest);
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
    catcher->subscribe(SIG_toFAI_AllocateRequest, this->lisAllocReq);
    //  AllocationRespNegative
    this->lisAllocResNega   = new LisFAIAllocResNega(this);
    catcher->subscribe(SIG_toFAI_AllocateResponseNegative, this->lisAllocResNega);
    //  AllocationRespPositive
    this->lisAllocResPosi   = new LisFAIAllocResPosi(this);
    catcher->subscribe(SIG_AERIBD_AllocateResponsePositive, this->lisAllocResPosi);
//    //  CreateFlowRequest
//    this->lisCreReq         = new LisFAICreReq(this);
//    catcher->subscribe(SIG_FAI_CreateFlowRequest, this->lisCreReq);
    //  CreateFlowResponseNegative
    this->lisCreResNega     = new LisFAICreResNega(this);
    catcher->subscribe(SIG_RIBD_CreateFlowResponseNegative, this->lisCreResNega);
    // CreateFlowResponsePositive
    this->lisCreResPosi     = new LisFAICreResPosi(this);
    catcher->subscribe(SIG_RIBD_CreateFlowResponsePositive, this->lisCreResPosi);
//    // CreateFlowDeleteRequest
//    this->lisDelReq         = new LisFAIDelReq(this);
//    catcher->subscribe(SIG_FAI_DeleteFlowRequest, this->lisDelReq);
//    // CreateFlowDeleteResponse
//    this->lisDelRes         = new LisFAIDelRes(this);
//    catcher->subscribe(SIG_FAI_DeleteFlowResponse, this->lisDelRes);
}

void FAI::signalizeCreateFlowRequest() {
    emit(this->sigFAICreReq, this->FlowObject);
}

void FAI::signalizeDeleteFlowResponse() {
    emit(this->sigFAIDelReq, this->FlowObject);

}

void FAI::signalizeCreateFlowResponsePositive() {
    emit(this->sigFAICreResPosi, this->FlowObject);
}

void FAI::signalizeCreateFlowResponseNegative() {
    emit(this->sigFAICreResNega, this->FlowObject);
}

void FAI::signalizeAllocationRequestFromFAI() {
    emit(sigFAIAllocReq, FlowObject);
}

void FAI::signalizeDeleteFlowRequest() {
    emit(this->sigFAIDelReq, this->FlowObject);
}

void FAI::signalizeAllocateResponseNegative() {
    emit(this->sigFAIAllocResNega, this->FlowObject);
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
