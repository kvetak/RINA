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

#include "DIF/RMT/MaxQueue/ECNMarkerLG/ECNMarkerLG.h"

const char * ECN_MARKER = "ECN_MARKER";


Define_Module(ECNMarkerLG);

void ECNMarkerLG::onPolicyInit() {
    sigStatECNMarker = registerSignal(ECN_MARKER);
}


bool ECNMarkerLG::run(RMTQueue* queue)
{
    if (queue->getLength() >= queue->getMaxLength())
    {
        EV << "ECNMarker: dropping message for queue " << queue->getName() << endl;
        return true;
    }
    else
    {
        EV << "ECNMarker: marking the last message in queue " << queue->getName() << endl;
        const cPacket* msg = queue->getLastPDU();
        PDU* pdu = (PDU*) msg;
        if(dynamic_cast<DataTransferPDU*>(pdu)) {
            emit(sigStatECNMarker, pdu->getSeqNum());
            queue->markCongestionOnLast();
        } else {
            EV << "Not a Data PDU to ECN-mark!" << endl;
        }
        return false;
    }
}

