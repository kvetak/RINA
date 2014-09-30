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

FAI::FAI() : FlowObject(NULL) {
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
        //Send negative response
        this->signalizeAllocateResponseNegative();
        return false;
    }
    //EV << "A jsme tam!" << endl;

    status = this->createEFCP();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
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
    bool status = this->createEFCP();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
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
        //Schedule negative M_Crete_R(Flow)
        return false;
    }
    //Pass AllocationRequest to IRM
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

bool FAI::receiveCreateResponseNegative() {
    //invokeAllocateRetryPolicy
    bool status = this->invokeAllocateRetryPolicy();
    if (!status)
    {
        EV << "invokeAllocateRetryPolicy() failed"  << endl;
        this->signalizeAllocateResponseNegative();
    }
    return status;
}

bool FAI::receiveCreateResponsePositive() {
    //TODO: Vesely - WTF? Bindings should be already created!
    //Create bindings
    //Pass Allocate Response to srcApp
    this->signalizeAllocateResponsePositive();
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
    efcp->createEFCPI(this->getFlow());

    return true; //TODO return true
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO << portId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    IPCModule->addGate(nameIpcDown.str().c_str(), cGate::INOUT, false);
    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO << this->getFlow()->getConId().getSrcCepId();
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //IPCModule.northIo <--> Efcp.fai
    gateEfcpUpOut->connectTo(gateIpcDownOut);
    gateIpcDownIn->connectTo(gateEfcpUpIn);

    //Create bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".rmt.rmt");
    rmtModule->createEfcpiGate(this->getFlow()->getConId().getSrcCepId());

    std::ostringstream nameRmtUp;
    nameRmtUp << GATE_EFCPIO << this->getFlow()->getConId().getSrcCepId();
    cGate* gateRmtUpIn = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::INPUT);
    cGate* gateRmtUpOut = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpDown;
    nameEfcpDown << GATE_RMT << this->getFlow()->getConId().getSrcCepId();
    cGate* gateEfcpDownIn = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::INPUT);
    cGate* gateEfcpDownOut = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::OUTPUT);

    //Efcp.rmt <--> Rmt.efcpIo
    gateRmtUpOut->connectTo(gateEfcpDownIn);
    gateEfcpDownOut->connectTo(gateRmtUpIn);

    return gateIpcDownIn->isConnected() && gateIpcDownOut->isConnected()
           && gateEfcpDownIn->isConnected() && gateEfcpDownOut->isConnected()
           && gateEfcpUpIn->isConnected() && gateEfcpUpOut->isConnected()
           && gateRmtUpIn->isConnected() && gateRmtUpOut->isConnected();
}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to delete bindings between EFCP, IPC and RMT" << endl;

    std::ostringstream nam1;
    nam1 << GATE_EFCPIO << cepId;
    cGate* g1i = this->gateHalf(nam1.str().c_str(), cGate::INPUT);
    cGate* g1o = this->gateHalf(nam1.str().c_str(), cGate::OUTPUT);

    std::ostringstream nam23;
    nam23 << "appIo_" << portId;
    cGate* g2i = this->gateHalf(nam23.str().c_str(), cGate::INPUT);
    cGate* g2o = this->gateHalf(nam23.str().c_str(), cGate::OUTPUT);

    cModule* FAModule = FaModule->getParentModule();
    cGate* g3i = FAModule->gateHalf(nam23.str().c_str(), cGate::INPUT);
    cGate* g3o = FAModule->gateHalf(nam23.str().c_str(), cGate::OUTPUT);

    std::ostringstream nam4;
    nam4 << GATE_NORTHIO << portId;
    cModule* IPCModule = FAModule->getParentModule();
    cGate* g4i = IPCModule->gateHalf(nam4.str().c_str(), cGate::INPUT);
    cGate* g4o = IPCModule->gateHalf(nam4.str().c_str(), cGate::OUTPUT);

    g1o->disconnect();
    g2o->disconnect();
    g3o->disconnect();
    g4o->disconnect();

    g1i->disconnect();
    g2i->disconnect();
    g3i->disconnect();
    g4i->disconnect();

    this->deleteGate(nam1.str().c_str());
    this->deleteGate(nam23.str().c_str());
    FAModule->deleteGate(nam23.str().c_str());
    IPCModule->deleteGate(nam4.str().c_str());

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
    catcher->subscribe(SIG_toFAI_AllocateResponsePositive, this->lisAllocResPosi);
//    //  CreateFlowRequest
//    this->lisCreReq         = new LisFAICreReq(this);
//    catcher->subscribe(SIG_FAI_CreateFlowRequest, this->lisCreReq);
//    //  CreateFlowResponseNegative
//    this->lisCreResNega     = new LisFAICreResNega(this);
//    catcher->subscribe(SIG_FAI_CreateFlowResponseNegative, this->lisCreResNega);
//    // CreateFlowResponsePositive
//    this->lisCreResPosi     = new LisFAICreResPosi(this);
//    catcher->subscribe(SIG_FAI_CreateFlowResponsePositive, this->lisCreResPosi);
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
    emit(this->sigFAIAllocReq, this->FlowObject);
}

void FAI::signalizeDeleteFlowRequest() {
    emit(this->sigFAIDelReq, this->FlowObject);
}

void FAI::signalizeAllocateResponseNegative() {
    emit(this->sigFAIAllocResNega, this->FlowObject);
}

void FAI::signalizeAllocateResponsePositive() {
    emit(this->sigFAIAllocResNega, this->FlowObject);
}

