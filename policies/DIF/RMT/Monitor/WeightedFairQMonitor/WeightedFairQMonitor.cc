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

#include "DIF/RMT/Monitor/WeightedFairQMonitor/WeightedFairQMonitor.h"

Define_Module(FWQ::WeightedFairQMonitor);

namespace FWQ {

using namespace std;

void WeightedFairQMonitor::onPolicyInit(){
    // Default Bandwith for Queues not linked to flows or with undefined bandwith
    defBW = par("defBW").longValue();

    // Queue sizes for lock and release EFCPi
    stopQAt = par("stopQAt").longValue();
    startQAt = par("startQAt").longValue();
}

void WeightedFairQMonitor::postQueueCreation(RMTQueue* queue){
    int bw = 0;

    if(queue->getFlow() != NULL) {
        bw = queue->getFlow()->getQosCube().getAvgBand();
    }

    queueTimes[queue] = FlowParams( bw > 0 ? bw : defBW );
}
void WeightedFairQMonitor::preQueueRemoval(RMTQueue* queue){
    /*
     * Release the lock on the EFCPi of the flow related to the queue.
     *
     * if(queue->getFlow() != NULL) {
     *     ReleaseEFCPiByFlow( queue->getFlow(), queue->getId() );
     * }
     */
    queueTimes.erase(queue);
}

void WeightedFairQMonitor::postPDUInsertion(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::INPUT){ return; }

    if(queueTimes.find(queue) != queueTimes.end()) {
        queueTimes[queue].insert( queue->getLastPDU()->getBitLength() );
    }

    /*
     * Add lock on the EFCPi of the flow related to the queue.
     *
     * if( queue->getLength() => stopQAt ) {
     *     if(queue->getFlow() != NULL) {
     *         LockEFCPiByFlow( queue->getFlow(), queue->getId() );
     *     }
     * }
     */
}

void WeightedFairQMonitor::postPDURelease(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::INPUT){ return; }

    if(queueTimes.find(queue) != queueTimes.end()) {
        queueTimes[queue].removeFirst();
    }

    /*
     * Release the lock on the EFCPi of the flow related to the queue.
     *
     * if( queue->getLength() <= startQAt ) {
     *     if(queue->getFlow() != NULL) {
     *         ReleaseEFCPiByFlow( queue->getFlow(), queue->getId() );
     *     }
     * }
     */
}

void WeightedFairQMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    if(queue->getType() == RMTQueue::INPUT){ return; }

    if(queueTimes.find(queue) != queueTimes.end()) {
        queueTimes[queue].removeLast();
    }

    /*
     * Release the lock on the EFCPi of the flow related to the queue.
     *
     * if( queue->getLength() <= startQAt ) {
     *     if(queue->getFlow() != NULL) {
     *         ReleaseEFCPiByFlow( queue->getFlow(), queue->getId() );
     *     }
     * }
     */
}


RMTQueue * WeightedFairQMonitor::getNextQueue() {
    simtime_t vFinTime = DBL_MAX;
    RMTQueue * ret = NULL;

    for(queue2FpIt it = queueTimes.begin(); it != queueTimes.end(); it++) {
        simtime_t qvFinTime = it->second.getFirstFinTime();
        if(qvFinTime < vFinTime) {
            vFinTime = qvFinTime;
            ret = it->first;
        }
    }

    return ret;
}


} /* namespace FWQ */
