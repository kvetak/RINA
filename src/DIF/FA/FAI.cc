// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/FA/FAI.h"

#include "Common/RINASignals.h"
#include "DIF/FA/FABase.h"
#include "DIF/RA/RABase.h"
#include "DIF/RMT/RMT.h"
#include "DIF/FA/NFlowTable.h"
#include "DIF/EFCP/EFCP.h"
#include "DIF/FA/AllocateRetry/AllocateRetryBase.h"

const char*     TIM_CREREQ          = "CreateRequestTimer";
const char*     MOD_ALLOCRETRYPOLICY= "allocateRetryPolicy";

Define_Module(FAI);

FAI::FAI()
    : FAIBase(),
      localPortId(VAL_UNDEF_PORTID),
      localCEPId(VAL_UNDEF_PORTID),
      remotePortId(VAL_UNDEF_PORTID),
      remoteCEPId(VAL_UNDEF_CEPID),
      efcp(nullptr),
      fa(nullptr)
{
}

FAI::~FAI() {
    if (lisDelRes != nullptr) {
        delete lisAllocResNega;
        delete lisAllocResPosi;
        delete lisCreResNega;
        delete lisCreResPosi;
        delete lisCreResNegaNmO;
        delete lisCreResPosiNmO;
        delete lisDelReq;
        delete lisDelRes;
    }
}

void FAI::initialize() {
    localPortId  = par(PAR_LOCALPORTID);
    localCEPId   = par(PAR_LOCALCEPID);
    remotePortId = par(PAR_REMOTEPORTID);
    remoteCEPId  = par(PAR_REMOTECEPID);

    AllocRetryPolicy = getRINAModule<AllocateRetryBase*>(this, 1, {MOD_ALLOCRETRYPOLICY});

    WATCH(degenerateDataTransfer);
    WATCH_PTR(flowObject);

    initSignalsAndListeners();
}

void FAI::postInitialize(FABase* fa, Flow* fl, EFCP* efcp) {
    //Initialize pointers! It cannot be done during model creation :(
    this->fa = fa;
    this->flowObject = fl;
    this->efcp = efcp;
}


bool FAI::receiveAllocateRequest() {
    Enter_Method("receiveAllocateRequest()");

    //Check for proper FSM state
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::ALLOC_PEND) {
        EV << "Cannot allocate flow which is not in pending state" << endl;
        return false;
    }

    //Invoke NewFlowReqPolicy
    bool status = this->fa->invokeNewFlowRequestPolicy(this->flowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createEFCPI();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
        return false;
    }

    // bind this flow to a suitable (N-1)-flow
    RABase* raModule = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});

    status = isDegenerateDataTransfer() ? true : raModule->bindNFlowToNM1Flow(flowObject);
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
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::ALLOC_PEND) {
        EV << "Cannot continue allocation of flow which is not in pending state" << endl;
        return false;
    }


    //Instantiate EFCPi
    bool status = this->createEFCPI();
    if (!status) {
        EV << "createEFCP() failed" << endl;
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        //Schedule negative M_Create_R(Flow)
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    //Interconnect IPC <-> EFCPi <-> RMT
    status = this->createBindings();
    if (!status) {
        EV << "createBindings() failed" << endl;
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        //Schedule M_Create_R(Flow-)
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    // bind this flow to a suitable (N-1)-flow
    RABase* raModule = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});
    status = isDegenerateDataTransfer() ? true : raModule->bindNFlowToNM1Flow(flowObject);

    ft->changeAllocStatus(flowObject, NFlowTableEntry::TRANSFER);
    //Signalizes M_Create_R(flow)
    if (status) {
        this->signalizeCreateFlowResponsePositive();
    }

    return true;
}

void FAI::receiveAllocateResponseNegative() {
    Enter_Method("receiveAllocateResponseNegative()");
    //Check for proper FSM state
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::ALLOC_PEND) {
        EV << "Cannot continue allocation of flow which is not in pending state" << endl;
        return;
    }

    ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);

    //IF it is not DDT then retry M_CREATE
    //if (!isDegenerateDataTransfer())
    this->signalizeCreateFlowResponseNegative();
}

