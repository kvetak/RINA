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

//Consts
const char* TIM_START           = "StartCommunication";
const char* TIM_STOP            = "StopCommunication";
const char* MSG_PING            = "PING-";
const char* PAR_START           = "startAt";
const char* PAR_STOP            = "stopAt";
const char* PAR_PING            = "pingAt";
const char* PAR_RATE            = "rate";
const char* PAR_DSTAPNAME       = "dstApName";
const char* PAR_DSTAPINSTANCE   = "dstApInstance";
const char* PAR_DSTAENAME       = "dstAeName";
const char* PAR_DSTAEINSTANCE   = "dstAeInstance";

AEPing::AEPing() {
}

AEPing::~AEPing() {

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

    //Destination for flow
    dstApName     = this->par(PAR_DSTAPNAME).stringValue();
    dstApInstance = this->par(PAR_DSTAPINSTANCE).stringValue();
    dstAeName     = this->par(PAR_DSTAENAME).stringValue();
    dstAeInstance = this->par(PAR_DSTAEINSTANCE).stringValue();


    //FIXME: Vesely - Move to StartCommunication processing
    //Flow
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                     this->dstAeName, this->dstAeInstance);

    Flow fl = Flow(src, dst);
    fl.setQosParameters(this->getQoSRequirements());
    //Insert it to the Flows ADT
    insertFlow(fl);

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
    WATCH_LIST(flows);
}

void AEPing::handleSelfMessage(cMessage *msg) {
    //EV << flows.back().info() << endl;
    if ( !strcmp(msg->getName(), "StartCommunication") ) {
        //signalizeAllocateRequest(&flows.back());
        //FIXME: Vesely - last flow in a list?!
        Irm->receiveAllocationRequest(&flows.back());
    }
    else if ( !strcmp(msg->getName(), "StopCommunication") )
        //signalizeDeallocateRequest(&flows.back());
        //Irm->receiveDeallocationRequest(&flows.back());
        EV << "StopCommunication";
    else if ( strstr(msg->getName(), "PING") ) {
        //Create PING messsage
        std::ostringstream ss;
        ss << "M_READ(" << msg->getName() << ")";
        CDAPMessage* ping = new CDAPMessage(ss.str().c_str());

        //Send message
        sendData(&flows.back(), ping);
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
