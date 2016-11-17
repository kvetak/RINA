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

#include "AEConstantServer.h"

Define_Module(AEConstantServer);



AEConstantServer::AEConstantServer() : AE() {}

AEConstantServer::~AEConstantServer() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
}


void AEConstantServer::initialize()
{
    //Init pointers
    initPointers();
    //Source info
    initNamingInfo();
    //Setup signals
    initSignalsAndListeners();
    //Init QoSRequirements
    initQoSRequiremets();

    countStart = par("countStart").longValue();
    countEnd = par("countEnd").longValue();
    stopAt = par("stopAt").longValue();

    rate = par("rate").doubleValue();
    wperbit = 1.0/(rate*1024);
    wvar = par("waitvar").doubleValue();

    size = par("size").longValue();
    sizevar = par("sizevar").longValue();

    signal_snd = registerSignal("AEConstantPing-SND");
    signal_rcv = registerSignal("AEConstantPong-RCV");

    count=0;
}

void AEConstantServer::finish() {
    if(count < 10) {
        std::cout << "WTF!! count >> "<<count <<endl;
    }
    /*
        if(FlowObject != NULL) {
            EV << this->getFullPath() << " / ";
            EV << "With QoS " << FlowObject->getConId().getQoSId() <<endl;
        }
    */
}

void AEConstantServer::handleSelfMessage(cMessage *msg) {
    if(count < stopAt) {
        PingMsg* ping = new PingMsg(count >= countStart && count < countEnd);

        int msgSize = size + omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), -sizevar,sizevar);
        ping->setByteLength(msgSize);

        if(ping->counted) {
            emit(signal_snd, new SignalMsg(FlowObject->getConId().getQoSId()));
        }

        //Send message
        sendData(FlowObject, ping);
        count++;
        double wtime = (msgSize+40)*wperbit*omnetpp::uniform(omnetpp::getEnvir()->getRNG(0), 1-wvar, 1+wvar);
        scheduleAt(simTime() + wtime, msg);

    } else if(count == stopAt) {
        scheduleAt(simTime() + 1, msg);
    } else {
        delete msg;
    }
}

void AEConstantServer::handleMessage(cMessage *msg)
{
    if ( msg->isSelfMessage() ) {
        this->handleSelfMessage(msg);
    } else if(PongMsg* m = dynamic_cast<PongMsg*>(msg)) {
        if(m->counted) {
            emit(signal_rcv, new SignalMsg(FlowObject->getConId().getQoSId(), simTime() - m->pongAt, simTime() - m->pingAt));
        }
    } else if(dynamic_cast<StartMsg*>(msg)) {
        scheduleAt(simTime(), new cMessage("Send"));
    } else {
        error ("Unknown msg received");
    }
}

void AEConstantServer::processMRead(CDAPMessage* msg) {
    handleMessage(msg);
}

void AEConstantServer::processMReadR(CDAPMessage* msg) {
    handleMessage(msg);
}
