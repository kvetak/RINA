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

#include "DIF/FA/FAIListeners.h"
#include "Common/Flow.h"
#include "DIF/FA/FABase.h"
#include "DIF/FA/FAI.h"

FAIListeners::FAIListeners(FAI* nfai) : fai(nfai) {}

FAIListeners::~FAIListeners() {}

void LisFAIAllocResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "AllocateResponsePositive initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if (fai->getFlow() == fl)
        fai->receiveAllocateResponsePositive();
}

void LisFAIAllocResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "AllocateResponseNegative initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if (fai->getFlow() == fl)
        fai->receiveAllocateResponseNegative();
}

void LisFAICreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateResponsePositive initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Only FAI with same CepId and PortId process this call
        if (fai->getFlow()->getSrcPortId() == flow->getSrcPortId()
                && fai->getFlow()->getConId().getSrcCepId() == flow->getConId().getSrcCepId()
                ) {
            //EV << "A!!!!!!!!!!!!!!IN" << endl;
            fai->receiveCreateResponsePositive(flow);
        }
    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAICreResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
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
        cObject* obj, cObject *detail) {
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
        cObject* obj, cObject *detail) {
    EV << "DeleteRequest initiated by " << src->getFullPath() << " and processed by " << fai->getFullPath() << endl;
    Flow* fl = dynamic_cast<Flow*>(obj);
    if ( fai->getFlow()->compare(*fl) )
        fai->receiveDeleteRequest(fl);
}

void LisFAICreResPosiNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "CreateResponsePositiveNminusOne initiated by " << src->getFullPath()
       << " and processed by " << fai->getFullPath() << endl;

    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getApn() == flow->getSrcApni().getApn()
            && fai->getFlow()->getConId().getQoSId() == flow->getConId().getQoSId()
            && !flow->isManagementFlow()
                ) {
            fai->receiveCreateFlowResponsePositiveFromNminusOne();
        }

    }
    else
        EV << "FAIListener received unknown object!" << endl;
}

void LisFAICreResNegaNminusOne::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (fai->getFa()->getMyAddress().getApn() == flow->getSrcApni().getApn() )
            fai->receiveCreateFlowResponseNegativeFromNminusOne();
    }
    else
        EV << "FAIListener received unknown object!" << endl;

}
