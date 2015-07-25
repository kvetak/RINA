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

#include "DQSch.h"

Define_Module(DQSch);

void DQSch::onPolicyInit()
{
    monitor= check_and_cast<DQMonitor::DQMonitor*>
        (getModuleByPath("^.queueMonitorPolicy"));
    if (monitor == NULL)
    {
        EV << "!!! DQMonitor has to be used in conjecture with DQSch!" << endl;
    }
}


void DQSch::processQueues(RMTPort* port, RMTQueueType direction) {
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
            } else {
                simtime_t t = monitor->getNextInputTime(port);
                if(t > simTime()){
                    scheduleReinvocation(t, port, RMTQueue::INPUT);
                }
            }
        }
    }
}
