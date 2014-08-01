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


#include "IRM.h"

Define_Module(IRM);

IRM::IRM() {
}

IRM::~IRM() {
}

void IRM::initialize() {
    this->initSignalsAndListeners();

}

void IRM::handleMessage(cMessage* msg) {

}

void IRM::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigIRMAllocReq      = registerSignal(SIG_IRM_AllocateRequest);
    sigIRMDeallocReq    = registerSignal(SIG_IRM_DeallocateRequest);
    sigIRMAllocResPosi  = registerSignal(SIG_IRM_AllocateResponsePositive);
    sigIRMAllocResNega  = registerSignal(SIG_IRM_AllocateResponseNegative);

    //Signals that this module is processing
    //  AllocationResponseNegative from FA
    lisAllocResNegaFa = new LisIRMAllocResNegaFa(this);
    catcher->subscribe(SIG_FA_AllocateResponseNegative, this->lisAllocResNegaFa);
    //  AllocationResponseNegative from FAI
    lisAllocResNegaFai = new LisIRMAllocResNegaFai(this);
    catcher->subscribe(SIG_FAI_AllocateResponseNegative, this->lisAllocResNegaFai);
    //  AllocationRequest from FAI
    this->lisAllocReqFai = new LisIRMAllocReqFai(this);
    catcher->subscribe(SIG_FAI_AllocateRequest, this->lisAllocReqFai);
    //  Allocate Request from App
    this->lisAllocReq = new LisIRMAllocReq(this);
    catcher->subscribe(SIG_AE_AllocateRequest, this->lisAllocReq);
    //  Deallocate Request from App
    this->lisDeallocReq = new LisIRMDeallocReq(this);
    catcher->subscribe(SIG_AE_DeallocateRequest, this->lisDeallocReq);
}

void IRM::receiveAllocationRequest(cObject* obj) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received Allocation Request" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    signalizeAllocateRequest(fl);
}

void IRM::receiveDeallocationRequest(cObject* obj) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocationRequest" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    signalizeDeallocateRequest(fl);
}


void IRM::receiveAllocationResponseNegativeAppNotFound(cObject* obj) {
    EV << this->getFullPath() << " received Negative Allocation Response App not found" << endl;
}

void IRM::receiveAllocationResponseNegative(cObject* obj) {
    //Flow* fl = dynamic_cast<Flow*>(obj);
    EV << this->getFullPath() << " received Negative Allocation Response" << endl;
}

void IRM::receiveAllocationRequestFromFAI(cObject* obj) {
    //EV << this->getFullPath() << " received AllocationRequest from FAI" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    //TODO: Vesely - Simulate AllocationResponses
    if (true) {
        this->signalizeAllocateResponsePositive(fl);
    }
    else {
        this->signalizeAllocateResponseNegative(fl);
    }
}

void IRM::signalizeAllocateRequest(Flow* flow) {
    //EV << "!!!!VYemitovano" << endl;
    //EV << "Emits AllocReq Flow = " << flow->getSrcApni() << "_" << flow->getDstApni() << endl;
    emit(sigIRMAllocReq, flow);
}

void IRM::signalizeDeallocateRequest(Flow* flow) {
    emit(sigIRMDeallocReq, flow);
}

void IRM::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigIRMAllocResPosi, flow);
}

void IRM::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigIRMAllocResNega, flow);
}
