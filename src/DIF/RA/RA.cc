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
    //Register FA signals
    registerFASigs();

    // connect to other modules
    DifAllocator = ModuleAccess<DA>("da").get();
    cModule* hostModule = getParentModule()->getParentModule();
    rmt = (RMT*) this->getParentModule()->getParentModule()->getModuleByPath(".rmt.rmt");

    processName = hostModule->par("ipcAddress").stdstringValue();
    std::string bottomGate = hostModule->gate("southIo$o", 0)->getNextGate()->getName();

    // identify the role of IPC process in processing system
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
            // we're on top of a single IPC process, RMT will only multiplex
        }
    }

//    if (processName == "2")
//    {
//        createFlow("3");
//    }
}

void RA::registerFASigs() {
    FA* fa = ModuleAccess<FA>("fa").get();
    //Register signals
    sigFACreReq = registerSignal("CreateRequestFlow");
    sigFACreRes = registerSignal("CreateResponseFlow");
    sigDelReq = registerSignal("DeleteRequestFlow");
    sigDelRes = registerSignal("DeleteResponseFlow");
    //Subscribe FA signals
    //this->getParentModule()->getParentModule()->subscribe("CreateRequest",  lCreReq);
    fa->lisCreReq = new LisFACreReq(fa);
    this->subscribe(sigFACreReq,  fa->lisCreReq);
    fa->lisCreRes = new LisFACreRes(fa);
    this->subscribe(sigFACreRes, fa->lisCreRes);
    fa->lisDelReq = new LisFADelReq(fa);
    this->subscribe(sigDelReq,  fa->lisDelReq);
    fa->lisDelRes = new LisFADelRes(fa);
    this->subscribe(sigDelRes, fa->lisDelRes);
}

void RA::signalizeFACreateRequestFlow() {
    //EV << "Sending... " << getSignalName(sigFACreReq) << endl;
    emit(sigFACreReq, true);
}

void RA::signalizeFACreateResponseFlow() {
    emit(sigFACreRes, true);
}

void RA::signalizeFADeleteRequestFlow() {
    emit(sigDelReq, true);
}

void RA::signalizeFADeleteResponseFlow() {
    emit(sigDelRes, true);
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
    std::ostringstream rmtPortId;
    rmtPortId << "rmtIo_"
              << ipc->getFullName()
              << '_' << flow->getSrcPortId() << endl;

    rmt->createSouthGate(rmtPortId.str());

    // get (N-1)-IPC gates
    std::ostringstream bottomIpcGate;
    bottomIpcGate << "northIo_" << flow->getSrcPortId();
    cGate* bottomIpcIn = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::INPUT);
    cGate* bottomIpcOut = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::OUTPUT);

    // get RMT gates
    cGate* rmtIn = rmt->getParentModule()->gateHalf(rmtPortId.str().c_str(), cGate::INPUT);
    cGate* rmtOut = rmt->getParentModule()->gateHalf(rmtPortId.str().c_str(), cGate::OUTPUT);

    // create an intermediate border gate
    cModule* thisIpc = this->getParentModule()->getParentModule();
    std::ostringstream thisIpcGate;
    thisIpcGate << "southIo_"
                << ipc->getFullName()
                << '_' << flow->getSrcPortId() << endl;

    thisIpc->addGate(thisIpcGate.str().c_str(), cGate::INOUT, false);
    cGate* thisIpcIn = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::INPUT);
    cGate* thisIpcOut = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::OUTPUT);


    bottomIpcOut->connectTo(thisIpcIn);
    thisIpcIn->connectTo(rmtIn);

    rmtOut->connectTo(thisIpcOut);
    thisIpcOut->connectTo(bottomIpcIn);

}

/**
 * Creates an (N-1)-flow.
 *
 * @param dstIpc address of the destination IPC process
 */
void RA::createFlow(std::string dstIpc)
{
    EV << "allocating an (N-1)-flow for IPC " << processName << endl;

    APNamingInfo src = APNamingInfo(APN(processName));
    APNamingInfo dst = APNamingInfo(APN(dstIpc));
    Flow *fl = new Flow(src, dst);

    //Ask DA which IPC to use to reach dst App
    cModule* ipc = DifAllocator->resolveApniToIpc(fl->getDstApni());
    FABase* fa = DifAllocator->resolveApniToFa(fl->getDstApni());


    bool status = false;
    if (fa)
        //signalizeAllocateRequest(flow);
        status = fa->receiveAllocateRequest(fl);
    else
        EV << "DA does not know target application" << endl;

    if (status)
        // connect the new flow to the RMT
        bindFlowToRMT(ipc, fl);
    else
        EV << "Flow not allocated!" << endl;
}
