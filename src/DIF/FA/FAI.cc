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
const char*     MOD_ALLOCRETRYPOLICY= "allocateRetryPolicy";

Define_Module(FAI);

FAI::FAI() : FAIBase() {
}

FAI::~FAI() {
    FaModule = NULL;
    FlowObject = NULL;
    degenerateDataTransfer = false;
    localPortId     = VAL_UNDEF_PORTID;
    localCEPId      = VAL_UNDEF_CEPID;
    remotePortId    = VAL_UNDEF_PORTID;
    remoteCEPId     = VAL_UNDEF_CEPID;
    cancelAndDelete(creReqTimer);
}

void FAI::initialize() {
    localPortId  = par(PAR_LOCALPORTID);
    localCEPId   = par(PAR_LOCALCEPID);
    remotePortId = par(PAR_REMOTEPORTID);
    remoteCEPId  = par(PAR_REMOTECEPID);

    creReqTimeout = par(PAR_CREREQTIMEOUT).doubleValue();
    creReqTimer = new cMessage(TIM_CREREQ);

    AllocRetryPolicy = check_and_cast<AllocateRetryBase*>(getParentModule()->getSubmodule(MOD_ALLOCRETRYPOLICY));

    WATCH(degenerateDataTransfer);
    WATCH_PTR(FlowObject);

    initSignalsAndListeners();
}

void FAI::postInitialize(FABase* fa, Flow* fl, EFCP* efcp) {
    //Initialize pointers! It cannot be done during model creation :(
    this->FaModule = fa;
    this->FlowObject = fl;
    this->efcp = efcp;
}

bool FAI::receiveAllocateRequest() {
    Enter_Method("receiveAllocateRequest()");

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::ALLOC_PEND) {
        EV << "Cannot allocate flow which is not in pending state" << endl;
        return false;
    }
/*
    if (isDegenerateDataTransfer()) {
        createNorthGates();
        FlowObject->swapFlow();
        signalizeAllocationRequestFromFai();
        return true;
    }
*/
    //Invoke NewFlowReqPolicy
    bool status = this->FaModule->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createEFCPI();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    //EV << "!!!!!!" << FlowObject->info() << endl << FlowObject->getDstNeighbor() << endl;

    // bind this flow to a suitable (N-1)-flow
    RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");

    status = isDegenerateDataTransfer() ? true : raModule->bindNFlowToNM1Flow(FlowObject);
    //IF flow is already available then schedule M_Create(Flow)
    if (status) {
        this->signalizeCreateFlowRequest();
    }

    //Everything went fine
    return true;
}

bool FAI::receiveAllocateResponsePositive() {
    Enter_Method("receiveAllocateResponsePositive()");

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::ALLOC_PEND) {
        EV << "Cannot continue allocation of flow which is not in pending state" << endl;
        return false;
    }

    //Is Degenerate Data Transfer
    /*if (isDegenerateDataTransfer()) {
        //Invoke NewFlowReqPolicy
        bool status = this->FaModule->invokeNewFlowRequestPolicy(this->FlowObject);
        if (!status){
            EV << "invokeNewFlowPolicy() failed"  << endl;
            ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
            return false;
        }

        //Instantiate 2 EFCPIs
        status = this->createEFCPI();
        if (!status) {
            EV << "createEFCP() failed" << endl;
            ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
            return false;
        }

        status = this->createBindings();
        if (!status) {
            EV << "createBindings() failed" << endl;
            ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
            return false;
        }
    }

    //Is normal flow allocation
    else*/
    {
        //Instantiate EFCPi
        bool status = this->createEFCPI();
        if (!status) {
            EV << "createEFCP() failed" << endl;
            ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
            //Schedule negative M_Create_R(Flow)
            this->signalizeCreateFlowResponseNegative();
            return false;
        }

        //Interconnect IPC <-> EFCPi <-> RMT
        status = this->createBindings();
        if (!status) {
            EV << "createBindings() failed" << endl;
            ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
            //Schedule M_Create_R(Flow-)
            this->signalizeCreateFlowResponseNegative();
            return false;
        }

        // bind this flow to a suitable (N-1)-flow
        RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");
        status = isDegenerateDataTransfer() ? true : raModule->bindNFlowToNM1Flow(FlowObject);

        ft->changeAllocStatus(FlowObject, FAITableEntry::TRANSFER);
        //Signalizes M_Create_R(flow)
        if (status) {
            this->signalizeCreateFlowResponsePositive();
        }
    }

    return true;
}

