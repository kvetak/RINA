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
 * @file DAFEnrollment.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment and CACE
 * @detail
 */


#include "DAF/Enrollment/DAFEnrollment.h"

Define_Module(DAFEnrollment);

const char* DAF_PAR_AUTH_TYPE       = "authType";
const char* DAF_PAR_AUTH_NAME       = "authName";
const char* DAF_PAR_AUTH_OTHER      = "authOther";
const char* DAF_PAR_AUTH_PASS       = "authPassword";
const char* DAF_PAR_CON_RETRIES     = "maxConRetries";
const char* DAF_PAR_ISSELFENROL     = "isSelfEnrolled";

const char* DAF_MSG_ENRLCON               = "Enrol-Connect";
const char* DAF_MSG_ENRLREL               = "Enrol-Release";

const char* DAF_ELEM_PREENROL     = "Preenrollment";
const char* DAF_ELEM_SIMTIME      = "SimTime";
const char* DAF_ELEM_CONNECT      = "Connect";
const char* DAF_ELEM_RELEASE      = "Release";
const char* DAF_ATTR_TIME         = "t";

DAFEnrollment::DAFEnrollment() : cace(NULL), StateTable(NULL)//, aemgmt(NULL)
{
}

DAFEnrollment::~DAFEnrollment(){
    StateTable = NULL;
    cace = NULL;
    //aemgmt = NULL;
}

void DAFEnrollment::initialize()
{
    currentMgmtAEInstanceId = 0;

    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    initSignalsAndListeners();
    initPointers();

    //Perform self-enrollment
    bool isSelfEnrol = par(DAF_PAR_ISSELFENROL).boolValue();
    if (isSelfEnrol) {
        //Vesely -> Jerabek: WTF?
        /*
        StateTable->insert(DAFEnrollmentStateTableEntry(
                APNamingInfo(FlowAlloc->getMyAddress().getApn()),
                APNamingInfo(FlowAlloc->getMyAddress().getApn()),
                DAFEnrollmentStateTableEntry::CON_ESTABLISHED,
                DAFEnrollmentStateTableEntry::ENROLL_ENROLLED));
        */
        updateEnrollmentDisplay(ENICON_ENROLLED);
    }
    else {
        updateEnrollmentDisplay(ENICON_NOTENROLLED);
    }


    apName = this->getModuleByPath("^.^")->par("apName").stringValue();
    apInstance = this->getModuleByPath("^.^")->par("apInstance").stringValue();
    authType = par(DAF_PAR_AUTH_TYPE);
    authName = this->par(DAF_PAR_AUTH_NAME).stringValue();
    authPassword = this->par(DAF_PAR_AUTH_PASS).stringValue();
    authOther = this->par(DAF_PAR_AUTH_OTHER).stringValue();

    maxConRetries = this->par(DAF_PAR_CON_RETRIES);

    cace = new CACEMgmt(this);

    WATCH_MAP(PreenrollConnects);
    WATCH_MAP(PreenrollReleases);

}

