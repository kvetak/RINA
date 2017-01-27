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

#include "DIF/RMT/MaxQueue/ReadRateReducer/ReadRateReducer.h"

Define_Module(ReadRateReducer);

void ReadRateReducer::onPolicyInit()
{
    fwd = getRINAModule<IntPDUForwarding*>(this, 1, {MOD_POL_RMT_PDUFWD});
}

bool ReadRateReducer::run(RMTQueue* queue)
{
    if (queue->getLength() >= queue->getMaxLength())
    {
        if (queue->getType() == RMTQueue::OUTPUT)
        {
            const PDU* pdu = dynamic_cast<const PDU*>(queue->getLastPDU());

            // this isn't optimal, but there doesn't seem to be a better way to
            // get output->input port mapping in connection-less forwarding
            RMTPorts inputPorts = fwd->lookup(pdu);

            if (!inputPorts.front()->hasBlockedInput())
            { // block read from the input port
                inputPorts.front()->blockInput();
            }

        }
    }

    return false;
}

void ReadRateReducer::onQueueLengthDrop(RMTQueue* queue)
{
    const PDU* pdu = dynamic_cast<const PDU*>(queue->getLastPDU());
    RMTPorts inputPorts = fwd->lookup(pdu);

    if (inputPorts.front()->hasBlockedInput())
    { // the output buffers are keeping up again, continue receiving on input
        inputPorts.front()->unblockInput();
    }
}
