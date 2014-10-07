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
        //Send out
        send(msg, g);
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
    sigIRMAllocResPosi  = registerSignal(SIG_IRM_AllocateResponsePositive);
    sigIRMAllocResNega  = registerSignal(SIG_IRM_AllocateResponseNegative);

    //Signals that this module is processing
    //  AllocationResponseNegative from FA
    lisAllocResNegaFa = new LisIRMAllocResNegaFa(this);
    catcher->subscribe(SIG_FA_AllocateResponseNegative, this->lisAllocResNegaFa);
    //  AllocationResponseNegative from FAI
    lisAllocResNegaFai = new LisIRMAllocResNegaFai(this);
    catcher->subscribe(SIG_FAI_AllocateResponseNegative, this->lisAllocResNegaFai);
    //  AllocationRequest from FAI
    this->lisAllocReqFai = new LisIRMAllocReqFai(this);
    catcher->subscribe(SIG_FAI_AllocateRequest, this->lisAllocReqFai);
    //  Allocate Request from App
    this->lisAllocReq = new LisIRMAllocReq(this);
    catcher->subscribe(SIG_AE_AllocateRequest, this->lisAllocReq);
    //  Deallocate Request from App
    this->lisDeallocReq = new LisIRMDeallocReq(this);
    catcher->subscribe(SIG_AE_DeallocateRequest, this->lisDeallocReq);
}

bool IRM::createBindings(Flow& flow) {
    EV << "Attempts to create bindings and bind registration of gates"<< endl;
    //Retrieve IPC process with allocated flow and prepared bindings
    cModule* Ipc = DifAllocator->resolveApnToIpc(flow.getDstApni().getApn());
    cModule* Ap = this->getParentModule();

    //Create connections

    //  Retrieve IPC gates
    std::ostringstream nam1;
    nam1 << GATE_NORTHIO << flow.getSrcPortId();
    cGate* g1i = Ipc->gateHalf(nam1.str().c_str(), cGate::INPUT);
    cGate* g1o = Ipc->gateHalf(nam1.str().c_str(), cGate::OUTPUT);

    //   Add AP gates
    std::ostringstream nam2;
    nam2 << GATE_SOUTHIO << flow.getSrcPortId();
    Ap->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g2i = Ap->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g2o = Ap->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //   Add IRM gates
    this->addGate(nam2.str().c_str(), cGate::INOUT, false);
    cGate* g3i = this->gateHalf(nam2.str().c_str(), cGate::INPUT);
    cGate* g3o = this->gateHalf(nam2.str().c_str(), cGate::OUTPUT);

    //TODO: Status check

    //   Connect gates together
    g1o->connectTo(g2o);
    g2o->connectTo(g3i);

    g3o->connectTo(g2i);
    g2i->connectTo(g1i);

    //Set south-half of the routing in ConnectionTable
    bool status = ConTable->setSouthGates(&flow, g3i, g3o);

    return status;
}

void IRM::receiveAllocationRequest(cObject* obj) {
    Enter_Method("receiveAllocateRequest()");
    EV << this->getFullPath() << " received Allocation Request" << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);

    //Ask DA which IPC to use to reach dst App
    FABase* fa = DifAllocator->resolveApnToFa(flow->getDstApni().getApn());

    //Store info into ConnectionTable
    ConTable->setFa(flow, fa);

    //Command target FA to allocate flow
    bool status = false;
    if (fa)
        //signalizeAllocateRequest(flow);
        status = fa->receiveAllocateRequest(flow);
    else
        EV << "DA does not know target application" << endl;

    //If AllocationRequest ended by creating connections
    if (status)
        status = createBindings(*flow);
    //Allocation either failed OR app not found
    else
       EV << "Flow not allocated!\n" << flow << endl;

    if (!status)
        EV << "Flow not binded!\n" << flow << endl;

    //Change ConnectionTable status
}

void IRM::receiveDeallocationRequest(cObject* obj) {
    Enter_Method("receiveDeallocateRequest()");
    EV << this->getFullPath() << " received DeallocationRequest" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    signalizeDeallocateRequest(fl);
}

void IRM::receiveAllocationResponseNegativeAppNotFound(cObject* obj) {
    EV << this->getFullPath() << " received Negative Allocation Response App not found" << endl;
}

void IRM::receiveAllocationResponseNegative(cObject* obj) {
    //Flow* fl = dynamic_cast<Flow*>(obj);
    EV << this->getFullPath() << " received Negative Allocation Response" << endl;
}

void IRM::receiveAllocationRequestFromFAI(cObject* obj) {
    //EV << this->getFullPath() << " received AllocationRequest from FAI" << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    //TODO: Vesely - Simulate AllocationResponses
    if (true) {
        this->signalizeAllocateResponsePositive(fl);
    }
    else {
        this->signalizeAllocateResponseNegative(fl);
    }
}

void IRM::signalizeAllocateRequest(Flow* flow) {
    //EV << "!!!!VYemitovano" << endl;
    //EV << "Emits AllocReq Flow = " << flow->getSrcApni() << "_" << flow->getDstApni() << endl;
    emit(sigIRMAllocReq, flow);
}

void IRM::signalizeDeallocateRequest(Flow* flow) {
    emit(sigIRMDeallocReq, flow);
}

void IRM::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigIRMAllocResPosi, flow);
}

void IRM::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigIRMAllocResNega, flow);
}
