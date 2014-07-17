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

FAI::FAI() :
//FlowAlloc(NULL),
FlowObject(NULL) {
}

FAI::~FAI() {
    // TODO Auto-generated destructor stub
}

void FAI::initialize() {
    this->portId = par("portId");
    this->cepId  = par("cepId");
}

void FAI::postInitialize(FABase* fa, Flow* fl, simsignal_t sigAlReq) {
    //Initialize pointers! It cannot be done during model creation :(
    this->FlowAlloc = fa;
    this->FlowObject = fl;
    this->sigFAIAllocReq = sigAlReq;
}

bool FAI::receiveAllocateRequest() {
    Enter_Method("receiveAllocateRequest()");
    //Is App local? YES then Degenerate transfer ELSE

    //Inove NewFlowReqPolicy
    bool status = this->FlowAlloc->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed";
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
    this->createBindings();

    //Everything went fine
    return true;
}

void FAI::processDegenerateDataTransfer() {
}

void FAI::receiveAllocateResponsePositive(cObject* obj) {

}

bool FAI::receiveCreateRequest() {
    Enter_Method("receiveCreateRequest()");
    //Invoke NewFlowReqPolicy
    bool status = this->FlowAlloc->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed";
        //Schedule negative M_Crete_R(Flow)
        return false;
    }
    //Pass AllocationRequest to IRM

    //Everything went fine
    return true;
}

void FAI::processCreateResponse() {
}

void FAI::receiveDeallocateRequest() {
    Enter_Method("receiveDeallocateRequest()");
    //deleteBindings
    this->deleteBindings();
    //signalize
    this->signalizeDeleteFlowRequest();
}

void FAI::receiveDeleteRequest() {
}

void FAI::receiveDeleteResponse() {
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
    EV << this->getFullPath() << " attempts to create EFCP instance";
    return false;
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP with FAI and RMT";
    return false;
}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to delete bindings between EFCP, FAI and RMT";
    return false;
}

void FAI::signalizeCreateFlowRequest(Flow* flow) {
    emit(this->sigFAICreReq, flow);
}

void FAI::signalizeDeleteFlowResponse(Flow* flow) {
    emit(this->sigFAIDelReq, flow);
}

void FAI::signalizeAllocationRequestFromFAI(Flow* flow) {
    emit(this->sigFAIAllocReq, flow);
}

void FAI::signalizeDeleteFlowRequest() {
}

void FAI::receiveAllocateResponseNegative() {
}
