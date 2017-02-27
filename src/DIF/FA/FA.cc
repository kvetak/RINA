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

#include "DIF/FA/FA.h"

//Constants
const int RANDOM_NUMBER_GENERATOR = 0;
const int MAX_PORTID = 65535;
const int MAX_CEPID  = 65535;
const char* MOD_NEFFLOWREQPOLICY = "newFlowRequestPolicy";

Define_Module(FA);

FA::FA() {
    N_flowTable = NULL;
}

FA::~FA() {
    N_flowTable = NULL;
}

void FA::initPointers() {
    N_flowTable = check_and_cast<NFlowTable*>(getParentModule()->getSubmodule(MOD_NFLOWTABLE));
    Efcp = getRINAModule<EFCP*>(this, 2, {MOD_EFCP, MOD_EFCP});

    DifAllocator = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});
    NFloReqPolicy = getRINAModule<NewFlowRequestBase*>(this, 1, {MOD_NEFFLOWREQPOLICY});
    RaModule = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});
    Enrollment = getRINAModule<EnrollmentStateTable*>(this, 2, {MOD_ENROLLMENT, MOD_ENROLLMENTTABLE});
}

void FA::initSignalsAndListeners() {
    cModule* catcher3 = this->getModuleByPath("^.^.^");
    cModule* catcher2 = this->getModuleByPath("^.^");

    //Signals that this module is emitting
    //sigFACreResPosiFwd  = registerSignal(SIG_FA_CreateFlowResponseForward);
    sigFACreReqFwd      = registerSignal(SIG_FA_CreateFlowRequestForward);
    sigFACreResNega     = registerSignal(SIG_FA_CreateFlowResponseNegative);
    sigFAAllocFinMgmt   = registerSignal(SIG_FA_MgmtFlowAllocated);

    //Signals that this module is processing
    /*
    //  AllocateRequest
    this->lisAllocReq = new LisFAAllocReq(this);
    catcher3->subscribe(SIG_IRM_AllocateRequest, this->lisAllocReq);
    //  DeallocateRequest
    this->lisDeallocReq = new LisFADeallocReq(this);
    catcher3->subscribe(SIG_IRM_DeallocateRequest, this->lisDeallocReq);
    */
    //AllocateResponsePositive
    lisCreFloPosi = new LisFACreFloPosi(this);
    catcher3->subscribe(SIG_FAI_AllocateResponsePositive, lisCreFloPosi);

    //CreateRequestFlow
    lisCreReq = new LisFACreReq(this);
    catcher2->subscribe(SIG_RIBD_CreateRequestFlow, lisCreReq);

    //Allocate after management flow is prepared (enrollment done)
    lisEnrollFin = new LisFAAllocFinMgmt(this);
    //catcher2->subscribe(SIG_FAI_AllocateFinishManagement, lisAllocFinMgmt);
    catcher2->subscribe(SIG_ENROLLMENT_Finished, lisEnrollFin);

}

void FA::initialize() {
    initPointers();
    initSignalsAndListeners();

    //Setup MyAddress
    initMyAddress();
}
//XXX: Vesely - Dirty! Needs refactoring...
const Address FA::getAddressFromDa(const APN& apn, bool useNeighbor, bool isMgmtFlow) {
    Address addr;
    if (!isMgmtFlow) {
        //Ask DA which IPC to use to reach src App
        const Address* ad = DifAllocator->resolveApnToBestAddress(apn, MyAddress.getDifName());
        if (ad == NULL) {
            EV << "DifAllocator returned NULL for resolving " << apn << endl;
            return Address();
        }
        addr = *ad;
    }
    else {
        addr = Address(apn);
    }
    if (useNeighbor) {
        const APNList* apnlist = DifAllocator->findApnNeigbors(addr.getApn());
        if (apnlist) {
            for (ApnCItem it = apnlist->begin(); it != apnlist->end(); ++it) {
                Address tmp = Address(it->getName());
                //EV << "!!!!!" << tmp << endl;
                if (addr.getDifName() == tmp.getDifName()) {
                    addr = tmp;
                    break;
                }
            }
        }
    }
    return addr;
}
bool FA::isMalformedFlow(Flow* flow) {
    //TODO: Vesely - Simulate malformed
    if ( !strcmp(flow->getDstApni().getApn().getName().c_str(), "AppMALFORMED") )
        return true;
    return false;
}

