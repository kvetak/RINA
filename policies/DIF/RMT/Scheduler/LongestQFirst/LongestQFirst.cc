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

#include "DIF/RMT/Scheduler/LongestQFirst/LongestQFirst.h"

Define_Module(LongestQFirst);

void LongestQFirst::processQueues(RMTPort* port, RMTQueueType direction)
{
    Enter_Method("processQueues()");

    if (direction == RMTQueue::OUTPUT)
    {
        if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT))
        {
                RMTQueue* outQ = port->getLongestQueue(RMTQueue::OUTPUT);
                outQ->releasePDU();
        }
    }
    else if (direction == RMTQueue::INPUT)
    {
        if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT))
        {
                RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
                inQ->releasePDU();
        }
    }
}
