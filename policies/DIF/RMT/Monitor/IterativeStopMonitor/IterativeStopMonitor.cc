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

#include "DIF/RMT/Monitor/IterativeStopMonitor/IterativeStopMonitor.h"

namespace IterativeScheduling {

using namespace std;

Define_Module(IterativeStopMonitor);

void IterativeStopMonitor::onPolicyInit(){
    schedMod= getRINAModule<IterativeScheduling*>(this, 1, {MOD_POL_RMT_SCHEDULER});
    stopAt = par("stopAt").longValue();
    restartAt = par("restartAt").longValue();

    stopSignal = registerSignal(SIG_EFCP_StopSending);
    startSignal = registerSignal(SIG_EFCP_StartSending);
}

void IterativeStopMonitor::postQueueCreation(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::OUTPUT){
        RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
        schedMod->addQueue(port, queue);
    }
}


void IterativeStopMonitor::preQueueRemoval(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::OUTPUT){
        RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
        schedMod->removeQueue(port, queue);
    }
}


void IterativeStopMonitor::postPDUInsertion(RMTQueue* queue) {
    if(     queue->getType() == RMTQueue::OUTPUT
            && strcmp(queue->getName(), "outQ_noflow")
            && queue->getLength() >= stopAt) {
        const Flow * f = queue->getFlow();
        if (f == nullptr) { error("Queue flow is null"); }
        emit(stopSignal, f);
    }
}

void IterativeStopMonitor::postPDURelease(RMTQueue* queue) {
    if(     queue->getType() == RMTQueue::OUTPUT
            && strcmp(queue->getName(), "outQ_noflow")
            && queue->getLength() <= restartAt) {
        const Flow * f = queue->getFlow();
        if (f == nullptr) { error("Queue flow is null"); }
        emit(startSignal, f);
    }
}

}