bool FAI::receiveCreateRequest() {
    Enter_Method("receiveCreateRequest()");

    //Check for proper FSM state
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::ALLOC_PEND) {
        EV << "Cannot allocate flow which is not in pending state" << endl;
        return false;
    }

    //Invoke NewFlowReqPolicy
    bool status = this->fa->invokeNewFlowRequestPolicy(this->flowObject);
    if (!status){
        EV << "invokeNewFlowPolicy() failed"  << endl;
        //Schedule negative M_Create_R(Flow)
        ft->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        this->signalizeCreateFlowResponseNegative();
        return false;
    }

    //Create IPC north gates
    createNorthGates();

    //Pass AllocationRequest to AP or RIBd
    this->signalizeAllocationRequestFromFai();

    //Everything went fine
    return true;
}

bool FAI::receiveDeallocateRequest() {
    Enter_Method("receiveDeallocateRequest()");

    //Check for proper FSM state
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::DEALLOC_PEND) {
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
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::TRANSFER) {
        EV << "Cannot deallocate flow which is not in transfer state" << endl;
        return;
    }

    ft->changeAllocStatus(flowObject, NFlowTableEntry::DEALLOC_PEND);

    //Get deallocation invokeId from Request
    flowObject->setDeallocInvokeId(flow->getDeallocInvokeId());

    //Notify application
    signalizeDeallocateRequestFromFai();

    //DeleteBindings
    this->deleteBindings();

    //Signalizes M_Delete_R(Flow)
    this->signalizeDeleteFlowResponse();

    ft->changeAllocStatus(flowObject, NFlowTableEntry::DEALLOCATED);
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
        fa->getNFlowTable()->changeAllocStatus(flowObject, NFlowTableEntry::ALLOC_NEGA);
        this->signalizeAllocateResponseNegative();
    }

    return status;
}

bool FAI::receiveCreateResponsePositive(Flow* flow) {
    Enter_Method("receiveCreResPositive()");
    //TODO: Vesely - D-Base-2011-015.pdf, p.9
    //              Create bindings. WTF? Bindings should be already created!''

    //Change dstCep-Id and dstPortId according to new information
    flowObject->getConnectionId().setDstCepId(flow->getConId().getDstCepId());
    flowObject->setDstPortId(flow->getDstPortId());
    remotePortId = flow->getDstPortId();
    remoteCEPId = flow->getConId().getDstCepId();
    par(PAR_REMOTEPORTID) = remotePortId;
    par(PAR_REMOTECEPID) = remoteCEPId;

    //Change status
    fa->getNFlowTable()->changeAllocStatus(flowObject, NFlowTableEntry::TRANSFER);

    //Pass Allocate Response to AE or RIBd
    this->signalizeAllocateResponsePositive();

    //FIXME: Vesely - always true
    return true;
}

void FAI::receiveDeleteResponse() {
    Enter_Method("receiveDeleteResponse()");

    //Check for proper FSM state
    NFlowTable* ft = fa->getNFlowTable();
    NFlowTableEntry* fte = ft->findEntryByFlow(flowObject);
    if (fte->getAllocateStatus() != NFlowTableEntry::DEALLOC_PEND) {
        EV << "Cannot deallocate flow which is not in deallocatre pending state" << endl;
        return;
    }

    //Notify application
    signalizeDeallocateRequestFromFai();

    ft->changeAllocStatus(flowObject, NFlowTableEntry::DEALLOCATED);
    fte->setTimeDeleted(simTime());
}

void FAI::handleMessage(cMessage *msg) {
    /*
    //CreateRequest was not delivered in time
    if ( !strcmp(msg->getName(), TIM_CREREQ) ) {
        //Increment and resend
        bool status = receiveCreateResponseNegative();
        if (!status)
            EV << "CreateRequest retries reached its maximum!" << endl;
    }
    */
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
    EFCPInstance* efcpi = efcp->createEFCPI(flowObject, localCEPId, localPortId);
    return efcpi ? true : false;
}

