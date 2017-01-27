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

#include "DAF/CDAP/CACE.h"

Define_Module(CACE);

void CACE::initialize()
{
    initSignalsAndListeners();
}

void CACE::handleMessage(cMessage *msg)
{
    //check message and process it to CACEStateMachine
    if (dynamic_cast<CDAPMessage*>(msg)) {
        CDAPMessage* cmsg = check_and_cast<CDAPMessage*>(msg);
        signalizeDataReceive(cmsg);
    }
}

void CACE::initSignalsAndListeners(){
    cModule* catcher = this->getModuleByPath("^.^");

    //Signals emitted by this module
    sigCACEReceiveData = registerSignal(SIG_CACE_DataReceive);

    //Signals that this module is processing
    //send data from AE/Enrollment
    lisCACESendData = new LisCACESendData(this);
    catcher->subscribe(SIG_RIBD_CACESend, lisCACESendData);

}

void CACE::sendData(CDAPMessage *cmsg){
    Enter_Method("CACE SendData()");
    take(check_and_cast<cOwnedObject*>(cmsg) );

    cGate* out = gateHalf(GATE_SPLITIO, cGate::OUTPUT);
    send(cmsg, out);
}

void CACE::signalizeDataReceive(CDAPMessage* cmsg) {
    emit(sigCACEReceiveData, cmsg);
}
