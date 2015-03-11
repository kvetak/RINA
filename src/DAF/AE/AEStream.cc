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

#include "AEStream.h"

Define_Module(AEStream);

AEStream::AEStream(){
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

        Flow fl = Flow(src, dst);
        fl.setQosParameters(this->getQoSRequirements());

        //Insert it to the Flows ADT
        insertFlow(fl);

        sendAllocationRequest(&flows.back());
    }
    else if ( !strcmp(msg->getName(), TIM_STOP) ) {
        sendDeallocationRequest(&flows.back());
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
        data->setSize(size);

        //Send message
        sendData(&flows.back(), data);
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
