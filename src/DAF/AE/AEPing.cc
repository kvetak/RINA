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

#include "AEPing.h"

Define_Module(AEPing);

AEPing::AEPing() : AE() {
  //Consts
  TIM_START           = "StartCommunication";
  TIM_STOP            = "StopCommunication";
  MSG_PING            = "PING-";
  PAR_START           = "startAt";
  PAR_STOP            = "stopAt";
  PAR_PING            = "pingAt";
  PAR_RATE            = "rate";
  PAR_SIZE            = "size";
  PAR_DSTAPNAME       = "dstApName";
  PAR_DSTAPINSTANCE   = "dstApInstance";
  PAR_DSTAENAME       = "dstAeName";
  PAR_DSTAEINSTANCE   = "dstAeInstance";
  VAL_MODULEPATH      = "getFullPath()";
}

AEPing::~AEPing() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
}

void AEPing::prepareAllocateRequest() {
    //Schedule AllocateRequest
    cMessage* m1 = new cMessage(TIM_START);
    scheduleAt(startAt, m1);
}

void AEPing::preparePing() {
    //Schedule Data transfer
    for (int i = 0; i < rate && pingAt + i < stopAt; i++) {
        std::ostringstream ss;
        ss << MSG_PING << i;
        cMessage* m2 = new cMessage(ss.str().c_str());
        scheduleAt(pingAt + i, m2);
    }
}

void AEPing::prepareDeallocateRequest() {
    //Schedule DeallocateRequest
    cMessage* m3 = new cMessage(TIM_STOP);
    scheduleAt(stopAt, m3);
}

void AEPing::initialize()
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
    startAt = simTime() + par(PAR_START);
    stopAt  = simTime() + par(PAR_STOP);
    pingAt  = simTime() + par(PAR_PING);
    rate    = par(PAR_RATE);
    size    = par(PAR_SIZE);

    //Destination for flow
    dstApName     = this->par(PAR_DSTAPNAME).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE).stringValue();

    //Schedule AllocateRequest
    if (startAt > 0)
        prepareAllocateRequest();
    //Schedule Data transfer
    if (pingAt > 0)
        preparePing();
    //Schedule DeallocateRequest
    if (stopAt > 0)
        prepareDeallocateRequest();

    myPath = this->getFullPath();

    //Watchers
    WATCH(FlowObject);
    WATCH(connectionState);
}

void AEPing::handleSelfMessage(cMessage *msg) {
    //EV << flows.back().info() << endl;
    if ( !strcmp(msg->getName(), TIM_START) ) {
        //Flow
        APNamingInfo src = this->getApni();
        APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                         this->dstAeName, this->dstAeInstance);

        FlowObject = new Flow(src, dst);
        FlowObject->setQosRequirements(this->getQoSRequirements());

        //Insert it to the Flows ADT
        insertFlow();

        sendAllocationRequest(FlowObject);
    }
    else if ( !strcmp(msg->getName(), TIM_STOP) ) {
        sendDeallocationRequest(FlowObject);
    }
    else if ( strstr(msg->getName(), MSG_PING) ) {
        //Create PING messsage
        CDAP_M_Read* ping = new CDAP_M_Read(VAL_MODULEPATH);
        object_t obj;
        obj.objectName = VAL_MODULEPATH;
        obj.objectClass = "string";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)(&myPath);
        ping->setObject(obj);
        ping->setByteLength(size);

        //Send message
        sendData(FlowObject, ping);
    }
    else
        EV << this->getFullPath() << " received unknown self-message " << msg->getName();
    delete(msg);
}

void AEPing::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() )
            this->handleSelfMessage(msg);
}

void AEPing::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);

    EV << "Received M_Read";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    if ( strstr(object.objectName.c_str(), VAL_MODULEPATH) ) {
        std::string* source = (std::string*)(object.objectVal);
        std::ostringstream os;
        os << "Ping requested by " <<  *source << endl;
        bubble(os.str().c_str());
        EV << os.str().c_str();

        //Create PING response
        CDAP_M_Read_R* pong = new CDAP_M_Read_R(VAL_MODULEPATH);
        object_t obj;
        obj.objectName = VAL_MODULEPATH;
        obj.objectClass = "string";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)(&myPath);
        pong->setObject(obj);

        sendData(FlowObject, pong);
    }
}

void AEPing::processMReadR(CDAPMessage* msg) {
    CDAP_M_Read_R* msg1 = check_and_cast<CDAP_M_Read_R*>(msg);

    EV << "Received M_Read_R";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "'" << endl;

    if ( strstr(object.objectName.c_str(), VAL_MODULEPATH) ) {
        std::string* source = (std::string*)(object.objectVal);
        std::ostringstream os;
        os << "Ping replied by " <<  *source << endl;
        bubble(os.str().c_str());
        EV << os.str().c_str();
    }
}
