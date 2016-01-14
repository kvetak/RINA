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

void AEPing::initPing() {
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

    if (!dstAeName.compare("AeErr")) {
        EV << "AEName is set to default which is AeErr. AeErr is for special testing purposes. Are you sure that it is right?" << endl;
    }

    //Schedule AllocateRequest
    if (startAt > 0)
        prepareAllocateRequest();
    //Schedule Data transfer
    if (pingAt > 0)
        preparePing();
    //Schedule DeallocateRequest
    if (stopAt > 0)
        prepareDeallocateRequest();

    //Watchers
    WATCH(FlowObject);
    WATCH(connectionState);

}

void AEPing::initialize()
{
    initPing();

    myPath = this->getFullPath();
}

void AEPing::handleSelfMessage(cMessage *msg) {
    //EV << flows.back().info() << endl;
    if ( !strcmp(msg->getName(), TIM_START) ) {
        onStart();
        afterOnStart();
    }
    else if ( !strcmp(msg->getName(), TIM_STOP) ) {
        onStop();
    }
    else if ( strstr(msg->getName(), MSG_PING) ) {
        onPing();
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

void AEPing::onStart() {
    AEPing::connect();
}

void AEPing::connect() {
    APNIPair* apnip = new APNIPair(
        APNamingInfo(APN(srcApName),
                    srcApInstance,
                    srcAeName,
                    srcAeInstance),
        APNamingInfo(APN(dstApName),
                    dstApInstance,
                    dstAeName,
                    dstAeInstance));

    emit(sigAEEnrolled, apnip);
}

void AEPing::afterOnStart() {
    Enter_Method("afterConnect()");

    //Prepare flow's source and destination
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                     this->dstAeName, this->dstAeInstance);

    //Create a flow
    FlowObject = new Flow(src, dst);
    FlowObject->setQosRequirements(this->getQoSRequirements());

    //Notify IRM about a new flow
    insertFlow();

    //Call flow allocation request
    sendAllocationRequest(FlowObject);
}

void AEPing::onPing() {
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

void AEPing::onStop() {
    //Call flow deallocation submit
    sendDeallocationRequest(FlowObject);
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
