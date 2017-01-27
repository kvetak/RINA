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
 * @file Enrollment.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment and CACE
 * @detail
 */


#include "DIF/Enrollment/Enrollment.h"

Define_Module(Enrollment);

const char* PAR_AUTH_TYPE       = "authType";
const char* PAR_AUTH_NAME       = "authName";
const char* PAR_AUTH_OTHER      = "authOther";
const char* PAR_AUTH_PASS       = "authPassword";
const char* PAR_CON_RETRIES     = "maxConRetries";
const char* PAR_ISSELFENROL     = "isSelfEnrolled";

const char* MSG_CONREQ                = "Connect/Auth";
const char* MSG_CONREQRETRY           = "ConnectRetry/Auth";
const char* MSG_CONRESPOS             = "Connect+/Auth";
const char* MSG_CONRESNEG             = "Connect-/Auth";
const char* MSG_ENRLCON               = "Enrol-Connect";
const char* MSG_ENRLREL               = "Enrol-Release";

const char* ELEM_PREENROL     = "Preenrollment";
const char* ELEM_SIMTIME      = "SimTime";
const char* ELEM_CONNECT      = "Connect";
const char* ELEM_RELEASE      = "Release";
const char* ATTR_TIME         = "t";

Enrollment::Enrollment() :
        StateTable(NULL), RibDaemon(NULL)
{
}

Enrollment::~Enrollment(){
    StateTable = NULL;
    RibDaemon = NULL;
}

void Enrollment::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    initSignalsAndListeners();
    initPointers();

    //Perform self-enrollment
    bool isSelfEnrol = par(PAR_ISSELFENROL).boolValue();
    if (isSelfEnrol) {
        StateTable->insert(EnrollmentStateTableEntry(
                APNamingInfo(FlowAlloc->getMyAddress().getApn()),
                APNamingInfo(FlowAlloc->getMyAddress().getApn()),
                EnrollmentStateTableEntry::CON_ESTABLISHED,
                EnrollmentStateTableEntry::ENROLL_ENROLLED));
        updateEnrollmentDisplay(ENICON_ENROLLED);
    }
    else {
        //TODO: Work more on checking of N-1 flow existence
        if (StateTable->isEnrolled(FlowAlloc->getMyAddress().getApn()))
            { updateEnrollmentDisplay(ENICON_FLOWMIS); }
        else
            { updateEnrollmentDisplay(ENICON_NOTENROLLED); }
    }

    authType = par(PAR_AUTH_TYPE);
    authName = this->par(PAR_AUTH_NAME).stringValue();
    authPassword = this->par(PAR_AUTH_PASS).stringValue();
    authOther = this->par(PAR_AUTH_OTHER).stringValue();

    maxConRetries = this->par(PAR_CON_RETRIES);

    WATCH_MAP(PreenrollConnects);
    WATCH_MAP(PreenrollReleases);
}

void Enrollment::initPointers(){
    StateTable = getRINAModule<EnrollmentStateTable*>(this, 1, {MOD_ENROLLMENTTABLE});
    RibDaemon = getRINAModule<RIBd*>(this, 2, {MOD_RIBDAEMON, MOD_RIBD});
    FlowAlloc = getRINAModule<FABase*>(this, 2, {MOD_FLOWALLOC, MOD_FA});
}

