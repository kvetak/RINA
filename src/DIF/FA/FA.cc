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
 * @file FA.cpp
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */

#include "FA.h"

//Constants
const int RANDOM_NUMBER_GENERATOR = 0;
const int MAX_PORTID = 65535;
const int MAX_CEPID  = 65535;

Define_Module(FA);

FA::FA() {
    this->FaiTable = NULL;

}

FA::~FA() {
    this->FaiTable = NULL;
}

void FA::initialize() {
    this->FaiTable = dynamic_cast<FAITable*>( getParentModule()->getSubmodule("faiTable") );
    this->efcp = (EFCP*)(getParentModule()->getParentModule()->getSubmodule("efcp")->getSubmodule("efcp"));
    this->initSignalsAndListeners();
}
/**
 *
 * @param obj
 */
bool FA::receiveAllocateRequest(cObject* obj) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received AllocateRequest" << endl;

    Flow* fl = dynamic_cast<Flow*>(obj);

    //Insert new Flow into FAITable
    FaiTable->insertNew(fl);
    //Is malformed?
    if (isMalformedFlow(fl)){
        FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_ERR);
        //TODO: Vesely - What about special signal for errors????
        //this->signalizeAllocateResponseNegative(fl);
        return false;
    }
    //Create FAI
    FAI* fai = this->createFAI(fl);
    //Is App local? YES then Degenerate transfer ELSE
    bool status;
    if (this->isAppLocal(fl)) {
        //Proceed with DegenerateDataTransfer
        status = fai->processDegenerateDataTransfer();
    }
    else {
        //Pass the AllocationRequest to newly created FAI
        status = fai->receiveAllocateRequest();
    }
    //If allocation was unsuccessful then return negative response
    if (!status)
    {
        //Change allocation status to rejected
        FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_NEGA);
    }
    //Else wait


    return status;
}

void FA::receiveAllocateResponsePositive(cObject* obj) {
    Enter_Method("receiveAllocateResponsePositive()");
    Flow* fl = dynamic_cast<Flow*>(obj);
    //Change status
    FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_POSI);
    //Delegate it towards FAI
    FAI* fai = FaiTable->findEntryByFlow(fl)->getFai();
    bool status = fai->receiveAllocateResponsePositive();
    if (!status){
        //Error occurred
        FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_ERR);
    }
}

void FA::receiveAllocateResponseNegative(cObject* obj) {
    Enter_Method("receiveAllocateResponseNegative()");
    Flow* fl = dynamic_cast<Flow*>(obj);
    //Change status
    FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_NEGA);
    //Delegate it towards FAI
    FAI* fai = FaiTable->findEntryByFlow(fl)->getFai();
    fai->receiveAllocateResponseNegative();
}

void FA::receiveCreateFlowRequest(cObject* obj) {
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    //Insert new Flow into FAITable
    FaiTable->insertNew(fl);
    //Is requested APP local?
    if (true){
        //Change allocation status to rejected
        FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_PEND);
        //Create FAI
        FAI* fai = this->createFAI(fl);
        //Pass the CreateRequest to newly created FAI
        bool status = fai->receiveCreateRequest();
        //If allocation was unsuccessful then return negative response
        if (!status)
        {
            //Change allocation status to rejected
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_NEGA);
            //Send negative response
            this->signalizeAllocateResponseNegative(fl);
        }
        else {
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_POSI);
        }
    }
    else {
        //Decrement HopCount
        fl->setHopCount(fl->getHopCount() - 1);
        if (fl->getHopCount()) {
            //Change status to forward
            FaiTable->changeAllocStatus(fl, FAITableEntry::FORWARDED);
            //TODO: Vesely - Forward M_Create(Flow)
            this->signalizeCreateFlowRequestForward(fl);
        }
        else {
            //TODO: Vesely - More granular error
            FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_ERR);
            //Schedule M_Create_R(Flow)
            this->signalizeCreateFlowResponseNegative(fl);
        }
    }
}

