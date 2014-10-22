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

#include "FAI.h"
#include "FAIListeners.h"

FAIListeners::FAIListeners(FAI* nfai) {
    this->fai = nfai;

}

FAIListeners::~FAIListeners() {
    // TODO Auto-generated destructor stub

}

void LisFAIAllocResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateResponsePositive initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if (fai->getFlow() == fl)
        fai->receiveAllocateResponsePositive();
}

void LisFAIAllocResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateResponseNegative initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if (fai->getFlow() == fl)
        fai->receiveAllocateResponseNegative();
}

void LisFAIAllocReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocateRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if (fai->getFlow() == fl)
        fai->receiveAllocateRequest();
}

void LisFAICreReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    fai->receiveCreateRequest();
}

void LisFAICreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponsePositive initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Only FAI with same CepId and PortId process this call
        if (fai->getFlow()->getSrcPortId() == flow->getSrcPortId()
                && fai->getFlow()->getConId().getSrcCepId() == flow->getConId().getSrcCepId() )
            fai->receiveCreateResponsePositive(flow);
    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAICreResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponseNegative initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Only FAI with same CepId and PortId process this call
        if (fai->getFlow()->getSrcPortId() == flow->getSrcPortId()
                && fai->getFlow()->getConId().getSrcCepId() == flow->getConId().getSrcCepId() )
        fai->receiveCreateResponseNegative(flow);
    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAIDelRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteResponse initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    fai->receiveDeleteResponse();
}

void LisFAIDelReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    fai->receiveDeleteRequest();
}

void LisFAICreResPosiNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponsePositiveNminusOne initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getIpcAddress() == flow->getSrcApni().getApn() )
            fai->receiveCreateFlowResponsePositiveFromNminusOne();
    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAICreResNegaNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getIpcAddress() == flow->getSrcApni().getApn() )
            fai->receiveCreateFlowResponseNegativeFromNminusOne();
    }
    else
        EV << "FAIListener received unknown object!" << endl;

}