void FAI::receiveAllocateResponseNegative() {
    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::ALLOC_PEND) {
        EV << "Cannot continue allocation of flow which is not in pending state" << endl;
        return;
    }

    ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);

    //IF it is not DDT then retry M_CREATE
    //if (!isDegenerateDataTransfer())
    this->signalizeCreateFlowResponseNegative();
}

bool FAI::receiveCreateRequest() {
    Enter_Method("receiveCreateRequest()");

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::ALLOC_PEND) {
        EV << "Cannot allocate flow which is not in pending state" << endl;
        return false;
    }

    //Invoke NewFlowReqPolicy
    bool status = this->FaModule->invokeNewFlowRequestPolicy(this->FlowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        //Schedule negative M_Create_R(Flow)
        ft->changeAllocStatus(FlowObject, FAITableEntry::ALLOC_NEGA);
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

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::DEALLOC_PEND) {
        EV << "Cannot deallocate flow which is not in deallocate pending state" << endl;
        return false;
    }

    //deleteBindings
    bool status = this->deleteBindings();

    //Signalize M_Delete(Flow)
    this->signalizeDeleteFlowRequest();

    return status;
}

void FAI::receiveDeleteRequest(Flow* flow) {
    Enter_Method("receiveDeleteRequest()");

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::TRANSFER) {
        EV << "Cannot deallocate flow which is not in transfer state" << endl;
        return;
    }

    ft->changeAllocStatus(FlowObject, FAITableEntry::DEALLOC_PEND);

    //Get deallocation invokeId from Request
    FlowObject->setDeallocInvokeId(flow->getDeallocInvokeId());

    //Notify application
    signalizeDeallocateRequestFromFai();

    //DeleteBindings
    this->deleteBindings();

    //Signalizes M_Delete_R(Flow)
    this->signalizeDeleteFlowResponse();

    ft->changeAllocStatus(FlowObject, FAITableEntry::DEALLOCATED);
    fte->setTimeDeleted(simTime());
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
    //TODO: Vesely - D-Base-2011-015.pdf, p.9
    //              Create bindings. WTF? Bindings should be already created!''

    cancelEvent(creReqTimer);

    //Change dstCep-Id and dstPortId according to new information
    FlowObject->getConnectionId().setDstCepId(flow->getConId().getDstCepId());
    FlowObject->setDstPortId(flow->getDstPortId());
    remotePortId = flow->getDstPortId();
    remoteCEPId = flow->getConId().getDstCepId();
    par(PAR_REMOTEPORTID) = remotePortId;
    par(PAR_REMOTECEPID) = remoteCEPId;

    //Change status
    FaModule->getFaiTable()->changeAllocStatus(FlowObject, FAITableEntry::TRANSFER);

    //Pass Allocate Response to AE or RIBd
    this->signalizeAllocateResponsePositive();

    //FIXME: Vesely - always true
    return true;
}

void FAI::receiveDeleteResponse() {
    Enter_Method("receiveDeleteResponse()");

    //Check for proper FSM state
    FAITable* ft = FaModule->getFaiTable();
    FAITableEntry* fte = ft->findEntryByFlow(FlowObject);
    if (fte->getAllocateStatus() != FAITableEntry::DEALLOC_PEND) {
        EV << "Cannot deallocate flow which is not in deallocatre pending state" << endl;
        return;
    }

    //Notify application
    signalizeDeallocateRequestFromFai();

    ft->changeAllocStatus(FlowObject, FAITableEntry::DEALLOCATED);
    fte->setTimeDeleted(simTime());
}

void FAI::handleMessage(cMessage *msg) {
    //CreateRequest was not delivered in time
    if ( !strcmp(msg->getName(), TIM_CREREQ) ) {
        //Increment and resend
        bool status = receiveCreateResponseNegative();
        if (!status)
            EV << "CreateRequest retries reached its maximum!" << endl;
    }
}

