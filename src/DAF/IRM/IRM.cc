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


#include "IRM.h"

const int VAL_UNDEF_HANDLE = -1;

Define_Module(IRM);

IRM::IRM() {
}

IRM::~IRM() {
}

void IRM::initPointers() {
    ConTable = dynamic_cast<ConnectionTable*>(this->getParentModule()->getSubmodule(MOD_CONNTABLE));
    if (!ConTable)
            error("ConTab is NULL!");
    DifAllocator = dynamic_cast<DA*>(this->getParentModule()->getParentModule()->getSubmodule(MOD_DIFALLOC)->getSubmodule(MOD_DA));
}

void IRM::initialize() {
    initPointers();
    initSignalsAndListeners();
}

void IRM::handleMessage(cMessage* msg) {
    if (!msg->isSelfMessage()) {
        //Find output gate based on input
        cGate* g = ConTable->findOutputGate(msg->getArrivalGate());
        //Send out if gate exist
        if (g)
            send(msg, g);
        else {
            EV << "Received message but destination gate is not in the ConnectionTable!" << endl;
        }
    }
    //Process self-message
    else {

    }

}

void IRM::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getParentModule();

    //Signals that this module emits
    sigIRMAllocReq      = registerSignal(SIG_IRM_AllocateRequest);
    sigIRMDeallocReq    = registerSignal(SIG_IRM_DeallocateRequest);

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
    IrmMod->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g2i = IrmMod->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g2o = IrmMod->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //   Add IRM gates
    this->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g3i = this->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g3o = this->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //TODO: Status check

    //   Connect gates together
    g1o->connectTo(g2i);
    g2i->connectTo(g3i);

    g3o->connectTo(g2o);
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

    //Command target FA to allocate flow
    FABase* fab = ConTable->getFa(flow);
    bool status = false;

    if (fab) {
        //signalizeDeallocateRequest(fl);
        status = fab->receiveDeallocateRequest(flow);
    }
    else
        EV << "FA could not be found in ConnectionTable!" << endl;

    return status;
}

void IRM::signalizeAllocateRequest(Flow* flow) {
    //EV << "!!!!VYemitovano" << endl;
    //EV << "Emits AllocReq Flow = " << flow->getSrcApni() << "_" << flow->getDstApni() << endl;
    emit(sigIRMAllocReq, flow);
}

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

void IRM::signalizeDeallocateRequest(Flow* flow) {
    emit(sigIRMDeallocReq, flow);
}

ConnectionTable* IRM::getConTable() const {
    return ConTable;
}

bool IRM::receiveAllocationResponsePositiveFromIpc(Flow* flow) {
    Enter_Method("allocationResponsePositive()");
    bool status = createBindings(flow);
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

int IRM::getGateHandle(Flow* flow) const {
    ConnectionTableEntry* cte = ConTable->findEntryByFlow(flow);
    return ( cte && cte->getNorthGateIn() ) ? cte->getNorthGateIn()->getIndex() : VAL_UNDEF_HANDLE;
}

void IRM::setNorthGates(Flow* flow, cGate* nIn, cGate* nOut) {
    ConTable->setNorthGates(flow, nIn, nOut);
}
