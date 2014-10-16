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

Define_Module(IRM);

IRM::IRM() {
}

IRM::~IRM() {
}

void IRM::initPointers() {
    ConTable = ModuleAccess<ConnectionTable>(MOD_CONNTABLE).get();
    DifAllocator = ModuleAccess<DA>(MOD_DA).get();
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
    cModule* Ap = this->getParentModule();

    //Decide portId
    int portId;
    if ( DifAllocator->isAppLocal(flow->getDstApni().getApn()) )
        portId = flow->getDstPortId();
    else if ( DifAllocator->isAppLocal(flow->getSrcApni().getApn()) )
        portId = flow->getSrcPortId();
    else
        throw("Binding to inconsistant PortId occured!");

    //  Retrieve IPC gates
    std::ostringstream nam1;
    nam1 << GATE_NORTHIO_ << portId;
    cGate* g1i = Ipc->gateHalf(nam1.str().c_str(), cGate::INPUT);
    cGate* g1o = Ipc->gateHalf(nam1.str().c_str(), cGate::OUTPUT);

    //   Add AP gates
    std::ostringstream nam2;
    nam2 << GATE_SOUTHIO_ << portId;
    Ap->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g2i = Ap->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g2o = Ap->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

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

void IRM::receiveAllocationRequest(Flow* flow) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received Allocation Request" << endl;

    //Command target FA to allocate flow
    bool status = ConTable->getFa(flow)->receiveAllocateRequest(flow);

    //If AllocationRequest NOT ended by creating connections
    if (!status)
       EV << "Flow not allocated!\n" << flow << endl;
}

void IRM::receiveDeallocationRequest(Flow* fl) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocationRequest" << endl;
    signalizeDeallocateRequest(fl);
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
    DirectoryEntry* de = DifAllocator->resolveApn(flow->getDstApni().getApn());

    if (de == NULL) {
        EV << "DA does not know target application" << endl;
        return;
    }

    //TODO: Vesely - Now using first available APN to DIFMember mapping
    Address addr = de->getSupportedDifs().front();

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

bool IRM::receiveAllocationResponsePositive(Flow* flow) {
    Enter_Method("allocationResponsePositive()");
    bool status = createBindings(flow);
    return status;
}
