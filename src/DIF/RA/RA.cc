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
 * @file RA.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Monitoring and adjustment of IPC process operations
 * @detail
 */

#include "RA.h"

Define_Module(RA);

void RA::initialize()
{
    // connect to other modules
    difAllocator = ModuleAccess<DA>("da").get();
    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    flTable = ModuleAccess<FlowTable>("flowTable").get();
    rmt = (RMT*) this->getParentModule()->getParentModule()->getModuleByPath(".rmt.rmt");

    // identify the role of IPC process in processing system
    cModule* hostModule = getParentModule()->getParentModule();
    processName = hostModule->par("ipcAddress").stdstringValue();
    std::string bottomGate = hostModule->gate("southIo$o", 0)->getNextGate()->getName();

    if (bottomGate == "medium$o")
    {
        // we're on wire! this is the bottommost "interface" DIF
        // let's connect RMT to the medium
        bindMediumToRMT();
    }
    else if (bottomGate == "northIo$o")
    { // other IPC processes are below us
        if (hostModule->gateSize("northIo") > 1)
        {
            // multiple (N-1)-DIFs are present, RMT shall be relaying
            rmt->enableRelay();
        }
        else
        {
            // we're on top of a single IPC process
        }
    }

    std::string dstIpc = getParentModule()->par("dstIpc").stdstringValue();

    if (dstIpc != "-1")
    {
        createFlow(dstIpc);
    }
}



void RA::handleMessage(cMessage *msg)
{

}

/**
 * Connects the RMT module to the medium defined in NED.
 * Used only for the bottom IPC process in a processing system.
 */
void RA::bindMediumToRMT()
{
    rmt->createSouthGate("rmtIo_PHY");
    cGate* rmtIn = rmt->getParentModule()->gateHalf("rmtIo_PHY", cGate::INPUT);
    cGate* rmtOut = rmt->getParentModule()->gateHalf("rmtIo_PHY", cGate::OUTPUT);

    cModule* thisIpc = this->getParentModule()->getParentModule();
    cGate* thisIpcIn = thisIpc->gateHalf("southIo$i", cGate::INPUT, 0);
    cGate* thisIpcOut = thisIpc->gateHalf("southIo$o", cGate::OUTPUT, 0);

    rmtOut->connectTo(thisIpcOut);
    thisIpcIn->connectTo(rmtIn);
}

/**
 * Connects the RMT module to the specified (N-1)-flow.
 *
 * @param ipc IPC process containing the (N-1)-flow
 * @param flow the (N-1)-flow
 */
void RA::bindFlowToRMT(cModule* ipc, Flow* flow)
{
    // expand the given portId so it's unambiguous within this IPC
    std::string combinedPortId = normalizePortId(ipc->getFullName(), flow->getSrcPortId());

    std::ostringstream rmtGate;
    rmtGate << "rmtIo_" << combinedPortId;

    rmt->createSouthGate(rmtGate.str());

    // get (N-1)-IPC gates
    std::ostringstream bottomIpcGate;
    bottomIpcGate << "northIo_" << flow->getSrcPortId();
    cGate* bottomIpcIn = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::INPUT);
    cGate* bottomIpcOut = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::OUTPUT);

    // get RMT gates
    cGate* rmtIn = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtOut = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    // create an intermediate border gate
    cModule* thisIpc = this->getParentModule()->getParentModule();
    std::ostringstream thisIpcGate;
    thisIpcGate << "southIo_" << combinedPortId;

    thisIpc->addGate(thisIpcGate.str().c_str(), cGate::INOUT, false);
    cGate* thisIpcIn = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::INPUT);
    cGate* thisIpcOut = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::OUTPUT);


    bottomIpcOut->connectTo(thisIpcIn);
    thisIpcIn->connectTo(rmtIn);

    rmtOut->connectTo(thisIpcOut);
    thisIpcOut->connectTo(bottomIpcIn);

    // modules are connected; register a handle
    rmt->addRMTPort(std::make_pair(ipc, flow->getSrcPortId()), rmtOut);

}

/**
 * Prefixes given port-id (originally returned by an FAI) with IPC process's ID
 * to prevent name collisions in current IPC process.
 *
 * @param ipcName module identifier of an underlying IPC process
 * @param flowPortId original portId to be expanded
 * @return normalizes port-id
 */
std::string RA::normalizePortId(std::string ipcName, int flowPortId)
{
    std::ostringstream newPortId;
    newPortId << ipcName << '_' << flowPortId << endl;
    return newPortId.str();
}

/**
 * Creates an (N-1)-flow.
 *
 * @param dstIpc address of the destination IPC process
 */
void RA::createFlow(std::string dstIpc)
{
    EV << " allocating an (N-1)-flow for IPC " << processName << endl;

    APNamingInfo src = APNamingInfo(APN(processName));
    APNamingInfo dst = APNamingInfo(APN(dstIpc));
    Flow *fl = new Flow(src, dst);

    // ask DA which IPC to use to reach destination IPC
    cModule* ipc = difAllocator->resolveApniToDif(fl->getDstApni());
    // reach IPC's FA for direct function calling (temporary solution)
    FABase* fa = difAllocator->resolveApniToDifFa(fl->getDstApni());

    bool status = false;
    if (fa)
    {
        //signalizeAllocateRequest(fl);
        status = fa->receiveAllocateRequest(fl);
    }
    else
    {
        EV << "DA does not know target IPC process!" << endl;
    }

    if (!status)
    {
        EV << "Flow not allocated!" << endl;
    }
    else
    {
        // connect the new flow to the RMT
        bindFlowToRMT(ipc, fl);
        // we're ready to go!
        signalizeFlowAllocated(fl);
        flTable->insert(fl, fa);
    }
}

void RA::initSignalsAndListeners() {
    // allocation request
    sigRAAllocReq      = registerSignal(SIG_RA_AllocateRequest);
    // deallocation request
    sigRADeallocReq    = registerSignal(SIG_RA_DeallocateRequest);
    // positive response to allocation request
    sigRAAllocResPosi  = registerSignal(SIG_RA_AllocateResponsePositive);
    // negative response to allocation request
    sigRAAllocResNega  = registerSignal(SIG_RA_AllocateResponseNegative);
    // successful allocation of an (N-1)-flow
    sigRAFlowAllocd  = registerSignal(SIG_RA_FlowAllocated);
    // successful deallocation of an (N-1)-flow
    sigRAFlowDeallocd  = registerSignal(SIG_RA_FlowDeallocated);

}

void RA::signalizeAllocateRequest(Flow* flow) {
    emit(sigRAAllocReq, flow);
}

void RA::signalizeDeallocateRequest(Flow* flow) {
    emit(sigRADeallocReq, flow);
}

void RA::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigRAAllocResPosi, flow);
}

void RA::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigRAAllocResNega, flow);
}

void RA::signalizeFlowAllocated(Flow* flow) {
    emit(sigRAFlowAllocd, flow);
}

void RA::signalizeFlowDeallocated(Flow* flow) {
    emit(sigRAFlowDeallocd, flow);
}
