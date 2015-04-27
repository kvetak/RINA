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

#include "Enrollment.h"

Define_Module(Enrollment);

const char* PAR_AUTH_TYPE       = "authType";
const char* PAR_AUTH_NAME       = "authName";
const char* PAR_AUTH_OTHER      = "authOther";
const char* PAR_AUTH_PASS       = "authPassword";
const char* PAR_CON_RETRIES     = "maxConRetries";

Enrollment::Enrollment() :
        StateTable(NULL)
{
}

Enrollment::~Enrollment(){

}

void Enrollment::initialize()
{
    initSignalsAndListeners();
    initPointers();

    authType = par(PAR_AUTH_TYPE);
    authName = this->par(PAR_AUTH_NAME).stringValue();
    authPassword = this->par(PAR_AUTH_PASS).stringValue();
    authOther = this->par(PAR_AUTH_OTHER).stringValue();

    maxConRetries = this->par(PAR_CON_RETRIES);
}

void Enrollment::initPointers(){
    StateTable = dynamic_cast<EnrollmentStateTable*>(this->getParentModule()->getSubmodule(MOD_ENROLLMENTTABLE));
    ribd = dynamic_cast<RIBd*>(this->getParentModule()->getParentModule()->getSubmodule(MOD_RIBDAEMON)->getSubmodule(MOD_RIBD));
}

void Enrollment::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule()->getParentModule();

    sigEnrollmentCACESendData   = registerSignal(SIG_ENROLLMENT_CACEDataSend);
    sigEnrollmentSendData       = registerSignal(SIG_ENROLLMENT_DataSend);
    sigEnrollmentStartEnrollReq = registerSignal(SIG_ENROLLMENT_StartEnrollmentRequest);
    sigEnrollmentStartEnrollRes = registerSignal(SIG_ENROLLMENT_StartEnrollmentResponse);
    sigEnrollmentStopEnrollReq  = registerSignal(SIG_ENROLLMENT_StopEnrollmentRequest);
    sigEnrollmentStopEnrollRes  = registerSignal(SIG_ENROLLMENT_StopEnrollmentResponse);
    sigEnrollmentStartOperReq   = registerSignal(SIG_ENROLLMENT_StartOperationRequest);
    sigEnrollmentStartOperRes   = registerSignal(SIG_ENROLLMENT_StartOperationResponse);

    lisEnrollmentAllResPosi = new LisEnrollmentAllResPosi(this);
    catcher1->subscribe(SIG_FAI_AllocateResponsePositive, lisEnrollmentAllResPosi);

    lisEnrollmentGetFlowFromFaiCreResPosi = new LisEnrollmentGetFlowFromFaiCreResPosi(this);
    catcher1->subscribe(SIG_FAI_CreateFlowResponsePositive, lisEnrollmentGetFlowFromFaiCreResPosi);

    lisEnrollmentStartEnrollReq = new LisEnrollmentStartEnrollReq(this);
    catcher1->subscribe(SIG_RIBD_StartEnrollmentRequest, lisEnrollmentStartEnrollReq);

    lisEnrollmentStartEnrollRes = new LisEnrollmentStartEnrollRes(this);
    catcher1->subscribe(SIG_RIBD_StartEnrollmentResponse, lisEnrollmentStartEnrollRes);

    lisEnrollmentStopEnrollReq = new LisEnrollmentStopEnrollReq(this);
    catcher1->subscribe(SIG_RIBD_StopEnrollmentRequest, lisEnrollmentStopEnrollReq);

    lisEnrollmentStopEnrollRes = new LisEnrollmentStopEnrollRes(this);
    catcher1->subscribe(SIG_RIBD_StopEnrollmentResponse, lisEnrollmentStopEnrollRes);

    lisEnrollmentStartOperationReq = new LisEnrollmentStopOperationReq(this);
    catcher1->subscribe(SIG_RIBD_StartOperationRequest, lisEnrollmentStartOperationReq);

    lisEnrollmentStartOperationRes = new LisEnrollmentStartOperationRes(this);
    catcher1->subscribe(SIG_RIBD_StartOperationResponse, lisEnrollmentStartOperationRes);

    lisEnrollmentConResPosi = new LisEnrollmentConResPosi(this);
    catcher1->subscribe(SIG_RIBD_ConnectionResponsePositive, lisEnrollmentConResPosi);

    lisEnrollmentConResNega = new LisEnrollmentConResNega(this);
    catcher1->subscribe(SIG_RIBD_ConnectionResponseNegative, lisEnrollmentConResNega);

    lisEnrollmentConReq = new LisEnrollmentConReq(this);
    catcher1->subscribe(SIG_RIBD_ConnectionRequest, lisEnrollmentConReq);


}

