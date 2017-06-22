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
 * @file RIBd.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief Kind of a Notification Board for DIF
 * @detail
 */

#include "DIF/RIB/RIBd.h"

const char* MSG_CONGEST         = "Congestion";
//const char* MSG_ROUTINGUPDATE   = "RoutingUpdate";
//const char* MSG_ENROLLMENT      = "Enrollment";

const char* PAR_USEFANOTIF          = "useFANotifier";
const char* PAR_USEENROLLNOTIF      = "useEnrollmentNotifier";
const char* PAR_USEROUTINGNOTIF      = "useRoutingNotifier";

Define_Module(RIBd);

void RIBd::initialize() {

    useFANotifier = false;
    useEnrollmentNotifier = false;
    useRoutingNotifier = false;

    //Init signals and listeners
    initSignalsAndListeners();

    //Init MyAddress
    initMyAddress();

    //Pointers
    initPointers();
}

void RIBd::initPointers() {
    FANotif = getRINAModule<FANotifierBase*>(this, 1, {"faNotifier"}, false);
    if (FANotif) {
        useFANotifier = true;
        this->par(PAR_USEFANOTIF) = true;
    }
    EnrollNotif = getRINAModule<EnrollmentNotifierBase*>(this, 1, {"enrollmentNotifier"}, false);
    if (EnrollNotif) {
        useEnrollmentNotifier = true;
        this->par(PAR_USEENROLLNOTIF) = true;
    }
    RoutingNotif = getRINAModule<RoutingNotifierBase*>(this, 1, {"routingNotifier"}, false);
    if (RoutingNotif) {
        useRoutingNotifier = true;
        this->par(PAR_USEROUTINGNOTIF) = true;
    }
}

void RIBd::handleMessage(cMessage *msg) {

}

