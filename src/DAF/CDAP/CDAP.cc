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

#include "DAF/CDAP/CDAP.h"

Define_Module(CDAP);

void CDAP::initialize()
{
    initSignalsAndListeners();
}

void CDAP::handleMessage(cMessage* msg)
{
    //Pass CDAP message to AE or RIBd or Enrollment
    if (dynamic_cast<CDAPMessage*>(msg)) {
        CDAPMessage* cmsg = check_and_cast<CDAPMessage*>(msg);
        signalizeReceiveData(cmsg);
        //delete cmsg;
    }
    //FIXME: Vesely - Proper disposing of object
    //cancelAndDelete(msg);
}

void CDAP::initSignalsAndListeners() {
    cModule* catcher = this->getModuleByPath("^.^");
    //cModule* catcher2 = this->getModuleByPath("^.^.^")->getSubmodule(MOD_ENROLLMENTMODULE)->getSubmodule(MOD_ENROLLMENT);

    //Signals emmited by this module
    sigCDAPReceiveData = registerSignal(SIG_CDAP_DateReceive);

    //Listeners registered to process signal
    lisCDAPSendData = new LisCDAPSendData(this);
    catcher->subscribe(SIG_AE_DataSend, lisCDAPSendData);
    catcher->subscribe(SIG_RIBD_DataSend, lisCDAPSendData);
}

void CDAP::sendData(CDAPMessage* cmsg) {
    //Change and take ownership
    Enter_Method("SendData()");
    take(check_and_cast<cOwnedObject*>(cmsg) );

    //Send message
    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CDAP::signalizeReceiveData(CDAPMessage* cmsg) {
    emit(sigCDAPReceiveData, cmsg);
}