void Enrollment::startCACE(Flow* flow) {
    StateTable->insert(EnrollmentStateTableEntry(flow, EnrollmentStateTableEntry::CON_AUTHENTICATING, true));

    CDAP_M_Connect* msg = new CDAP_M_Connect("connect");

    authValue_t aValue;
    aValue.authName = authName;
    aValue.authPassword = authPassword;
    aValue.authOther = authOther;

    auth_t auth;
    auth.authType = authType;
    auth.authValue = aValue;

    msg->setAuth(auth);
    msg->setAbsSyntax(GPB);
    msg->setOpCode(M_CONNECT);

    naming_t dst;
    dst.AEInst = flow->getDstApni().getAeinstance();
    dst.AEName = flow->getDstApni().getAename();
    dst.ApInst = flow->getDstApni().getApinstance();
    dst.ApName = flow->getDstAddr().getApname().getName();

    naming_t src;
    src.AEInst = flow->getSrcApni().getAeinstance();
    src.AEName = flow->getSrcApni().getAename();
    src.ApInst = flow->getSrcApni().getApinstance();
    src.ApName = flow->getSrcAddr().getApname().getName();

    msg->setDst(dst);
    msg->setSrc(src);

    msg->setDstAddr(flow->getDstAddr());

    //send data to ribd to send
    signalizeCACESendData(msg);
}

void Enrollment::startEnrollment(EnrollmentStateTableEntry* entry) {
    Enter_Method("startEnrollment()");

    EnrollmentObj* enrollObj = new EnrollmentObj(entry->getFlow()->getSrcAddr(), entry->getFlow()->getDstAddr());

    enrollObj->setAddress(APN(ribd->getMyAddress().getIpcAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentRequest(enrollObj);

    entry->setEnrollmentStatus(EnrollmentStateTableEntry::Enroll)
}

void Enrollment::insertStateTableEntry(Flow* flow){
    StateTable->insert(EnrollmentStateTableEntry(flow, EnrollmentStateTableEntry::CON_CONNECTPENDING, false));
}

void Enrollment::receivePositiveConnectResponse(CDAPMessage* msg) {
    Enter_Method("receivePositiveConnectResponse()");

    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(cmsg->getSrc().ApName.c_str()));

    //check appropriate state
    if (entry->getCACEConStatus() != EnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_ESTABLISHED);

    startEnrollment(entry);
}

void Enrollment::receiveNegativeConnectResponse(CDAPMessage* msg) {
    Enter_Method("receiveNegativeConnectResponse()");

    CDAP_M_Connect* cmsg = check_and_cast<CDAP_M_Connect*>(msg);
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(cmsg->getSrc().ApName.c_str()));

    //check appropriate state
    if (entry->getCACEConStatus() != EnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_CONNECTPENDING);

    //create and send new connect retry
    processNewConReq(entry);
}

void Enrollment::receiveConnectRequest(CDAPMessage* msg) {
    Enter_Method("receiveConnectRequest()");

    CDAP_M_Connect* cmsg = check_and_cast<CDAP_M_Connect*>(msg);
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(cmsg->getSrc().ApName.c_str()));

    //check appropriate state
    if (entry->getCACEConStatus() != EnrollmentStateTableEntry::CON_CONNECTPENDING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    //check if message is valid
    if (cmsg->getAbsSyntax() != GPB ||
            cmsg->getOpCode() != M_CONNECT) {
        this->processConResNega(entry, cmsg);
        return;
    }

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_AUTHENTICATING);

    authenticate(entry, cmsg);
}

