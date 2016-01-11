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

#include "AEStream.h"

Define_Module(AEStream);

AEStream::AEStream() : AE() {
  //Consts
      TIM_START           = "StartCommunication";
      TIM_STOP            = "StopCommunication";
      MSG_STDATA          = "DATA-";
      PAR_START           = "startAt";
      PAR_STOP            = "stopAt";
      PAR_BEGIN           = "beginStreamAt";
      PAR_END             = "endStreamAt";
      PAR_INTERVAL        = "interval";
      PAR_SIZE            = "size";
      PAR_DSTAPNAME       = "dstApName";
      PAR_DSTAPINSTANCE   = "dstApInstance";
      PAR_DSTAENAME       = "dstAeName";
      PAR_DSTAEINSTANCE   = "dstAeInstance";
}


void AEStream::initialize()
{
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    //Destination for flow
    dstApName     = this->par(PAR_DSTAPNAME).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE).stringValue();

    if (!dstAeName.compare("AeErr")) {
        EV << "Destination AEName is set to default which is AeErr. AeErr is for special testing purposes. Are you sure that it is right?" << endl;
    }

    //Timers
    startAt         = simTime() + par(PAR_START);
    stopAt          = simTime() + par(PAR_STOP);
    beginStreamAt   = simTime() + par(PAR_BEGIN);
    endStreamAt     = simTime() + par(PAR_END);
    interval        = par(PAR_INTERVAL).doubleValue();
    size            = par(PAR_SIZE);

    //Schedule AllocateRequest
    if (startAt > 0)
        prepareAllocateRequest();
    //Schedule Data transfer
    if (beginStreamAt > 0 && beginStreamAt < endStreamAt)
        prepareStreamData();
    //Schedule DeallocateRequest
    if (stopAt > 0)
        prepareDeallocateRequest();


}

void AEStream::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() )
        this->handleSelfMessage(msg);
}

void AEStream::handleSelfMessage(cMessage* msg) {
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
    else if ( strstr(msg->getName(), MSG_STDATA) ) {
        //Create data stream chunk messsage
        CDAP_M_Read* data = new CDAP_M_Read(msg->getName());
        object_t obj;
        obj.objectName = msg->getName();
        obj.objectClass = "string";
        obj.objectInstance = -1;
        obj.objectVal = (cObject*)("0123456789abcdef");
        data->setObject(obj);
        data->setByteLength(size);

        //Send message
        sendData(FlowObject, data);
    }
    else
        EV << this->getFullPath() << " received unknown self-message " << msg->getName();
    delete(msg);
}

void AEStream::prepareAllocateRequest() {
    //Schedule AllocateRequest
    cMessage* m1 = new cMessage(TIM_START);
    scheduleAt(startAt, m1);
}

void AEStream::prepareStreamData() {
    //Schedule stream data chunk
    int j = 0;
    for (simtime_t i = beginStreamAt; i < endStreamAt; i += interval) {
        std::ostringstream ss;
        ss << MSG_STDATA << j++;
        cMessage* m2 = new cMessage(ss.str().c_str());
        scheduleAt(i, m2);
    }
}

void AEStream::prepareDeallocateRequest() {
    //Schedule DeallocateRequest
    cMessage* m3 = new cMessage(TIM_STOP);
    scheduleAt(stopAt, m3);
}

void AEStream::processMRead(CDAPMessage* msg) {
    CDAP_M_Read* msg1 = check_and_cast<CDAP_M_Read*>(msg);

    EV << "Received data M_DATA";
    object_t object = msg1->getObject();
    EV << " with object '" << object.objectClass << "' and value '" << object.objectVal << "'" << endl;

}
