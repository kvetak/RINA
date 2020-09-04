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

#include "EthShimDIF/ShimFA/ShimFA.h"

#include "Common/ConnectionId.h"
#include "Common/Flow.h"
#include "Common/RINASignals.h"
#include "Common/Utils.h"
#include "DIF/FA/NFlowTable.h"
#include "EthShimDIF/EthShim/EthShim.h"
#include "EthShimDIF/RINArp/RINArp.h"
#include "EthShimDIF/ShimFA/ShimFAI.h"

Define_Module(ShimFA);

/*
 * Initialisation functionality
 */
ShimFA::ShimFA() : FABase::FABase()
{
    qos.setQosId("unreliable");
}

ShimFA::~ShimFA() = default;

void ShimFA::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL) {
        shimIpcProcess = getModuleByPath("^.^");
        if (shimIpcProcess == nullptr)
            throw cRuntimeError("ShimFA not used in any IPC Process");

        arp = getRINAModule<RINArp *>(this, 2, {"arp"});
        shim = getRINAModule<EthShim *>(this, 2, {"shim"});
        nFlowTable = getRINAModule<NFlowTable *>(this, 1, {MOD_NFLOWTABLE});

        // Registering an application is not supported in RINASim since any upper
        // layer connected IPCP/AP is implicitly registered. We still need the AP name
        // of the upper layer. Unfortunately pretty hacky solution for the time being,
        // but finds connected IPC process
        const cGate *dstGate = shimIpcProcess->gate("northIo$o")->getPathEndGate();
        if (dstGate == nullptr) {
            EV_ERROR
                << "Shim IPC not connected to overlying application. It will be able to receive "
                << "ARP requests, but will never send ARP reply" << endl;
            return;
        }

        connectedApplication = dstGate->getOwnerModule();
        if (!connectedApplication->hasPar("apName"))
            throw cRuntimeError(
                "Shim IPC process not connected to overlying IPC/Application Process");

        // displayString for IPC Process
        initMyAddress();
    } else if (stage == inet::INITSTAGE_TRANSPORT_LAYER) {
        // Needs to be done in initialisation phase since registration is implicit in RINASim.
        registeredApplication = APN(connectedApplication->par("apName").stringValue());

        // Registers application with static entry in Arp, needs to be called after stage 0 to
        // guarantee allocation of MAC address
        shim->registerApplication(registeredApplication);
    }
}

void ShimFA::handleMessage(cMessage *msg)
{
    // self message is the only valid message here
    delete msg;
}

bool ShimFA::createUpperFlow(const APN &dstApn)
{
    Enter_Method("createUpperFlow(%s)", dstApn.c_str());

    EV << "Received request to forward allocation request to N+1, with source address " << dstApn
       << endl;

    ConnectionId connId;
    // TODO replace this with QoS ID that we accept
    connId.setQoSId(qos.getQosId());

    Flow *flow = new Flow(registeredApplication, dstApn);
    flow->setQosCube(qos);
    flow->setConId(connId);
    flow->setDstNeighbor(dstApn);
    flow->setSrcNeighbor(registeredApplication);

    ShimFAI *fai = createFAI(flow);
    nFlowTable->insertNew(flow);
    flow->setSrcPortId(fai->getLocalPortId());
    nFlowTable->setFaiToFlow(fai, flow);
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::TRANSFER);

    return fai->receiveCreateRequest();
}

bool ShimFA::receiveAllocateRequest(Flow *flow)
{
    Enter_Method("receiveAllocateRequest()");

    EV << "Received allocation request for flow with destination address "
       << flow->getDstApni().getApn() << endl;

    const auto &apName = flow->getDstApni().getApn();

    // If an entry already exists for specified application, use that
    // NOTE: this creates problems with the current implementation of flow allocation, since the
    // resource allocator of the N+1 IPCP will have checked the existence of a satisfactory flow
    // already. With other words, we are essentially forced to make sure that the N+1 IPCP asks
    // for the very same QoS cube that the shim IPCP supports.
    auto nft = nFlowTable->findEntryByApnisAndQosId(registeredApplication, apName, qos.getQosId());
    if (nft != nullptr) {
        auto *fai = static_cast<ShimFAI *>(nft->getFai());
        flow->setSrcPortId(fai->getLocalPortId());
        return true;
    }

    const auto result = shim->createEntry(apName);
    if (result == EthShim::CreateResult::error)
        return false;

    ConnectionId connId;
    connId.setQoSId(qos.getQosId());
    flow->setConId(connId);
    flow->setQosCube(qos);

    ShimFAI *fai = createFAI(flow);
    nFlowTable->insertNew(flow);
    flow->setSrcPortId(fai->getLocalPortId());
    nFlowTable->setFaiToFlow(fai, flow);
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::ALLOC_PEND);

    if (result == EthShim::CreateResult::completed)
        return fai->receiveAllocateRequest();

    return true;
}

