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

#include "DIF/Enrollment/EnrollmentNotifier.h"

const char* MSG_ENROLLMENT      = "Enrollment";

Define_Module(EnrollmentNotifier);

void EnrollmentNotifier::initialize()
{
    initSignalsAndListeners();
    initPointers();
}

void EnrollmentNotifier::initPointers() {
    RIBd = check_and_cast<RIBdBase*>( getModuleByPath("^.ribd") );
}

void EnrollmentNotifier::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getModuleByPath("^.^");
    //cModule* catcher3 = this->getModuleByPath("^.^.^");

    sigRIBDStartEnrollReq = registerSignal(SIG_RIBD_StartEnrollmentRequest);
    sigRIBDStartEnrollRes = registerSignal(SIG_RIBD_StartEnrollmentResponse);
    sigRIBDStopEnrollReq  = registerSignal(SIG_RIBD_StopEnrollmentRequest);
    sigRIBDStopEnrollRes  = registerSignal(SIG_RIBD_StopEnrollmentResponse);
    sigRIBDStartOperationReq = registerSignal(SIG_RIBD_StartOperationRequest);
    sigRIBDStartOperationRes = registerSignal(SIG_RIBD_StartOperationResponse);
    sigRIBDConResPosi    = registerSignal(SIG_RIBD_ConnectionResponsePositive);
    sigRIBDConResNega    = registerSignal(SIG_RIBD_ConnectionResponseNegative);
    sigRIBDConReq        = registerSignal(SIG_RIBD_ConnectionRequest);
    sigRIBDCACESend      = registerSignal(SIG_RIBD_CACESend);

    lisRIBDRcvCACE = new LisRIBDRcvCACE(this);
    catcher1->subscribe(SIG_CACE_DataReceive, lisRIBDRcvCACE);

    lisRIBDRcvEnrollCACE = new LisRIBDRcvEnrollCACE(this);
    catcher2->subscribe(SIG_ENROLLMENT_CACEDataSend, lisRIBDRcvEnrollCACE);

    lisRIBDStaEnrolReq = new LisRIBDStaEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentRequest, lisRIBDStaEnrolReq);

    lisRIBDStaEnrolRes = new LisRIBDStaEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentResponse, lisRIBDStaEnrolRes);

    lisRIBDStoEnrolReq = new LisRIBDStoEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentRequest, lisRIBDStoEnrolReq);

    lisRIBDStoEnrolRes = new LisRIBDStoEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentResponse, lisRIBDStoEnrolRes);

    lisRIBDStaOperReq = new LisRIBDStaOperReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationRequest, lisRIBDStaOperReq);

    lisRIBDStaOperRes = new LisRIBDStaOperRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationResponse, lisRIBDStaOperRes);

}

void EnrollmentNotifier::handleMessage(cMessage *msg)
{

}

void EnrollmentNotifier::signalizeMessage(CDAPMessage* msg) {
    RIBd->signalizeSendData(msg);
}


void EnrollmentNotifier::sendStartEnrollmentRequest(EnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentRequest()");

    CDAP_M_Start* msg = new CDAP_M_Start(MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = VAL_DEFINSTANCE;
    msg->setObjectItem(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeMessage(msg);
}

void EnrollmentNotifier::sendStartEnrollmentResponse(EnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentResponse()");

    CDAP_M_Start_R* msg = new CDAP_M_Start_R(MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = VAL_DEFINSTANCE;
    msg->setObjectItem(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());


    signalizeMessage(msg);
}

void EnrollmentNotifier::sendStopEnrollmentRequest(EnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentRequest()");

    CDAP_M_Stop* msg = new CDAP_M_Stop(MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = VAL_DEFINSTANCE;
    msg->setObjectItem(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeMessage(msg);
}

void EnrollmentNotifier::sendStopEnrollmentResponse(EnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentResponse()");

    CDAP_M_Stop_R* msg = new CDAP_M_Stop_R(MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = VAL_DEFINSTANCE;
    msg->setObjectItem(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeMessage(msg);
}

void EnrollmentNotifier::sendStartOperationRequest(OperationObj* obj) {
    Enter_Method("sendStartOperationRequest()");
}

void EnrollmentNotifier::sendStartOperationResponse(OperationObj* obj) {
    Enter_Method("sendStartOperationResponse()");
}

void EnrollmentNotifier::sendCACE(CDAPMessage* msg) {
    Enter_Method("sendCACE()");

    //TODO: add invoke id

    signalizeSendCACE(msg);
}

void EnrollmentNotifier::signalizeConnectResponsePositive(CDAPMessage* msg) {
    EV << "Emits ConnectResponsePositive to enrollment" << endl;
    emit(sigRIBDConResPosi, msg);
}

void EnrollmentNotifier::signalizeConnectResponseNegative(CDAPMessage* msg) {
    EV << "Emits ConnectResponseNegative to enrollment" << endl;
    emit(sigRIBDConResNega, msg);
}

void EnrollmentNotifier::signalizeConnectRequest(CDAPMessage* msg) {
    EV << "Emits ConnectRequest to enrollment" << endl;
    emit(sigRIBDConReq, msg);
}

void EnrollmentNotifier::signalizeSendCACE(CDAPMessage* msg) {
    EV << "Emits CACE data to CACE module" << endl;
    emit(sigRIBDCACESend, msg);
}

void EnrollmentNotifier::signalizeStartEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStartEnrollReq, msg);
}

void EnrollmentNotifier::signalizeStartEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStartEnrollRes, msg);
}

void EnrollmentNotifier::signalizeStopEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStopEnrollReq, msg);
}

void EnrollmentNotifier::signalizeStopEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStopEnrollRes, msg);
}

void EnrollmentNotifier::signalizeStartOperationRequest(CDAPMessage* msg) {
    EV << "Emits StartOperationRequest to enrollment" << endl;
    emit(sigRIBDStartOperationReq, msg);
}

void EnrollmentNotifier::processMConnect(CDAP_M_Connect* msg) {
    EV << "Received M_Connect";
    signalizeConnectRequest(msg);
}

void EnrollmentNotifier::processMConnectR(CDAP_M_Connect_R* msg) {
    EV << "Received M_Connect_R";
    if (!msg->getResult().resultValue) {
       signalizeConnectResponsePositive(msg);
    }
    else {
       signalizeConnectResponseNegative(msg);
    }
}

void EnrollmentNotifier::processMStart(CDAP_M_Start* msg) {
//    EV << "Received M_Start";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
       signalizeStartEnrollmentRequest(msg);
    }
}

void EnrollmentNotifier::processMStartR(CDAP_M_Start_R* msg) {
//    EV << "Received M_Start_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStartEnrollmentResponse(msg);
    }
}

void EnrollmentNotifier::processMStop(CDAP_M_Stop* msg) {
//    EV << "Received M_Stop";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentRequest(msg);
    }
}

void EnrollmentNotifier::processMStopR(CDAP_M_Stop_R* msg) {
//    EV << "Received M_Stop_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentResponse(msg);
    }
}

void EnrollmentNotifier::signalizeStartOperationResponse(CDAPMessage* msg) {
    EV << "Emits StartOperationResponse to enrollment" << endl;
    emit(sigRIBDStartOperationRes, msg);
}
