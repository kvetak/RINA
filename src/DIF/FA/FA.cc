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

#include "Common/Flow.h"
#include "Common/RINASignals.h"
#include "DAF/DA/DA.h"
#include "DIF/EFCP/EFCP.h"
#include "DIF/Enrollment/Enrollment.h"
#include "DIF/Enrollment/EnrollmentStateTable.h"
#include "DIF/FA/FAI.h"
#include "DIF/FA/NFlowTable.h"
#include "DIF/FA/NewFlowRequest/NewFlowRequestBase.h"
#include "DIF/RA/RABase.h"

//Constants
const char* MOD_NEFFLOWREQPOLICY = "newFlowRequestPolicy";

// Signals that this module emits
const simsignal_t FA::createRequestForwardSignal = registerSignal(SIG_FA_CreateFlowRequestForward);
const simsignal_t FA::createResponseNegativeSignal = registerSignal(SIG_FA_CreateFlowResponseNegative);

Define_Module(FA);

void FA::initPointers() {
    nFlowTable = getRINAModule<NFlowTable*>(this, 1, {MOD_NFLOWTABLE});
    efcp = getRINAModule<EFCP*>(this, 2, {MOD_EFCP, MOD_EFCP});

    difAllocator = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});
    nFloReqPolicy = getRINAModule<NewFlowRequestBase*>(this, 1, {MOD_NEFFLOWREQPOLICY});
    raModule = getRINAModule<RABase*>(this, 2, {MOD_RESALLOC, MOD_RA});
    enrollment = getRINAModule<Enrollment*>(this, 2, {MOD_ENROLLMENTMODULE, MOD_ENROLLMENT});
    enrollmentStateTable = getRINAModule<EnrollmentStateTable*>(this, 2, {MOD_ENROLLMENTMODULE, MOD_ENROLLMENTTABLE});
}

void FA::initSignalsAndListeners() {
    // tbh should be N-1 IPC Process
    cModule* catcher3 = this->getModuleByPath("^.^.^");

    //AllocateResponsePositive
    catcher3->subscribe(FAI::allocateResponsePositiveSignal, this);
}