void Enrollment::initSignalsAndListeners() {
    cModule* catcher1 = this->getModuleByPath("^.^");

    sigEnrollmentCACESendData   = registerSignal(SIG_ENROLLMENT_CACEDataSend);
    sigEnrollmentSendData       = registerSignal(SIG_ENROLLMENT_DataSend);
    sigEnrollmentStartEnrollReq = registerSignal(SIG_ENROLLMENT_StartEnrollmentRequest);
    sigEnrollmentStartEnrollRes = registerSignal(SIG_ENROLLMENT_StartEnrollmentResponse);
    sigEnrollmentStopEnrollReq  = registerSignal(SIG_ENROLLMENT_StopEnrollmentRequest);
    sigEnrollmentStopEnrollRes  = registerSignal(SIG_ENROLLMENT_StopEnrollmentResponse);
    sigEnrollmentStartOperReq   = registerSignal(SIG_ENROLLMENT_StartOperationRequest);
    sigEnrollmentStartOperRes   = registerSignal(SIG_ENROLLMENT_StartOperationResponse);
    sigEnrollmentFinish         = registerSignal(SIG_ENROLLMENT_Finished);

    lisEnrollmentAllResPosi = new LisEnrollmentAllResPosi(this);
    catcher1->subscribe(SIG_FA_MgmtFlowAllocated, lisEnrollmentAllResPosi);
    catcher1->subscribe(SIG_RA_MgmtFlowAllocated, lisEnrollmentAllResPosi);

    //lisEnrollmentGetFlowFromFaiCreResPosi = new LisEnrollmentGetFlowFromFaiCreResPosi(this);
    //catcher1->subscribe(SIG_FAI_CreateFlowResponsePositive, lisEnrollmentGetFlowFromFaiCreResPosi);

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

void Enrollment::startCACE(APNIPair* apnip) {
    Enter_Method("startCACE()");

    auto entry = EnrollmentStateTableEntry(apnip->first, apnip->second, EnrollmentStateTableEntry::CON_AUTHENTICATING);
    StateTable->insert(entry);

    CDAP_M_Connect* msg = new CDAP_M_Connect(MSG_CONREQ);

    authValue_t aValue;
    aValue.authName = authName;
    aValue.authPassword = authPassword;
    aValue.authOther = authOther;

    auth_t auth;
    auth.authType = authType;
    auth.authValue = aValue;

    msg->setAuth(auth);
    msg->setAbsSyntax(GPB);

    APNamingInfo src = APNamingInfo(entry.getLocal().getApn(),
                entry.getLocal().getApinstance(),
                entry.getLocal().getAename(),
                entry.getLocal().getAeinstance());

    APNamingInfo dst = APNamingInfo(entry.getRemote().getApn(),
            entry.getRemote().getApinstance(),
            entry.getRemote().getAename(),
            entry.getRemote().getAeinstance());
    /*
     * XXX: Vesely@Jerabek> Removing unnecessary *.msg ADT when there exists
     *                      exactly the same ADT in RINASim source codes.
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
    */

    msg->setSrc(src);
    msg->setDst(dst);

    msg->setSrcAddr(Address(entry.getLocal().getApn()));
    msg->setDstAddr(Address(entry.getRemote().getApn()));

    //send data to ribd to send
    signalizeCACESendData(msg);
}

void Enrollment::insertStateTableEntry(Flow* flow){
    //insert only first flow created (management flow)
    if(StateTable->findEntryByDstAPN(APN(flow->getDstAddr().getApn().getName().c_str())) != NULL) {
        return;
    }
    StateTable->insert(EnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(), EnrollmentStateTableEntry::CON_CONNECTPENDING));
}

void Enrollment::receivePositiveConnectResponse(CDAPMessage* msg) {
    Enter_Method("receivePositiveConnectResponse()");

    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

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

    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

    //check appropriate state
    if (entry->getCACEConStatus() != EnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    if (this->maxConRetries <= entry->getCurrentConnectRetries()) {
        entry->setCACEConStatus(EnrollmentStateTableEntry::CON_NIL);
        //TODO: send release and deallocate
        return;
    }


    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_CONNECTPENDING);
    entry->increaseCurrentConnectRetries();
    //create and send new connect retry
    processNewConReq(entry);
}

void Enrollment::receiveConnectRequest(CDAPMessage* msg) {
    Enter_Method("receiveConnectRequest()");

    CDAP_M_Connect* cmsg = check_and_cast<CDAP_M_Connect*>(msg);

    auto ent = EnrollmentStateTableEntry(
             cmsg->getDst(), cmsg->getSrc(), EnrollmentStateTableEntry::CON_CONNECTPENDING);
    StateTable->insert(ent);

    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(cmsg->getSrc().getApn());

    if (!entry) {
        EV << "Enrollment status not found for "
           << cmsg->getSrc().getApn() << endl;
        return;
    }

    //check appropriate state
    if (entry->getCACEConStatus() != EnrollmentStateTableEntry::CON_CONNECTPENDING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    //check if message is valid
    if (cmsg->getAbsSyntax() != GPB) {
        this->processConResNega(entry, cmsg);
        return;
    }

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_AUTHENTICATING);

    authenticate(entry, cmsg);
}

/*   enrollment initiator */