void FA::receiveDeallocateRequest(cObject* obj) {
    Enter_Method("receiveDeallocateRequest()");
    Flow* fl = dynamic_cast<Flow*>(obj);
    EV << this->getFullPath() << " received DeallocateRequest" << endl;
    //Pass the request to appropriate FAI
    FAITableEntry* fte = FaiTable->findEntryByFlow(fl);
    FAI* fai = fte->getFai();
    fai->receiveDeallocateRequest();
}

bool FA::invokeNewFlowRequestPolicy(Flow* flow) {
    Enter_Method("invokeNewFlowRequest()");
    //Is flow policy acceptable
    //TODO: Vesely - Simulate wrong Flow
    if ( !strcmp(flow->getSrcApni().getApn().getName().c_str(), "AppH2") )
        return false;
    return true;
}

FAI* FA::createFAI(Flow* flow) {
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.DIF.FA.FAI");

    //Prepare parameters
    int portId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_PORTID);
    int cepId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_CEPID);

    //Create a name
    std::ostringstream ostr;
    ostr << "fai_" << portId << "_" << cepId;

    //Instatiate module
    cModule *module = moduleType->create(ostr.str().c_str(), this->getParentModule());
    module->par("portId") = portId;
    module->par("cepId") = cepId;
    module->finalizeParameters();
    module->buildInside();

    // create activation message
    module->scheduleStart(simTime());
    module->callInitialize();

    //Prepare return pointer and setup internal FAI pointers
    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, flow, efcp);

    //Change state in FAITable
    FaiTable->bindFaiToFlow(fai, flow);
    FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_PEND);

    //Update flow object
    flow->setSrcPortId(portId);

    return fai;
}

void FA::deinstantiateFai(Flow* flow) {
    FaiTable->changeAllocStatus(flow, FAITableEntry::DEINST_PEND);
    //TODO: Vesely
    //Prepare deinstantitation self-message
}

void FA::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request

    //Deinstantiation
    //deleteModule();
}

bool FA::isMalformedFlow(Flow* flow) {
    //TODO: Vesely - Simulate malformed
    if ( !strcmp(flow->getDstApni().getApn().getName().c_str(), "AppERR") )
        return true;
    return false;
}

bool FA::isAppLocal(Flow* flow) {
    //TODO: Vesely - Simulate localApp
    if ( !strcmp(flow->getDstApni().getApn().getName().c_str(), "App11") )
        return true;
    return false;
}

void FA::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigFAAllocResNega   = registerSignal(SIG_FA_AllocateResponseNegative);
    sigFAAllocResPosi   = registerSignal(SIG_FA_AllocateResponsePositive);
    sigFACreReqFwd      = registerSignal(SIG_FA_CreateFlowRequestForward);
    sigFACreResNega     = registerSignal(SIG_FA_CreateFlowResponseNegative);
    sigFACreResPosi     = registerSignal(SIG_FA_CreateFlowResponsePositive);

    //Signals that this module is processing
    //  AllocateRequest
    this->lisAllocReq = new LisFAAllocReq(this);
    catcher->subscribe(SIG_IRM_AllocateRequest, this->lisAllocReq);
    //  AllocateResponsePositive
    this->lisAllocResPosi = new LisFAAllocResPosi(this);
    catcher->subscribe(SIG_IRM_AllocateResponsePositive, this->lisAllocResPosi);
    //  AllocateResponseNegative
    this->lisAllocResNega = new LisFAAllocResNega(this);
    catcher->subscribe(SIG_IRM_AllocateResponseNegative, this->lisAllocResNega);
    //  DeallocateRequest
    this->lisDeallocReq = new LisFADeallocReq(this);
    catcher->subscribe(SIG_IRM_DeallocateRequest, this->lisDeallocReq);



}

void FA::signalizeAllocateResponseNegative(Flow* flow) {
    emit(this->sigFAAllocResNega, flow);
}

void FA::signalizeCreateFlowRequestForward(Flow* flow) {
    emit(this->sigFACreReqFwd, flow);
}

void FA::signalizeCreateFlowResponseNegative(Flow* flow) {
    emit(this->sigFACreResNega, flow);
}