bool FAI::createBindings() {
    EV << this->getFullPath() << " attempts to bind EFCP and RMT" << endl;

    cModule* IPCModule = fa->getModuleByPath("^.^");

    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << localPortId;
    cModule* efcpModule = getRINAModule<cModule*>(IPCModule, 0, {MOD_EFCP});
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);

    //Management Flow should be connected with RIBd
    if (flowObject->isManagementFlowLocalToIPCP()) {
        std::ostringstream ribdName;
        ribdName << GATE_EFCPIO_ << localPortId;
        cModule* ribdModule = getRINAModule<cModule*>(IPCModule, 0, {MOD_RIBDAEMON});
        cModule* ribdSplitterModule =
                getRINAModule<cModule*>(IPCModule, 0, {MOD_RIBDAEMON, MOD_RIBDSPLITTER});

        if (!ribdModule->hasGate(ribdName.str().c_str()))
            {createNorthGates();}

        cGate* gateRibdIn  = ribdModule->gateHalf(ribdName.str().c_str(), cGate::INPUT);
        cGate* gateRibdOut = ribdModule->gateHalf(ribdName.str().c_str(), cGate::OUTPUT);
        cGate* gateRibdSplitIn  = ribdSplitterModule->gateHalf(ribdName.str().c_str(), cGate::INPUT);
        cGate* gateRibdSplitOut = ribdSplitterModule->gateHalf(ribdName.str().c_str(), cGate::OUTPUT);

        //EFCPi.efcpio <--> RIBDaemon.efcpIo_ <--> RIBDaemon.ribdSplitter.efcpIo_
        gateEfcpUpOut->connectTo(gateRibdIn);
        gateRibdIn->connectTo(gateRibdSplitIn);
        gateRibdSplitOut->connectTo(gateRibdOut);
        gateRibdOut->connectTo(gateEfcpUpIn);
    }
    //Data flow
    else {
        std::ostringstream nameIpcDown;
        nameIpcDown << GATE_NORTHIO_ << localPortId;

        //IF called as consequence of AllocateRequest then createNorthGate
        //ELSE (called as consequence of CreateRequestFlow) skip
        if (!IPCModule->hasGate(nameIpcDown.str().c_str()))
            {createNorthGates();}

        cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
        cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

        //IPCModule.northIo <--> Efcp.fai
        gateEfcpUpOut->connectTo(gateIpcDownOut);
        gateIpcDownIn->connectTo(gateEfcpUpIn);
    }

    //Create bindings in RMT
    RMT* rmtModule = getRINAModule<RMT*>(IPCModule, 0, {MOD_RELAYANDMUX, MOD_RMT});
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

    return gateEfcpDownIn->isConnected() && gateEfcpDownOut->isConnected()
           && gateEfcpUpIn->isConnected() && gateEfcpUpOut->isConnected()
           && gateRmtUpIn->isConnected() && gateRmtUpOut->isConnected();

}

bool FAI::deleteBindings() {
    EV << this->getFullPath() << " attempts to disconnect bindings between EFCP, IPC and RMT" << endl;

    //Flush All messages in EFCPI
    efcp->deleteEFCPI(this->getFlow());

    //Management flow
    if (flowObject->isManagementFlowLocalToIPCP()) {
        std::ostringstream ribdName;
        ribdName << GATE_EFCPIO_ << localPortId;
        cModule* ribdModule = getRINAModule<cModule*>(this, 2, {MOD_RIBDAEMON});
        cModule* ribdSplitterModule = getRINAModule<cModule*>(this, 2, {MOD_RIBDAEMON, MOD_RIBDSPLITTER});

        cGate* gateRibdIn  = ribdModule->gateHalf(ribdName.str().c_str(), cGate::INPUT);
        cGate* gateRibdOut = ribdModule->gateHalf(ribdName.str().c_str(), cGate::OUTPUT);
        cGate* gateRibdSplitIn  = ribdSplitterModule->gateHalf(ribdName.str().c_str(), cGate::INPUT);
        cGate* gateRibdSplitOut = ribdSplitterModule->gateHalf(ribdName.str().c_str(), cGate::OUTPUT);

        gateRibdIn->disconnect();
        gateRibdOut->disconnect();
        gateRibdSplitIn->disconnect();
        gateRibdSplitOut->disconnect();
    }
    //Data flow
    else {
        cModule* IPCModule = fa->getModuleByPath("^.^");
        std::ostringstream nameIpcDown;
        nameIpcDown << GATE_NORTHIO_ << localPortId;
        cGate* gateIpcDownIn = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::INPUT);
        cGate* gateIpcDownOut = IPCModule->gateHalf(nameIpcDown.str().c_str(), cGate::OUTPUT);

        //IPCModule.northIo
        gateIpcDownOut->disconnect();
        gateIpcDownIn->disconnect();
    }

    //Delete EFCP bindings
    std::ostringstream nameEfcpNorth;
    nameEfcpNorth << GATE_APPIO_ << localPortId;
    cModule* efcpModule = getRINAModule<cModule*>(this, 2, {MOD_EFCP});
    cGate* gateEfcpUpIn = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::INPUT);
    cGate* gateEfcpUpOut = efcpModule->gateHalf(nameEfcpNorth.str().c_str(), cGate::OUTPUT);
    gateEfcpUpIn->disconnect();
    gateEfcpUpOut->disconnect();

    //Delete bindings in RMT
    RMT* rmtModule = getRINAModule<RMT*>(this, 2, {MOD_RELAYANDMUX, MOD_RMT});

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
    //cancelEvent(creReqTimer);
    return AllocRetryPolicy->run(*getFlow());
}

