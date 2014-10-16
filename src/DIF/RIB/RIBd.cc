//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file RIBd.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief Kind of a Notification Board for DIF
 * @detail
 */

#include "RIBd.h"

const char* MSG_CREREQFLO       = "Flow";
const char* MSG_CRERESFLOPOSI   = "Flow+";
const char* MSG_CRERESFLONEGA   = "Flow-";
const char* CLS_FLOW            = "Flow";
const int   VAL_DEFINSTANCE     = -1;
const int   VAL_FLOWPOSI        = 1;
const int   VAL_FLOWNEGA        = 0;
const char* VAL_FLREQ           = "Request  ";
const char* VAL_FLREQPOSI       = "Response+  ";
const char* VAL_FLREQNEGA       = "Response-  ";

Define_Module(RIBd);

void RIBd::initialize() {
    //Init signals and listeners
    initSignalsAndListeners();
    //Init CDAP gates and connections
    initCdapBindings();
    //Init MyAddress
    initMyAddress();

    invokeIdCounter = 0;
}

void RIBd::handleMessage(cMessage *msg) {

}

void RIBd::initCdapBindings() {

    //Get RIBDaemon gates
    cModule* RibD = this->getParentModule();
    cGate* gRibdIn = RibD->gateHalf(GATE_RMTIO, cGate::INPUT);
    cGate* gRibdOut = RibD->gateHalf(GATE_RMTIO, cGate::OUTPUT);

    //CDAPParent Module gates
    cModule* Cdap = RibD->getSubmodule(MOD_CDAP);
    cGate* gCdapParentIn;
    cGate* gCdapParentOut;
    Cdap->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gCdapParentIn, *&gCdapParentOut);

    //CDAPSplitter gates
    cModule* CdapSplit = Cdap->getSubmodule(MOD_CDAPSPLIT);
    cGate* gSplitIn;
    cGate* gSplitOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gSplitIn, *&gSplitOut);
    cGate* gSplitCaceIn;
    cGate* gSplitCaceOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CACEIO, false, true, *&gSplitCaceIn, *&gSplitCaceOut);
    cGate* gSplitAuthIn;
    cGate* gSplitAuthOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_AUTHIO, false, true, *&gSplitAuthIn, *&gSplitAuthOut);
    cGate* gSplitCdapIn;
    cGate* gSplitCdapOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CDAPIO, false, true, *&gSplitCdapIn, *&gSplitCdapOut);

    //CACE Module gates
    cModule* CdapCace = Cdap->getSubmodule(MOD_CDAPCACE);
    cGate* gCaceIn;
    cGate* gCaceOut;
    CdapCace->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCaceIn, *&gCaceOut);

    //AUTH Module gates
    cModule* CdapAuth = Cdap->getSubmodule(MOD_CDAPAUTH);
    cGate* gAuthIn;
    cGate* gAuthOut;
    CdapAuth->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gAuthIn, *&gAuthOut);

    //CDAP Module gates
    cModule* CdapCdap = Cdap->getSubmodule(MOD_CDAPCDAP);
    cGate* gCdapIn;
    cGate* gCdapOut;
    CdapCdap->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCdapIn, *&gCdapOut);

    //Connect gates together
    gRibdIn->connectTo(gCdapParentIn);
    gCdapParentIn->connectTo(gSplitIn);

    gSplitOut->connectTo(gCdapParentOut);
    gCdapParentOut->connectTo(gRibdOut);

    gSplitCaceOut->connectTo(gCaceIn);
    gCaceOut->connectTo(gSplitCaceIn);

    gSplitAuthOut->connectTo(gAuthIn);
    gAuthOut->connectTo(gSplitAuthIn);

    gSplitCdapOut->connectTo(gCdapIn);
    gCdapOut->connectTo(gSplitCdapIn);

}

void RIBd::sendCreateRequestFlow(Flow* flow) {
    Enter_Method("sendCreateRequestFlow()");

    //Prepare M_CREATE Flow
    CDAP_M_Create* mcref = new CDAP_M_Create(MSG_CREREQFLO);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObject(flowobj);

    //Append destination address for RMT "routing"
    mcref->setDstAddr(flow->getDstAddr());

    //TODO: Vesely - Work more on InvokeId
    mcref->setInvokeID(invokeIdCounter++);

    //Send it
    signalizeSendData(mcref);
}

void RIBd::processMCreate(CDAPMessage* msg) {
    CDAP_M_Create* msg1 = check_and_cast<CDAP_M_Create*>(msg);

    EV << "Received M_Create";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //CreateRequest Flow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* fl = (check_and_cast<Flow*>(object.objectVal))->dup();
        signalizeCreateRequestFlow(fl);
    }
}

void RIBd::processMCreateR(CDAPMessage* msg) {
    CDAP_M_Create_R* msg1 = check_and_cast<CDAP_M_Create_R*>(msg);

    EV << "Received M_Create_R";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    //CreateResponseFlow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* flow = (check_and_cast<Flow*>(object.objectVal))->dup();

        //Positive response
        if (!msg1->getResult().resultValue) {
            signalizeCreateResponseFlowPositive(flow);
        }
        //Negative response
        else
            signalizeCreateResponseFlowNegative(flow);
    }
}