void FA::handleMessage(cMessage *msg) {
    if ( msg->isSelfMessage() && !opp_strcmp(msg->getName(), TIM_FAPENDFLOWS) ) {
        while (!PendingFlows.empty()) {
            NFlowTableEntry* fte = N_flowTable->findEntryByFlow(PendingFlows.front());
            if (fte && fte->getFai()) {
                FAIBase* fai = fte->getFai();
                if (fai) {
                    fai->receiveAllocateRequest();
                }
            }
            PendingFlows.pop_front();
        }
        cancelAndDelete(msg);
    }
    else
    {
        EV << "Unsupported message received by FA " << getFullName() << endl;
    }
}

bool FA::changeSrcAddress(Flow* flow, bool useNeighbor) {
    //Add source...
    if (!useNeighbor) {
        flow->setSrcAddr(MyAddress);
    }
    else {
        //Ask DA which IPC to use to reach src App
        const Address* ad = DifAllocator->resolveApnToBestAddress(flow->getSrcApni().getApn(), MyAddress.getDifName());
        if (ad == NULL) {
            EV << "DifAllocator returned NULL for resolving " << flow->getSrcApni().getApn() << endl;
            return false;
        }
        Address addr = *ad;
        flow->setSrcAddr(addr);
    }
    return true;
}

bool FA::changeDstAddresses(Flow* flow, bool useNeighbor) {
    //Ask DA which IPC to use to reach dst App
    const Address* ad = DifAllocator->resolveApnToBestAddress(flow->getDstApni().getApn());
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << flow->getDstApni().getApn() << endl;
        return false;
    }
    Address addr = *ad;

    //...and destination addresses

    //If destination address does have neighbor then use first neighbor address
    if (useNeighbor) {
        const APNList* apnlist = DifAllocator->findApnNeigbors(addr.getIpcAddress());
        if (apnlist)
            addr.setIpcAddress(apnlist->front());
    }

    flow->setDstAddr(addr);

    return true;
}

//XXX: Vesely - Dirty! Needs refactoring...
bool FA::setOriginalAddresses(Flow* flow) {
    Address adr = getAddressFromDa(flow->getSrcApni().getApn(), false, false);
    if (adr.isUnspecified())
        return false;
    flow->setSrcAddr(adr);

    adr = getAddressFromDa(flow->getDstApni().getApn(), false, false);
    if (adr.isUnspecified())
        return false;
    flow->setDstAddr(adr);
    return true;
}
//XXX: Vesely - Dirty! Needs refactoring...
bool FA::setNeighborAddresses(Flow* flow) {
    Address adr;
    if (!flow->isManagementFlowLocalToIPCP()) {
        adr = getAddressFromDa(flow->getSrcApni().getApn(), true, flow->isManagementFlowLocalToIPCP());
        if (adr.isUnspecified())
            return false;
        flow->setSrcNeighbor(adr);
    }

    adr = getAddressFromDa(flow->getDstApni().getApn(), true, flow->isManagementFlowLocalToIPCP());
    if (adr.isUnspecified())
        return false;
    flow->setDstNeighbor(adr);
    return true;
}

bool FA::receiveAllocateRequest(Flow* flow) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received AllocateRequest" << endl;

    //Insert new Flow into FAITable
    N_flowTable->insertNew(flow);

    //Change allocation status to pending
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    //Add source and destination address in case of data flow
    if (flow->getSrcAddr() == Address::UNSPECIFIED_ADDRESS
        && flow->getSrcNeighbor() == Address::UNSPECIFIED_ADDRESS) {
        setOriginalAddresses(flow);
        setNeighborAddresses(flow);
        //XXX: Vesely - Dirty! Needs refactoring...
        flow->setSrcNeighbor(flow->getSrcAddr());
    }

    //Are both Apps local? YES then Degenerate transfer
    if ( DifAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
        flow->setDdtFlag(true);
    }

    //Check whether local IPCP is enrolled into DIF
    //Successful enrollment implies existence of N-1 mgmt-flow, if not then
    //FA needs to init allocation of N-1 mgmt-flow
    if (!flow->isDdtFlag() && !Enrollment->isEnrolled(MyAddress.getApn())) {
        EV << "IPCP not enrolled to DIF, thus executing enrollment!" << endl;
        receiveMgmtAllocateRequest(APNamingInfo(MyAddress.getApn()), APNamingInfo(flow->getDstNeighbor().getApn()));
    }

    //Is malformed?
    if (isMalformedFlow(flow)){
        N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_ERR);
        //TODO: Vesely - What about special signal for errors????
        //this->signalizeAllocateResponseNegative(fl);
        return false;
    }

    //Create FAI
    FAI* fai = this->createFAI(flow);
    fai->setDegenerateDataTransfer(flow->isDdtFlag());

    //Update flow object
    flow->setSrcPortId(fai->getLocalPortId());
    flow->getConnectionId().setSrcCepId(fai->getLocalCepId());

    //Postpone allocation request until management flow is ready
    bool status;
    if ( flow->isDdtFlag() || Enrollment->isEnrolled(MyAddress.getApn())
       ){
        status = fai->receiveAllocateRequest();
    }
    else
    {
        status = true;
        EV << "Management flow is not ready!" << endl;
    }

    //Potentially wait for response from RA, after this continue with X

    return status;
}

