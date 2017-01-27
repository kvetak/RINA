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

#include "DIF/RMT/Scheduler/QTASch/QTASch.h"

Define_Module(QTASch);

void QTASch::onPolicyInit() {
    monitor= getRINAModule<QTAMux::QTAMonitor*>(this, 1, {MOD_POL_RMT_QMONITOR});
    if (monitor == NULL) { error("!!! QAMonitor has to be used in conjecture with QTASch!"); }
}

void QTASch::scheduleNow(RMTPort * port) {
    Enter_Method_Silent();
    scheduleReinvocation(simTime(), port, RMTQueue::OUTPUT);
}

void QTASch::processQueues(RMTPort* port, RMTQueueType direction) {
    RMTQueue * Q = nullptr;
    if (direction == RMTQueue::OUTPUT) {
        if(! port->isOutputReady()) { return; }
        Q = monitor->getNext(port);
    } else {
        if(! port->isInputReady()) { return; }
        Q = port->getLongestQueue(RMTQueue::INPUT);
    }
    if(Q != nullptr && Q->getLength()>0) {
        Q->releasePDU();
    }
}
