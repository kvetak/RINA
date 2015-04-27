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

#include <EnrollmentListeners.h>

EnrollmentListeners::EnrollmentListeners(Enrollment* nenrollment): enrollment(nenrollment) {
}

EnrollmentListeners::~EnrollmentListeners() {
    enrollment = NULL;
}

void LisEnrollmentAllResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationResponsePositive initiated by " << src->getFullPath() << " and processed by " << enrollment->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        enrollment->startCACE(flow);
    }
    else
        EV << "EnrollmentListener received unknown object!" << endl;

}


void LisEnrollmentGetFlowFromFaiCreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        enrollment->insertStateTableEntry(flow);
    else
        EV << "EnrollmentListener received unknown object!" << endl;
}


void LisEnrollmentStartEnrollReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStartEnrollmentRequest(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentStartEnrollRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStartEnrollmentResponse(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentStopEnrollReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStopEnrollmentRequest(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentStopEnrollRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStopEnrollmentResponse(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentStopOperationReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStartOperationRequest(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentStartOperationRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveStartOperationResponse(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentConResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receivePositiveConnectResponse(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentConResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveNegativeConnectResponse(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}

void LisEnrollmentConReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        enrollment->receiveConnectRequest(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}
