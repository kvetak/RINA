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

void IRM::initialize() {
    this->registerFASigs();
    //Testing purposes
    prepareTestMessage(100);
}

void IRM::handleTestMessage(cMessage *msg) {
    //IF it is a TEST message from host1
    if ( msg->isSelfMessage() && !strcmp(msg->getName(), "TEST") && strstr(this->getFullPath().c_str(), "host1")){
        //EV << msg->getName() << endl;

        Flow* fl = new Flow( APNamingInfo( APN("AppH1") ), APNamingInfo( APN("AppH2") ) );

        signalizeFAAllocateRequest(fl);
        delete(msg);
    }
    if ( msg->isSelfMessage() && !strcmp(msg->getName(), "TEST") && strstr(this->getFullPath().c_str(), "host2")){
        //EV << msg->getName() << endl;

        Flow* fl = new Flow( APNamingInfo( APN("AppH2") ), APNamingInfo( APN("AppERR") ) );

        signalizeFAAllocateRequest(fl);
        delete(msg);
    }
}

void IRM::handleMessage(cMessage* msg) {
    //Testing purpose message
    this->handleTestMessage(msg);
}

void IRM::prepareTestMessage(simtime_t tim){
    cMessage* mcre = new cMessage("TEST");
    scheduleAt(simTime() + tim, mcre);
}

void IRM::registerFASigs() {
    FA* fa = ModuleAccess<FA>("fa").get();
    //EV << "!!!!!" << fa->getFullPath() << endl;
    //Subscribe FA signals
    //  Allocation Request
    sigIRMAllocReq = registerSignal("AllocateRequest");
    fa->lisAllocReq = new LisFAAllocReq(fa);
    this->subscribe(sigIRMAllocReq, fa->lisAllocReq);

    //  Allocation Response NEGATIVE
    fa->sigFAAllocResNega = registerSignal("AllocateResponseNegative");
    lisAllocResNega = new LisIRMAllocResNega(this);
    fa->subscribe(fa->sigFAAllocResNega, this->lisAllocResNega);

    //  Deallocation Request
    sigIRMDeallocReq = registerSignal("DeallocateRequest");
    fa->lisDeallocReq = new LisFADeallocReq(fa);
    this->subscribe(sigIRMDeallocReq, fa->lisDeallocReq);

    //  Allocation Request from FAI
    sigFAIAllocReq = registerSignal("AllocateRequestFromFAI");
    fa->sigFAIAllocReq = sigFAIAllocReq;
    this->lisAllocReqFromFai = new LisIRMAllocReqFromFAI(this);
    this->subscribe(sigFAIAllocReq, this->lisAllocReqFromFai);

    //  Allocation Response POSITIVE
    sigIRMAllocResPosi = registerSignal("AllocateResponsePositive");

    //  Allocation Response NEGATIVE
    sigIRMAllocResNega = registerSignal("AllocateResponseNegative");
}

void IRM::receiveAllocationResponseNegative(cObject* obj) {
    //Flow* fl = dynamic_cast<Flow*>(obj);
    EV << this->getFullPath() << " received Negative Allocation Response" << endl;
}

void IRM::receiveAllocationRequestFromFAI(cObject* obj) {
    //Flow* fl = dynamic_cast<Flow*>(obj);
    EV << this->getFullPath() << " received AllocationRequest from FAI" << endl;
}

void IRM::signalizeFAAllocateRequest(Flow* flow) {
    //EV << "!!!!VYemitovano" << endl;
    EV << "Vyemitovan AllocReq s Flow = " << flow->getSrcApni() << "_" << flow->getDstApni() << endl;
    emit(sigIRMAllocReq, flow);
}
