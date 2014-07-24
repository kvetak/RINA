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
    this->FlowAlloc = NULL;
    this->FlowObject = NULL;
}

void FAI::initialize() {
    this->portId = par("portId");
    this->cepId  = par("cepId");
    this->initSignalsAndListeners();
}

void FAI::postInitialize(FABase* fa, Flow* fl) {
    //Initialize pointers! It cannot be done during model creation :(
    this->FlowAlloc = fa;
    this->FlowObject = fl;
    //this->sigFAIAllocReq = sigAlReq;
}

bool FAI::receiveAllocateRequest() {
    Enter_Method("receiveAllocateRequest()");
    //Invoke NewFlowReqPolicy
    bool status = this->FlowAlloc->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        //Send negative response
        this->signalizeAllocateResponseNegative();
        return false;
    }
    //EV << "A jsme tam!" << endl;

    status = this->createEFCP();
    if (!status) {
        EV << "createEFCP() failed";
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed";
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
    bool status = this->FlowAlloc->invokeNewFlowRequestPolicy(this->FlowObject);
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
    this->FlowAlloc->deinstantiateFai(this->FlowObject);
}


void FAI::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv Allocate_Response

    //Receive M_Create(Flow)

    //Receive M_Create_R(Flow)

    //Receive Deallocate_Request

    //Receive M_Delete(Flow)

    //Receive M_Delete_R(Flow)

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
    return false;
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP with FAI and RMT" << endl;
    return false;
}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to delete bindings between EFCP, FAI and RMT" << endl;
    return false;
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

