//
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

#include "DAFRIBd.h"

const char* PAR_USEDAFENROLLNOTIF      = "useEnrollmentNotifier";

Define_Module(DAFRIBd);

void DAFRIBd::initialize() {

    useEnrollmentNotifier = false;

    //Init signals and listeners
    initSignalsAndListeners();

    //Pointers
    initPointers();
}

void DAFRIBd::initPointers() {
    EnrollNotif = getRINAModule<EnrollmentNotifierBase*>(this, 1, {"enrollmentNotifier"}, false);
    if (EnrollNotif) {
        useEnrollmentNotifier = true;
        this->par(PAR_USEDAFENROLLNOTIF) = true;
    }
}

void DAFRIBd::handleMessage(cMessage *msg) {

}

void DAFRIBd::receiveData(CDAPMessage* msg) {
    Enter_Method("receiveData()");

    //EnrollmentNotifier processing
    if (useEnrollmentNotifier && EnrollNotif->isMessageProcessable(msg)) {
        EnrollNotif->receiveMessage(msg);
    }
    //delete msg;
}

void DAFRIBd::initSignalsAndListeners() {
    cModule* catcher1 = this->getParentModule();

    //Signals that this module is emitting
    sigDAFRIBDSendData      = registerSignal(SIG_RIBD_DataSend);


    lisDAFRIBDRcvData = new LisDAFRIBDRcvData(this);
    catcher1->subscribe(SIG_CDAP_DateReceive, lisDAFRIBDRcvData);

}

void DAFRIBd::signalizeSendData(CDAPMessage* msg) {
    Enter_Method("signalizeSendData()");

    //Check dstAddress
    if (msg->getDstAddr() == Address::UNSPECIFIED_ADDRESS) {
        EV << "Destination address cannot be UNSPECIFIED!" << endl;
        return;
    }

    msg->setBitLength(msg->getBitLength() + msg->getHeaderBitLength());
    //Pass message to CDAP
    EV << "Emits SendData signal for message " << msg->getName() << endl;
    emit(sigDAFRIBDSendData, msg);
}


