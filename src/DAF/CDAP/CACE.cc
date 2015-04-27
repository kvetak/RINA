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

#include "CACE.h"

Define_Module(CACE);

void CACE::initialize()
{
    initPointers();
    initSignalsAndListeners();
    potentialConTimer = 0;
    currentConRetries = 0;
    maxConRetries = 1;
}

void CACE::handleMessage(cMessage *msg)
{
    //check message and process it to CACEStateMachine
    if (dynamic_cast<CDAPMessage*>(msg)) {
        CDAPMessage* cmsg = check_and_cast<CDAPMessage*>(msg);
        signalizeDataReceive(cmsg);
    }
}

void CACE::initPointers(){
    //TODO potentially rib daemon for setting status
    ae = dynamic_cast<AE*>(this->getParentModule()->getParentModule()->getSubmodule(MOD_IAE));
}

void CACE::initSignalsAndListeners(){
    cModule* catcher = this->getParentModule()->getParentModule();
    cModule* catcher2 = this->getParentModule()->getSubmodule(MOD_CDAPAUTH);

    //Signals emitted by this module
    sigCACEConResPosi = registerSignal(SIG_CACE_ConnectionResponsePositive);
    sigCACEConResNega = registerSignal(SIG_CACE_ConnectionResponseNegative);
    sigCACERelRes = registerSignal(SIG_CACE_ReleaseResponse);
    sigCACEAuthReq = registerSignal(SIG_CACE_AuthenticationRequest);
    sigCACEReceiveData = registerSignal(SIG_CACE_DataReceive);

    //Signals that this module is processing
    //connection request from AE
    lisCACEConReq = new LisCACEConReq(this);
    catcher->subscribe(SIG_AE_ConnectionRequest, lisCACEConReq);

    //release request from AE
    lisCACERelReq = new LisCACERelReq(this);
    catcher->subscribe(SIG_AE_ReleaseRequest, lisCACERelReq);

    //authentication validation response from Auth
    lisCACEAuthRes = new LisCACEAuthRes(this);
    catcher2->subscribe(SIG_Auth_AuthenticationResponse, lisCACEAuthRes);

    //send data from AE/Enrollment
    lisCACESendData = new LisCACESendData(this);
    catcher->subscribe(SIG_RIBD_CACESend, lisCACESendData);

}

void CACE::changeConnectionState(CDAPConnectionState connectionState){
    ae->changeConStatus(connectionState);
}

void CACE::treatAuthRes(CDAPMessage *cmsg) {
    CDAP_M_Connect_R* cmsgCR = dynamic_cast<CDAP_M_Connect_R*>(cmsg);

    take(cmsg);

    if (cmsgCR->getResult().resultValue == R_SUCCESS) {
        processMConnectResPosi(cmsgCR);
    }
    else {
        processMConnectResNega(cmsgCR);
    }
}

void CACE::CACEStateMachine(CDAPMessage *cmsg){
    //M_Connect
    if (dynamic_cast<CDAP_M_Connect*>(cmsg)) {
        if (ae->getConStatus() == CONNECTION_PENDING) {
            //TODO: potentialConnectionTimer
            CDAP_M_Connect* msgC = check_and_cast<CDAP_M_Connect*>(cmsg);

            //validate M_Connect message
            if (msgC->getAbsSyntax() == GPB &&
                    msgC->getOpCode() == M_CONNECT) {
                //check connection retries
                if (currentConRetries <= maxConRetries) {
                    changeConnectionState(AUTHENTICATING);
                    //emit signal to auth module
                    signalizeAuthenticationRequest(msgC);
                }
                //unautorized number of retries
                else {
                    //TODO: probably immediate deallocation
                    processMRelease();
                }
            }
            //not valid M_Connect message
            else {
                //TODO: probably immediate deallocation
                processMRelease();
            }
        }
        //message came in bad connection state
        else {
            //TODO: probably immediate deallocation
            processMRelease();
        }
    }
    //M_Connect_R
    else if (dynamic_cast<CDAP_M_Connect_R*>(cmsg)){
        if (ae->getConStatus() == AUTHENTICATING) {
            CDAP_M_Connect_R* msgCR = check_and_cast<CDAP_M_Connect_R*>(cmsg);
            if (msgCR->getResult().resultValue == 0) {//SUCCESS
                signalizeConnResponsePositive(cmsg);
            }
            else {
                signalizeConnResponseNegative(cmsg);
            }
        }
        else {
            //TODO: probably immediate deallocation
            processMRelease();
        }
    }
    //M_Release
    else if (dynamic_cast<CDAP_M_Release*>(cmsg)){
        if (!dynamic_cast<CDAP_M_Release*>(cmsg)->getInvokeID()){
            changeConnectionState(NIL);
            //deallocate connection
            ae->sendDeallocationRequest(ae->getFlowObject());
        }
        else {
            processMReleaseR(cmsg);
            changeConnectionState(NIL);
        }
    }
    //M_Release_R
    else if (dynamic_cast<CDAP_M_Release_R*>(cmsg) != NULL){
        signalizeReleaseResponse(cmsg);
    }
    else {
        //TODO: probably immediate deallocation
        processMRelease();
    }
}

