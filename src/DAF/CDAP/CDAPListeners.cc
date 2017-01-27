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
#include "DAF/CDAP/CDAPListeners.h"

CDAPListeners::CDAPListeners(CDAP* ncdap): cdap(ncdap)
{
}

CDAPListeners::~CDAPListeners() {
    cdap = NULL;
}

void LisCDAPSendData::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail) {
    EV << "SendData initiated by " << src->getFullPath() << " and processed by " << cdap->getFullPath() << endl;
    CDAPMessage* msg = dynamic_cast<CDAPMessage*>(obj);
    if (msg)
        cdap->sendData(msg);
    else
        EV << "Received not a CDAPMessage!" << endl;
}