void DAFEnrollment::createBindings(Flow* flow, DAFEnrollmentNotifier* module) {
    //FIXME: Vesely: Unused variable commented
    //cModule* Cdap = module->getModuleByPath("^.commonDistributedApplicationProtocol");
    //FIXME: Vesely: Unused variable commented
    //cGate* gCdapIn = Cdap->gateHalf(GATE_SOUTHIO, cGate::INPUT);
    //FIXME: Vesely: Unused variable commented
    //cGate* gCdapOut = Cdap->gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    //Get Socket South Gates
    cModule* SocketMod = module->getModuleByPath("^.socket");
    cGate* gSocketIn;
    cGate* gSocketOut;
    SocketMod->getOrCreateFirstUnconnectedGatePair("southIo", false, true, *&gSocketIn, *&gSocketOut);

    //Get Socket CDAP Gates
    //FIXME: Vesely: Unused variable commented
    //cGate* gSocketCdapIn = SocketMod->gateHalf("cdapIo", cGate::INPUT);
    //FIXME: Vesely: Unused variable commented
    //cGate* gSocketCdapOut = SocketMod->gateHalf("cdapIo", cGate::OUTPUT);


    cModule* aeMgmt = module->getModuleByPath("^");
    cGate* gaeMgmtIn;
    cGate* gaeMgmtOut;
    aeMgmt->getOrCreateFirstUnconnectedGatePair("aeIo", false, true, *&gaeMgmtIn, *&gaeMgmtOut);

    cModule* aeMgmtParent = module->getModuleByPath("^.^");
    cGate* gaeMgmtParentIn;
    cGate* gaeMgmtParentOut;
    aeMgmtParent->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gaeMgmtParentIn, *&gaeMgmtParentOut);

    //Create new gates
    cGate* gIrmIn;
    cGate* gIrmOut;
    Irm->getOrCreateFirstUnconnectedGatePair(GATE_AEIO, false, true, *&gIrmIn, *&gIrmOut);

    cModule* IrmMod = Irm->getParentModule();
    cGate* gIrmModIn;
    cGate* gIrmModOut;
    IrmMod->getOrCreateFirstUnconnectedGatePair(GATE_NORTHIO, false, true, *&gIrmModIn, *&gIrmModOut);

    cModule* ApMon = module->getModuleByPath("^.^.^");
    cGate* gApIn;
    cGate* gApOut;
    ApMon->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gApIn, *&gApOut);

    //Connect gates together
    gIrmOut->connectTo(gIrmModOut);
    gIrmModOut->connectTo(gApIn);
    gApIn->connectTo(gaeMgmtParentIn);
    gaeMgmtParentIn->connectTo(gaeMgmtIn);
    gaeMgmtIn->connectTo(gSocketIn);
    //gSocketCdapIn->connectTo(gCdapIn);

    //gCdapOut->connectTo(gSocketCdapOut);
    gSocketOut->connectTo(gaeMgmtOut);
    gaeMgmtOut->connectTo(gaeMgmtParentOut);
    gaeMgmtParentOut->connectTo(gApOut);
    gApOut->connectTo(gIrmModIn);
    gIrmModIn->connectTo(gIrmIn);

    //Set north-half of the routing in ConnectionTable
    Irm->setNorthGates(flow, gIrmIn, gIrmOut);
}

void DAFEnrollment::initPointers(){
    StateTable = check_and_cast<DAFEnrollmentStateTable*>(getModuleByPath("^.enrollmentStateTable"));
    //aemgmt = check_and_cast<AEMgmt*>( getModuleByPath("^.^.aemanagement.aemgmt") );
    Irm = check_and_cast<IRM*>( getModuleByPath("^.^.^")->getSubmodule(MOD_IPCRESMANAGER)->getSubmodule(MOD_IRM) );
    //FlowAlloc = check_and_cast<FABase*>( getModuleByPath("^.^.flowAllocator.fa") );
}

