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
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init connection
    initConnections();

    //Timers
    startAt = simTime() + par("start");
    stopAt  = simTime() + par("stop");
    pingAt  = simTime() + par("ping");
    rate    = par("rate");

    //Destination for flow
    dstApName     = this->par("dstApName").str();
    dstApInstance = this->par("dstApInstance").str();
    dstAeName     = this->par("dstAeName").str();
    dstAeInstance = this->par("dstAeInstance").str();

    //Flow
    APNamingInfo src = APNamingInfo( APN(this->srcApName), this->srcApInstance,
                                                     this->srcAeName, this->srcAeInstance);
    APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                                     this->dstAeName, this->dstAeInstance);
    this->insert(Flow(src, dst));

    //Schedule AllocateRequest
    if (startAt > 0)
        prepareAllocateRequest();
    //Schedule Data transfer
    if (pingAt > 0)
        preparePing();
    //Schedule DeallocateRequest
    if (stopAt > 0)
        prepareDeallocateRequest();
}

void AEPing::handleSelfMessage(cMessage *msg) {
    if ( !strcmp(msg->getName(), "StartCommunication") )
        signalizeAllocateRequest(&flows.back());
    else if ( !strcmp(msg->getName(), "StopCommunication") )
        signalizeDeallocateRequest(&flows.back());
    else if ( strstr(msg->getName(), "PING") ) {
        //TODO: Vesely - Send M_READ
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
