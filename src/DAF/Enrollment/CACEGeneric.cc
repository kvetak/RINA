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

#include "DAF/Enrollment/CACEGeneric.h"

CACEGeneric::CACEGeneric() {

}

CACEGeneric::~CACEGeneric() {
}

CACEGeneric::CACEGeneric(AE *outerClass) {
    this->outerClass = outerClass;
    this->StateTable = check_and_cast<DAFEnrollmentStateTable*>(this->outerClass->getModuleByPath("^.^.^.enrollment.enrollmentStateTable"));
}

void CACEGeneric::authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg) {
    //Enter_Method("authenticate()");

    //check and validate expected auth type
    if (msg->getAuth().authType == this->outerClass->authType) {
        //none auth option
        if (msg->getAuth().authType == AUTH_NONE) {
            processConResPosi(entry, msg);
            return;

        }
        //passwd auth option
        else if (msg->getAuth().authType == AUTH_PASSWD) {
            //correct passwd
            if (!strcmp(msg->getAuth().authValue.authPassword.c_str(), this->outerClass->authPassword.c_str())) {
                processConResPosi(entry, msg);
                return;
            }
        }
        //TODO: support for other options
    }

    //not valid auth send negative response
    processConResNega(entry, msg);
}

void CACEGeneric::startCACE(Flow* flow) {
    //Enter_Method("startCACE()");

    DAFEnrollmentStateTableEntry entryr = DAFEnrollmentStateTableEntry(flow->getSrcApni(),flow->getDstApni(), DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);
    StateTable->insert(entryr);


    auto entry = StateTable->findEntryByDstAPNI(flow->getDstApni());

    CDAP_M_Connect* msg = new CDAP_M_Connect(DAF_MSG_CONREQ);

    authValue_t aValue;
    aValue.authName = this->outerClass->authName;
    aValue.authPassword = this->outerClass->authPassword;
    aValue.authOther = this->outerClass->authOther;

    auth_t auth;
    auth.authType = this->outerClass->authType;
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

    msg->setSrcAddr(Address(entry->getLocal().getApn()));
    msg->setDstAddr(Address(entry->getRemote().getApn()));

    //send data to ribd to send
    outerClass->signalizeSendData(msg);
}

void CACEGeneric::insertStateTableEntry(Flow* flow) {
    //Enter_Method("insertStateTableEntry()");
    //insert only first flow created (management flow)
    if(StateTable->findEntryByDstAPNI(flow->getDstApni()) != NULL) {
        return;
    }
    StateTable->insert(DAFEnrollmentStateTableEntry(flow->getSrcApni(), flow->getDstApni(), DAFEnrollmentStateTableEntry::CON_CONNECTPENDING));
}

void CACEGeneric::receivePositiveConnectResponse(CDAPMessage* msg) {
    //Enter_Method("receivePositiveConnectResponse()");

    //signalizeEnrolled();

    /* this is commented only for testing ---> refactoring of adress is need to be done*/
    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPNI(APNamingInfo(
            cmsg->getSrc().getApn(),
            cmsg->getSrc().getApinstance(),
            cmsg->getSrc().getAename(),
            cmsg->getSrc().getAeinstance()));

    //check appropriate state
    if (entry->getCACEConStatus() != DAFEnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_ESTABLISHED);

    outerClass->CACEFinished();
}

void CACEGeneric::receiveNegativeConnectResponse(CDAPMessage* msg) {
    //Enter_Method("receiveNegativeConnectResponse()");

    CDAP_M_Connect_R* cmsg = check_and_cast<CDAP_M_Connect_R*>(msg);
    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPNI(APNamingInfo(
            cmsg->getSrc().getApn(),
            cmsg->getSrc().getApinstance(),
            cmsg->getSrc().getAename(),
            cmsg->getSrc().getAeinstance()));

    //check appropriate state
    if (entry->getCACEConStatus() != DAFEnrollmentStateTableEntry::CON_AUTHENTICATING) {
        //TODO: send M_Release and invoke deallocate
        return;
    }

    if (this->outerClass->maxConRetries <= entry->getCurrentConnectRetries()) {
        entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_NIL);
        //TODO: send release and deallocate
        return;
    }


    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);
    entry->increaseCurrentConnectRetries();
    //create and send new connect retry
    processNewConReq(entry);
}

void CACEGeneric::receiveConnectRequest(CDAPMessage* msg) {
    //Enter_Method("receiveConnectRequest()");

    CDAP_M_Connect* cmsg = check_and_cast<CDAP_M_Connect*>(msg);

    auto ent = DAFEnrollmentStateTableEntry(
             cmsg->getDst(), cmsg->getSrc(), DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);
    StateTable->insert(ent);

    DAFEnrollmentStateTableEntry* entry = StateTable->findEntryByDstAPNI(APNamingInfo(
            cmsg->getSrc().getApn(),
            cmsg->getSrc().getApinstance(),
            cmsg->getSrc().getAename(),
            cmsg->getSrc().getAeinstance()));

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

void CACEGeneric::processConResPosi(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
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
    outerClass->signalizeSendData(msg);

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_ESTABLISHED);
    //entry->setDAFEnrollmentStatus(DAFEnrollmentStateTableEntry::ENROLL_WAIT_START_ENROLLMENT);
}

void CACEGeneric::processConResNega(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) {
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
    outerClass->signalizeSendData(msg);

    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_CONNECTPENDING);

    //increase number of connects
    entry->increaseCurrentConnectRetries();
}

void CACEGeneric::processNewConReq(DAFEnrollmentStateTableEntry* entry) {
    //Enter_Method("processNewConReq()");

    //TODO: probably change values, this is retry

    CDAP_M_Connect* msg = new CDAP_M_Connect(DAF_MSG_CONREQRETRY);

    authValue_t aValue;
    aValue.authName = this->outerClass->authName;
    aValue.authPassword = this->outerClass->authPassword;
    aValue.authOther = this->outerClass->authOther;

    auth_t auth;
    auth.authType = this->outerClass->authType;
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
    outerClass->signalizeSendData(msg);

    //change state to auth after send retry
    entry->setCACEConStatus(DAFEnrollmentStateTableEntry::CON_AUTHENTICATING);
}
