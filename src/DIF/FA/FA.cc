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

void FA::initPointers() {
//    EV << ( dynamic_cast<FAITable*>(getParentModule()->getSubmodule(MOD_FAITABLE))
//          == ModuleAccess<FAITable>(MOD_FAITABLE).get() ) << endl;
//
//    EV << ( dynamic_cast<RABase*>(getParentModule()->getParentModule()->getSubmodule(MOD_RESALLOC)->getSubmodule(MOD_RA))
//          == ModuleAccess<RABase>(MOD_RA).get() ) << endl;
    FaiTable = ModuleAccess<FAITable>(MOD_FAITABLE).get();
    Efcp = (EFCP*) ((getParentModule()->getParentModule()->getSubmodule(MOD_EFCP)->getSubmodule(MOD_EFCP)));
    ResourceAllocator = ModuleAccess<RABase>(MOD_RA).get();
    DifAllocator = ModuleAccess<DA>(MOD_DA).get();
}

void FA::initialize() {
    initPointers();
    initSignalsAndListeners();

    //Setup MyAddress
    initMyAddress();
}

bool FA::receiveAllocateRequest(Flow* flow) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received AllocateRequest" << endl;

    //Insert new Flow into FAITable
    FaiTable->insertNew(flow);

    //Add source...
    flow->setSrcAddr(MyAddress);
    //Ask DA which IPC to use to reach dst App
    DirectoryEntry* de = DifAllocator->resolveApn(flow->getDstApni().getApn());
    if (de == NULL) {
        EV << "DA does not know target application" << endl;
        return false;
    }
    //TODO: Vesely - Now using first available APN to DIFMember mapping
    Address addr = de->getSupportedDifs().front();
    //...and destination addresses
    flow->setDstAddr(addr);

    //Is malformed?
    if (isMalformedFlow(flow)){
        FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_ERR);
        //TODO: Vesely - What about special signal for errors????
        //this->signalizeAllocateResponseNegative(fl);
        return false;
    }

    //Create FAI
    FAI* fai = this->createFAI(flow);

    //Update flow object
    flow->setSrcPortId(fai->par(PAR_PORTID));
    flow->getConnectionId().setSrcCepId(fai->par(PAR_CEPID));

    //Are both Apps local? YES then Degenerate transfer ELSE
    bool status;
    if ( DifAllocator->isAppLocal( flow->getDstApni().getApn() )
         && DifAllocator->isAppLocal( flow->getSrcApni().getApn() )
       ) {
        //Proceed with DegenerateDataTransfer
        status = fai->processDegenerateDataTransfer();
    }
    else {
        //Pass the AllocationRequest to newly created FAI
        status = fai->receiveAllocateRequest();
    }

    //Potentially wait for response from RA, after this continue with X

    return status;
}

/*
void FA::receiveAllocateResponsePositive(Flow* flow) {
    Enter_Method("receiveAllocateResponsePositive()");
    //Change status
    FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_POSI);
    //Delegate it towards FAI
    FAIBase* fai = FaiTable->findEntryByFlow(flow)->getFai();
    bool status = fai->receiveAllocateResponsePositive();
    if (!status){
        //Error occurred
        FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_ERR);
    }
}

void FA::receiveAllocateResponseNegative(Flow* flow) {
    Enter_Method("receiveAllocateResponseNegative()");
    //Change status
    FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_NEGA);
    //Delegate it towards FAI
    FAIBase* fai = FaiTable->findEntryByFlow(flow)->getFai();
    fai->receiveAllocateResponseNegative();
}
*/

void FA::receiveCreateFlowRequestFromRibd(Flow* flow) {
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;

    //Insert new Flow into FAITable
    FaiTable->insertNew(flow);

    //Is requested APP local?
    if ( DifAllocator->isAppLocal(flow->getSrcApni().getApn()) ){
        //Change allocation status to pending
        FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_PEND);

        //Create FAI
        FAI* fai = this->createFAI(flow);

        //Update flow object
        flow->setSrcPortId(fai->par(PAR_PORTID));
        flow->getConnectionId().setSrcCepId(fai->par(PAR_CEPID));

        //Pass the CreateRequest to newly created FAI
        bool status = fai->receiveCreateRequest();

        //If allocation was unsuccessful then return negative response
        if (status)
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_POSI);
        else
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_NEGA);
    }
    else {
        //Decrement HopCount
        flow->setHopCount(flow->getHopCount() - 1);
        if (flow->getHopCount()) {
            //Change status to forward
            FaiTable->changeAllocStatus(flow, FAITableEntry::FORWARDED);
            //TODO: Vesely - Forward M_Create(Flow)
            this->signalizeCreateFlowRequestForward(flow);
        }
        else {
            //TODO: Vesely - More granular error
            FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_ERR);
            //Schedule M_Create_R(Flow)
            this->signalizeCreateFlowResponseNegative(flow);
        }
    }
}