void FAI::initSignalsAndListeners() {
    cModule* catcher2 = this->getModuleByPath("^.^");
    cModule* catcher3 = this->getModuleByPath("^.^.^");
    //Signals that module processes
    //  AllocationRespNegative
    this->lisAllocResNega   = new LisFAIAllocResNega(this);
    catcher3->subscribe(SIG_AERIBD_AllocateResponseNegative, this->lisAllocResNega);
    //  AllocationRespPositive
    this->lisAllocResPosi   = new LisFAIAllocResPosi(this);
    catcher3->subscribe(SIG_AERIBD_AllocateResponsePositive, this->lisAllocResPosi);
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
    //Signalize RIBd to send M_CREATE(flow)
    emit(this->createRequestSignal, flowObject);
}

void FAI::signalizeDeleteFlowResponse() {
    emit(this->deleteResponseSignal, this->flowObject);

}

void FAI::signalizeCreateFlowResponsePositive() {
    emit(this->createResponsePositiveSignal, flowObject);
}

void FAI::signalizeCreateFlowResponseNegative() {
    emit(this->createResponseNegativeSignal, flowObject);
}

void FAI::signalizeAllocationRequestFromFai() {
    EV << "Trying to notify " << flowObject->getSrcApni() << endl;
    emit(allocateRequestSignal, flowObject);
}

void FAI::signalizeDeleteFlowRequest() {
    emit(this->deleteRequestSignal, this->flowObject);
}

void FAI::signalizeAllocateResponseNegative() {
    emit(this->allocateResponseNegativeSignal, this->flowObject);
}

void FAI::signalizeDeallocateRequestFromFai() {
    emit(this->deallocateRequestSignal, this->flowObject);
}

void FAI::signalizeDeallocateResponseFromFai() {
    emit(this->deallocateResponseSignal, this->flowObject);
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
    emit(this->allocateResponsePositiveSignal, this->flowObject);
}

void FAI::createNorthGates() {
    //Management flow
    if (flowObject->isManagementFlowLocalToIPCP()) {
        std::ostringstream ribdName;
        ribdName << GATE_EFCPIO_ << localPortId;
        cModule* ribdModule = getRINAModule<cModule*>(this, 2, {MOD_RIBDAEMON});
        cModule* ribdSplitterModule =
                getRINAModule<cModule*>(this, 2, {MOD_RIBDAEMON, MOD_RIBDSPLITTER});
        ribdModule->addGate(ribdName.str().c_str(), cGate::INOUT, false);
        ribdSplitterModule->addGate(ribdName.str().c_str(), cGate::INOUT, false);
    }
    //Data flow
    else {
        std::ostringstream nameIpcDown;
        nameIpcDown << GATE_NORTHIO_ << localPortId;
        cModule* IPCModule = fa->getModuleByPath("^.^");
        IPCModule->addGate(nameIpcDown.str().c_str(), cGate::INOUT, false);
    }
    return;
}

void FAI::receiveCreateFlowResponsePositiveFromNminusOne() {
    Enter_Method("receiveCreFlowResPositiveFromNminusOne()");
    //Schedule M_Create(Flow)
    signalizeCreateFlowRequest();
}

void FAI::receiveCreateFlowResponseNegativeFromNminusOne() {
    this->signalizeAllocateResponseNegative();
}

