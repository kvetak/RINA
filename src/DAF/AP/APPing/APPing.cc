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

#include <APPing/APPing.h>

Define_Module(APPing);

APPing::APPing() {
}

APPing::~APPing() {
}

void APPing::initialize() {
    AP::initialize();
    if (strcmp(par("dstApName").stringValue(),"AppErr")) {
        m1 = new cMessage("start");
        scheduleAt(simTime() + par("startAt").longValue(), m1);

        m2 = new cMessage("stop");
        scheduleAt(simTime() + par("stopAt").longValue(), m2);
    }
}

void APPing::handleMessage(cMessage *msg) {
    if(msg->isSelfMessage()) {
        if ( !strcmp(msg->getName(), "start") ) {
            invokeId = getNewInvokeID();
            a_open(invokeId, par("dstApName").stringValue(), "0", "AEMonitor", "-1");
        }
        else if (!strcmp(msg->getName(), "stop")) {
            a_close(conID);
        }
        else if (!strcmp(msg->getName(), "ping")) {
            if (par("stopAt").doubleValue() < (simTime().dbl()+1)) {
                a_read(conID, "ping");
                m2 = new cMessage("ping");
                scheduleAt(simTime() + par("interval"), m2);
            }
        }
        else
            EV << this->getFullPath() << " received unknown self-message " << msg->getName();
        delete(msg);
    }
}


void APPing::onA_getOpen(APIResult* result) {
    if (result->getInvokeId() == invokeId) {
        conID = result->getCDAPConId();
        a_read(conID, "ping");

        m2 = new cMessage("ping");
        scheduleAt(simTime() + par("interval"), m2);
    }
}

void APPing::onA_getRead(APIResult* result) {
    value = (int*)(result->getObj()->objectVal);
}