bool FA::receiveMgmtAllocateRequest(Flow* mgmtflow) {
    bool status = true;
    //If N-1 mgmt-flow not ready, then allocate
    if (!RaModule->hasFlow(mgmtflow->getDstAddr().getApn().getName(), VAL_MGMTQOSID)) {
        status = RaModule->bindNFlowToNM1Flow(mgmtflow);
    }

    //If N-1 mgmt ready, then starting enrollment procedure
    APNIPair* apnip = new APNIPair(mgmtflow->getSrcApni(), mgmtflow->getDstApni());
    if (status) {
        emit(sigFAAllocFinMgmt, apnip);
    }

    return status;
}

bool FA::receiveMgmtAllocateRequest(APNamingInfo src, APNamingInfo dst) {
    Enter_Method("receiveLocalMgmtAllocateRequest()");
    EV << this->getFullPath() << " received LocalMgmtAllocateRequest" << endl;

    Flow* mgmtflow = new Flow(src, dst);
    mgmtflow->setQosRequirements(QoSReq::MANAGEMENT);
    mgmtflow->setSrcAddr(Address(src.getApn()));
    mgmtflow->setDstAddr(Address(dst.getApn()));
    mgmtflow->setSrcNeighbor(Address(src.getApn()));
    mgmtflow->setDstNeighbor(Address(dst.getApn()));

    bool status = true;
    //If N-1 mgmt-flow not ready, then allocate
    if (!RaModule->hasFlow(mgmtflow->getDstAddr().getApn().getName(), VAL_MGMTQOSID)) {
        status = RaModule->bindNFlowToNM1Flow(mgmtflow);
    }

    //If N-1 mgmt ready, then starting enrollment procedure
    APNIPair* apnip = new APNIPair(mgmtflow->getSrcApni(), mgmtflow->getDstApni());
    if (status) {
        emit(sigFAAllocFinMgmt, apnip);
    }

    return status;
}

bool FA::receiveMgmtAllocateFinish() {
    Enter_Method("receiveAllocFinishMgmt()");
    scheduleAt(simTime(), new cMessage(TIM_FAPENDFLOWS) );
    //TODO: Vesely - Fix unused return value
    return true;
}

bool FA::receiveCreateFlowRequestFromRibd(Flow* flow) {
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;

    bool status;

    //Is requested APP local?
    if ( DifAllocator->isAppLocal(flow->getSrcApni().getApn()) ){
        //Check for duplicity
        if (!DifAllocator->isAppLocal(flow->getDstApni().getApn())
            && N_flowTable->findEntryByInvokeId(flow->getAllocInvokeId())
            ) {
            EV << "Duplicit M_CREATE received thus ignoring!" << endl;
            return false;
        }

        //Insert new Flow into FAITable
        N_flowTable->insertNew(flow);

        //Change neighbor addresses
        //if (!flow->isManagementFlowLocalToIPCP()) {
            setNeighborAddresses(flow);
            //XXX: Vesely - Dirty! Needs refactoring...
            flow->setSrcNeighbor(flow->getSrcAddr());
        //}

        EV << "Processing M_CREATE(flow)" << endl;
        //Change allocation status to pending
        N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

        //Create FAI
        FAI* fai = this->createFAI(flow);
        if ( DifAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
            fai->setDegenerateDataTransfer(true);
            flow->setDdtFlag(true);
        }
        fai->setRemotePortId(flow->getDstPortId());
        fai->setRemoteCepId(flow->getConId().getDstCepId());

        //Update flow object
        flow->setSrcPortId(fai->getLocalPortId());
        flow->getConnectionId().setSrcCepId(fai->getLocalCepId());

        //Pass the CreateRequest to newly created FAI
        status = fai->receiveCreateRequest();

    }
    //...if not then forward CreateRequest Flow to next neighbor
    else {
        //App is not local but it should be (based on DA)
        if (flow->getSrcAddr() == this->getMyAddress()) {
            EV << "Rejecting flow allocation, APN not present on this system!" << endl;
            this->signalizeCreateFlowResponseNegative(flow);
            return false;
        }
        //
        else {
            EV << "Forwarding M_CREATE(flow)" << endl;

            //Before that reverse SRC-DST information back
            flow->swapFlow();
            //Insert new Flow into FAITable
            N_flowTable->insertNew(flow);
            //Change neighbor addresses
            setNeighborAddresses(flow);
            //Change status to forward
            N_flowTable->changeAllocStatus(flow, NFlowTableEntry::FORWARDING);

            //Decrement HopCount
            flow->setHopCount(flow->getHopCount() - 1);
            if (!flow->getHopCount()) {
                //TODO: Vesely - More granular error
                N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_ERR);
                //Schedule M_Create_R(Flow)
                EV << "Hopcount decremented to zero!" << endl;
                this->signalizeCreateFlowResponseNegative(flow);
                return false;
            }

            // bind this flow to a suitable (N-1)-flow
            RABase* raModule = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});
            status = raModule->bindNFlowToNM1Flow(flow);

            //EV << "status: " << status << endl;
            if (status == true) {
                // flow is already allocated
                receiveNM1FlowCreated(flow);
            }
            //else WAIT until allocation of N-1 flow is completed
            else {
                EV << "FA waits until N-1 IPC allocates auxilliary N-1 flow" << endl;
            }
        }
    }
    return status;
}