bool FA::receiveDeallocateRequest(Flow* flow) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocateRequest" << endl;
    //Pass the request to appropriate FAI
    FAITableEntry* fte = FaiTable->findEntryByFlow(flow);
    if (fte && fte->getFai()) {
        FAIBase* fai = fte->getFai();
        FaiTable->changeAllocStatus(fai, FAITableEntry::DEALLOC_PEND);
        fai->receiveDeallocateRequest();
        return true;
    }
    else {
        EV << "Flow or FAI not found in FAITable!" << endl;
        return false;
    }
}

bool FA::invokeNewFlowRequestPolicy(Flow* flow) {
    Enter_Method("invokeNewFlowRequest()");
    //Is flow policy acceptable
    std::string apname = flow->getSrcApni().getApn().getName();

    //FIXME: Vesely - Simulate error and DTCP flag better
    if ( apname.find("Err") != std::string::npos) {
        return false;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QosCubeSet cubes = ResourceAllocator->getQosCubes();
    //EV << ResourceAllocator->getQosCubes();

    unsigned short qosid = 0;
    short score = 0;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        short tmpscore = flow->getQosParameters().countFeasibilityScore(*it);
        //EV << "QosID: " << it->getQosId() << "  tmpscore: " << tmpscore << endl;
        if (score < tmpscore)
            qosid = it->getQosId();
    }

    flow->getConnectionId().setQoSId(qosid);
    return qosid ? true : false;
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

    //Instantiate module
    cModule *module = moduleType->create(ostr.str().c_str(), this->getParentModule());
    module->par(PAR_PORTID) = portId;
    module->par(PAR_CEPID) = cepId;
    module->finalizeParameters();
    module->buildInside();

    // create activation message
    module->scheduleStart(simTime());
    module->callInitialize();

    //Prepare return pointer and setup internal FAI pointers
    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, flow, Efcp);

    //Change state in FAITable
    FaiTable->bindFaiToFlow(fai, flow);
    FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_PEND);

    return fai;
}

void FA::deinstantiateFai(Flow* flow) {
    FaiTable->changeAllocStatus(flow, FAITableEntry::DEINSTANTIATED);
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

void FA::initSignalsAndListeners() {
    cModule* catcher3 = this->getParentModule()->getParentModule()->getParentModule();
    cModule* catcher2 = this->getParentModule()->getParentModule();

    //Signals that this module is emitting
    //sigFAAllocResNega   = registerSignal(SIG_FA_AllocateResponseNegative);
    //sigFAAllocResPosi   = registerSignal(SIG_FA_AllocateResponsePositive);
    sigFACreReqFwd      = registerSignal(SIG_FA_CreateFlowRequestForward);
    sigFACreResNega     = registerSignal(SIG_FA_CreateFlowResponseNegative);
    //sigFACreResPosi     = registerSignal(SIG_FA_CreateFlowResponsePositive);

    //Signals that this module is processing
    //  AllocateRequest
    this->lisAllocReq = new LisFAAllocReq(this);
    catcher3->subscribe(SIG_IRM_AllocateRequest, this->lisAllocReq);
    //  DeallocateRequest
    this->lisDeallocReq = new LisFADeallocReq(this);
    catcher3->subscribe(SIG_IRM_DeallocateRequest, this->lisDeallocReq);
    //CreateRequestFlow
    lisCreReq = new LisFACreReq(this);
    catcher2->subscribe(SIG_RIBD_CreateRequestFlow, lisCreReq);

}

/*
void FA::signalizeAllocateResponseNegative(Flow* flow) {
    emit(this->sigFAAllocResNega, flow);
}
*/

void FA::signalizeCreateFlowRequestForward(Flow* flow) {
    emit(this->sigFACreReqFwd, flow);
}

void FA::signalizeCreateFlowResponseNegative(Flow* flow) {
    emit(this->sigFACreResNega, flow);
}