/*
void RIBd::receiveAllocationRequestFromFai(Flow* flow) {
    Enter_Method("receiveAllocationRequestFromFai()");
    if (flow->isManagementFlowLocalToIPCP())
    {
        receiveCreateFlowPositiveFromRa(flow);
    }
    else {
        //Execute flow allocate
        signalizeCreateFlow(flow);
    }
}

void RIBd::receiveCreateFlowPositiveFromRa(Flow* flow) {
    signalizeAllocateResponsePositive(flow);
}

void RIBd::receiveCreateFlowNegativeFromRa(Flow* flow) {
    signalizeAllocateResponseNegative(flow);
}

void RIBd::sendCreateRequestFlow(Flow* flow) {
    Enter_Method("sendCreateRequestFlow()");

    //Prepare M_CREATE Flow
    CDAP_M_Create* mcref = new CDAP_M_Create(MSG_FLO);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObjectItem(flowobj);

    //Append src/dst address for RMT "routing"
    mcref->setSrcAddr(flow->getSrcNeighbor());
    mcref->setDstAddr(flow->getDstNeighbor());

    //Generate InvokeId
    if (!flow->getAllocInvokeId())
        flow->setAllocInvokeId(getNewInvokeId());
    mcref->setInvokeID(flow->getAllocInvokeId());

    //Send it
    signalizeSendData(mcref);
}

void RIBd::sendDeleteRequestFlow(Flow* flow) {
    Enter_Method("sendDeleteRequestFlow()");

    //Prepare M_CREATE Flow
    CDAP_M_Delete* mdereqf = new CDAP_M_Delete(MSG_FLO);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mdereqf->setObjectItem(flowobj);

    //Append src/dst address for RMT "routing"
    mdereqf->setSrcAddr(flow->getSrcNeighbor());
    mdereqf->setDstAddr(flow->getDstAddr());

    //Generate InvokeId
    if (!flow->getDeallocInvokeId())
        flow->setDeallocInvokeId(getNewInvokeId());
    mdereqf->setInvokeID(flow->getDeallocInvokeId());

    //Send it
    signalizeSendData(mdereqf);
}

void RIBd::sendCreateResponseNegative(Flow* flow) {
    Enter_Method("sendCreateResponseFlowNegative()");

    //Prepare M_CREATE_R Flow-
    CDAP_M_Create_R* mcref = new CDAP_M_Create_R(MSG_FLONEGA);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObjectItem(flowobj);

    //Prepare result object
    result_t resultobj;
    resultobj.resultValue = R_FAIL;
    mcref->setResult(resultobj);

    //Generate InvokeId
    mcref->setInvokeID(flow->getAllocInvokeId());

    //Append src/dst address for RMT "routing"
    mcref->setSrcAddr(flow->getSrcNeighbor());
    mcref->setDstAddr(flow->getDstAddr());

    //Send it
    signalizeSendData(mcref);
}

void RIBd::sendCreateResponsePostive(Flow* flow) {
    Enter_Method("sendCreateResponseFlowPositive()");

    //Prepare M_CREATE_R Flow+
    CDAP_M_Create_R* mcref = new CDAP_M_Create_R(MSG_FLOPOSI);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObjectItem(flowobj);

    //Prepare result object
    result_t resultobj;
    resultobj.resultValue = R_SUCCESS;
    mcref->setResult(resultobj);

    //Generate InvokeId
    mcref->setInvokeID(flow->getAllocInvokeId());

    //Append src/dst address for RMT "routing"
    mcref->setSrcAddr(flow->getSrcNeighbor());
    mcref->setDstAddr(flow->getDstAddr());

    //Send it
    signalizeSendData(mcref);
}

void RIBd::sendDeleteResponseFlow(Flow* flow) {
    Enter_Method("sendDeleteResponseFlow()");

    //Prepare M_CREATE_R Flow+
    CDAP_M_Delete_R* mderesf = new CDAP_M_Delete_R(MSG_FLOPOSI);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mderesf->setObjectItem(flowobj);

    //Prepare result object
    result_t resultobj;
    resultobj.resultValue = R_SUCCESS;
    mderesf->setResult(resultobj);

    //Generate InvokeId
    mderesf->setInvokeID(flow->getDeallocInvokeId());

    //Append src/dst address for RMT "routing"
    mderesf->setSrcAddr(flow->getSrcNeighbor());
    mderesf->setDstAddr(flow->getDstAddr());

    //Send it
    signalizeSendData(mderesf);
}

void RIBd::signalizeAllocateResponsePositive(Flow* flow) {
    EV << "Emits AllocateResponsePositive signal for flow" << endl;
    emit(sigRIBDAllocResPosi, flow);
}

void RIBd::signalizeCreateRequestFlow(Flow* flow) {
    EV << "Emits CreateRequestFlow signal for flow" << endl;
    emit(sigRIBDCreReqFlo, flow);
}

void RIBd::signalizeCreateResponseFlowPositive(Flow* flow) {
    EV << "Emits CreateResponsetFlowPositive signal for flow" << endl;
    emit(sigRIBDCreResFloPosi, flow);
}

void RIBd::signalizeCreateResponseFlowNegative(Flow* flow) {
    EV << "Emits CreateResponsetFlowNegative signal for flow" << endl;
    emit(sigRIBDCreResFloNega, flow);
}

void RIBd::signalizeCreateFlow(Flow* flow) {
    EV << "Emits CreateFlow signal for flow" << endl;
    emit(sigRIBDCreFlow, flow);
}

void RIBd::signalizeDeleteRequestFlow(Flow* flow) {
    EV << "Emits DeleteRequestFlow signal for flow" << endl;
    emit(sigRIBDDelReqFlo, flow);
}

void RIBd::signalizeAllocateResponseNegative(Flow* flow) {
    EV << "Emits AllocateResponseNegative signal for flow" << endl;
    emit(sigRIBDAllocResNega, flow);
}

void RIBd::signalizeDeleteResponseFlow(Flow* flow) {
    EV << "Emits DeleteResponseFlow signal for flow" << endl;
    emit(sigRIBDDelResFlo, flow);
}
*/
void RIBd::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //std::string xxx = FANotif->getFullPath();

    //EnrollmentNotifier processing
    if (useEnrollmentNotifier && EnrollNotif->isMessageProcessable(msg)) {
        EnrollNotif->receiveMessage(msg);
    }
    //FANotifier processing
    else if (useFANotifier && FANotif->isMessageProcessable(msg)) {
        FANotif->receiveMessage(msg);
    }
    //RoutingNotifier processing
    else if (useRoutingNotifier && RoutingNotif->isMessageProcessable(msg)) {
        RoutingNotif->receiveMessage(msg);
    }

    //TODO: Vesely - Hardcoded message processing should be removed!
    //M_WRITE_Request
