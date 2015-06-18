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

#include "FA.h"

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
    Efcp = (EFCP*) ((getParentModule()->getParentModule()->getSubmodule(MOD_EFCP)->getSubmodule(MOD_EFCP)));

    DifAllocator = ModuleAccess<DA>(MOD_DA).get();
    NFloReqPolicy = check_and_cast<NewFlowRequestBase*>(getParentModule()->getSubmodule(MOD_NEFFLOWREQPOLICY));
}

void FA::initialize() {
    initPointers();
    initSignalsAndListeners();

    //Setup MyAddress
    initMyAddress();
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
    }

    //Are both Apps local? YES then Degenerate transfer
    if ( DifAllocator->isAppLocal( flow->getDstApni().getApn() ) ) {
        flow->setDdtFlag(true);
    }

    if ( !flow->isDdtFlag() && !N_flowTable->findMgmtEntryByDstAddr(flow->getDstAddr()) ) {
        EV << "Management flow is not present, thus allocating one first!" << endl;
        Flow* mgmtflow = flow->dupToMgmt();
        receiveLocalMgmtAllocateRequest(mgmtflow);
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

    bool status;
    //Postpone allocation request until management flow is ready
    NFlowTableEntry* fte = N_flowTable->findMgmtEntryByDstAddr(flow->getDstAddr());
    if ( flow->isDdtFlag()
         ||
         ( fte && fte->getAllocateStatus() == NFlowTableEntry::TRANSFER )
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

bool FA::receiveLocalMgmtAllocateRequest(Flow* flow) {
    Enter_Method("receiveLocalMgmtAllocateRequest()");
    EV << this->getFullPath() << " received LocalMgmtAllocateRequest" << endl;

    //Insert new Flow into FAITable
    N_flowTable->insertNew(flow);

    //Change allocation status to pending
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    //Add source and destination address in case of data flow

    flow->setSrcAddr(Address(flow->getSrcApni().getApn()));
    flow->setDstAddr(Address(flow->getDstApni().getApn()));
    setNeighborAddresses(flow);
    //flow->setSrcNeighbor(getMyAddress());
    flow->setDdtFlag(false);


    //Create FAI
    FAI* fai = this->createFAI(flow);

    fai->setDegenerateDataTransfer(flow->isDdtFlag());

    //Update flow object
    flow->setSrcPortId(fai->getLocalPortId());
    flow->getConnectionId().setSrcCepId(fai->getLocalCepId());

    bool status = fai->receiveAllocateRequest();

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
            this->signalizeCreateFlowResponseNegative(flow);
            return false;
        }

        // bind this flow to a suitable (N-1)-flow
        RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");
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

bool FA::invokeNewFlowRequestPolicy(Flow* flow) {
    return NFloReqPolicy->run(*flow);
}

FAI* FA::createFAI(Flow* flow) {
  //@Vladimir: what about using ExternConsts.cc for this?
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.src.DIF.FA.FAI");

    //Prepare parameters
    int portId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_PORTID);
    int cepId = ev.getRNG(RANDOM_NUMBER_GENERATOR)->intRand(MAX_CEPID);

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
    sigFACreReqFwd      = registerSignal(SIG_FA_CreateFlowRequestForward);
    sigFACreResPosiFwd  = registerSignal(SIG_FA_CreateFlowResponseForward);
    sigFACreResNega     = registerSignal(SIG_FA_CreateFlowResponseNegative);

    //Signals that this module is processing
    //  AllocateRequest
    this->lisAllocReq = new LisFAAllocReq(this);
    catcher3->subscribe(SIG_IRM_AllocateRequest, this->lisAllocReq);
    //  DeallocateRequest
    this->lisDeallocReq = new LisFADeallocReq(this);
    catcher3->subscribe(SIG_IRM_DeallocateRequest, this->lisDeallocReq);

    //AllocateResponsePositive
    lisCreFloPosi = new LisFACreFloPosi(this);
    catcher3->subscribe(SIG_FAI_AllocateResponsePositive, lisCreFloPosi);

    //CreateRequestFlow
    lisCreReq = new LisFACreReq(this);
    catcher2->subscribe(SIG_RIBD_CreateRequestFlow, lisCreReq);

    //Allocate after management flow is prepared (enrollment done)
    lisAllocFinMgmt = new LisFAAllocFinMgmt(this);
    //catcher2->subscribe(SIG_FAI_AllocateFinishManagement, lisAllocFinMgmt);
    catcher2->subscribe(SIG_ENROLLMENT_Finished, lisAllocFinMgmt);

}

void FA::signalizeCreateFlowRequestForward(Flow* flow) {
    emit(this->sigFACreReqFwd, flow);
}

void FA::receiveNM1FlowCreated(Flow* flow) {
    Enter_Method("receiveNM1FlowCreated()");
    EV << "Continue M_CREATE(flow) forward!" << endl;

    Flow* tmpfl = flow->dup();
    N_flowTable->changeAllocStatus(flow, NFlowTableEntry::FORWARDED);
    setNeighborAddresses(tmpfl);

    this->signalizeCreateFlowRequestForward(tmpfl);
}

void FA::signalizeCreateFlowResponseNegative(Flow* flow) {
    emit(this->sigFACreResNega, flow);
}

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
        const APNList* apnlist = DifAllocator->findApnNeigbors(addr.getApname());
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
