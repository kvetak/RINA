//
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
/**
 * @file AEMgmt.cc
 * @author Vladimir Vesely, Kamil Jerabek (ivesely@fit.vutbr.cz, xjerab18@fit.vutbr.cz)
 * @date Oct 2, 2015
 * @brief Kind of a Notification Board for DAF
 * @detail
 */

#include "AEMgmt.h"

Define_Module(AEMgmt);

const char* DAF_MSG_CONGEST         = "Congestion";
const char* DAF_MSG_FLO             = "Flow";
const char* DAF_MSG_FLOPOSI         = "Flow+";
const char* DAF_MSG_FLONEGA         = "Flow-";
const int   DAF_VAL_DEFINSTANCE     = -1;
const int   DAF_VAL_FLOWPOSI        = 1;
const int   DAF_VAL_FLOWNEGA        = 0;
const char* DAF_VAL_FLREQ           = "Request  ";
const char* DAF_VAL_FLREQPOSI       = "Response+  ";
const char* DAF_VAL_FLREQNEGA       = "Response-  ";
const char* DAF_MSG_ROUTINGUPDATE   = "RoutingUpdate";
const char* DAF_MSG_ENROLLMENT      = "Enrollment";

void AEMgmt::initialize() {
    //Init signals and listeners
    initSignalsAndListeners();
}

void AEMgmt::handleMessage(cMessage *msg) {

}



void AEMgmt::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //M_START_Request
    if (dynamic_cast<CDAP_M_Start*>(msg)) {
        processMStart(msg);
    }
    //M_START_Response
    else if (dynamic_cast<CDAP_M_Start_R*>(msg)) {
        processMStartR(msg);
    }
    //M_Stop_Request
    else if (dynamic_cast<CDAP_M_Stop*>(msg)) {
        processMStop(msg);
    }
    //M_Stop_Response
    else if (dynamic_cast<CDAP_M_Stop_R*>(msg)) {
        processMStopR(msg);
    }

    delete msg;
}

void AEMgmt::receiveCACE(CDAPMessage* msg) {
    Enter_Method("receiveCACE()");

    //M_CONNECT_Request
    if (dynamic_cast<CDAP_M_Connect*>(msg)) {
        processMConnect(msg);
    }
    //M_CONNECT_Response
    else if (dynamic_cast<CDAP_M_Connect_R*>(msg)) {
        processMConnectR(msg);
    }

    delete msg;
}

void AEMgmt::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getParentModule()->getParentModule();

    //Signals that this module is emitting
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


    //Signals that this module is processing
    lisAEMgmtRcvCACE = new LisAEMgmtRcvCACE(this);
    catcher1->subscribe(SIG_CACE_DataReceive, lisAEMgmtRcvCACE);

    lisAEMgmtRcvEnrollCACE = new LisAEMgmtRcvEnrollCACE(this);
    catcher2->subscribe(SIG_ENROLLMENT_CACEDataSend, lisAEMgmtRcvEnrollCACE);

    lisAEMgmtStaEnrolReq = new LisAEMgmtStaEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentRequest, lisAEMgmtStaEnrolReq);

    lisAEMgmtStaEnrolRes = new LisAEMgmtStaEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentResponse, lisAEMgmtStaEnrolRes);

    lisAEMgmtStoEnrolReq = new LisAEMgmtStoEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentRequest, lisAEMgmtStoEnrolReq);

    lisAEMgmtStoEnrolRes = new LisAEMgmtStoEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentResponse, lisAEMgmtStoEnrolRes);

    lisAEMgmtStaOperReq = new LisAEMgmtStaOperReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationRequest, lisAEMgmtStaOperReq);

    lisAEMgmtStaOperRes = new LisAEMgmtStaOperRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationResponse, lisAEMgmtStaOperRes);

}

void AEMgmt::signalizeSendData(CDAPMessage* msg) {
    //Check dstAddress
    if (msg->getDstAddr() == Address::UNSPECIFIED_ADDRESS) {
        EV << "Destination address cannot be UNSPECIFIED!" << endl;
        return;
    }

    msg->setBitLength(msg->getBitLength() + msg->getHeaderBitLength());
    //Pass message to CDAP
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigRIBDSendData, msg);
}

void AEMgmt::signalizeConnectResponsePositive(CDAPMessage* msg) {
    EV << "Emits ConnectResponsePositive to enrollment" << endl;
    emit(sigRIBDConResPosi, msg);
}

void AEMgmt::signalizeConnectResponseNegative(CDAPMessage* msg) {
    EV << "Emits ConnectResponseNegative to enrollment" << endl;
    emit(sigRIBDConResNega, msg);
}

void AEMgmt::signalizeConnectRequest(CDAPMessage* msg) {
    EV << "Emits ConnectRequest to enrollment" << endl;
    emit(sigRIBDConReq, msg);
}

