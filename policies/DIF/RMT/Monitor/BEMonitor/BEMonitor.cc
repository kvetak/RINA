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

#include <BEMonitor.h>

namespace BEMonitor {

Define_Module(BEMonitor);

void BEMonitor::onPolicyInit(){}

void BEMonitor::onMessageArrival(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] ++;
            inQ[port].push_back(queue);
        }
        if(queue->getType() == RMTQueue::OUTPUT){
            outC[port] ++;
            outQ[port].push_back(queue);
        }
    }
}

void BEMonitor::onMessageDeparture(RMTQueue* queue) {}

void BEMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] --;
            inQ[port].pop_back();
        } else {
            outC[port] --;
            outQ[port].pop_back();
        }
    }
}

void BEMonitor::postQueueCreation(RMTQueue* queue){
}

int BEMonitor::getInCount(RMTPort* port) {
    return inC[port];
}

int BEMonitor::getInThreshold(RMTQueue * queue){
    return queue->getMaxLength();
}

RMTQueue* BEMonitor::getNextInput(RMTPort* port){
    RMTQueue* q = NULL;

    QueuesList* ql = &(inQ[port]);
    if(!ql->empty()) {
        q = ql->front();
        ql->pop_front();
    }

    if(q != NULL){
        inC[port]--;
    }

    return q;
}

int BEMonitor::getOutCount(RMTPort* port){
    return outC[port];
}

int BEMonitor::getOutThreshold(RMTQueue * queue){
    return queue->getMaxLength();
}

RMTQueue* BEMonitor::getNextOutput(RMTPort* port){
    RMTQueue* q = NULL;

    QueuesList* ql = &(outQ[port]);
    if(!ql->empty()) {
        q = ql->front();
        ql->pop_front();
    }

    if(q != NULL){
        outC[port]--;
    }

    return q;
}

queueStat BEMonitor::getInStat(RMTQueue * queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return queueStat(inC[port],queue->getMaxLength(),1,queue->getMaxLength());
}
queueStat BEMonitor::getOutStat(RMTQueue * queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return queueStat(outC[port],queue->getMaxLength(),1,queue->getMaxLength());
}



}
