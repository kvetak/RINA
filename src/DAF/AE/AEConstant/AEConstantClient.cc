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

#include "AEConstantClient.h"

Define_Module(AEConstantClient);

AEConstantClient::AEConstantClient() : AE() {}

AEConstantClient::~AEConstantClient() {
    connectionState = NIL;
    FlowObject = NULL;
    Irm = NULL;
    Cdap = NULL;
}


void AEConstantClient::initialize()
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
    dstApName     = this->par("dstApName").stringValue();
    dstApInstance = this->par("dstApInstance").stringValue();
    dstAeName     = this->par("dstAeName").stringValue();
    dstAeInstance = this->par("dstAeInstance").stringValue();

    signal = registerSignal("AEConstantPing-RCV");

    //Timers
    simtime_t startAt = simTime() + par("startAt");
    if(startAt<0) { startAt = 0; }
    scheduleAt(startAt, new cMessage("Start"));
}

void AEConstantClient::finish() {

    if(FlowObject == NULL || FlowObject->getConId().getDstCepId() == VAL_UNDEF_CEPID) {
        EV << "Flow not initialized :" << endl;

        APNamingInfo src = this->getApni();
        APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                         this->dstAeName, this->dstAeInstance);
        EV << "\t" << src << " -> " << dst << endl;
    }
}

void AEConstantClient::handleSelfMessage(cMessage *msg) {
    if(StartMsg* m = dynamic_cast<StartMsg*>(msg)) {
        if(FlowObject->getConId().getDstCepId() != VAL_UNDEF_CEPID) {
            sendData(FlowObject, m);
        } else {
            scheduleAt(simTime()+1, m);
        }
    } else {
           APNamingInfo src = this->getApni();
           APNamingInfo dst = APNamingInfo( APN(this->dstApName), this->dstApInstance,
                                            this->dstAeName, this->dstAeInstance);

           FlowObject = new Flow(src, dst);
           FlowObject->setQosRequirements(this->getQoSRequirements());

           insertFlow();

           sendAllocationRequest(FlowObject);

           scheduleAt(simTime()+1, new StartMsg());
           delete msg;
       }
}

void AEConstantClient::handleMessage(cMessage *msg) {
    if ( msg->isSelfMessage() ) {
        this->handleSelfMessage(msg);
    } else if(PingMsg* m = dynamic_cast<PingMsg*>(msg)) {
        if(m->counted) {
            emit(signal, new SignalMsg(FlowObject->getConId().getQoSId(), simTime() - m->pingAt));
        }

        PongMsg* r = new PongMsg(m->pingAt, m->counted);
        r->setByteLength(m->getByteLength());
        sendData(FlowObject, r);
    } else {
        std::cout << "Unknown msg received" << endl;
 //       error ("Unknown msg received");
    }
}

void AEConstantClient::processMRead(CDAPMessage* msg) {
    handleMessage(msg);
}

void AEConstantClient::processMReadR(CDAPMessage* msg) {
    handleMessage(msg);
}
