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

#include "DAF/AE/AE.h"
#include "DAF/AE/AEListeners.h"

AEListeners::AEListeners(AE* nae) : ae(nae)
{
}

AEListeners::~AEListeners() {
    ae = NULL;
}

void LisAEReceiveData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
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
        cObject* obj, cObject *detail) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        //const APN dstApn = flow->getSrcApni().getApn();
        //if (ae->getApni().getApn() == dstApn)
        const APNamingInfo dstApni = flow->getSrcApni();
        if (ae->getApni() == dstApni)
            { ae->receiveAllocationRequestFromFAI(flow); }
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEAllResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
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
        cObject* obj, cObject *detail) {
    EV << "AllocateResponseNegative initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        if (ae->hasFlow(flow))
            ae->receiveAllocationResponseNegative(flow);
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEDeallReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "DeallocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        //const APN dstApn = flow->getSrcApni().getApn();
        //if (ae->getApni().getApn() == dstApn && ae->hasFlow(flow))
        const APNamingInfo dstApni = flow->getSrcApni();
        if (ae->getApni() == dstApni && ae->hasFlow(flow))
            { ae->receiveDeallocationRequestFromFAI(flow); }
    }
    else
        EV << "AEListener received unknown object!" << endl;
}

void LisAEConResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {

    ae->changeConStatus(ESTABLISHED);
    //TODO: signalize that result is available --> api call
}

void LisAEConResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {

    ae->changeConStatus(CONNECTION_PENDING);
    //TODO: signalize that result is available --> api call

}

void LisAERelRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {

    ae->changeConStatus(NIL);
    //TODO: signalize that ae can close flow, result is available --> api call
}

void LisAEEnrolled::receiveSignal(cComponent* src, simsignal_t id,
        long obj, cObject *detail) {

    //TODO: checks before call
    //ae->afterOnStart();
}

void LisAPAEAPI::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "APIRequest initiated by " << src->getFullPath()
       << " and processed by " << ae->getFullPath() << endl;
    APIReqObj* apiObj = dynamic_cast<APIReqObj*>(obj);
    if (apiObj->getCDAPConId() == ae->getCdapConId()) {
        ae->apiSwitcher(apiObj);
    }
}