std::string FAI::info() const {
    std::stringstream os;
    os << "FAI>" << endl
       << "\tlocal  Port-ID: " << this->localPortId << "\tCEP-ID: " << this->localCEPId << endl
       << "\tremote Port-ID: " << this->remotePortId << "\tCEP-ID: " << this->remoteCEPId;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai) {
    return os << fai.info();
}

bool FAI::createEFCPI() {
    EV << this->getFullPath() << " attempts to create EFCP instance" << endl;
    //Create EFCPI for local bindings
    EFCPInstance* efcpi = efcp->createEFCPI(FlowObject, localCEPId, localPortId);
    /*
    //In case of DDT create another EFCPI
    if (efcpi && isDegenerateDataTransfer()) {
        Flow* flow = FlowObject->dup();
        flow->swapFlow();
        efcpi = efcp->createEFCPI(flow, remoteCEPId, remotePortId);
    }
    */
    return efcpi ? true : false;
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << localPortId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();

    //IF called as consequence of AllocateRequest then createNorthGate
    //ELSE (called as consequence of CreateRequestFlow) skip
    if (!IPCModule->hasGate(nameIpcDown.str().c_str()))
        createNorthGates();

    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << localPortId;
    cModule* efcpModule = IPCModule->getModuleByPath(".efcp");
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //IPCModule.northIo <--> Efcp.fai
    gateEfcpUpOut->connectTo(gateIpcDownOut);
    gateIpcDownIn->connectTo(gateEfcpUpIn);

    //Create bindings in RMT
    RMT* rmtModule = (RMT*) IPCModule->getModuleByPath(".relayAndMux.rmt");
    rmtModule->createEfcpiGate(localCEPId);

    std::ostringstream nameRmtUp;
    nameRmtUp << GATE_EFCPIO_ << localCEPId;
    cGate* gateRmtUpIn = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::INPUT);
    cGate* gateRmtUpOut = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpDown;
    nameEfcpDown << GATE_RMT_ << localCEPId;
    cGate* gateEfcpDownIn = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::INPUT);
    cGate* gateEfcpDownOut = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::OUTPUT);

    //Efcp.rmt <--> Rmt.efcpIo
    gateRmtUpOut->connectTo(gateEfcpDownIn);
    gateEfcpDownOut->connectTo(gateRmtUpIn);

    /*
    if (isDegenerateDataTransfer()) {
        std::ostringstream nameIpcDownRemote;
        nameIpcDownRemote << GATE_NORTHIO_ << remotePortId;

        cGate* gateIpcDownInRemote = IPCModule->gateHalf(nameIpcDownRemote.str().c_str(), cGate::INPUT);
        cGate* gateIpcDownOutRemote = IPCModule->gateHalf(nameIpcDownRemote.str().c_str(), cGate::OUTPUT);

        std::ostringstream nameEfcpNorthRemote;
        nameEfcpNorthRemote << GATE_APPIO_ << remotePortId;
        cGate* gateEfcpUpInRemote = efcpModule->gateHalf(nameEfcpNorthRemote.str().c_str(), cGate::INPUT);
        cGate* gateEfcpUpOutRemote = efcpModule->gateHalf(nameEfcpNorthRemote.str().c_str(), cGate::OUTPUT);

        //IPCModule.northIo <--> Efcp.fai
        gateEfcpUpOutRemote->connectTo(gateIpcDownOutRemote);
        gateIpcDownInRemote->connectTo(gateEfcpUpInRemote);

        //Create bindings in RMT
        rmtModule->createEfcpiGate(remoteCEPId);

        std::ostringstream nameRmtUpRemote;
        nameRmtUpRemote << GATE_EFCPIO_ << remoteCEPId;
        cGate* gateRmtUpInRemote = rmtModule->getParentModule()->gateHalf(nameRmtUpRemote.str().c_str(), cGate::INPUT);
        cGate* gateRmtUpOutRemote = rmtModule->getParentModule()->gateHalf(nameRmtUpRemote.str().c_str(), cGate::OUTPUT);

        std::ostringstream nameEfcpDownRemote;
        nameEfcpDownRemote << GATE_RMT_ << remoteCEPId;
        cGate* gateEfcpDownInRemote = efcpModule->gateHalf(nameEfcpDownRemote.str().c_str(), cGate::INPUT);
        cGate* gateEfcpDownOutRemote = efcpModule->gateHalf(nameEfcpDownRemote.str().c_str(), cGate::OUTPUT);

        //Efcp.rmt <--> Rmt.efcpIo
        gateRmtUpOutRemote->connectTo(gateEfcpDownInRemote);
        gateEfcpDownOutRemote->connectTo(gateRmtUpInRemote);
    }*/

    return gateEfcpDownIn->isConnected() && gateEfcpDownOut->isConnected()
           && gateEfcpUpIn->isConnected() && gateEfcpUpOut->isConnected()
           && gateRmtUpIn->isConnected() && gateRmtUpOut->isConnected();

}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to disconnect bindings between EFCP, IPC and RMT" << endl;

    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << localPortId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
    cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << localPortId;
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
    nameRmtUp << GATE_EFCPIO_ << localCEPId;
    cGate* gateRmtUpIn = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::INPUT);
    cGate* gateRmtUpOut = rmtModule->getParentModule()->gateHalf(nameRmtUp.str().c_str(), cGate::OUTPUT);

    std::ostringstream nameEfcpDown;
    nameEfcpDown << GATE_RMT_ << localCEPId;
    cGate* gateEfcpDownIn = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::INPUT);
    cGate* gateEfcpDownOut = efcpModule->gateHalf(nameEfcpDown.str().c_str(), cGate::OUTPUT);

    //Efcp.rmt <- XX -> Rmt.efcpIo
    gateRmtUpOut->disconnect();
    gateRmtUpIn->disconnect();
    gateEfcpDownIn->disconnect();
    gateEfcpDownOut->disconnect();

    rmtModule->deleteEfcpiGate(localCEPId);

    return true;
}