void DAFEnrollment::initSignalsAndListeners() {
    cModule* catcher1 = this->getModuleByPath("^.^");
    cModule* catcher2 = this->getModuleByPath("^.^");
    cModule* catcher3 = this->getModuleByPath("^.^.^");

    sigDAFEnrollmentCACESendData   = registerSignal(SIG_ENROLLMENT_CACEDataSend);
    sigDAFEnrollmentSendData       = registerSignal(SIG_ENROLLMENT_DataSend);
    sigDAFEnrollmentStartEnrollReq = registerSignal(SIG_ENROLLMENT_StartEnrollmentRequest);
    sigDAFEnrollmentStartEnrollRes = registerSignal(SIG_ENROLLMENT_StartEnrollmentResponse);
    sigDAFEnrollmentStopEnrollReq  = registerSignal(SIG_ENROLLMENT_StopEnrollmentRequest);
    sigDAFEnrollmentStopEnrollRes  = registerSignal(SIG_ENROLLMENT_StopEnrollmentResponse);
    sigDAFEnrollmentStartOperReq   = registerSignal(SIG_ENROLLMENT_StartOperationRequest);
    sigDAFEnrollmentStartOperRes   = registerSignal(SIG_ENROLLMENT_StartOperationResponse);
    sigDAFEnrollmentFinish         = registerSignal(SIG_ENROLLMENT_Finished);

    sigDAFEnrollmentEnrollPosi     = registerSignal(SIG_AEMGMT_ConnectionResponsePositive);

    sigDAFEnrollmentAllocResNega   = registerSignal(SIG_AERIBD_AllocateResponseNegative);
    sigDAFEnrollmentAllocResPosi   = registerSignal(SIG_AERIBD_AllocateResponsePositive);

    lisDAFEnrollmentAllResPosi = new LisDAFEnrollmentAllResPosi(this);
    catcher3->subscribe(SIG_FAI_AllocateResponsePositive, lisDAFEnrollmentAllResPosi);
    //catcher1->subscribe(SIG_RA_MgmtFlowAllocated, lisDAFEnrollmentAllResPosi);

    //  AllocationRequest from FAI
    lisDAFEnrollmentAllReqFromFai = new LisDAFEnrollmentAllReqFromFai(this);
    catcher3->subscribe(SIG_FAI_AllocateRequest, lisDAFEnrollmentAllReqFromFai);


    lisDAFEnrollmentRequest = new LisDAFEnrollmentRequest(this);
    catcher2->subscribe(SIG_AE_Enrolled, lisDAFEnrollmentRequest);



    lisDAFEnrollmentStartEnrollReq = new LisDAFEnrollmentStartEnrollReq(this);
    catcher1->subscribe(SIG_RIBD_StartEnrollmentRequest, lisDAFEnrollmentStartEnrollReq);

    lisDAFEnrollmentStartEnrollRes = new LisDAFEnrollmentStartEnrollRes(this);
    catcher1->subscribe(SIG_RIBD_StartEnrollmentResponse, lisDAFEnrollmentStartEnrollRes);

    lisDAFEnrollmentStopEnrollReq = new LisDAFEnrollmentStopEnrollReq(this);
    catcher1->subscribe(SIG_RIBD_StopEnrollmentRequest, lisDAFEnrollmentStopEnrollReq);

    lisDAFEnrollmentStopEnrollRes = new LisDAFEnrollmentStopEnrollRes(this);
    catcher1->subscribe(SIG_RIBD_StopEnrollmentResponse, lisDAFEnrollmentStopEnrollRes);

    lisDAFEnrollmentStartOperationReq = new LisDAFEnrollmentStopOperationReq(this);
    catcher1->subscribe(SIG_RIBD_StartOperationRequest, lisDAFEnrollmentStartOperationReq);

    lisDAFEnrollmentStartOperationRes = new LisDAFEnrollmentStartOperationRes(this);
    catcher1->subscribe(SIG_RIBD_StartOperationResponse, lisDAFEnrollmentStartOperationRes);

    lisDAFEnrollmentConResPosi = new LisDAFEnrollmentConResPosi(this);
    catcher1->subscribe(SIG_RIBD_ConnectionResponsePositive, lisDAFEnrollmentConResPosi);

    lisDAFEnrollmentConResNega = new LisDAFEnrollmentConResNega(this);
    catcher1->subscribe(SIG_RIBD_ConnectionResponseNegative, lisDAFEnrollmentConResNega);

    lisDAFEnrollmentConReq = new LisDAFEnrollmentConReq(this);
    catcher1->subscribe(SIG_RIBD_ConnectionRequest, lisDAFEnrollmentConReq);
}
/*
void DAFEnrollment::startCACE(Flow* flow) {
    Enter_Method("startCACE()");

    //auto entry = DAFEnrollmentStateTableEntry(apnip->first, apnip->second, DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);
    //StateTable->insert(entry);

    auto entry = StateTable->findEntryByDstAPN(flow->getDstApni().getApn());

    CDAP_M_Connect* msg = new CDAP_M_Connect(DAF_MSG_CONREQ);

    authValue_t aValue;
    aValue.authName = authName;
    aValue.authPassword = authPassword;
    aValue.authOther = authOther;

    auth_t auth;
    auth.authType = authType;
    auth.authValue = aValue;

    msg->setAuth(auth);
    msg->setAbsSyntax(GPB);

    APNamingInfo src = APNamingInfo(entry->getLocal().getApn(),
                entry->getLocal().getApinstance(),
                entry->getLocal().getAename(),
                entry->getLocal().getAeinstance());

    APNamingInfo dst = APNamingInfo(entry->getRemote().getApn(),
            entry->getRemote().getApinstance(),
            entry->getRemote().getAename(),
            entry->getRemote().getAeinstance());
    //XXX: Vesely@Jerabek> Removing unnecessary *.msg ADT when there exists
    //                      exactly the same ADT in RINASim source codes.
    naming_t dst;
    dst.AEInst = entry.getRemote().getAeinstance();
    dst.AEName = entry.getRemote().getAename();
    dst.ApInst = entry.getRemote().getApinstance();
    dst.ApName = entry.getRemote().getApn().getName();

    naming_t src;
    src.AEInst = entry.getLocal().getAeinstance();
    src.AEName = entry.getLocal().getAename();
    src.ApInst = entry.getLocal().getApinstance();
    src.ApName = entry.getLocal().getApn().getName();


    msg->setSrc(src);
    msg->setDst(dst);

    msg->setSrcAddr(Address(entry->getLocal().getApn()));
    msg->setDstAddr(Address(entry->getRemote().getApn()));

    //send data to ribd to send
    signalizeCACESendData(msg);
}

void DAFEnrollment::insertStateTableEntry(Flow* flow){
    Enter_Method("insertStateTableEntry()");
    //insert only first flow created (management flow)
    if(StateTable->findEntryByDstAPN(APN(flow->getDstAddr().getApn().getName().c_str())) != NULL) {
        return;
    }
    StateTable->insert(DAFEnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(), DAFEnrollmentStateTableEntry::CON_CONNECTPENDING));
}

void DAFEnrollment::receivePositiveConnectResponse(CDAPMessage* msg) {
    Enter_Method("receivePositiveConnectResponse()");

    //signalizeEnrolled();

    // this is commented only for testing ---> refactoring of adress is need to be done
    //    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

    //check appropriate state
    if (entry->getCACEConStatus() != DAFEnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_ESTABLISHED);

    startEnrollment(entry);

}

void DAFEnrollment::receiveNegativeConnectResponse(CDAPMessage* msg) {
    Enter_Method("receiveNegativeConnectResponse()");

    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

    //check appropriate state
    if (entry->getCACEConStatus() != DAFEnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    if (this->maxConRetries <= entry->getCurrentConnectRetries()) {
        entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_NIL);
        //TODO: send release and deallocate
        return;
    }


    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);
    entry->increaseCurrentConnectRetries();
    //create and send new connect retry
    processNewConReq(entry);
}

void DAFEnrollment::receiveConnectRequest(CDAPMessage* msg) {
    Enter_Method("receiveConnectRequest()");

    CDAP_M_Connect* cmsg = check_and_cast<CDAP_M_Connect*>(msg);

    auto ent = DAFEnrollmentStateTableEntry(
             cmsg->getDst(), cmsg->getSrc(), DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);
    StateTable->insert(ent);

    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

    if (!entry) {
        EV << "DAFEnrollment status not found for "
           << cmsg->getSrc().getApn() << endl;
        return;
    }

    //check appropriate state
    if (entry->getCACEConStatus() != DAFEnrollmentStateTableEntry::CON_CONNECTPENDING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    //check if message is valid
    if (cmsg->getAbsSyntax() != GPB) {
        this->processConResNega(entry, cmsg);
        return;
    }

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);

    authenticate(entry, cmsg);
}
*/
/*   enrollment initiator */