bool ShimFA::receiveDeallocateRequest(Flow *flow)
{
    Enter_Method("receiveDeallocateRequest()");
    EV << "Received deallocation request for flow with destination APN " << endl;

    auto *entry = nFlowTable->findEntryByFlow(flow);
    if (entry == nullptr)
        return false;

    deinstantiateFai(flow);
    return true;
}

void ShimFA::completedAddressResolution(const APN &dstApn)
{
    Enter_Method("completedAddressResolution(%s)", dstApn.getName().c_str());
    EV << "Completed address resolution for " << dstApn << endl;
    auto nft =
        nFlowTable->findEntryByApnisAndQosId(registeredApplication, dstApn, qos.getQosId());
    if (nft == nullptr) {
        EV << "No such pending flow found" << endl;
        return;
    } else if (nft->getAllocateStatus() == NFlowTableEntry::TRANSFER) {
        EV << "Flow already exists, continue sending" << endl;
    }

    Flow *flow = nft->getFlow();
    nFlowTable->changeAllocStatus(flow, NFlowTableEntry::TRANSFER);
    auto *fai = static_cast<ShimFAI *>(nft->getFai());
    fai->receiveAllocateRequest();
}

void ShimFA::failedAddressResolution(const APN &dstApn)
{
    Enter_Method("failedAddressResolution(%s)", dstApn.getName().c_str());
    auto *entry =
        nFlowTable->findEntryByApnisAndQosId(registeredApplication, dstApn, qos.getQosId());
    deinstantiateFai(entry->getFlow());
}

ShimFAI *ShimFA::createFAI(Flow *flow)
{
    cModuleType *type = cModuleType::get("rina.src.EthShimDIF.ShimFA.ShimFAI");
    unsigned int portId = intrand(MAX_PORTID, RANDOM_NUMBER_GENERATOR);

    std::ostringstream ostr;
    ostr << "fai_" << portId;

    cModule *module = type->create(ostr.str().c_str(), getParentModule());
    module->par(PAR_LOCALPORTID) = portId;
    module->finalizeParameters();
    module->buildInside();
    module->scheduleStart(simTime());
    module->callInitialize();

    auto *fai = check_and_cast<ShimFAI *>(module);
    fai->postInitialize(this, flow, shim);

    // Make created module listen to allocation responses from upper IPCP
    connectedApplication->subscribe(SIG_AERIBD_AllocateResponsePositive, fai);
    connectedApplication->subscribe(SIG_AERIBD_AllocateResponseNegative, fai);

    return fai;
}

void ShimFA::deinstantiateFai(Flow *flow)
{
    // Might be kind of redundant to find entry _again_ but whatever, we're trying to comply with
    // the FABase API
    auto *entry = nFlowTable->findEntryByFlow(flow);
    ShimFAI *fai = static_cast<ShimFAI *>(entry->getFai());

    // This should honestly have some return value
    fai->receiveDeallocateRequest();
}

// Not sure what to do with this function as of yet. This is called by upper
// layer, but not checked. It's possible at least a subset of the flow
// allocation policies should be implemented
bool ShimFA::invokeNewFlowRequestPolicy(Flow *)
{
    return true;
}

/* Mandatory but unused function definitions due to FABase (most of these are _very_ specific
 * to the normal IPCP FA, so should probably exclusively belong there) */
bool ShimFA::setOriginalAddresses(Flow *)
{
    return false;
}

bool ShimFA::setNeighborAddresses(Flow *)
{
    return false;
}

bool ShimFA::receiveMgmtAllocateRequest(Flow *)
{
    throw cRuntimeError("ShimFA does not support creation of management flows");
}

bool ShimFA::receiveMgmtAllocateRequest(APNamingInfo, APNamingInfo)
{
    throw cRuntimeError("ShimFA does not support creation of management flows");
}

bool ShimFA::receiveMgmtAllocateFinish(APNIPair *)
{
    throw cRuntimeError("ShimFA does not support creation of management flows");
}

void ShimFA::receiveNM1FlowCreated(Flow *)
{
    throw cRuntimeError("ShimFA should be on medium, no NM1 flow possible");
}

bool ShimFA::receiveCreateFlowRequestFromRibd(Flow *)
{
    throw cRuntimeError("ShimFA should not need to communicate with RIBd");
}