void Enrollment::startEnrollment(EnrollmentStateTableEntry* entry) {
    Enter_Method("startEnrollment()");

    auto enrollObj = new EnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    enrollObj->setAddress(APN(RibDaemon->getMyAddress().getIpcAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentRequest(enrollObj);

    //set appropriate state
    entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT);
}

void Enrollment::receiveStartEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartEnrollmentResponse()");

    CDAP_M_Start_R* smsg = check_and_cast<CDAP_M_Start_R*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    EnrollmentObj* enrollRec = (check_and_cast<EnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getEnrollmentStatus() != EnrollmentStateTableEntry::ENROLL_WAIT_START_RESPONSE_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    //assign new, received address
    Address newAddr = RibDaemon->getMyAddress();
    newAddr.setIpcAddress(APN(enrollRec->getAddress().getName().c_str()));
    RibDaemon->setMyAddress(newAddr);

    //TODO: assign other received values

    //change state
    entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT);

    //TODO: wait for create messages and stop enrollment request
}

void Enrollment::receiveStopEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStopEnrollmentRequest()");


    CDAP_M_Stop* smsg = check_and_cast<CDAP_M_Stop*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    EnrollmentObj* enrollRec = (check_and_cast<EnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getEnrollmentStatus() != EnrollmentStateTableEntry::ENROLL_WAIT_STOP_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    //set immediate transition to operational state
    entry->setIsImmediateEnrollment(enrollRec->getIsImmediate());

    //set appropriate state
    entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_READ_RESPONSE);

    //TODO: send read requests, wait for responses, send Mstop enrollment
    //for now send stop enrollment response
    processStopEnrollmentResponse(entry);
}

void Enrollment::processStopEnrollmentResponse(EnrollmentStateTableEntry* entry) {

    auto enrollObj = new EnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    signalizeStopEnrollmentResponse(enrollObj);

    if (entry->getIsImmediateEnrollment()) {
        entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_ENROLLED);
        signalizeEnrollmentFinished(entry);
    }
    else {
        entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_START_OPERATION);
        //TODO: continue enrollment here
    }
}

void Enrollment::receiveStartOperationRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationRequest()");

}

/* enrollment member */

void Enrollment::receiveStartEnrollmentRequest(CDAPMessage* msg) {
    Enter_Method("receiveStartEnrollmentRequest()");

    CDAP_M_Start* smsg = check_and_cast<CDAP_M_Start*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    EnrollmentObj* enrollRec = (check_and_cast<EnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getEnrollmentStatus() != EnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }


    auto enrollObj = new EnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    //TODO: repair this dummy address assign
    enrollObj->setAddress(APN(enrollRec->getAddress().getName()));

    //TODO: add other necessary information

    //process enrollment object to ribd to send
    signalizeStartEnrollmentResponse(enrollObj);

    //TODO: send create messages, wait for responses, then send stop enrollment
    //for now send stop enrollment
    processStopEnrollmentImmediate(entry);
}

void Enrollment::receiveStopEnrollmentResponse(CDAPMessage* msg) {
    Enter_Method("receiveStopEnrollmentResponse()");

    CDAP_M_Stop_R* smsg = check_and_cast<CDAP_M_Stop_R*>(msg);

    //not expected message
    if (!smsg) {
        //TODO: send release and deallocate
        return;
    }

    EnrollmentObj* enrollRec = (check_and_cast<EnrollmentObj*>(smsg->getObjectItem().objectVal))->dup();
    EnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPN(APN(enrollRec->getSrcAddress().getApn().getName().c_str()));

    //check for appropriate state
    if (entry->getEnrollmentStatus() != EnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT) {
        //TODO: send release and deallocate
        return;
    }

    if (entry->getIsImmediateEnrollment()) {
        entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_ENROLLED);
        //TODO: emit signal somewhere and probably send rib update ...
    }
    else {
        //TODO: add appropriate state for read and wait operation
    }
}

void Enrollment::receiveStartOperationResponse(CDAPMessage* msg) {
    Enter_Method("receiveStartOperationResponse()");

}

void Enrollment::processStopEnrollmentImmediate(EnrollmentStateTableEntry* entry) {
    auto enrollObj = new EnrollmentObj(Address(entry->getLocal().getApn()), Address(entry->getRemote().getApn()));

    //set immediate
    enrollObj->setIsImmediate(true);
    entry->setIsImmediateEnrollment(true);

    //TODO: add other necessary information

    signalizeStopEnrollmentRequest(enrollObj);

    entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_STOP_RESPONSE_ENROLLMENT);
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

void Enrollment::processNewConReq(EnrollmentStateTableEntry* entry) {
    Enter_Method("processNewConReq()");

    //TODO: probably change values, this is retry

    CDAP_M_Connect* msg = new CDAP_M_Connect(MSG_CONREQRETRY);

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
    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_AUTHENTICATING);
}

