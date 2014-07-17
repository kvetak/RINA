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

Define_Module(FA);

FA::FA() {
    this->FaiTable = NULL;

}

FA::~FA() {
    this->FaiTable = NULL;
}

void FA::initialize() {
    this->FaiTable = dynamic_cast<FAITable*>( getParentModule()->getSubmodule("faiTable") );
}

void FA::receiveAllocateRequest(cObject* obj) {
    Flow* fl = dynamic_cast<Flow*>(obj);
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received AllocateRequest" << endl;
    //Insert new Flow into FAITable
    this->insertNewFTRecord(fl);
    //Is malformed?
    if (isMalformedFlow(fl)){
        FaiTable->changeAllocStatus(fl, FAITableEntry::ALLOC_ERR);
        //TODO: Vesely - What about special signal for errors????
        this->signalizeAllocateResponseNegative(fl);
        return;
    }
    //Create FAI
    FAI* fai = this->createFAI(fl);
    //Pass the AllocationRequest to newly created FAI
    bool status = fai->receiveAllocateRequest();
    //If allocation was unsuccessful then return negative response
    if (!status)
    {
        //Change allocation status to rejected
        FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_NEGA);
        //Send negative response
        this->signalizeAllocateResponseNegative(fl);
    }
    //Else wait
}

void FA::receiveCreateFlowRequest(cObject* obj) {
    Flow* fl = dynamic_cast<Flow*>(obj);
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;
    //Insert new Flow into FAITable
    this->insertNewFTRecord(fl);
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
    Flow* fl = dynamic_cast<Flow*>(obj);
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocateRequest" << endl;
    //Pass the request to appropriate FAI
    FAITableEntry* fte = FaiTable->findByFlow(fl);
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
    fai->postInitialize(this, flow, sigFAIAllocReq);
    //Change state in FAITable
    FaiTable->bindFaiToFlow(fai, flow);
    FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_PEND);
    return fai;
}


void FA::handleMessage(cMessage *msg) {
    //Rcv Allocate_Request

    //Rcv M_Create(Flow)

    //Rcv Deallocate_Request
}

bool FA::isMalformedFlow(Flow* flow) {
    //TODO: Vesely - Simulate malformed
    if ( !strcmp(flow->getDstApni().getApn().getName().c_str(), "AppERR") )
        return true;
    return false;
}

void FA::insertNewFTRecord(Flow* flow) {
    //Insert to FAITable
    FAITableEntry* fte = new FAITableEntry(flow);
    FaiTable->insert(*fte);
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