void DAFEnrollment::startEnrollment(DAFEnrollmentStateTableEntry* entry) {
    Enter_Method("startDAFEnrollment()");

    auto enrollObj = new DAFEnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    //TODO: assign address to new one to send it
    //enrollObj->setAddress(APN(aemgmt->getMyAddress().getIpcAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentRequest(enrollObj);

    //set appropriate state
    entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT);
}

void DAFEnrollment::receiveStartEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartDAFEnrollmentResponse()");

    CDAP_M_Start_R* smsg = check_and_cast<CDAP_M_Start_R*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    DAFEnrollmentObj* enrollRec = (check_and_cast<DAFEnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getDAFEnrollmentStatus() != DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    //assign new, received address
    //Address newAddr = aemgmt->getMyAddress();
    //newAddr.setIpcAddress(APN(enrollRec->getAddress().getName().c_str()));
    //aemgmt->setMyAddress(newAddr);

    //TODO: assign other received values

    //change state
    entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT);

    //TODO: wait for create messages and stop enrollment request
}

void DAFEnrollment::receiveStopEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStopDAFEnrollmentRequest()");


    CDAP_M_Stop* smsg = check_and_cast<CDAP_M_Stop*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    DAFEnrollmentObj* enrollRec = (check_and_cast<DAFEnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getDAFEnrollmentStatus() != DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    //set immediate transition to operational state
    entry->setIsImmediateDAFEnrollment(enrollRec->getIsImmediate());

    //set appropriate state
    entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_READ_RESPONSE);

    //TODO: send read requests, wait for responses, send Mstop enrollment
    //for now send stop enrollment response
    processStopEnrollmentResponse(entry);
}

