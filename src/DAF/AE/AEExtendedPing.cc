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

#include "AEExtendedPing.h"

Define_Module(AEExtendedPing);

//Consts
const char* TIM_START_E           = "StartCommunication";
const char* TIM_CONNECT_E         = "StartConnection";
const char* TIM_STOP_E            = "StopCommunication";
const char* MSG_PING_E            = "PING-";
const char* PAR_START_E           = "startAt";
const char* PAR_STOP_E            = "stopAt";
const char* PAR_CONNECT_E         = "connectAt";
const char* PAR_PING_E            = "pingAt";
const char* PAR_RATE_E            = "rate";
const char* PAR_SIZE_E            = "size";
const char* PAR_DSTAPNAME_E       = "dstApName";
const char* PAR_DSTAPINSTANCE_E   = "dstApInstance";
const char* PAR_DSTAENAME_E       = "dstAeName";
const char* PAR_DSTAEINSTANCE_E   = "dstAeInstance";
const char* PAR_AUTH_TYPE_E       = "authType";
const char* PAR_AUTH_NAME_E       = "authName";
const char* PAR_AUTH_OTHER_E      = "authOther";
const char* PAR_AUTH_PASS_E       = "authPassword";
const char* VAL_MODULEPATH_E      = "getFullPath()";
const char* VAL_CONNECTION_E      = "connect";
const char* VAL_RELEASE_E         = "release";


AEExtendedPing::AEExtendedPing() {
}

AEExtendedPing::~AEExtendedPing() {

}

void AEExtendedPing::prepareAllocateRequest() {
    //Schedule AllocateRequest
    cMessage* m1 = new cMessage(TIM_START_E);
    scheduleAt(startAt, m1);
}

void AEExtendedPing::preparePing() {
    //Schedule Data transfer
    for (int i = 0; i < rate && pingAt + i < stopAt; i++) {
        std::ostringstream ss;
        ss << MSG_PING_E << i;
        cMessage* m2 = new cMessage(ss.str().c_str());
        scheduleAt(pingAt + i, m2);
    }
}

void AEExtendedPing::prepareDeallocateRequest() {
    //Schedule DeallocateRequest
    cMessage* m3 = new cMessage(TIM_STOP_E);
    scheduleAt(stopAt, m3);
}

void AEExtendedPing::prepareConnectionRequest(){
    cMessage* m4 = new cMessage(TIM_CONNECT_E);
    scheduleAt(connectAt, m4);
}

void AEExtendedPing::initialize()
{
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    //Timers
    startAt = simTime() + par(PAR_START_E);
    stopAt  = simTime() + par(PAR_STOP_E);
    connectAt = simTime() + par(PAR_CONNECT_E);
    pingAt  = simTime() + par(PAR_PING_E);
    rate    = par(PAR_RATE_E);
    size    = par(PAR_SIZE_E);

    //Authentication for application
    authType = par(PAR_AUTH_TYPE_E);
    authName = this->par(PAR_AUTH_NAME_E).stringValue();
    authPassword = this->par(PAR_AUTH_PASS_E).stringValue();
    authOther = this->par(PAR_AUTH_OTHER_E).stringValue();

    //Destination for flow
    dstApName     = this->par(PAR_DSTAPNAME_E).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE_E).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME_E).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE_E).stringValue();

    //Schedule AllocateRequest
    if (startAt > 0)
        prepareAllocateRequest();
    //Schedule Data transfer
    if (pingAt > 0)
        preparePing();

    //Schedule CACEConnectionRequest
    if (connectAt > 0)
        prepareConnectionRequest();

    //Schedule DeallocateRequest
    if (stopAt > 0)
        prepareDeallocateRequest();

    myPath = this->getFullPath();

    //Watchers
    WATCH_LIST(flows);
}

void AEExtendedPing::handleSelfMessage(cMessage *msg) {
    //EV << flows.back().info() << endl;
    if ( !strcmp(msg->getName(), TIM_START_E) ) {
        //FIXME: Vesely - last flow in a list?!

        //Flow
        APNamingInfo src = this->getApni();
        APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                         this->dstAeName, this->dstAeInstance);

        Flow fl = Flow(src, dst);
        fl.setQosParameters(this->getQoSRequirements());

        //Insert it to the Flows ADT
        insertFlow(fl);

        sendAllocationRequest(&flows.back());
    }
    else if ( !strcmp(msg->getName(), TIM_CONNECT_E)){
        //Create MConnect message
        CDAP_M_Connect* connect = new CDAP_M_Connect(VAL_CONNECTION_E);
        authValue_t aValue;
        aValue.authName = authName;
        aValue.authPassword = authPassword;
        aValue.authOther = authOther;

        auth_t auth;
        auth.authType = authType;
        auth.authValue = aValue;

        connect->setAuth(auth);
        connect->setAbsSyntax(GPB);
        connect->setOpCode(M_CONNECT);

        //Send message
        sendData(&flows.back(), connect);
    }
    else if ( !strcmp(msg->getName(), TIM_STOP_E) ) {
        CDAP_M_Release* releaseRequest = new CDAP_M_Release(VAL_RELEASE_E);
        releaseRequest->setInvokeID(0);

        sendData(&flows.back(), releaseRequest);

    }
    else if ( strstr(msg->getName(), MSG_PING_E) ) {
        //Create PING messsage
        CDAP_M_Read* ping = new CDAP_M_Read(VAL_MODULEPATH_E);
        object_t obj;
        obj.objectName = VAL_MODULEPATH_E;
        obj.objectClass = "string";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)(&myPath);
        ping->setObject(obj);
        ping->setSize(size);

        //Send message
        sendData(&flows.back(), ping);
    }
    else
        EV << this->getFullPath() << " received unknown self-message " << msg->getName();
    delete(msg);
}

void AEExtendedPing::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() )
            this->handleSelfMessage(msg);
}

void AEExtendedPing::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);

    EV << "Received M_Read";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    if ( strstr(object.objectName.c_str(), VAL_MODULEPATH_E) ) {
        std::string* source = (std::string*)(object.objectVal);
        std::ostringstream os;
        os << "Ping requested by " <<  *source << endl;
        bubble(os.str().c_str());
        EV << os.str().c_str();

        //Create PING response
        CDAP_M_Read_R* pong = new CDAP_M_Read_R(VAL_MODULEPATH_E);
        object_t obj;
        obj.objectName = VAL_MODULEPATH_E;
        obj.objectClass = "string";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)(&myPath);
        pong->setObject(obj);

        sendData(&flows.back(), pong);
    }
}

void AEExtendedPing::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);

    EV << "Received M_Read_R";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    if ( strstr(object.objectName.c_str(), VAL_MODULEPATH_E) ) {
        std::string* source = (std::string*)(object.objectVal);
        std::ostringstream os;
        os << "Ping replied by " <<  *source << endl;
        bubble(os.str().c_str());
        EV << os.str().c_str();
    }
}