void Enrollment::receiveStartEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartEnrollmentRequest()");

    EnrollmentObj* enrollObj = new EnrollmentObj(entry->getFlow()->getSrcAddr(), entry->getFlow()->getDstAddr());

    enrollObj->setAddress(APN(ribd->getMyAddress().getIpcAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentRequest(enrollObj);
}

void Enrollment::receiveStartEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartEnrollmentResponse()");

}

void Enrollment::receiveStopEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStopEnrollmentRequest()");

}

void Enrollment::receiveStopEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStopEnrollmentResponse()");

}

void Enrollment::receiveStartOperationRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationRequest()");
}

void Enrollment::receiveStartOperationResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationResponse()");

}



void Enrollment::authenticate(EnrollmentStateTableEntry* entry, CDAP_M_Connect* msg) {
    Enter_Method("authenticate()");

    //check and validate expected auth type
    if (msg->getAuth().authType == authType) {
        //none auth option
        if (msg->getAuth().authType == AUTH_NONE) {
            processConResPosi(entry, msg);
            return;

        }
        //passwd auth option
        else if (msg->getAuth().authType == AUTH_PASSWD) {
            //correct passwd
            if (!strcmp(msg->getAuth().authValue.authPassword.c_str(), authPassword.c_str())) {
                processConResPosi(entry, msg);
                return;
            }
        }
        //TODO: support for other options
    }

    //not valid auth send negative response
    processConResNega(entry, msg);
}

/*void Enrollment::caceStateMachine(CDAPMessage *msg) {
    //M_Connect_R
    else if (dynamic_cast<CDAP_M_Connect_R*>(msg)){
        CDAP_M_Connect_R* msgCR = check_and_cast<CDAP_M_Connect_R*>(msg);
        EnrollmentStateTableEntry* StateEntry = StateTable->findEntryByDstAPN(APN(msgCR->getSrc().ApName.c_str()));
        if (StateEntry->getCACEConStatus() == EnrollmentStateTableEntry::CON_AUTHENTICATING) {
            if (msgCR->getResult().resultValue == 0) {//SUCCESS
                //signalizeConnResponsePositive(cmsg);
                StateEntry->setCACEConStatus(EnrollmentStateTableEntry::CON_ESTABLISHED);
                //now start enrollment
                enrollmentStart(StateEntry);
            }
            else {
                //this is connection retry
                //signalizeConnResponseNegative(cmsg);
                StateEntry->setCACEConStatus(EnrollmentStateTableEntry::CON_CONNECTPENDING);
                //TODO: send cdap message with new auth
            }
        }
        else {
            //TODO: probably immediate deallocation
            //processMRelease();
        }
    }
}*/

void Enrollment::processNewConReq(EnrollmentStateTableEntry* entry) {
    Enter_Method("processNewConReq()");

    //TODO: probably change values, this is retry

    CDAP_M_Connect* msg = new CDAP_M_Connect("connectRetry");

    authValue_t aValue;
    aValue.authName = authName;
    aValue.authPassword = authPassword;
    aValue.authOther = authOther;

    auth_t auth;
    auth.authType = authType;
    auth.authValue = aValue;

    msg->setAuth(auth);
    msg->setAbsSyntax(GPB);
    msg->setOpCode(M_CONNECT);

    naming_t dst;
    dst.AEInst = entry->getFlow()->getDstApni().getAeinstance();
    dst.AEName = entry->getFlow()->getDstApni().getAename();
    dst.ApInst = entry->getFlow()->getDstApni().getApinstance();
    dst.ApName = entry->getFlow()->getDstAddr().getApname().getName();

    naming_t src;
    src.AEInst = entry->getFlow()->getSrcApni().getAeinstance();
    src.AEName = entry->getFlow()->getSrcApni().getAename();
    src.ApInst = entry->getFlow()->getSrcApni().getApinstance();
    src.ApName = entry->getFlow()->getSrcAddr().getApname().getName();

    msg->setDst(dst);
    msg->setSrc(src);

    msg->setDstAddr(entry->getFlow()->getDstAddr());

    //send data to ribd to send
    signalizeCACESendData(msg);

}