void DAFEnrollment::processStopEnrollmentResponse(DAFEnrollmentStateTableEntry* entry) {

    auto enrollObj = new DAFEnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    signalizeStopEnrollmentResponse(enrollObj);


    if (entry->getIsImmediateDAFEnrollment()) {
        entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_ENROLLED);
        signalizeEnrollmentFinished(entry);

        signalizeEnrolled();
    }
    else {
        entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_OPERATION);
        //TODO: continue enrollment here
    }
}

void DAFEnrollment::receiveStartOperationRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationRequest()");

}

/* enrollment member */

void DAFEnrollment::receiveStartEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartDAFEnrollmentRequest()");

    CDAP_M_Start* smsg = check_and_cast<CDAP_M_Start*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    DAFEnrollmentObj* enrollRec = (check_and_cast<DAFEnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getDAFEnrollmentStatus() != DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }


    auto enrollObj = new DAFEnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    //TODO: repair this dummy address assign
    //enrollObj->setAddress(APN(enrollRec->getAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentResponse(enrollObj);

    //TODO: send create messages, wait for responses, then send stop enrollment
    //for now send stop enrollment
    processStopEnrollmentImmediate(entry);
}

void DAFEnrollment::receiveStopEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStopDAFEnrollmentResponse()");

    CDAP_M_Stop_R* smsg = check_and_cast<CDAP_M_Stop_R*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    DAFEnrollmentObj* enrollRec = (check_and_cast<DAFEnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getDAFEnrollmentStatus() != DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    if (entry->getIsImmediateDAFEnrollment()) {
        entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_ENROLLED);
        //TODO: emit signal somewhere and probably send rib update ...
    }
    else {
        //TODO: add appropriate state for read and wait operation
    }
}

void DAFEnrollment::receiveStartOperationResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationResponse()");

}

void DAFEnrollment::processStopEnrollmentImmediate(DAFEnrollmentStateTableEntry* entry) {
    auto enrollObj = new DAFEnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    //set immediate
    enrollObj->setIsImmediate(true);
    entry->setIsImmediateDAFEnrollment(true);

    //TODO: add other necessary information

    signalizeStopEnrollmentRequest(enrollObj);

    entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT);
}

