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

#include "DAF/Enrollment/DAFEnrollmentNotifier.h"


const char* DAF_MSG_ENROLLMENT      = "Enrollment";
const int DAF_VAL_DEFINSTANCE     = -1;

Define_Module(DAFEnrollmentNotifier);

void DAFEnrollmentNotifier::initialize() {
    initSignalsAndListeners();
    initPointers();
}

void DAFEnrollmentNotifier::initPointers() {
    RIBd = check_and_cast<AEMgmtBase*>( getModuleByPath("^.aemgmt") );
    FlowObj = NULL;
}

void DAFEnrollmentNotifier::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getModuleByPath("^.^.^");

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
    lisDAFEnrollmentNotifierRcvCACE = new LisDAFEnrollmentNotifierRcvCACE(this);
    catcher1->subscribe(SIG_CACE_DataReceive, lisDAFEnrollmentNotifierRcvCACE);

    lisDAFEnrollmentNotifierRcvEnrollCACE = new LisDAFEnrollmentNotifierRcvEnrollCACE(this);
    catcher2->subscribe(SIG_ENROLLMENT_CACEDataSend, lisDAFEnrollmentNotifierRcvEnrollCACE);

    lisDAFEnrollmentNotifierStaEnrolReq = new LisDAFEnrollmentNotifierStaEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentRequest, lisDAFEnrollmentNotifierStaEnrolReq);

    lisDAFEnrollmentNotifierStaEnrolRes = new LisDAFEnrollmentNotifierStaEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartEnrollmentResponse, lisDAFEnrollmentNotifierStaEnrolRes);

    lisDAFEnrollmentNotifierStoEnrolReq = new LisDAFEnrollmentNotifierStoEnrolReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentRequest, lisDAFEnrollmentNotifierStoEnrolReq);

    lisDAFEnrollmentNotifierStoEnrolRes = new LisDAFEnrollmentNotifierStoEnrolRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StopEnrollmentResponse, lisDAFEnrollmentNotifierStoEnrolRes);

    lisDAFEnrollmentNotifierStaOperReq = new LisDAFEnrollmentNotifierStaOperReq(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationRequest, lisDAFEnrollmentNotifierStaOperReq);

    lisDAFEnrollmentNotifierStaOperRes = new LisDAFEnrollmentNotifierStaOperRes(this);
    catcher2->subscribe(SIG_ENROLLMENT_StartOperationResponse, lisDAFEnrollmentNotifierStaOperRes);

}

void DAFEnrollmentNotifier::setFlow(Flow* flow) {
    FlowObj = flow;
}


Flow* DAFEnrollmentNotifier::getFlow() {
    return FlowObj;
}

void DAFEnrollmentNotifier::handleMessage(cMessage *msg)
{

}

void DAFEnrollmentNotifier::signalizeMessage(CDAPMessage* msg) {
    RIBd->signalizeSendData(msg);
}


void DAFEnrollmentNotifier::sendStartEnrollmentRequest(DAFEnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentRequest()");

    CDAP_M_Start* msg = new CDAP_M_Start(DAF_MSG_ENROLLMENT);

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

void DAFEnrollmentNotifier::sendStartEnrollmentResponse(DAFEnrollmentObj* obj) {
    Enter_Method("sendStartEnrollmentResponse()");

    CDAP_M_Start_R* msg = new CDAP_M_Start_R(DAF_MSG_ENROLLMENT);

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

void DAFEnrollmentNotifier::sendStopEnrollmentRequest(DAFEnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentRequest()");

    CDAP_M_Stop* msg = new CDAP_M_Stop(DAF_MSG_ENROLLMENT);

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

void DAFEnrollmentNotifier::sendStopEnrollmentResponse(DAFEnrollmentObj* obj) {
    Enter_Method("sendStopEnrollmentResponse()");

    CDAP_M_Stop_R* msg = new CDAP_M_Stop_R(DAF_MSG_ENROLLMENT);

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

void DAFEnrollmentNotifier::sendStartOperationRequest(DAFOperationObj* obj) {
    Enter_Method("sendStartOperationRequest()");
}

void DAFEnrollmentNotifier::sendStartOperationResponse(DAFOperationObj* obj) {
    Enter_Method("sendStartOperationResponse()");
}

void DAFEnrollmentNotifier::sendCACE(CDAPMessage* msg) {
    Enter_Method("sendCACE()");

    //TODO: add invoke id

    signalizeSendCACE(msg);
}

void DAFEnrollmentNotifier::signalizeConnectResponsePositive(CDAPMessage* msg) {
    EV << "Emits ConnectResponsePositive to enrollment" << endl;
    emit(sigRIBDConResPosi, msg);
}

void DAFEnrollmentNotifier::signalizeConnectResponseNegative(CDAPMessage* msg) {
    EV << "Emits ConnectResponseNegative to enrollment" << endl;
    emit(sigRIBDConResNega, msg);
}

void DAFEnrollmentNotifier::signalizeConnectRequest(CDAPMessage* msg) {
    EV << "Emits ConnectRequest to enrollment" << endl;
    emit(sigRIBDConReq, msg);
}

void DAFEnrollmentNotifier::signalizeSendCACE(CDAPMessage* msg) {
    EV << "Emits CACE data to CACE module" << endl;
    emit(sigRIBDCACESend, msg);
}

void DAFEnrollmentNotifier::signalizeStartEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStartEnrollReq, msg);
}

void DAFEnrollmentNotifier::signalizeStartEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStartEnrollRes, msg);
}

void DAFEnrollmentNotifier::signalizeStopEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStopEnrollReq, msg);
}

void DAFEnrollmentNotifier::signalizeStopEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStopEnrollRes, msg);
}

void DAFEnrollmentNotifier::signalizeStartOperationRequest(CDAPMessage* msg) {
    EV << "Emits StartOperationRequest to enrollment" << endl;
    emit(sigRIBDStartOperationReq, msg);
}

void DAFEnrollmentNotifier::processMConnect(CDAP_M_Connect* msg) {
    EV << "Received M_Connect";
    signalizeConnectRequest(msg);
}

void DAFEnrollmentNotifier::processMConnectR(CDAP_M_Connect_R* msg) {
    EV << "Received M_Connect_R";
    if (!msg->getResult().resultValue) {
       signalizeConnectResponsePositive(msg);
    }
    else {
       signalizeConnectResponseNegative(msg);
    }
}

void DAFEnrollmentNotifier::processMStart(CDAP_M_Start* msg) {
//    EV << "Received M_Start";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<DAFEnrollmentObj*>(object.objectVal)) {
       signalizeStartEnrollmentRequest(msg);
    }
}

void DAFEnrollmentNotifier::processMStartR(CDAP_M_Start_R* msg) {
//    EV << "Received M_Start_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<DAFEnrollmentObj*>(object.objectVal)) {
        signalizeStartEnrollmentResponse(msg);
    }
}

void DAFEnrollmentNotifier::processMStop(CDAP_M_Stop* msg) {
//    EV << "Received M_Stop";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<DAFEnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentRequest(msg);
    }
}

void DAFEnrollmentNotifier::processMStopR(CDAP_M_Stop_R* msg) {
//    EV << "Received M_Stop_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //Enrollment
    if (dynamic_cast<DAFEnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentResponse(msg);
    }
}

void DAFEnrollmentNotifier::signalizeStartOperationResponse(CDAPMessage* msg) {
    EV << "Emits StartOperationResponse to enrollment" << endl;
    emit(sigRIBDStartOperationRes, msg);
}
