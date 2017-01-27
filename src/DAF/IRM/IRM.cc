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


#include "DAF/IRM/IRM.h"

const int VAL_UNDEF_HANDLE = -1;
const char* SIG_STAT_IRM_UP = "IRM_PassUp";
const char* SIG_STAT_IRM_DOWN = "IRM_PassDown";

Define_Module(IRM);

IRM::IRM() {
    statPassUp = 0;
    statPassDown = 0;
    statDiscarded = 0;
}

IRM::~IRM() {
    ConTable = NULL;
    DifAllocator = NULL;
    statPassUp = 0;
    statPassDown = 0;
    statDiscarded = 0;
}

void IRM::initPointers() {
    ConTable = getRINAModule<ConnectionTable*>(this, 1, {MOD_CONNTABLE});
    if (!ConTable)
            error("ConTab is NULL!");
    DifAllocator = getRINAModule<DA*>(this, 2, {MOD_DIFALLOC, MOD_DA});
}

void IRM::initialize() {
    initPointers();
    initSignalsAndListeners();
}

void IRM::handleMessage(cMessage* msg) {
    if (!msg->isSelfMessage()) {
        //Find output gate based on input
        bool isGoingUp = false;
        cGate* g = ConTable->findOutputGate(msg->getArrivalGate(), isGoingUp);
        //Send out if gate exist
        cPacket* packet = dynamic_cast<cPacket*>(msg);
        cPacket* outPacket;
        if (g) {
            if (isGoingUp) {
                statPassUp++;
                emit(sigStatIRMPassUp, true);
                outPacket = packet->decapsulate();
                delete packet;
            }
            else
            {
                statPassDown++;
                emit(sigStatIRMPassDown, true);
                SDUData* sduData = new SDUData();
                sduData->encapsulate(packet);
                outPacket = sduData;
            }


            send(outPacket, g);

        }
        else {
            EV << "Received message but destination gate is not in the ConnectionTable!" << endl;
            statDiscarded++;
            delete msg;
        }

        updateDisplayString();
    }
    //Process self-message
    else {

    }

}

void IRM::initSignalsAndListeners() {
    cModule* catcher = this->getModuleByPath("^.^");

    //Signals that this module emits
    /*
    sigIRMAllocReq      = registerSignal(SIG_IRM_AllocateRequest);
    sigIRMDeallocReq    = registerSignal(SIG_IRM_DeallocateRequest);
    */
    sigStatIRMPassUp      = registerSignal(SIG_STAT_IRM_UP);
    sigStatIRMPassDown      = registerSignal(SIG_STAT_IRM_DOWN);

    //  Allocate Request from App
    this->lisAllocReq = new LisIRMAllocReq(this);
    catcher->subscribe(SIG_AE_AllocateRequest, this->lisAllocReq);
    //  Deallocate Request from App
    this->lisDeallocReq = new LisIRMDeallocReq(this);
    catcher->subscribe(SIG_AE_DeallocateRequest, this->lisDeallocReq);
}

bool IRM::createBindings(Flow* flow) {
    Enter_Method("createBindings()");
    EV << "Attempts to create bindings and bind registration of gates"<< endl;
    //Retrieve IPC process with allocated flow and prepared bindings

    ConnectionTableEntry* cte = ConTable->findEntryByFlow(flow);
    //if (!cte) {
    //    EV << "======================" << endl << flow->info() << endl;
    //    return false;
    //}
    cModule* Ipc = cte->getIpc();
    cModule* IrmMod = this->getParentModule();

    //Decide portId
    int portId = flow->getSrcPortId();
    /*
    if ( DifAllocator->isAppLocal(flow->getDstApni().getApn()) )
        portId = flow->getDstPortId();
    else if ( DifAllocator->isAppLocal(flow->getSrcApni().getApn()) )
        portId
    else
        throw("Binding to inconsistant PortId occured!");
    */

    //  Retrieve IPC gates
    std::ostringstream nam1;
    nam1 << GATE_NORTHIO_ << portId;
    cGate* g1i = Ipc->gateHalf(nam1.str().c_str(), cGate::INPUT);
    cGate* g1o = Ipc->gateHalf(nam1.str().c_str(), cGate::OUTPUT);

    //   Add AP gates
    std::ostringstream nam2;
    nam2 << GATE_SOUTHIO_ << portId;
    if (!IrmMod->hasGate(nam2.str().c_str()))
        IrmMod->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g2i = IrmMod->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g2o = IrmMod->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //   Add IRM gates
    if (!this->hasGate(nam2.str().c_str()))
        this->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g3i = this->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g3o = this->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //TODO: Status check

    //   Connect gates together
    if (!g1o->getNextGate())
        g1o->connectTo(g2i);
    if (!g2i->getNextGate())
        g2i->connectTo(g3i);

    if (!g3o->getNextGate())
        g3o->connectTo(g2o);
    if (!g2o->getNextGate())
        g2o->connectTo(g1i);


    //Set south-half of the routing in ConnectionTable
    bool status = ConTable->setSouthGates(flow, g3i, g3o);

    return status;
}

bool IRM::receiveAllocationRequestFromAe(Flow* flow) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received Allocation Request" << endl;

    //Command target FA to allocate flow
    FABase* fab = ConTable->getFa(flow);
    bool status = false;

    if (fab) {
        //signalizeAllocateRequest(fl);
        status = fab->receiveAllocateRequest(flow);
        //If AllocationRequest NOT ended by creating connections
        if (!status)
           EV << "Flow not allocated!\n" << flow << endl;
    }
    else
        EV << "FA could not be found in ConnectionTable!" << endl;

    return status;
}

