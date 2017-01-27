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

#include "APListeners.h"

APListeners::APListeners(AP* nap) : ap(nap) {
}

APListeners::~APListeners() {
    ap = NULL;
}

void LisAPAllReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ap->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        const APNamingInfo dstApni = flow->getSrcApni();
        if (std::strcmp(dstApni.getAename().c_str(),""))
            if (ap->getCurrentAEInstNum(dstApni.getAename()) < std::stoi(dstApni.getAeinstance()) ||
                std::stoi(dstApni.getAeinstance()) == -1)
                { ap->receiveAllocationRequestFromFAI(flow); }
    }
    else
        EV << "APListener received unknown object!" << endl;
}

void LisAEAPAPI::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "APWriteR initiated by " << src->getFullPath()
       << " and processed by " << ap->getFullPath() << endl;
    APIResult* result = dynamic_cast<APIResult*>(obj);
    if (result) {
        ap->resultAssign(result);
    }
    else
        EV << "APListener received unknown object!" << endl;
}


void LisAPEnrolled::receiveSignal(cComponent* src, simsignal_t id,
        long obj, cObject *detail) {
    EV << "APEnrollmentEnrolled initiated by " << src->getFullPath()
           << " and processed by " << ap->getFullPath() << endl;
    ap->startRequestedConnections();
}