/*void DAFEnrollment::authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg) {
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

void DAFEnrollment::processNewConReq(DAFEnrollmentStateTableEntry* entry) {
    Enter_Method("processNewConReq()");

    //TODO: probably change values, this is retry

    CDAP_M_Connect* msg = new CDAP_M_Connect(DAF_MSG_CONREQRETRY);

    authValue_t aValue;
    aValue.authName = authName;
    aValue.authPassword = authPassword;
    aValue.authOther = authOther;

    auth_t auth;
    auth.authType = authType;
    auth.authValue = aValue;

    msg->setAuth(auth);
    msg->setAbsSyntax(GPB);

    APNamingInfo src = APNamingInfo(entry->getLocal().getApn(),
                entry->getLocal().getApinstance(),
                entry->getLocal().getAename(),
                entry->getLocal().getAeinstance());

    APNamingInfo dst = APNamingInfo(entry->getRemote().getApn(),
            entry->getRemote().getApinstance(),
            entry->getRemote().getAename(),
            entry->getRemote().getAeinstance());

    msg->setSrc(src);
    msg->setDst(dst);

    msg->setSrcAddr(Address(entry->getLocal().getApn()));
    msg->setDstAddr(Address(entry->getRemote().getApn()));

    //send data to ribd to send
    signalizeCACESendData(msg);

    //change state to auth after send retry
    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);
}

void DAFEnrollment::processConResPosi(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R(DAF_MSG_CONRESPOS);
    CDAP_M_Connect* cmsg1 = check_and_cast<CDAP_M_Connect*>(cmsg);

    APNamingInfo src = APNamingInfo(entry->getLocal().getApn(),
                entry->getLocal().getApinstance(),
                entry->getLocal().getAename(),
                entry->getLocal().getAeinstance());

    APNamingInfo dst = APNamingInfo(entry->getRemote().getApn(),
            entry->getRemote().getApinstance(),
            entry->getRemote().getAename(),
            entry->getRemote().getAeinstance());

    result_t result;
    result.resultValue = R_SUCCESS;

    auth_t auth;
    auth.authType = cmsg1->getAuth().authType;
    auth.authValue = cmsg1->getAuth().authValue;

    msg->setAbsSyntax(GPB);
    msg->setResult(result);
    msg->setAuth(auth);

    msg->setSrc(src);
    msg->setDst(dst);

    msg->setSrcAddr(Address(entry->getLocal().getApn()));
    msg->setDstAddr(Address(entry->getRemote().getApn()));

    //send data to ribd to send
    signalizeCACESendData(msg);

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_ESTABLISHED);
    entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT);
}

void DAFEnrollment::processConResNega(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R(DAF_MSG_CONRESNEG);
    CDAP_M_Connect* cmsg1 = check_and_cast<CDAP_M_Connect*>(cmsg);

    APNamingInfo src = APNamingInfo(entry->getLocal().getApn(),
                entry->getLocal().getApinstance(),
                entry->getLocal().getAename(),
                entry->getLocal().getAeinstance());

    APNamingInfo dst = APNamingInfo(entry->getRemote().getApn(),
            entry->getRemote().getApinstance(),
            entry->getRemote().getAename(),
            entry->getRemote().getAeinstance());

    result_t result;
    result.resultValue = R_FAIL;

    auth_t auth;
    auth.authType = cmsg1->getAuth().authType;
    auth.authValue = cmsg1->getAuth().authValue;

    msg->setAbsSyntax(GPB);
    msg->setResult(result);
    msg->setAuth(auth);

    msg->setSrc(src);
    msg->setDst(dst);

    msg->setSrcAddr(Address(entry->getLocal().getApn()));
    msg->setDstAddr(Address(entry->getRemote().getApn()));

    //send data to send to ribd
    signalizeCACESendData(msg);

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);

    //increase number of connects
    entry->increaseCurrentConnectRetries();
}
*/
void DAFEnrollment::signalizeCACESendData(CDAPMessage* cmsg) {
    emit(sigDAFEnrollmentCACESendData, cmsg);
}

void DAFEnrollment::signalizeStartEnrollmentRequest(DAFEnrollmentObj* obj) {
    emit(sigDAFEnrollmentStartEnrollReq, obj);
}

void DAFEnrollment::signalizeStartEnrollmentResponse(DAFEnrollmentObj* obj) {
    emit(sigDAFEnrollmentStartEnrollRes, obj);
}

void DAFEnrollment::signalizeStopEnrollmentRequest(DAFEnrollmentObj* obj) {
    //TODO: move following line somewhere else
    updateEnrollmentDisplay(ENICON_ENROLLED);
    emit(sigDAFEnrollmentStopEnrollReq, obj);
}

void DAFEnrollment::signalizeStopEnrollmentResponse(DAFEnrollmentObj* obj) {
    emit(sigDAFEnrollmentStopEnrollRes, obj);
}

void DAFEnrollment::signalizeStartOperationRequest(DAFOperationObj* obj) {
    emit(sigDAFEnrollmentStartOperReq, obj);
}

void DAFEnrollment::signalizeStartOperationResponse(DAFOperationObj* obj) {
    emit(sigDAFEnrollmentStartOperRes, obj);
}

void DAFEnrollment::signalizeEnrollmentFinished(DAFEnrollmentStateTableEntry* entry) {
    updateEnrollmentDisplay(ENICON_ENROLLED);
    APNIPair* apnip = new APNIPair(entry->getLocal(), entry->getRemote());
    emit(sigDAFEnrollmentFinish, apnip);
}

