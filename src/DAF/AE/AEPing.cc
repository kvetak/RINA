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

AEPing::AEPing() {
}

AEPing::~AEPing() {

}

void AEPing::prepareAllocateRequest() {
    //Schedule AllocateRequest
    cMessage* m1 = new cMessage("StartCommunication");
    scheduleAt(startAt, m1);
}

void AEPing::preparePing() {
    //Schedule Data transfer
    for (int i = 0; i < rate && pingAt + i < stopAt; i++) {
        std::stringstream ss;
        ss << "PING-" << i;
        cMessage* m2 = new cMessage(ss.str().c_str());
        scheduleAt(pingAt + i, m2);
    }
}

void AEPing::prepareDeallocateRequest() {
    //Schedule DeallocateRequest
    cMessage* m3 = new cMessage("StopCommunication");
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

    //Timers
    startAt = simTime() + par("start");
    stopAt  = simTime() + par("stop");
    pingAt  = simTime() + par("ping");
    rate    = par("rate");

    //Destination for flow
    dstApName     = this->par("dstApName").stringValue();
    dstApInstance = this->par("dstApInstance").stringValue();
    dstAeName     = this->par("dstAeName").stringValue();
    dstAeInstance = this->par("dstAeInstance").stringValue();

    //Flow
    APNamingInfo src = this->getApni();
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                     this->dstAeName, this->dstAeInstance);
    Flow fl = Flow(src, dst);

    //Insert it to the Flows ADT
    insert(fl);

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
        //TODO: Vesely - Send M_READ
        std::stringstream ss;
        ss << "M_READ(" << msg->getName() << ")";
        cMessage* ping = new cMessage(ss.str().c_str());
        send(ping , "dataIo$o", 0);
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
