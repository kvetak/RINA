//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <BEMonitor.h>

namespace BEMonitor {

Define_Module(BEMonitor);

void BEMonitor::onPolicyInit(){}

void BEMonitor::onMessageArrival(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] ++;
            if(inM[port] != queue) {
                inQ[port].push_back(queue);
            }
        }
        if(queue->getType() == RMTQueue::OUTPUT){
            outC[port] ++;
            if(outM[port] != queue) {
                outQ[port].push_back(queue);
            }
        }
    }
}

void BEMonitor::onMessageDeparture(RMTQueue* queue) {}

void BEMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] --;
            if(inM[port] != queue) {
                inQ[port].pop_back();
            }
        } else {
            outC[port] --;
            if(outM[port] != queue) {
                outQ[port].pop_back();
            }
        }
    }
}

void BEMonitor::postQueueCreation(RMTQueue* queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    inM[port] = port->getManagementQueue(RMTQueue::INPUT);
    outM[port] = port->getManagementQueue(RMTQueue::OUTPUT);
}

int BEMonitor::getInCount(RMTPort* port) {
    return inC[port];
}

int BEMonitor::getInThreshold(RMTQueue * queue){
    return queue->getMaxLength();
}

RMTQueue* BEMonitor::getNextInput(RMTPort* port){
    RMTQueue* q = NULL;

    if(inM[port]->getLength() > 0) {
        q = inM[port];
    } else {
        QueuesList* ql = &(inQ[port]);
        if(!ql->empty()) {
            q = ql->front();
            ql->pop_front();
        }
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

    if(outM[port]->getLength() > 0) {
        q = outM[port];
    } else {
        QueuesList* ql = &(outQ[port]);
        if(!ql->empty()) {
            q = ql->front();
            ql->pop_front();
        }
    }

    if(q != NULL){
        outC[port]--;
    }

    return q;
}



}
