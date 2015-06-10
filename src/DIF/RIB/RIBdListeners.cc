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

#include "RIBdListeners.h"
#include "IntRoutingUpdate.h"


RIBdListeners::RIBdListeners(RIBdBase* nribd) : ribd(nribd)
{
}

RIBdListeners::~RIBdListeners() {
    ribd = NULL;
}

void LisRIBDCreReq::receiveSignal(cComponent* src, simsignal_t id, cObject* obj) {
    EV << "CreateRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->sendCreateRequestFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDRcvData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveData initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        ribd->receiveData(cimsg);
    }
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDAllReqFromFai::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "AllocationRequest{fromFAI} initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow) {
        //Check whether dstApp is local...
        const APN dstApn = flow->getSrcApni().getApn();
        if (ribd->getMyAddress().getApname() == dstApn) {
            EV << "DST>" << dstApn << "    MyAddr> " << ribd->getMyAddress().getApname() << endl;;
            ribd->receiveAllocationRequestFromFai(flow);
        }
    }
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDCreResNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponseFlowNegative initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->sendCreateResponseNegative(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDCreResPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateResponseFlowPositive initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->sendCreateResponsePostive(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDDelReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->sendDeleteRequestFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDDelRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "DeleteResponse initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->sendDeleteResponseFlow(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDCreFloNega::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateFlowNegative initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->receiveCreateFlowNegativeFromRa(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDCreFloPosi::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "CreateFlowPositive initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
        ribd->receiveCreateFlowPositiveFromRa(flow);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDRoutingUpdate::receiveSignal(
        cComponent* src, simsignal_t id, cObject* obj)
{
    EV << "LisRIBDRoutingUpdate initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;

    IntRoutingUpdate * info = dynamic_cast<IntRoutingUpdate *>(obj);

    if (info)
    {
        ribd->receiveRoutingUpdateFromRouting(info);
    }
    else
    {
        EV << "ForwardingInfoUpdate listener received unknown object!" << endl;
    }
}

void LisRIBDCongesNotif::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "LisRIBDCongesNotif initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;

    PDU* pdu = dynamic_cast<PDU*>(obj);
    if (pdu)
       ribd->sendCongestionNotification(pdu);
    else
       EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDRcvCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "ReceiveCACEData initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        ribd->receiveCACE(cimsg);
    }
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDRcvEnrollCACE::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "Send CACE from Enrollment" << endl;
    CDAPMessage* cimsg = dynamic_cast<CDAPMessage*>(obj);
    if (cimsg) {
        ribd->sendCACE(cimsg);
    }
    else
        EV << "RIBdListener received unknown object!" << endl;
}

void LisRIBDStaEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        ribd->sendStartEnrollmentRequest(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        ribd->sendStartEnrollmentResponse(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStoEnrolReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StopEnrollmentRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        ribd->sendStopEnrollmentRequest(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStoEnrolRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StopEnrollmentResponse initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    EnrollmentObj* enroll = dynamic_cast<EnrollmentObj*>(obj);
    if (enroll)
        ribd->sendStopEnrollmentResponse(enroll);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaOperReq::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartOperationRequest initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        ribd->sendStartOperationRequest(oper);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

void LisRIBDStaOperRes::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj) {
    EV << "StartOperationResponse initiated by " << src->getFullPath()
       << " and processed by " << ribd->getFullPath() << endl;
    OperationObj* oper = dynamic_cast<OperationObj*>(obj);
    if (oper)
        ribd->sendStartOperationResponse(oper);
    else
        EV << "RIBdListener received unknown object!" << endl;

}

