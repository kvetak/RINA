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
    if ( fai->getFlow()->compare(*fl) )
        fai->receiveAllocateRequest();
}
/*
void LisFAICreReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    fai->receiveCreateRequest();
}
*/
void LisFAICreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponsePositive initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Only FAI with same CepId and PortId process this call
        if (fai->getFlow()->getSrcPortId() == flow->getSrcPortId()
                && fai->getFlow()->getConId().getSrcCepId() == flow->getConId().getSrcCepId() ) {
            //EV << "A!!!!!!!!!!!!!!IN" << endl;
            fai->receiveCreateResponsePositive(flow);
        }

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
        fai->receiveCreateResponseNegative();
    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAIDelRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteResponse initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if ( fai->getFlow()->compare(*flow) )
            fai->receiveDeleteResponse();
    }
    else
        EV << "FAIListener received unknown object!" << endl;

}

void LisFAIDelReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
//    EV << fl->info() << endl << "=================="<< endl << fai->getFlow()->info();
//    EV << "srcAPNI = " << (fai->getFlow()->getSrcApni() == fl->getSrcApni()) << endl
//        << "dstAPNI = " << (fai->getFlow()->getDstApni() == fl->getDstApni()) << endl
//        << "srcPortId = " << (fai->getFlow()->getSrcPortId() == fl->getSrcPortId()) << endl
//        << "dstPortId = " << (fai->getFlow()->getDstPortId() == fl->getDstPortId()) << endl
//        << "srcAddr = " << (fai->getFlow()->getSrcAddr() == fl->getSrcAddr()) << endl
//        << "dstAddr = " << (fai->getFlow()->getDstAddr() == fl->getDstAddr()) << endl;
//    EV << "Vysledek> " << (fai->getFlow() == fl) << endl;
    if ( fai->getFlow()->compare(*fl) )
        fai->receiveDeleteRequest(fl);
}

void LisFAICreResPosiNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponsePositiveNminusOne initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getApname() == flow->getSrcApni().getApn() ) {
            //EV << "B!!!!!!!!!!!!!!IN" << endl;
            fai->receiveCreateFlowResponsePositiveFromNminusOne();
        }

    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAICreResNegaNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getApname() == flow->getSrcApni().getApn() )
            fai->receiveCreateFlowResponseNegativeFromNminusOne();
    }
    else
        EV << "FAIListener received unknown object!" << endl;

}