//    else if (dynamic_cast<CDAP_M_Write*>(msg)) {
//        processMWrite(msg);
//    }
    //M_START_Request
    else if (dynamic_cast<CDAP_M_Start*>(msg)) {
        processMStart(msg);
    }
    /*
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
    */
    //delete msg;
}

void RIBd::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getModuleByPath("^.^");
    //cModule* catcher3 = this->getModuleByPath("^.^.^");

    //Signals that this module is emitting
    sigRIBDSendData      = registerSignal(SIG_RIBD_DataSend);
    /*
    sigRIBDCreReqFlo     = registerSignal(SIG_RIBD_CreateRequestFlow);
    sigRIBDDelReqFlo     = registerSignal(SIG_RIBD_DeleteRequestFlow);
    sigRIBDDelResFlo     = registerSignal(SIG_RIBD_DeleteResponseFlow);
    sigRIBDAllocResPosi  = registerSignal(SIG_AERIBD_AllocateResponsePositive);
    sigRIBDAllocResNega  = registerSignal(SIG_AERIBD_AllocateResponseNegative);
    sigRIBDCreFlow       = registerSignal(SIG_RIBD_CreateFlow);
    sigRIBDCreResFloPosi = registerSignal(SIG_RIBD_CreateFlowResponsePositive);
    sigRIBDCreResFloNega = registerSignal(SIG_RIBD_CreateFlowResponseNegative);
    */
    // sigRIBDFwdUpdateRecv = registerSignal(SIG_RIBD_ForwardingUpdateReceived);
    //sigRIBDRoutingUpdateRecv = registerSignal(SIG_RIBD_RoutingUpdateReceived);
    sigRIBDCongNotif     = registerSignal(SIG_RIBD_CongestionNotification);

    /*
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
    */

    //Signals that this module is processing
    /*
    lisRIBDCreReqByForward = new LisRIBDCreReq(this);
    catcher2->subscribe(SIG_FA_CreateFlowRequestForward, lisRIBDCreReqByForward);
    lisRIBDCreReq = new LisRIBDCreReq(this);
    catcher2->subscribe(SIG_FAI_CreateFlowRequest, lisRIBDCreReq);

    lisRIBDDelReq = new LisRIBDDelReq(this);
    catcher2->subscribe(SIG_FAI_DeleteFlowRequest, lisRIBDDelReq);
    lisRIBDDelRes = new LisRIBDDelRes(this);
    catcher2->subscribe(SIG_FAI_DeleteFlowResponse, lisRIBDDelRes);

    lisRIBDCreResNegaFromFa = new LisRIBDCreResNega(this);
    catcher2->subscribe(SIG_FA_CreateFlowResponseNegative, lisRIBDCreResNegaFromFa);
    lisRIBDCreResNega = new LisRIBDCreResNega(this);
    catcher2->subscribe(SIG_FAI_CreateFlowResponseNegative, lisRIBDCreResNega);

    lisRIBDCreResPosi = new LisRIBDCreResPosi(this);
    catcher2->subscribe(SIG_FAI_CreateFlowResponsePositive, lisRIBDCreResPosi);
    lisRIBDCreResPosiForward = new LisRIBDCreResPosi(this);
    catcher2->subscribe(SIG_FA_CreateFlowResponseForward, lisRIBDCreResPosiForward);

    lisRIBDAllReqFromFai = new LisRIBDAllReqFromFai(this);
    catcher3->subscribe(SIG_FAI_AllocateRequest, lisRIBDAllReqFromFai);

    lisRIBDCreFloPosi = new LisRIBDCreFloPosi(this);
    catcher2->subscribe(SIG_RA_CreateFlowPositive, lisRIBDCreFloPosi);
    lisRIBDCreFloNega = new LisRIBDCreFloNega(this);
    catcher2->subscribe(SIG_RA_CreateFlowNegative, lisRIBDCreFloNega);
    */
    lisRIBDRcvData = new LisRIBDRcvData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisRIBDRcvData);