bool FA::receiveDeallocateRequest(Flow* flow) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocateRequest" << endl;

    //Check flow in table
    NFlowTableEntry* fte = N_flowTable->findEntryByFlow(flow);
    if (fte && fte->getFai()) {
        //Pass the request to appropriate FAI
        FAIBase* fai = fte->getFai();
        N_flowTable->changeAllocStatus(fai, NFlowTableEntry::DEALLOC_PEND);

        fai->receiveDeallocateRequest();
        return true;
    }
    else {
        if (!fte)
            EV << "Flow or FAI not found in FAITable!" << endl;
        else if (fte->getAllocateStatus() != NFlowTableEntry::TRANSFER)
            EV << "Cannot deallocate flow which is not in tranfer phase!" << endl;
        return false;
    }
}

void FA::receiveNM1FlowCreated(Flow* flow) {
    Enter_Method("receiveNM1FlowCreated()");
    EV << "Continue M_CREATE(flow) forward!" << endl;

    Flow* tmpfl = flow->dup();
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::FORWARDED);
    setNeighborAddresses(tmpfl);

    this->signalizeCreateFlowRequestForward(tmpfl);
}

bool FA::invokeNewFlowRequestPolicy(Flow* flow) {
    return NFloReqPolicy->run(*flow);
}

FAI* FA::createFAI(Flow* flow) {
  //@Vladimir: what about using ExternConsts.cc for this?
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.src.DIF.FA.FAI");

    //Prepare parameters
    int portId = getEnvir()->getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_PORTID);
    int cepId = getEnvir()->getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_CEPID);

    //Create a name
    std::ostringstream ostr;
    ostr << "fai_" << portId << "_" << cepId;

    //Instantiate module
    cModule *module = moduleType->create(ostr.str().c_str(), this->getParentModule());
    module->par(PAR_LOCALPORTID) = portId;
    module->par(PAR_LOCALCEPID) = cepId;
    //module->par(PAR_CREREQTIMEOUT) = par(PAR_CREREQTIMEOUT).doubleValue();
    module->finalizeParameters();
    module->buildInside();

    // create activation message
    module->scheduleStart(simTime());
    module->callInitialize();

    //Layouting
    /*
    module->getDisplayString().setTagArg("p", 0, "100");
    std::ostringstream os;
    os << (70 + N_flowTable->getSize() * 50);
    module->getDisplayString().setTagArg("p", 1, os.str().c_str());
    */

    //Prepare return pointer and setup internal FAI pointers
    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, flow, Efcp);

    //Change state in FAITable
    N_flowTable->setFaiToFlow(fai, flow);
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    return fai;
}

void FA::deinstantiateFai(Flow* flow) {
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::DEINSTANTIATED);
    //TODO: Vesely
    //Prepare deinstantitation self-message
}

void FA::signalizeCreateFlowRequestForward(Flow* flow) {
    emit(this->sigFACreReqFwd, flow);
}

void FA::signalizeCreateFlowResponseNegative(Flow* flow) {
    emit(this->sigFACreResNega, flow);
}