void AEMgmt::signalizeSendCACE(CDAPMessage* msg) {
    EV << "Emits CACE data to CACE module" << endl;
    emit(sigRIBDCACESend, msg);
}

void AEMgmt::signalizeStartEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStartEnrollReq, msg);
}

void AEMgmt::signalizeStartEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStartEnrollRes, msg);
}

void AEMgmt::signalizeStopEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStopEnrollReq, msg);
}

void AEMgmt::signalizeStopEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStopEnrollRes, msg);
}

void AEMgmt::signalizeStartOperationRequest(CDAPMessage* msg) {
    EV << "Emits StartOperationRequest to enrollment" << endl;
    emit(sigRIBDStartOperationReq, msg);
}

void AEMgmt::signalizeStartOperationResponse(CDAPMessage* msg) {
    EV << "Emits StartOperationResponse to enrollment" << endl;
    emit(sigRIBDStartOperationRes, msg);
}

void AEMgmt::sendStartEnrollmentRequest(EnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentRequest()");

    CDAP_M_Start* msg = new CDAP_M_Start(DAF_MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = DAF_VAL_DEFINSTANCE;
    msg->setObject(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeSendData(msg);
}

void AEMgmt::sendStartEnrollmentResponse(EnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentResponse()");

    CDAP_M_Start_R* msg = new CDAP_M_Start_R(DAF_MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = DAF_VAL_DEFINSTANCE;
    msg->setObject(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());


    signalizeSendData(msg);
}

void AEMgmt::sendStopEnrollmentRequest(EnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentRequest()");

    CDAP_M_Stop* msg = new CDAP_M_Stop(DAF_MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = DAF_VAL_DEFINSTANCE;
    msg->setObject(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeSendData(msg);
}

void AEMgmt::sendStopEnrollmentResponse(EnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentResponse()");

    CDAP_M_Stop_R* msg = new CDAP_M_Stop_R(DAF_MSG_ENROLLMENT);

    //TODO: assign appropriate values
    std::ostringstream os;
    os << "Enrollment";
    object_t enrollobj;
    enrollobj.objectClass = obj->getClassName();
    enrollobj.objectName = os.str();
    enrollobj.objectVal = obj;
    enrollobj.objectInstance = DAF_VAL_DEFINSTANCE;
    msg->setObject(enrollobj);

    //TODO: check and rework generate invoke id
    //msg->setInvokeID(getNewInvokeId());

    //Append src/dst address for RMT "routing"
    msg->setSrcAddr(obj->getSrcAddress());
    msg->setDstAddr(obj->getDstAddress());

    signalizeSendData(msg);
}

void AEMgmt::sendStartOperationRequest(OperationObj* obj) {
    Enter_Method("sendStartOperationRequest()");
}

void AEMgmt::sendStartOperationResponse(OperationObj* obj) {
    Enter_Method("sendStartOperationResponse()");
}

void AEMgmt::processMConnect(CDAPMessage* msg) {
    CDAP_M_Connect* msg1 = check_and_cast<CDAP_M_Connect*>(msg);

    EV << "Received M_Connect";

    if (msg1) {
        signalizeConnectRequest(msg);
    }
}

void AEMgmt::processMConnectR(CDAPMessage* msg) {
    CDAP_M_Connect_R* msg1 = check_and_cast<CDAP_M_Connect_R*>(msg);

    EV << "Received M_Connect_R";

    if (msg1) {
        if (!msg1->getResult().resultValue) {
            signalizeConnectResponsePositive(msg);
        }
        else {
            signalizeConnectResponseNegative(msg);
        }
    }
}

void AEMgmt::processMStart(CDAPMessage* msg) {
    CDAP_M_Start* msg1 = check_and_cast<CDAP_M_Start*>(msg);

    EV << "Received M_Start";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
       signalizeStartEnrollmentRequest(msg);
    }

}

void AEMgmt::processMStartR(CDAPMessage* msg) {
    CDAP_M_Start_R* msg1 = check_and_cast<CDAP_M_Start_R*>(msg);

    EV << "Received M_Start_R";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStartEnrollmentResponse(msg);
    }
}

void AEMgmt::processMStop(CDAPMessage* msg) {
    CDAP_M_Stop* msg1 = check_and_cast<CDAP_M_Stop*>(msg);

    EV << "Received M_Stop";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentRequest(msg);
    }
}

void AEMgmt::processMStopR(CDAPMessage* msg) {
    CDAP_M_Stop_R* msg1 = check_and_cast<CDAP_M_Stop_R*>(msg);

    EV << "Received M_Stop_R";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentResponse(msg);
    }
}

void AEMgmt::sendCACE(CDAPMessage* msg) {
    Enter_Method("sendCACE()");

    //TODO: add invoke id

    signalizeSendCACE(msg);
}
