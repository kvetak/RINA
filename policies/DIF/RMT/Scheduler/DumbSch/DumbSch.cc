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

#include "DIF/RMT/Scheduler/DumbSch/DumbSch.h"

Define_Module(DumbSch);

void DumbSch::onPolicyInit()
{
    monitor= getRINAModule<SmartMonitor*>(this, 1, {MOD_POL_RMT_QMONITOR});
    if (monitor == NULL)
    {
        EV << "!!! SmartMonitor has to be used in conjecture with DumbSch!" << endl;
    }
}


void DumbSch::processQueues(RMTPort* port, RMTQueueType direction) {
    if (direction == RMTQueue::OUTPUT) {
        if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT)) {
            RMTQueue* outQ = monitor->getNextOutput(port);
            if(outQ && outQ->getLength()>0) {
                outQ->releasePDU();
            }
        }
    } else if (direction == RMTQueue::INPUT) {
        if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT)) {
            RMTQueue* inQ = monitor->getNextInput(port);
            if(inQ && inQ->getLength()>0) {
                inQ->releasePDU();
            }
        }
    }
}
