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

#include "AEMgmtListeners.h"
#include "IntRoutingUpdate.h"


AEMgmtListeners::AEMgmtListeners(AEMgmtBase* naemgmt) : aemgmt(naemgmt)
{
}

AEMgmtListeners::~AEMgmtListeners() {
    aemgmt = NULL;
}


void LisAEMgmtRcvData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveData initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        aemgmt->receiveData(cimsg);
    }
    else
        EV << "AEMgmtListener received unknown object!" << endl;
}

void LisAEMgmtRcvCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveCACEData initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        aemgmt->receiveCACE(cimsg);
    }
    else
        EV << "AEMgmtListener received unknown object!" << endl;
}

void LisAEMgmtRcvEnrollCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "Send CACE from Enrollment" << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        aemgmt->sendCACE(cimsg);
    }
    else
        EV << "AEMgmtListener received unknown object!" << endl;
}

void LisAEMgmtStaEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        aemgmt->sendStartEnrollmentRequest(enroll);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

void LisAEMgmtStaEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        aemgmt->sendStartEnrollmentResponse(enroll);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

void LisAEMgmtStoEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StopEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        aemgmt->sendStopEnrollmentRequest(enroll);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

void LisAEMgmtStoEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StopEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        aemgmt->sendStopEnrollmentResponse(enroll);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

void LisAEMgmtStaOperReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartOperationRequest initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        aemgmt->sendStartOperationRequest(oper);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

void LisAEMgmtStaOperRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartOperationResponse initiated by " << src->getFullPath()
       << " and processed by " << aemgmt->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        aemgmt->sendStartOperationResponse(oper);
    else
        EV << "AEMgmtListener received unknown object!" << endl;

}