bool IRM::receiveDeallocationRequestFromAe(Flow* flow) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocationRequest" << endl;

    auto cte = ConTable->findEntryByFlow(flow);
    bool status = false;

    if (cte) {
        //TODO: Vesely - Change CONNECT_PENDING to establish ASAP when AE Enrollment
        //               implementation is finished
        if (cte->getConStatus() == ConnectionTableEntry::CON_CONNECTPENDING
                && cte->getSouthGateOut() && cte->getSouthGateIn() ) {
            status = cte->getFlowAlloc()->receiveDeallocateRequest(flow);
        }
        else {
            EV << "Connection not in proper state or south gates are missing!" << endl;
        }
    }
    else {
        EV << "There is no valid entry in Connection Table!" << endl;
    }
    return status;
}
/*
void IRM::signalizeAllocateRequest(Flow* flow) {
    //EV << "!!!!VYemitovano" << endl;
    //EV << "Emits AllocReq Flow = " << flow->getSrcApni() << "_" << flow->getDstApni() << endl;
    emit(sigIRMAllocReq, flow);
}
*/
void IRM::newFlow(Flow* flow) {
    Enter_Method("newFlow()");

    //Create a new record in ConnectionTable
    ConTable->insertNew(flow);

    //Ask DA which IPC to use to reach dst App
    const Address* ad = DifAllocator->resolveApnToBestAddress(flow->getDstApni().getApn());
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << flow->getDstApni().getApn() << endl;
        return;
    }
    Address addr = *ad;

    //TODO: Vesely - New IPC must be enrolled or DIF created
    if (!DifAllocator->isDifLocal(addr.getDifName())) {
        EV << "Local CS does not have any IPC in DIF " << addr.getDifName() << endl;
        return;
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = DifAllocator->getDifMember(addr.getDifName());

    //Store info into ConnectionTable
    ConTable->setFa(flow, DifAllocator->findFaInsideIpc(targetIpc));
}

void IRM::updateDisplayString() {
    std::ostringstream os;
    os << "up: " << statPassUp << endl << "down: " << statPassDown << endl << "discard: " << statDiscarded;
    setPolicyDisplayString(this, os.str().c_str());
}
/*
void IRM::signalizeDeallocateRequest(Flow* flow) {
    emit(sigIRMDeallocReq, flow);
}
*/
ConnectionTable* IRM::getConTable() const {
    return ConTable;
}

bool IRM::receiveAllocationResponsePositiveFromIpc(Flow* flow) {
    Enter_Method("allocationResponsePositive()");
    bool status = createBindings(flow);

    status ?
    changeStatus(flow, ConnectionTableEntry::CON_CONNECTPENDING)
    :
    changeStatus(flow, ConnectionTableEntry::CON_ERROR);
    return status;
}

bool IRM::deleteBindings(Flow* flow) {
    Enter_Method("deleteBindings()");
    EV << "Attempts to delete bindings"<< endl;
    //Retrieve IPC process with allocated flow and prepared bindings

    ConnectionTableEntry* cte = ConTable->findEntryByFlow(flow);
    cModule* Ipc = cte->getIpc();
    cModule* IrmMod = this->getParentModule();

    //Decide portId
    int portId = flow->getSrcPortId();

    //  Retrieve IPC gates
    std::ostringstream nam1;
    nam1 << GATE_NORTHIO_ << portId;
    cGate* g1i = Ipc->gateHalf(nam1.str().c_str(), cGate::INPUT);
    cGate* g1o = Ipc->gateHalf(nam1.str().c_str(), cGate::OUTPUT);

    //   Add AP gates
    std::ostringstream nam2;
    nam2 << GATE_SOUTHIO_ << portId;
    cGate* g2i = IrmMod->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g2o = IrmMod->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //   Add IRM gates
    cGate* g3i = this->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g3o = this->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //   Connect gates together
    g1o->disconnect();
    g2i->disconnect();
    g3i->disconnect();

    g3o->disconnect();
    g2o->disconnect();
    g1i->disconnect();

    return !g1o->isConnected() && !g1i->isConnected()
           && !g2o->isConnected() && !g2i->isConnected()
           && !g3o->isConnected() && !g3i->isConnected();
}

void IRM::changeStatus(Flow* flow,ConnectionTableEntry::ConnectionStatus status) {
    ConTable->setStatus(flow, status);
}

int IRM::getIrmGateHandle(Flow* flow) const {
    ConnectionTableEntry* cte = ConTable->findEntryByFlow(flow);
    if (cte && cte->getNorthGateIn()) {
        //EV << "!!!!!!!!!!!!!!" << cte->getNorthGateIn()->getFullName() << endl;
        return cte->getNorthGateIn()->getIndex();
    }
    return VAL_UNDEF_HANDLE;
}

void IRM::setNorthGates(Flow* flow, cGate* nIn, cGate* nOut) {
    ConTable->setNorthGates(flow, nIn, nOut);
}

int IRM::getApGateHandle(Flow* flow) const {
    ConnectionTableEntry* cte = ConTable->findEntryByFlow(flow);
    if (cte && cte->getNorthGateIn()) {
        std::string desc = cte->getNorthGateIn()->getPreviousGate()->getPreviousGate()->getFullName();
        //EV << "!!!!!!!!!!!!!!" << desc << endl;
        return cte->getNorthGateIn()->getPreviousGate()->getPreviousGate()->getIndex();
    }
    return VAL_UNDEF_HANDLE;
}
