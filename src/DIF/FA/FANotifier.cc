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

#include "DIF/FA/FANotifier.h"

const char* MSG_FLO             = "Flow";
const char* MSG_FLOPOSI         = "Flow+";
const char* MSG_FLONEGA         = "Flow-";
//FIXME: Vesely: Unused variable commented
//const int   VAL_FLOWPOSI        = 1;
//FIXME: Vesely: Unused variable commented
//const int   VAL_FLOWNEGA        = 0;
const char* VAL_FLREQ           = "Request  ";
const char* VAL_FLREQPOSI       = "Response+  ";
const char* VAL_FLREQNEGA       = "Response-  ";

Define_Module(FANotifier);

void FANotifier::initSignalsAndListeners() {
    cModule* catcher2 = this->getModuleByPath("^.^");
    cModule* catcher3 = this->getModuleByPath("^.^.^");

    //Signals that this module is emitting
    //sigRIBDSendData      = registerSignal(SIG_RIBD_DataSend);
    sigRIBDCreReqFlo     = registerSignal(SIG_RIBD_CreateRequestFlow);
    sigRIBDDelReqFlo     = registerSignal(SIG_RIBD_DeleteRequestFlow);
    sigRIBDDelResFlo     = registerSignal(SIG_RIBD_DeleteResponseFlow);
    sigRIBDAllocResPosi  = registerSignal(SIG_AERIBD_AllocateResponsePositive);
    sigRIBDAllocResNega  = registerSignal(SIG_AERIBD_AllocateResponseNegative);
    sigRIBDCreFlow       = registerSignal(SIG_RIBD_CreateFlow);
    sigRIBDCreResFloPosi = registerSignal(SIG_RIBD_CreateFlowResponsePositive);
    sigRIBDCreResFloNega = registerSignal(SIG_RIBD_CreateFlowResponseNegative);

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

    lisRIBDCreFloPosi = new LisRIBDCreFloPosi(this);
    catcher2->subscribe(SIG_RA_CreateFlowPositive, lisRIBDCreFloPosi);
    lisRIBDCreFloNega = new LisRIBDCreFloNega(this);
    catcher2->subscribe(SIG_RA_CreateFlowNegative, lisRIBDCreFloNega);

    lisRIBDAllReqFromFai = new LisRIBDAllReqFromFai(this);
    catcher3->subscribe(SIG_FAI_AllocateRequest, lisRIBDAllReqFromFai);
}

void FANotifier::receiveAllocationRequestFromFai(Flow* flow) {
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

void FANotifier::receiveCreateFlowPositiveFromRa(Flow* flow) {
    signalizeAllocateResponsePositive(flow);
}

void FANotifier::receiveCreateFlowNegativeFromRa(Flow* flow) {
    signalizeAllocateResponseNegative(flow);
}

void FANotifier::sendCreateRequestFlow(Flow* flow) {
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
    signalizeMessage(mcref);
}

void FANotifier::sendDeleteRequestFlow(Flow* flow) {
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
    signalizeMessage(mdereqf);
}

void FANotifier::sendCreateResponseNegative(Flow* flow) {
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
    signalizeMessage(mcref);
}

void FANotifier::sendCreateResponsePostive(Flow* flow) {
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
    signalizeMessage(mcref);
}

void FANotifier::sendDeleteResponseFlow(Flow* flow) {
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
    signalizeMessage(mderesf);
}

void FANotifier::signalizeAllocateResponsePositive(Flow* flow) {
    EV << "Emits AllocateResponsePositive signal for flow" << endl;
    emit(sigRIBDAllocResPosi, flow);
}

void FANotifier::signalizeCreateRequestFlow(Flow* flow) {
    EV << "Emits CreateRequestFlow signal for flow" << endl;
    emit(sigRIBDCreReqFlo, flow);
}

void FANotifier::signalizeCreateResponseFlowPositive(Flow* flow) {
    EV << "Emits CreateResponsetFlowPositive signal for flow" << endl;
    emit(sigRIBDCreResFloPosi, flow);
}

void FANotifier::initPointers() {
    RIBd = check_and_cast<RIBdBase*>( getModuleByPath("^.ribd") );
}

void FANotifier::signalizeCreateResponseFlowNegative(Flow* flow) {
    EV << "Emits CreateResponsetFlowNegative signal for flow" << endl;
    emit(sigRIBDCreResFloNega, flow);
}

void FANotifier::signalizeCreateFlow(Flow* flow) {
    EV << "Emits CreateFlow signal for flow" << endl;
    emit(sigRIBDCreFlow, flow);
}

void FANotifier::signalizeDeleteRequestFlow(Flow* flow) {
    EV << "Emits DeleteRequestFlow signal for flow" << endl;
    emit(sigRIBDDelReqFlo, flow);
}

void FANotifier::signalizeAllocateResponseNegative(Flow* flow) {
    EV << "Emits AllocateResponseNegative signal for flow" << endl;
    emit(sigRIBDAllocResNega, flow);
}

void FANotifier::signalizeDeleteResponseFlow(Flow* flow) {
    EV << "Emits DeleteResponseFlow signal for flow" << endl;
    emit(sigRIBDDelResFlo, flow);
}

void FANotifier::processMCreate(CDAP_M_Create* msg) {
//    EV << "Received M_Create";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* fl = (check_and_cast<Flow*>(object.objectVal))->dup();
        //EV << fl->info();
        fl->swapFlow();
        //EV << "\n===========\n" << fl->info();
        signalizeCreateRequestFlow(fl);
    }
}

void FANotifier::processMCreateR(CDAP_M_Create_R* msg) {
//    EV << "Received M_Create_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //CreateResponseFlow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* flow = (check_and_cast<Flow*>(object.objectVal))->dup();
        flow->swapFlow();
        //Positive response
        if (!msg->getResult().resultValue) {
            signalizeCreateResponseFlowPositive(flow);
        }
        //Negative response
        else
            signalizeCreateResponseFlowNegative(flow);
    }
}

void FANotifier::processMDelete(CDAP_M_Delete* msg) {
//    EV << "Received M_Delete";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //DeleteRequest Flow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* fl = (check_and_cast<Flow*>(object.objectVal))->dup();
        fl->swapFlow();
        signalizeDeleteRequestFlow(fl);
    }
}

void FANotifier::processMDeleteR(CDAP_M_Delete_R* msg) {
//    EV << "Received M_Delete_R";
    object_t object = msg->getObjectItem();
//    EV << " with object '" << object.objectClass << "'" << endl;
    //DeleteResponseFlow
    if (dynamic_cast<Flow*>(object.objectVal)) {
        Flow* flow = (check_and_cast<Flow*>(object.objectVal))->dup();
        flow->swapFlow();
        signalizeDeleteResponseFlow(flow);
    }
}

void FANotifier::initialize() {
    initMyAddress();
    initSignalsAndListeners();
    initPointers();
}

void FANotifier::signalizeMessage(CDAPMessage* msg) {
    RIBd->signalizeSendData(msg);
}

long FANotifier::getNewInvokeId() {
    return RIBd->getNewInvokeId();
}

