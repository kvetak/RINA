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

#include "AE.h"
#include "AEListeners.h"

AEListeners::AEListeners(AE* nae) : ae(nae)
{
}

AEListeners::~AEListeners() {
    ae = NULL;
}

void LisAEReceiveData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveData initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg) {
        ae->receiveData(msg);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEAllReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        const APN dstApn = flow->getSrcApni().getApn();
        if (ae->getApni().getApn() == dstApn)
            ae->receiveAllocationRequestFromFAI(flow);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEAllResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateResponsePositive initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (ae->hasFlow(flow))
            ae->receiveAllocationResponsePositive(flow);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEAllResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateResponseNegative initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (ae->hasFlow(flow))
            ae->receiveAllocationResponsePositive(flow);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEDeallReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeallocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        const APN dstApn = flow->getSrcApni().getApn();
        if (ae->getApni().getApn() == dstApn && ae->hasFlow(flow))
            ae->receiveDeallocationRequestFromFAI(flow);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}