void DAFEnrollment::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(DAF_ELEM_PREENROL))
        mainTag = config->getFirstChildWithTag(DAF_ELEM_PREENROL);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElementList enrll = mainTag->getChildrenByTagName(DAF_ELEM_SIMTIME);
    for (cXMLElementList::const_iterator it = enrll.begin(); it != enrll.end(); ++it) {
        cXMLElement* m = *it;

        if (!m->getAttribute(DAF_ATTR_TIME)) {
            EV << "\nSimTime tag is missing time attribute!" << endl;
            continue;
        }

        simtime_t cas = atof(m->getAttribute(DAF_ATTR_TIME));

        if (m->getFirstChildWithTag(DAF_ELEM_CONNECT)) {
            PreenrollConnects[cas] = new APNIPairs();
            cMessage* cmsg = new cMessage(DAF_MSG_ENRLCON);
            scheduleAt(cas, cmsg);
        }

        if (m->getFirstChildWithTag(DAF_ELEM_RELEASE)) {
            PreenrollReleases[cas] = new APNIPairs();
            cMessage* cmsg = new cMessage(DAF_MSG_ENRLREL);
            scheduleAt(cas, cmsg);
        }

        cXMLElementList coms = m->getChildren();
        for (cXMLElementList::const_iterator jt = coms.begin(); jt != coms.end(); ++jt) {
            cXMLElement* n = *jt;

            if ( !( strcmp(n->getTagName(), DAF_ELEM_CONNECT) xor strcmp(n->getTagName(), DAF_ELEM_RELEASE) )
                    && !(n->getAttribute(ATTR_SRC))
                    && !(n->getAttribute(ATTR_DST))
               ) {
                EV << "\nError when parsing Connect/Release record" << endl;
                continue;
            }

            if ( !strcmp(n->getTagName(), DAF_ELEM_CONNECT) ) {
                PreenrollConnects[cas]->push_back( APNIPair(n->getAttribute(ATTR_SRC), n->getAttribute(ATTR_DST)) );
                //EV << "!!!!!!!!!!!!!" << PreenrollConnects[cas]->size() << endl;
            }
            else if ( !strcmp(n->getTagName(), DAF_ELEM_RELEASE) ) {
                PreenrollReleases[cas]->push_back( APNIPair(n->getAttribute(ATTR_SRC), n->getAttribute(ATTR_DST)) );
            }
        }
    }
}

void DAFEnrollment::updateEnrollmentDisplay(DAFEnrollment::IconEnrolStatus status) {
    cModule* ipc = this->getParentModule()->getParentModule();
    std::string ico, col;
    switch (status) {
        case ENICON_ENROLLED: {ico="status/check"; col="green"; break;}
        case ENICON_FLOWMIS: {ico="status/excl"; col="yellow";break;}
        case ENICON_NOTENROLLED:
        default:              {ico="status/cross"; col="red"; break;}

    }
    ipc->getDisplayString().setTagArg("i2", 0, ico.c_str());
    ipc->getDisplayString().setTagArg("i2", 1, col.c_str());
}

void DAFEnrollment::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if ( !opp_strcmp(msg->getName(), DAF_MSG_ENRLCON) ) {
            APNIPairs* apnip = PreenrollConnects[simTime()];

            while (!apnip->empty())
            {
                APNIPair pair = apnip->front();
                auto entry = StateTable->findEntryByDstAPN(pair.second.getApn());
                if (!entry) {
                    //Vesely -> Jerabek: WTF?
                    //FlowAlloc->receiveMgmtAllocateRequest(pair.first, pair.second);
                }
                apnip->pop_front();
            }
        }
        else if ( !opp_strcmp(msg->getName(), DAF_MSG_ENRLREL) ) {
            APNIPairs* apnip = PreenrollReleases[simTime()];
            while (!apnip->empty())
            {
                APNIPair pair = apnip->front();
                auto entry = StateTable->findEntryByDstAPN(pair.second.getApn());
                if (entry && entry->getDAFEnrollmentStatus() == DAFEnrollmentStateTableEntry::ENROLL_ENROLLED ) {
                    //FIXME: Vesely->Jerabek: Here goes release part of DAFEnrollment
                }
                apnip->pop_front();
            }
        }
        delete msg;
    }
}