void RIBd::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");
    //M_CREATE_Request
    if (dynamic_cast<CDAP_M_Create*>(msg)) {
        processMCreate(msg);
    }
    //M_CREATE_Response
    else if (dynamic_cast<CDAP_M_Create_R*>(msg)) {
        processMCreateR(msg);
    }

    delete msg;
}

void RIBd::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();
    cModule* catcher2 = this->getParentModule()->getParentModule();
    cModule* catcher3 = this->getParentModule()->getParentModule()->getParentModule();

    //Signals that this module is emitting
    sigRIBDSendData      = registerSignal(SIG_RIBD_DataSend);
    sigRIBDCreReqFlo     = registerSignal(SIG_RIBD_CreateRequestFlow);
    sigRIBDAllocResPosi  = registerSignal(SIG_AERIBD_AllocateResponsePositive);
    sigRIBDCreFlow       = registerSignal(SIG_RIBD_CreateFlow);
    sigRIBDCreResFloPosi = registerSignal(SIG_RIBD_CreateFlowResponsePositive);
    sigRIBDCreResFloNega = registerSignal(SIG_RIBD_CreateFlowResponseNegative);

    //Signals that this module is processing

    lisRIBDCreReqByForward = new LisRIBDCreReq(this);
    catcher2->subscribe(SIG_FA_CreateFlowRequestForward, lisRIBDCreReqByForward);
    lisRIBDCreReq = new LisRIBDCreReq(this);
    catcher2->subscribe(SIG_FAI_CreateFlowRequest, lisRIBDCreReq);

    lisRIBDCreResNegaFromFa = new LisRIBDCreResNega(this);
    catcher2->subscribe(SIG_FA_CreateFlowResponseNegative, lisRIBDCreResNegaFromFa);
    lisRIBDCreResNega = new LisRIBDCreResNega(this);
    catcher2->subscribe(SIG_FAI_CreateFlowResponseNegative, lisRIBDCreResNega);

    lisRIBDCreResPosi = new LisRIBDCreResPosi(this);
    catcher2->subscribe(SIG_FAI_CreateFlowResponsePositive, lisRIBDCreResPosi);

    lisRIBDRcvData = new LisRIBDRcvData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisRIBDRcvData);

    lisRIBDAllReqFromFai = new LisRIBDAllReqFromFai(this);
    catcher3->subscribe(SIG_FAI_AllocateRequest, lisRIBDAllReqFromFai);

}

void RIBd::receiveAllocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveAllocationRequestFromFai()");
    //Execute flow allocate
    signalizeCreateFlow(flow);
    //TODO: Vesely - Return result
    signalizeAllocateResponsePositive(flow);
}

void RIBd::sendCreateResponseNegative(Flow* flow) {
    Enter_Method("sendCreateResponseFlowNegative()");

    //Prepare M_CREATE_R Flow-
    CDAP_M_Create_R* mcref = new CDAP_M_Create_R(MSG_CRERESFLONEGA);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObject(flowobj);

    //Prepare result object
    result_t resultobj;
    resultobj.resultValue = R_FAIL;
    mcref->setResult(resultobj);

    //TODO: Vesely - Work more on InvokeId

    //Append destination address for RMT "routing"
    mcref->setDstAddr(flow->getSrcAddr());

    //Send it
    signalizeSendData(mcref);
}

void RIBd::sendCreateResponsePostive(Flow* flow) {
    Enter_Method("sendCreateResponseFlowPositive()");

    //Prepare M_CREATE_R Flow+
    CDAP_M_Create_R* mcref = new CDAP_M_Create_R(MSG_CRERESFLOPOSI);

    //Prepare object
    std::ostringstream os;
    os << flow->getFlowName();
    object_t flowobj;
    flowobj.objectClass = flow->getClassName();
    flowobj.objectName = os.str();
    flowobj.objectVal = flow;
    //TODO: Vesely - Assign appropriate values
    flowobj.objectInstance = VAL_DEFINSTANCE;
    mcref->setObject(flowobj);

    //Prepare result object
    result_t resultobj;
    resultobj.resultValue = R_SUCCESS;
    mcref->setResult(resultobj);

    //TODO: Vesely - Work more on InvokeId

    //Append destination address for RMT "routing"
    mcref->setDstAddr(flow->getSrcAddr());

    //Send it
    signalizeSendData(mcref);
}

void RIBd::signalizeSendData(CDAPMessage* msg) {
    //Setup handle which is for RIBd always 0
    msg->setHandle(0);
    //Pass message to CDAP
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigRIBDSendData, msg);
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
    EV << "Emits CreateRequestFlow signal for flow" << endl;
    emit(sigRIBDCreResFloPosi, flow);
}

void RIBd::signalizeCreateResponseFlowNegative(Flow* flow) {
    EV << "Emits CreateRequestFlow signal for flow" << endl;
    emit(sigRIBDCreResFloNega, flow);
}

void RIBd::signalizeCreateFlow(Flow* flow) {
    EV << "Emits CreateFlow signal for flow" << endl;
    emit(sigRIBDCreFlow, flow);
}