bool FAI::invokeAllocateRetryPolicy() {
    //Increase CreateFlowRetries
    cancelEvent(creReqTimer);
    return AllocRetryPolicy->run(*getFlow());
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

int FAI::getLocalCepId() const {
    return localCEPId;
}

void FAI::setLocalCepId(int localCepId) {
    localCEPId = localCepId;
}

int FAI::getLocalPortId() const {
    return localPortId;
}

void FAI::setLocalPortId(int localPortId) {
    this->localPortId = localPortId;
}

int FAI::getRemoteCepId() const {
    return remoteCEPId;
}

void FAI::setRemoteCepId(int remoteCepId) {
    remoteCEPId = remoteCepId;
}

int FAI::getRemotePortId() const {
    return remotePortId;
}

void FAI::setRemotePortId(int remotePortId) {
    this->remotePortId = remotePortId;
}

void FAI::signalizeAllocateResponsePositive() {
    emit(this->sigFAIAllocResPosi, this->FlowObject);
}

void FAI::createNorthGates() {
    std::ostringstream nameIpcDown;
    nameIpcDown << GATE_NORTHIO_ << localPortId;
    cModule* IPCModule = FaModule->getParentModule()->getParentModule();
    IPCModule->addGate(nameIpcDown.str().c_str(), cGate::INOUT, false);

/*
    if (isDegenerateDataTransfer()) {
        std::ostringstream nameIpcDownRemote;
        nameIpcDownRemote << GATE_NORTHIO_ << remotePortId;
        IPCModule->addGate(nameIpcDownRemote.str().c_str(), cGate::INOUT, false);
    }
*/
    return;
}

void FAI::receiveCreateFlowResponsePositiveFromNminusOne() {
    Enter_Method("receiveCreFlowResPositiveFromNminusOne()");
    //Schedule M_Create(Flow)
    this->signalizeCreateFlowRequest();
}

void FAI::receiveCreateFlowResponseNegativeFromNminusOne() {
    this->signalizeAllocateResponseNegative();
}