void Enrollment::processConResPosi(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R("positiveConnectResponse");
    CDAP_M_Connect* cmsg1 = check_and_cast<CDAP_M_Connect*>(cmsg);

    naming_t dst;
    dst.AEInst = entry->getFlow()->getDstApni().getAeinstance();
    dst.AEName = entry->getFlow()->getDstApni().getAename();
    dst.ApInst = entry->getFlow()->getDstApni().getApinstance();
    dst.ApName = entry->getFlow()->getDstAddr().getApname().getName();

    naming_t src;
    src.AEInst = entry->getFlow()->getSrcApni().getAeinstance();
    src.AEName = entry->getFlow()->getSrcApni().getAename();
    src.ApInst = entry->getFlow()->getSrcApni().getApinstance();
    src.ApName = entry->getFlow()->getSrcAddr().getApname().getName();

    result_t result;
    result.resultValue = R_SUCCESS;

    auth_t auth;
    auth.authType = cmsg1->getAuth().authType;
    auth.authValue = cmsg1->getAuth().authValue;

    msg->setAbsSyntax(GPB);
    msg->setOpCode(M_CONNECT_R);
    msg->setResult(result);
    msg->setAuth(auth);
    msg->setDst(dst);
    msg->setSrc(src);

    msg->setDstAddr(entry->getFlow()->getDstAddr());

    //send data to ribd to send
    signalizeCACESendData(msg);

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_ESTABLISHED);
}

void Enrollment::processConResNega(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R("negativeConnectResponse");
    CDAP_M_Connect* cmsg1 = check_and_cast<CDAP_M_Connect*>(cmsg);

    naming_t dst;
    dst.AEInst = entry->getFlow()->getDstApni().getAeinstance();
    dst.AEName = entry->getFlow()->getDstApni().getAename();
    dst.ApInst = entry->getFlow()->getDstApni().getApinstance();
    dst.ApName = entry->getFlow()->getDstAddr().getApname().getName();

    naming_t src;
    src.AEInst = entry->getFlow()->getSrcApni().getAeinstance();
    src.AEName = entry->getFlow()->getSrcApni().getAename();
    src.ApInst = entry->getFlow()->getSrcApni().getApinstance();
    src.ApName = entry->getFlow()->getSrcAddr().getApname().getName();

    result_t result;
    result.resultValue = R_FAIL;

    auth_t auth;
    auth.authType = cmsg1->getAuth().authType;
    auth.authValue = cmsg1->getAuth().authValue;

    msg->setAbsSyntax(GPB);
    msg->setOpCode(M_CONNECT_R);
    msg->setResult(result);
    msg->setAuth(auth);
    msg->setDst(dst);
    msg->setSrc(src);

    msg->setDstAddr(entry->getFlow()->getDstAddr());

    //send data to send to ribd
    signalizeCACESendData(msg);

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_CONNECTPENDING);

    //increase number of connects
    entry->increaseCurrentConnectRetries();
}

void Enrollment::signalizeCACESendData(CDAPMessage* cmsg) {
    emit(sigEnrollmentCACESendData, cmsg);
}

void Enrollment::signalizeStartEnrollmentRequest(EnrollmentObj* obj) {
    emit(sigEnrollmentStartEnrollReq, obj);
}

void Enrollment::signalizeStartEnrollmentResponse(EnrollmentObj* obj) {
    emit(sigEnrollmentStartEnrollRes, obj);
}

void Enrollment::signalizeStopEnrollmentRequest(EnrollmentObj* obj) {
    emit(sigEnrollmentStopEnrollReq, obj);
}

void Enrollment::signalizeStopEnrollmentResponse(EnrollmentObj* obj) {
    emit(sigEnrollmentStopEnrollRes, obj);
}

void Enrollment::signalizeStartOperationRequest(OperationObj* obj) {
    emit(sigEnrollmentStartOperReq, obj);
}

void Enrollment::signalizeStartOperationResponse(OperationObj* obj) {
    emit(sigEnrollmentStartOperRes, obj);
}

void Enrollment::handleMessage(cMessage *msg)
{

}
