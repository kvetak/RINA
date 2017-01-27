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

#include "DIF/RMT/Scheduler/WeightedFairQ/WeightedFairQ.h"

Define_Module(FWQ::WeightedFairQ);

namespace FWQ {

using namespace std;


void WeightedFairQ::onPolicyInit() {
    monitor = getRINAModule<WeightedFairQMonitor*>(this, 1, {MOD_POL_RMT_QMONITOR});
    if (monitor == NULL) {
        EV << "!!! WeightedFairQMaxQ has to be used in conjecture with WeightedFairQ!" << endl;
    }
}


void WeightedFairQ::processQueues(RMTPort* port, RMTQueueType direction) {
    Enter_Method("processQueues()");

    switch(direction){
        case RMTQueue::INPUT:
            if (port->isInputReady() && port->getWaiting(RMTQueue::INPUT)) {
                RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
                inQ->releasePDU();
            }
        break;
        case RMTQueue::OUTPUT:
            if (port->isOutputReady() && port->getWaiting(RMTQueue::OUTPUT)) {
                RMTQueue* outQ =  monitor->getNextQueue();
                if(outQ && outQ->getLength() > 0) {
                    outQ->releasePDU();
                }
            }
            break;
    }
}

} /* namespace FWQ */