void CACE::processMConnect(CDAPMessage *cmsg){
    Enter_Method("processMConnect()");
    //set CDAPConnection state
    changeConnectionState(AUTHENTICATING);

    take(check_and_cast<cOwnedObject*>(cmsg) );
    //Send message
    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CACE::processMConnectResPosi(CDAPMessage *cmsg){
    Enter_Method("processMConnectResPosi()");

    take(cmsg);
    //set CDAPConnection state
    changeConnectionState(ESTABLISHED);

    currentConRetries = 0;

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CACE::processMConnectResNega(CDAPMessage *cmsg){
    Enter_Method("processMConnectResNega()");

    changeConnectionState(CONNECTION_PENDING);
    //increment connection retries
    currentConRetries++;

    take(cmsg);

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CACE::processMRelease(){
    Enter_Method("processMRelease()");

    //set CDAPConnection State
    changeConnectionState(NIL);

    CDAP_M_Release* msg = new CDAP_M_Release("release");
    msg->setInvokeID(0);

    //set message type
    msg->setOpCode(M_RELEASE);

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(msg, out);
}

void CACE::processMRelease(CDAPMessage *cmsg){
    Enter_Method("processMRelease()");

    take(check_and_cast<cOwnedObject*>(cmsg));

    CDAP_M_Release* msg = dynamic_cast<CDAP_M_Release*>(cmsg);

    if (msg->getInvokeID()) {
        //setCDAPConnection state
        changeConnectionState(RELEASING);
    }
    else {
        //set CDAPConnection state
        changeConnectionState(NIL);
    }

    //set message type
    msg->setOpCode(M_RELEASE);
    //Send message
    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);

}

void CACE::processMReleaseR(CDAPMessage *cmsg){
    Enter_Method("processMRelease()");
    //TODO:potentialy "after 2MPL+A invokes Deallocate"
    CDAP_M_Release_R* releaseResponse = new CDAP_M_Release_R("releaseResponse");
    result_t result;
    result.resultReason = "success";
    result.resultValue = 0;

    releaseResponse->setResult(result);

    //set message type
    releaseResponse->setOpCode(M_RELEASE_R);

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(releaseResponse, out);
}

void CACE::sendMessage(CDAPMessage *cmsg){

}

void CACE::sendData(CDAPMessage *cmsg){
    Enter_Method("CACE SendData()");
    take(check_and_cast<cOwnedObject*>(cmsg) );

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CACE::signalizeDataReceive(CDAPMessage* cmsg) {
    emit(sigCACEReceiveData, cmsg);
}

void CACE::signalizeConnResponseNegative(CDAPMessage* cmsg){
    emit(sigCACEConResNega, cmsg);
}

void CACE::signalizeConnResponsePositive(CDAPMessage* cmsg){
    emit(sigCACEConResPosi, cmsg);
}

void CACE::signalizeReleaseResponse(CDAPMessage* cmsg){
    emit(sigCACERelRes, cmsg);
}

void CACE::signalizeAuthenticationRequest(CDAPMessage* cmsg){
    emit(sigCACEAuthReq, cmsg);
}