void DAFEnrollment::signalizeEnrolled() {
    emit(sigDAFEnrollmentEnrollPosi, 0);
}

void DAFEnrollment::checkEnrolled(APNIPair* apnip) {
    Enter_Method("checkEnrolled()");
    if (!StateTable->findEntryByDstAPN(apnip->first.getApn())) {
        createFlow(apnip);
    }
    else {
        signalizeEnrolled();
    }
}

void DAFEnrollment::createFlow(APNIPair* apnip) {
    Enter_Method("createFlow()");


    APNamingInfo src = APNamingInfo(apnip->first.getApn(),
                                    apnip->first.getApinstance(),
                                    "mgmt",
                                    std::to_string(currentMgmtAEInstanceId));

    APNamingInfo dst = APNamingInfo(apnip->second.getApn(),
                                    apnip->second.getApinstance(),
                                    "mgmt",
                                    "0");

    //Create a flow
    Flow* flow = new Flow(src,dst);
    flow->setQosRequirements(QoSReq::MANAGEMENT);

    Irm->newFlow(flow);
    Irm->receiveAllocationRequestFromAe(flow);
}

void DAFEnrollment::receiveAllocationResponsePositive(Flow* flow) {
    Enter_Method("receiveAllocationResponsePositive()");

    Irm->receiveAllocationResponsePositiveFromIpc(flow);

    auto module = createMgmtAE(flow);

    createBindings(flow, module);

    DAFEnrollmentStateTableEntry entry = DAFEnrollmentStateTableEntry(flow->getSrcApni(),flow->getDstApni(), DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);
    StateTable->insert(entry);

    cace->startCACE(flow);

}

DAFEnrollmentNotifier* DAFEnrollment::createMgmtAE(Flow* flow) {
    cModuleType *moduleType = cModuleType::get("rina.src.DAF.AEManagement.AEmanagementModule");

    //Create a name
    std::ostringstream ostr;
    ostr << "mgmtae_" << currentMgmtAEInstanceId;

    //Instantiate module
    cModule *module = moduleType->create(ostr.str().c_str(), this->getModuleByPath("^.^.aeManagement"));

    module->finalizeParameters();
    module->buildInside();

    cModule *aemgmt = module->getSubmodule("aemgmt");
    aemgmt->par("aeInstance") = std::to_string(currentMgmtAEInstanceId);
    aemgmt->par("dstApName") = flow->getDstApni().getApn().getName();
    aemgmt->par("dstApInstance") = flow->getDstApni().getApinstance();
    aemgmt->par("dstAeName") = flow->getDstApni().getAename();
    aemgmt->par("dstAeInstance") = flow->getDstApni().getAeinstance();

    //TODO: create activation message
    //module->scheduleStart(simTime());
    module->callInitialize();

    currentMgmtAEInstanceId += 1;

    DAFEnrollmentNotifier* enrollNotif = dynamic_cast<DAFEnrollmentNotifier*>(module->getSubmodule("enrollmentNotifier"));
    enrollNotif->setFlow(flow);

    return enrollNotif;
}

void DAFEnrollment::receiveAllocationRequestFromFAI(Flow* flow) {
    Enter_Method("receiveAllocationRequestFromFai()");

    if ( flow->getQosRequirements().compare(QoSReq::MANAGEMENT) ) {

        Irm->newFlow(flow);

        bool status = Irm->receiveAllocationResponsePositiveFromIpc(flow);

        //Change connection status
        if (status) {
            this->signalizeAllocateResponsePositive(flow);
        }
        else {
            EV << "IRM was unable to create bindings!" << endl;
        }

        auto module = createMgmtAE(flow);

        createBindings(flow,module);
    }
    else {
        EV << "QoS Requirement cannot be met, please check AE attributes!" << endl;
        this->signalizeAllocateResponseNegative(flow);
    }
}

void DAFEnrollment::signalizeAllocateResponsePositive(Flow* flow) {
    emit(sigDAFEnrollmentAllocResPosi, flow);
}

void DAFEnrollment::signalizeAllocateResponseNegative(Flow* flow) {
    emit(sigDAFEnrollmentAllocResNega, flow);
}
