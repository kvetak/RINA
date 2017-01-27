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

#include "DIF/Enrollment/EnrollmentNotifierListeners.h"

EnrollmentNotifierListeners::EnrollmentNotifierListeners(EnrollmentNotifierBase* nenb) : enb(nenb)
{
}

EnrollmentNotifierListeners::~EnrollmentNotifierListeners() {
    enb = NULL;
}

void LisRIBDRcvCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "ReceiveCACEData initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        enb->receiveMessage(cimsg);
    }
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDRcvEnrollCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "Send CACE from Enrollment" << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        enb->sendCACE(cimsg);
    }
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDStaEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StartEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        enb->sendStartEnrollmentRequest(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StartEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        enb->sendStartEnrollmentResponse(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStoEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StopEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        enb->sendStopEnrollmentRequest(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStoEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StopEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        enb->sendStopEnrollmentResponse(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaOperReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StartOperationRequest initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        enb->sendStartOperationRequest(oper);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaOperRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "StartOperationResponse initiated by " << src->getFullPath()
       << " and processed by " << enb->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        enb->sendStartOperationResponse(oper);
    else
        EV << "RIBdListener received unknown object!" << endl;

}
