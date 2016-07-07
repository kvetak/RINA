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

#include "LongestQFirst.h"

Define_Module(LongestQFirst);

using namespace std;

void LongestQFirst::processQueues(RMTPort* port, RMTQueueType direction)
{
    Enter_Method("processQueues()");
    bool print = false;
    if(getFullPath() == "net.N0.dataIpc.relayAndMux.schedulingPolicy") { print = true; }

    if(print)  { cout<<simTime() << " - Called for OUTPUT at "<< getFullPath() <<endl;}

    if (direction == RMTQueue::OUTPUT)  {
        if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT))
        {
                RMTQueue* outQ = port->getLongestQueue(RMTQueue::OUTPUT);
                outQ->releasePDU();

                if(print)  { cout<< "\t Port ready, releasing queue "<< outQ->getFullPath()<<endl; }
        } else {
            if(print)  { cout<< "\t Port not ready"<<endl; }
        }
    }
    else if (direction == RMTQueue::INPUT)  {
        if(print)  { cout<<simTime() << " - Called for INPUT at "<< getFullPath() <<endl;}
        if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT))
        {
                RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
                inQ->releasePDU();
                if(print)  { cout<< "\t Port ready, releasing queue "<< inQ->getFullPath()<<endl; }
        } else {
            if(print)  { cout<< "\t Port not ready"<<endl; }
        }
    }
}