//    lisRIBDRoutingUpdate = new LisRIBDRoutingUpdate(this);
//    catcher2->subscribe(SIG_RIBD_RoutingUpdate, lisRIBDRoutingUpdate);

    lisRIBDCongNotif = new LisRIBDCongesNotif(this);
    catcher2->subscribe(SIG_RA_InvokeSlowdown, lisRIBDCongNotif);

    /*
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
    */
}

void RIBd::signalizeSendData(CDAPMessage* msg) {
    Enter_Method("signalizeSendData()");

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

void RIBd::sendCongestionNotification(PDU* pdu) {
    Enter_Method("sendCongestionNotification()");

    //Prepare M_START ConDescr
    CDAP_M_Start* mstarcon = new CDAP_M_Start(MSG_CONGEST);
    CongestionDescriptor* conDesc = new CongestionDescriptor(pdu->getConnId().getDstCepId(), pdu->getConnId().getSrcCepId(), pdu->getConnId().getQoSId());
    //Prepare object
    std::ostringstream os;
    os << conDesc->getCongesDescrName();
    object_t condesobj;
    condesobj.objectClass = conDesc->getClassName();
    condesobj.objectName = os.str();
    condesobj.objectVal = conDesc;
    //TODO: Vesely - Assign appropriate values
    condesobj.objectInstance = VAL_DEFINSTANCE;
    mstarcon->setObjectItem(condesobj);

    //Generate InvokeId
    mstarcon->setInvokeID(DONTCARE_INVOKEID);

    //Append src/dst address for RMT "routing"
    mstarcon->setSrcAddr(pdu->getDstAddr());
    mstarcon->setDstAddr(pdu->getSrcAddr());

    //Send it
    signalizeSendData(mstarcon);
}

//void RIBd::receiveRoutingUpdateFromRouting(IntRoutingUpdate * info)
//{
//    EV << getFullPath() << " Forwarding update to send to " << info->getDestination();
//
//    /* Emits the CDAP message. */
//
//    CDAP_M_Write * cdapm = new CDAP_M_Write(MSG_ROUTINGUPDATE);
//    std::ostringstream os;
//    object_t flowobj;
//
//    /* Prepare the object to send. */
//
//    os << "RoutingUpdateTo" << info->getDestination();
//
//    flowobj.objectClass = info->getClassName();
//    flowobj.objectName  = os.str();
//    flowobj.objectVal   = info;
//    //TODO: Vesely - Assign appropriate values
//    flowobj.objectInstance = VAL_DEFINSTANCE;
//
//    cdapm->setObjectItem(flowobj);
//
//    //TODO: Vesely - Work more on InvokeId
//
//    /* This message will be sent to... */
//    cdapm->setDstAddr(info->getDestination());
//
//    /* Finally order to send the data... */
//    signalizeSendData(cdapm);
//}

void RIBd::signalizeCongestionNotification(CongestionDescriptor* congDesc) {
    EV << "Emits CongestionNotification" << endl;
    emit(sigRIBDCongNotif, congDesc);
}
/*
void RIBd::signalizeConnectResponsePositive(CDAPMessage* msg) {
    EV << "Emits ConnectResponsePositive to enrollment" << endl;
    emit(sigRIBDConResPosi, msg);
}

void RIBd::signalizeConnectResponseNegative(CDAPMessage* msg) {
    EV << "Emits ConnectResponseNegative to enrollment" << endl;
    emit(sigRIBDConResNega, msg);
}

void RIBd::signalizeConnectRequest(CDAPMessage* msg) {
    EV << "Emits ConnectRequest to enrollment" << endl;
    emit(sigRIBDConReq, msg);
}

void RIBd::signalizeSendCACE(CDAPMessage* msg) {
    EV << "Emits CACE data to CACE module" << endl;
    emit(sigRIBDCACESend, msg);
}

void RIBd::signalizeStartEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStartEnrollReq, msg);
}

void RIBd::signalizeStartEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StartEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStartEnrollRes, msg);
}

void RIBd::signalizeStopEnrollmentRequest(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentRequest to enrollment" << endl;
    emit(sigRIBDStopEnrollReq, msg);
}

void RIBd::signalizeStopEnrollmentResponse(CDAPMessage* msg) {
    EV << "Emits StopEnrollmentResponse to enrollment" << endl;
    emit(sigRIBDStopEnrollRes, msg);
}

void RIBd::signalizeStartOperationRequest(CDAPMessage* msg) {
    EV << "Emits StartOperationRequest to enrollment" << endl;
    emit(sigRIBDStartOperationReq, msg);
}

void RIBd::signalizeStartOperationResponse(CDAPMessage* msg) {
    EV << "Emits StartOperationResponse to enrollment" << endl;
    emit(sigRIBDStartOperationRes, msg);
}
*/
/*
void RIBd::sendStartEnrollmentRequest(EnrollmentObj* obj) {
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

    signalizeSendData(msg);
}

void RIBd::sendStartEnrollmentResponse(EnrollmentObj* obj) {
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


    signalizeSendData(msg);
}

void RIBd::sendStopEnrollmentRequest(EnrollmentObj* obj) {
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

    signalizeSendData(msg);
}

void RIBd::sendStopEnrollmentResponse(EnrollmentObj* obj) {
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

    signalizeSendData(msg);
}

void RIBd::sendStartOperationRequest(OperationObj* obj) {
    Enter_Method("sendStartOperationRequest()");
}

void RIBd::sendStartOperationResponse(OperationObj* obj) {
    Enter_Method("sendStartOperationResponse()");
}

void RIBd::sendCACE(CDAPMessage* msg) {
    Enter_Method("sendCACE()");

    //TODO: add invoke id

    signalizeSendCACE(msg);
}
void RIBd::receiveCACE(CDAPMessage* msg) {
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
*/
/*
void RIBd::processMCreate(CDAPMessage* msg) {
    CDAP_M_Create* msg1 = check_and_cast<CDAP_M_Create*>(msg);

    EV << "Received M_Create";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

//    //CreateRequest Flow
//    if (dynamic_cast<Flow*>(object.objectVal)) {
//        Flow* fl = (check_and_cast<Flow*>(object.objectVal))->dup();
//        //EV << fl->info();
//        fl->swapFlow();
//        //EV << "\n===========\n" << fl->info();
//        signalizeCreateRequestFlow(fl);
//    }
}

void RIBd::processMCreateR(CDAPMessage* msg) {
    CDAP_M_Create_R* msg1 = check_and_cast<CDAP_M_Create_R*>(msg);

    EV << "Received M_Create_R";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

//    //CreateResponseFlow
//    if (dynamic_cast<Flow*>(object.objectVal)) {
//        Flow* flow = (check_and_cast<Flow*>(object.objectVal))->dup();
//        flow->swapFlow();
//        //Positive response
//        if (!msg1->getResult().resultValue) {
//            signalizeCreateResponseFlowPositive(flow);
//        }
//        //Negative response
//        else
//            signalizeCreateResponseFlowNegative(flow);
//    }
}

void RIBd::processMDelete(CDAPMessage* msg) {
    //CDAP_M_Delete* msg1 = check_and_cast<CDAP_M_Delete*>(msg);

    EV << "Received M_Delete";

    //DeleteRequest Flow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* fl = (check_and_cast<Flow*>(object.objectVal))->dup();
        fl->swapFlow();
        signalizeDeleteRequestFlow(fl);
    }

}

void RIBd::processMDeleteR(CDAPMessage* msg) {
    CDAP_M_Delete_R* msg1 = check_and_cast<CDAP_M_Delete_R*>(msg);

    EV << "Received M_Delete_R";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

//    //DeleteResponseFlow
//    if (dynamic_cast<Flow*>(object.objectVal)) {
//        Flow* flow = (check_and_cast<Flow*>(object.objectVal))->dup();
//        flow->swapFlow();
//        signalizeDeleteResponseFlow(flow);
//    }

}
*/

/*
void RIBd::processMConnect(CDAPMessage* msg) {
    CDAP_M_Connect* msg1 = check_and_cast<CDAP_M_Connect*>(msg);

    EV << "Received M_Connect";

    if (msg1) {
        signalizeConnectRequest(msg);
    }
}

void RIBd::processMConnectR(CDAPMessage* msg) {
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
*/
void RIBd::processMStart(CDAPMessage* msg) {
    CDAP_M_Start* msg1 = check_and_cast<CDAP_M_Start*>(msg);

    EV << "Received M_Start";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

    //CongestionNotification CongestDescr
    if (dynamic_cast<CongestionDescriptor*>(object.objectVal)) {
        CongestionDescriptor* congdesc = (check_and_cast<CongestionDescriptor*>(object.objectVal))->dup();
        congdesc->getConnectionId().swapCepIds();
        EV << "\n===========\n" << congdesc->getConnectionId().info();
        signalizeCongestionNotification(congdesc);
        delete msg;
    }
    /*
    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
       signalizeStartEnrollmentRequest(msg);
    }
    */
}
/*
void RIBd::processMStartR(CDAPMessage* msg) {
    CDAP_M_Start_R* msg1 = check_and_cast<CDAP_M_Start_R*>(msg);

    EV << "Received M_Start_R";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStartEnrollmentResponse(msg);
    }
}

void RIBd::processMStop(CDAPMessage* msg) {
    CDAP_M_Stop* msg1 = check_and_cast<CDAP_M_Stop*>(msg);

    EV << "Received M_Stop";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentRequest(msg);
    }
}

void RIBd::processMStopR(CDAPMessage* msg) {
    CDAP_M_Stop_R* msg1 = check_and_cast<CDAP_M_Stop_R*>(msg);

    EV << "Received M_Stop_R";
    object_t object = msg1->getObjectItem();
    EV << " with object '" << object.objectClass << "'" << endl;

    //Enrollment
    if (dynamic_cast<EnrollmentObj*>(object.objectVal)) {
        signalizeStopEnrollmentResponse(msg);
    }
}
*/
//void RIBd::processMWrite(CDAPMessage* msg)
//{
//    CDAP_M_Write * msg1 = check_and_cast<CDAP_M_Write *>(msg);
//
//    EV << "Received M_Write";
//    object_t object = msg1->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
//
//    if (dynamic_cast<IntRoutingUpdate *>(object.objectVal))
//    {
//        IntRoutingUpdate * update = (check_and_cast<IntRoutingUpdate *>(object.objectVal));
//
//        /* Signal that an update obj has been received. */
//        emit(sigRIBDRoutingUpdateRecv, update);
//    }
//}