void FA::initialize(int stage) {
    if (stage == 0) {
        initPointers();
        initSignalsAndListeners();

        //Setup MyAddress
        initMyAddress();
    }
}
//XXX: Vesely - Dirty! Needs refactoring...
const Address FA::getAddressFromDa(const APN& apn, bool useNeighbor, bool isMgmtFlow) {
    Address addr;
    if (!isMgmtFlow) {
        //Ask DA which IPC to use to reach src App
        const Address* ad = difAllocator->resolveApnToBestAddress(apn, myAddress.getDifName());
        if (ad == nullptr) {
            EV << " DIF Allocator returned NULL for resolving " << apn << endl;
            return Address();
        }
        addr = *ad;
    }
    else {
        addr = Address(apn);
    }

    if (useNeighbor) {
        const APNList* apnlist = difAllocator->findApnNeighbors(addr.getApn());
        if (apnlist) {
            for (const auto &it : *apnlist) {
                Address tmp = Address(it.getName());
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
        while (!pendingFlows.empty()) {
            Flow *flow = pendingFlows.front();
            pendingFlows.pop();
            NFlowTableEntry* fte = nFlowTable->findEntryByFlow(flow);
            if (fte == nullptr) {
                EV_ERROR << "No flow table entry corresponding to pending flow!" << endl;
                continue;
            }

            if (fte->getAllocateStatus() == NFlowTableEntry::ALLOC_PEND) {
                FAIBase* fai = fte->getFai();
                if (fai != nullptr) {
                    fai->receiveAllocateRequest();
                } else {
                    EV_ERROR << "No FAI for flow with pending allocation!" << endl;
                }
            } else if (fte->getAllocateStatus() == NFlowTableEntry::FORWARDING) {
                if (raModule->bindNFlowToNM1Flow(flow)) {
                    receiveNM1FlowCreated(flow);
                } else {
                    EV << "FA waits until N-1 IPC allocates auxilliary N-1 flow" << endl;
                }
            }
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
        flow->setSrcAddr(myAddress);
    }
    else {
        //Ask DA which IPC to use to reach src App
        const Address* ad = difAllocator->resolveApnToBestAddress(flow->getSrcApni().getApn(), myAddress.getDifName());
        if (ad == nullptr) {
            EV << "difAllocator returned NULL for resolving " << flow->getSrcApni().getApn() << endl;
            return false;
        }
        Address addr = *ad;
        flow->setSrcAddr(addr);
    }
    return true;
}

bool FA::changeDstAddresses(Flow* flow, bool useNeighbor) {
    //Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(flow->getDstApni().getApn());
    if (ad == nullptr) {
        EV << "difAllocator returned NULL for resolving " << flow->getDstApni().getApn() << endl;
        return false;
    }
    Address addr = *ad;

    //...and destination addresses

    //If destination address does have neighbor then use first neighbor address
    if (useNeighbor) {
        const APNList* apnlist = difAllocator->findApnNeighbors(addr.getIpcAddress());
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
        adr = getAddressFromDa(flow->getSrcApni().getApn(), true, false);
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
    nFlowTable->insertNew(flow);

    //Change allocation status to pending
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    //Add source and destination address in case of data flow
    if (flow->getSrcAddr() == Address::UNSPECIFIED_ADDRESS
        && flow->getSrcNeighbor() == Address::UNSPECIFIED_ADDRESS) {
        setOriginalAddresses(flow);
        setNeighborAddresses(flow);
        //XXX: Vesely - Dirty! Needs refactoring...
        flow->setSrcNeighbor(flow->getSrcAddr());
    }

    //Are both Apps local? YES then Degenerate transfer
    if ( difAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
        flow->setDdtFlag(true);
    }

    //Check whether local IPCP is enrolled into DIF
    // FIXME the below statement is incorrect.
    //Successful enrollment implies existence of N-1 mgmt-flow, if not then
    //FA needs to init allocation of N-1 mgmt-flow
    if (!flow->isDdtFlag() &&
        !enrollmentStateTable->isConnectedTo(flow->getDstNeighbor().getApn())) {
        EV << "IPCP not connected to remote IPC, executing CACE" << endl;
        receiveMgmtAllocateRequest(APNamingInfo(myAddress.getApn()),
                                   APNamingInfo(flow->getDstNeighbor().getApn()));
    }

    //Is malformed?
    if (isMalformedFlow(flow)){
        nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_ERR);
        // FIXME: Shouldn't this come before an attempt to allocate management flow?
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
    if (flow->isDdtFlag() || enrollmentStateTable->isConnectedTo(flow->getDstNeighbor().getApn())) {
        status = fai->receiveAllocateRequest();
    } else {
        status = true;
        EV << "Management flow is not ready!" << endl;
    }

    //Potentially wait for response from RA, after this continue with X

    return status;
}

bool FA::receiveMgmtAllocateRequest(Flow* mgmtflow) {
    Enter_Method("receiveMgmtAllocateRequest()");
    bool status = true;
    //If N-1 mgmt-flow not ready, then allocate
    if (!raModule->hasFlow(mgmtflow->getDstAddr().getApn().getName(), VAL_MGMTQOSID)) {
        status = raModule->bindNFlowToNM1Flow(mgmtflow);
    }

    if (status) {
        // If N-1 mgmt ready, then starting enrollment procedure
        enrollment->startCACE(APNIPair(mgmtflow->getSrcApni(), mgmtflow->getDstApni()));
    }

    return status;
}

bool FA::receiveMgmtAllocateRequest(APNamingInfo src, APNamingInfo dst) {
    Enter_Method("receiveLocalMgmtAllocateRequest()");
    EV << this->getFullPath() << " received LocalMgmtAllocateRequest" << endl;

    bool status = true;
    //If N-1 mgmt-flow not ready, then allocate
    if (!raModule->hasFlow(dst.getApn().getName(), VAL_MGMTQOSID)) {
        Flow mgmtflow(src, dst);
        mgmtflow.setQosRequirements(QoSReq::MANAGEMENT);
        mgmtflow.setSrcAddr(Address(src.getApn()));
        mgmtflow.setDstAddr(Address(dst.getApn()));
        mgmtflow.setSrcNeighbor(Address(src.getApn()));
        mgmtflow.setDstNeighbor(Address(dst.getApn()));

        status = raModule->bindNFlowToNM1Flow(&mgmtflow);
    }

    if (status) {
        // If N-1 mgmt ready, then starting enrollment procedure
        enrollment->startCACE(APNIPair(src, dst));
    }

    return status;
}

bool FA::receiveMgmtAllocateFinish(APNIPair *apnip) {
    Enter_Method("receiveAllocFinishMgmt()");
    EV << "AllocFinMgmt initiated" << endl;

    TFAIPtrs entries = nFlowTable->findEntriesAffectedByMgmt(apnip);
    for (auto &entry : entries)
        pendingFlows.push(entry->getFlow());

    scheduleAt(simTime(), new cMessage(TIM_FAPENDFLOWS) );
    //TODO: Vesely - Fix unused return value
    return true;
}

bool FA::receiveCreateFlowRequestFromRibd(Flow* flow) {
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;

    //Is requested APP local?
    if ( difAllocator->isAppLocal(flow->getSrcApni().getApn()) ){
        //Check for duplicity
        if (!difAllocator->isAppLocal(flow->getDstApni().getApn())
            && nFlowTable->findEntryByInvokeId(flow->getAllocInvokeId())
            ) {
            EV << "Duplicit M_CREATE received thus ignoring!" << endl;
            return false;
        }

        //Insert new Flow into FAITable
        nFlowTable->insertNew(flow);

        //Change neighbor addresses
        setNeighborAddresses(flow);
        //XXX: Vesely - Dirty! Needs refactoring...
        flow->setSrcNeighbor(flow->getSrcAddr());

        EV << "Processing M_CREATE(flow)" << endl;
        //Change allocation status to pending
        nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

        //Create FAI
        FAI* fai = this->createFAI(flow);
        if ( difAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
            fai->setDegenerateDataTransfer(true);
            flow->setDdtFlag(true);
        }
        fai->setRemotePortId(flow->getDstPortId());
        fai->setRemoteCepId(flow->getConId().getDstCepId());

        //Update flow object
        flow->setSrcPortId(fai->getLocalPortId());
        flow->getConnectionId().setSrcCepId(fai->getLocalCepId());

        //Pass the CreateRequest to newly created FAI
        return fai->receiveCreateRequest();
    }

    //...if not then forward CreateRequest Flow to next neighbor
    // TODO split into new function, add secondary function to easily replace
    // this when the time comes
    //App is not local but it should be (based on DA)
    if (flow->getSrcAddr() == this->getMyAddress()) {
        EV << "Rejecting flow allocation, APN not present on this system!" << endl;
        emit(this->createResponseNegativeSignal, flow);
        return false;
    }

    EV << "Forwarding M_CREATE(flow)" << endl;

    //Before that reverse SRC-DST information back
    flow->swapFlow();
    //Insert new Flow into FAITable
    nFlowTable->insertNew(flow);
    //Change neighbor addresses
    setNeighborAddresses(flow);
    //Change status to forward
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::FORWARDING);

    //Decrement HopCount
    flow->setHopCount(flow->getHopCount() - 1);
    if (!flow->getHopCount()) {
        //TODO: Vesely - More granular error
        nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_ERR);
        //Schedule M_Create_R(Flow)
        EV << "Hopcount decremented to zero!" << endl;
        emit(this->createResponseNegativeSignal, flow);
        return false;
    }

    // Need to check if connected to remote application first
    if (!enrollmentStateTable->isConnectedTo(flow->getDstNeighbor().getApn())) {
        EV << "IPCP not connected to remote IPC, executing CACE" << endl;
        return receiveMgmtAllocateRequest(APNamingInfo(myAddress.getApn()),
                                          APNamingInfo(flow->getDstNeighbor().getApn()));
    }

    // bind this flow to a suitable (N-1)-flow
    bool status = raModule->bindNFlowToNM1Flow(flow);
    if (status == true) {
        // flow is already allocated
        receiveNM1FlowCreated(flow);
    }
    //else WAIT until allocation of N-1 flow is completed
    else {
        EV << "FA waits until N-1 IPC allocates auxilliary N-1 flow" << endl;
    }

    return status;
}

bool FA::receiveDeallocateRequest(Flow* flow) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocateRequest" << endl;

    //Check flow in table
    NFlowTableEntry* fte = nFlowTable->findEntryByFlow(flow);
    if (fte && fte->getFai()) {
        //Pass the request to appropriate FAI
        FAIBase* fai = fte->getFai();
        nFlowTable->changeAllocStatus(fai, NFlowTableEntry::DEALLOC_PEND);

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
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::FORWARDED);
    setNeighborAddresses(tmpfl);

    emit(this->createRequestForwardSignal, tmpfl;
}

bool FA::invokeNewFlowRequestPolicy(Flow* flow) {
    return nFloReqPolicy->run(*flow);
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
    os << (70 + nFlowTable->getSize() * 50);
    module->getDisplayString().setTagArg("p", 1, os.str().c_str());
    */

    //Prepare return pointer and setup internal FAI pointers
    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, flow, efcp);

    //Change state in FAITable
    nFlowTable->setFaiToFlow(fai, flow);
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    return fai;
}

void FA::deinstantiateFai(Flow* flow) {
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::DEINSTANTIATED);
    //TODO: Vesely
    //Prepare deinstantitation self-message
}

void FA::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *) {
    if (id != FAI::allocateResponsePositiveSignal)
        throw cRuntimeError("Flow allocator received unsupported signal type");

    EV << "Received positive allocation response from " << src->getFullPath() << endl;
    Flow *flow = dynamic_cast<Flow *>(obj);
    if (flow == nullptr) {
        throw cRuntimeError("Flow allocator received ");
    } else if (myAddress.getApn() != flow->getSrcApni().getApn()) {
        EV << "Allocation response not intended for this FA." << endl;
        return;
    } else if (flow->isManagementFlowLocalToIPCP()) {
        EV << "Management flow allocated!" << endl;
        return;
    }

    // TODO split this into separate functions
    TFAIPtrs entries = nFlowTable->findEntriesByDstNeighborAndFwd(flow->getDstApni().getApn());
    for (auto &entry : entries)
        receiveNM1FlowCreated(entry->getFlow());
}