void Enrollment::processConResPosi(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R(MSG_CONRESPOS);
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

    entry->setCACEConStatus(EnrollmentStateTableEntry::CON_ESTABLISHED);
    entry->setEnrollmentStatus(EnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT);
}

void Enrollment::processConResNega(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
    CDAP_M_Connect_R* msg = new CDAP_M_Connect_R(MSG_CONRESNEG);
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

void Enrollment::signalizeEnrollmentFinished(EnrollmentStateTableEntry* entry) {
    updateEnrollmentDisplay(ENICON_ENROLLED);
    APNIPair* apnip = new APNIPair(entry->getLocal(), entry->getRemote());
    emit(sigEnrollmentFinish, apnip);
}

void Enrollment::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_PREENROL))
        mainTag = config->getFirstChildWithTag(ELEM_PREENROL);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElementList enrll = mainTag->getChildrenByTagName(ELEM_SIMTIME);
    for (cXMLElementList::const_iterator it = enrll.begin(); it != enrll.end(); ++it) {
        cXMLElement* m = *it;

        if (!m->getAttribute(ATTR_TIME)) {
            EV << "\nSimTime tag is missing time attribute!" << endl;
            continue;
        }

        simtime_t cas = atof(m->getAttribute(ATTR_TIME));

        if (m->getFirstChildWithTag(ELEM_CONNECT)) {
            PreenrollConnects[cas] = new APNIPairs();
            cMessage* cmsg = new cMessage(MSG_ENRLCON);
            scheduleAt(cas, cmsg);
        }

        if (m->getFirstChildWithTag(ELEM_RELEASE)) {
            PreenrollReleases[cas] = new APNIPairs();
            cMessage* cmsg = new cMessage(MSG_ENRLREL);
            scheduleAt(cas, cmsg);
        }

        cXMLElementList coms = m->getChildren();
        for (cXMLElementList::const_iterator jt = coms.begin(); jt != coms.end(); ++jt) {
            cXMLElement* n = *jt;

            if ( !( strcmp(n->getTagName(), ELEM_CONNECT) xor strcmp(n->getTagName(), ELEM_RELEASE) )
                    && !(n->getAttribute(ATTR_SRC))
                    && !(n->getAttribute(ATTR_DST))
               ) {
                EV << "\nError when parsing Connect/Release record" << endl;
                continue;
            }

            if ( !strcmp(n->getTagName(), ELEM_CONNECT) ) {
                PreenrollConnects[cas]->push_back( APNIPair(n->getAttribute(ATTR_SRC), n->getAttribute(ATTR_DST)) );
                //EV << "!!!!!!!!!!!!!" << PreenrollConnects[cas]->size() << endl;
            }
            else if ( !strcmp(n->getTagName(), ELEM_RELEASE) ) {
                PreenrollReleases[cas]->push_back( APNIPair(n->getAttribute(ATTR_SRC), n->getAttribute(ATTR_DST)) );
            }
        }
    }
}

void Enrollment::updateEnrollmentDisplay(Enrollment::IconEnrolStatus status) {
    cModule* ipc = this->getModuleByPath("^.^");
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

void Enrollment::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if ( !opp_strcmp(msg->getName(), MSG_ENRLCON) ) {
            APNIPairs* apnip = PreenrollConnects[simTime()];
            EV << "Preallocation at time " << simTime() << " has " << apnip->size() << " elements" << endl;
            while (!apnip->empty())
            {
                APNIPair pair = apnip->front();
                auto entry = StateTable->findEntryByDstAPN(pair.second.getApn());
                if (!entry) {
                    FlowAlloc->receiveMgmtAllocateRequest(pair.first, pair.second);
                }
                apnip->pop_front();
            }
        }
        else if ( !opp_strcmp(msg->getName(), MSG_ENRLREL) ) {
            APNIPairs* apnip = PreenrollReleases[simTime()];
            while (!apnip->empty())
            {
                APNIPair pair = apnip->front();
                auto entry = StateTable->findEntryByDstAPN(pair.second.getApn());
                if (entry && entry->getEnrollmentStatus() == EnrollmentStateTableEntry::ENROLL_ENROLLED ) {
                    //FIXME: Vesely->Jerabek: Here goes release part of Enrollment
                }
                apnip->pop_front();
            }
        }
        delete msg;
    }
}
