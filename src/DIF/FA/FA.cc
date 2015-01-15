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
    FaiTable->insertNew(flow);

    //Add source and destination address
    setOriginalAddresses(flow);
    setNeighborAddresses(flow);

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

bool FA::receiveCreateFlowRequestFromRibd(Flow* flow) {
    Enter_Method("receiveCreateFlowRequest()");
    EV << this->getFullPath() << " received CreateFlowRequest" << endl;

    bool status;

    //Is requested APP local?
    if ( DifAllocator->isAppLocal(flow->getSrcApni().getApn()) ){
        //Insert new Flow into FAITable
        FaiTable->insertNew(flow);
        //Change neighbor addresses
        setNeighborAddresses(flow);
        EV << "Processing M_Create(flow)" << endl;
        //Change allocation status to pending
        FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_PEND);

        //Create FAI
        FAI* fai = this->createFAI(flow);

        //Update flow object
        flow->setSrcPortId(fai->par(PAR_PORTID));
        flow->getConnectionId().setSrcCepId(fai->par(PAR_CEPID));

        //Pass the CreateRequest to newly created FAI
        status = fai->receiveCreateRequest();

        //If allocation was unsuccessful then return negative response
        if (status)
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_POSI);
        else
            FaiTable->changeAllocStatus(fai, FAITableEntry::ALLOC_NEGA);
    }
    //...if not then forward CreateRequest Flow to next neighbor
    else {
        EV << "Forwarding M_Create(flow)" << endl;

        //Before that reverse SRC-DST information back
        flow->swapFlow();
        //Insert new Flow into FAITable
        FaiTable->insertNew(flow);
        //Change neighbor addresses
        setNeighborAddresses(flow);
        //Change status to forward
        FaiTable->changeAllocStatus(flow, FAITableEntry::FORWARDED);

        //Decrement HopCount
        flow->setHopCount(flow->getHopCount() - 1);
        if (!flow->getHopCount()) {
            //TODO: Vesely - More granular error
            FaiTable->changeAllocStatus(flow, FAITableEntry::ALLOC_ERR);
            //Schedule M_Create_R(Flow)
            this->signalizeCreateFlowResponseNegative(flow);
            return false;
        }

        // bind this flow to a suitable (N-1)-flow
        RABase* raModule = (RABase*) getModuleByPath("^.^.resourceAllocator.ra");
        status = raModule->bindNFlowToNM1Flow(flow);

        EV << "status: " << status << endl;
        if (status == true)
        { // flow is already allocated
            receiveCreateFlowPositive(flow);
        }
        //else WAIT until allocation of N-1 flow is completed
    }
    return status;
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
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    unsigned short qosid = 0;
    short score = 0;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        short tmpscore = flow->getQosParameters().countFeasibilityScore(*it);
//        EV << "QosID: " << it->getQosId()
//           << " tmpscore: " << tmpscore
//           << " score: " << score << endl
//           << " qosid: " << qosid << endl;
        if (score < tmpscore) {
            score = tmpscore;
            qosid = it->getQosId();
        }
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
    module->par(PAR_CREREQTIMEOUT) = par(PAR_CREREQTIMEOUT).doubleValue();
    module->finalizeParameters();
    module->buildInside();

    // create activation message
    module->scheduleStart(simTime());
    module->callInitialize();

    //Prepare return pointer and setup internal FAI pointers
    FAI* fai = dynamic_cast<FAI*>(module);
    fai->postInitialize(this, flow, Efcp);

    //Change state in FAITable
    FaiTable->setFaiToFlow(fai, flow);
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
    sigFACreResPosiFwd  = registerSignal(SIG_FA_CreateFlowResponseForward);
    sigFACreResNega     = registerSignal(SIG_FA_CreateFlowResponseNegative);
    //sigFACreResPosi     = registerSignal(SIG_FA_CreateFlowResponsePositive);

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

    //CreateResponseFlowPositive
    lisCreResFloPosi = new LisFACreRes(this);
    catcher2->subscribe(SIG_RIBD_CreateFlowResponsePositive, lisCreResFloPosi);

}

/*
void FA::signalizeAllocateResponseNegative(Flow* flow) {
    emit(this->sigFAAllocResNega, flow);
}
*/

void FA::signalizeCreateFlowRequestForward(Flow* flow) {
    emit(this->sigFACreReqFwd, flow);
}

void FA::receiveCreateFlowPositive(Flow* flow) {
    Enter_Method("receiveCreateFlowPositive()");
    EV << "Continue M_CREATE(flow) forward!" << endl;

    Flow* tmpfl = flow->dup();
    setNeighborAddresses(tmpfl);

    this->signalizeCreateFlowRequestForward(tmpfl);
}

void FA::receiveCreateResponseFlowPositiveFromRibd(Flow* flow) {
    Enter_Method("createFlowResponseForward()");

    FAITableEntry* entry = FaiTable->findEntryByApns(flow->getSrcApni().getApn(), flow->getDstApni().getApn());
    entry->getFlow()->getConnectionId().setDstCepId(flow->getConId().getDstCepId());
    entry->getFlow()->setDstPortId(flow->getDstPortId());

    Flow* tmpfl = entry->getFlow()->dup();
    tmpfl->swapFlow();

    //Add source address
    setNeighborAddresses(tmpfl);

    signalizeCreateFlowResponsePositiveForward(tmpfl);
}

void FA::signalizeCreateFlowResponseNegative(Flow* flow) {
    emit(this->sigFACreResNega, flow);
}

bool FA::setOriginalAddresses(Flow* flow) {
    Address adr = getAddressFromDa(flow->getSrcApni().getApn(), false);
    if (adr.isUnspecified())
        return false;
    flow->setSrcAddr(adr);

    adr = getAddressFromDa(flow->getDstApni().getApn(), false);
    if (adr.isUnspecified())
        return false;
    flow->setDstAddr(adr);
    return true;
}

bool FA::setNeighborAddresses(Flow* flow) {
    Address adr = getAddressFromDa(flow->getSrcApni().getApn(), true);
    if (adr.isUnspecified())
        return false;
    flow->setSrcNeighbor(adr);

    adr = getAddressFromDa(flow->getDstApni().getApn(), true);
    if (adr.isUnspecified())
        return false;
    flow->setDstNeighbor(adr);
    return true;
}

const Address FA::getAddressFromDa(const APN& apn, bool useNeighbor) {
    //Ask DA which IPC to use to reach src App
    const Address* ad = DifAllocator->resolveApnToBestAddress(apn, MyAddress.getDifName());
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << apn << endl;
        return Address();
    }
    Address addr = *ad;
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


void FA::signalizeCreateFlowResponsePositiveForward(Flow* flow) {
    emit(this->sigFACreResPosiFwd, flow);
}
