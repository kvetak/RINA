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

#include "DL.h"

Define_Module(DL);

void DL::onPolicyInit()
{
    monitor= check_and_cast<DLMonitor*>
        (getModuleByPath("^.queueMonitorPolicy"));
    if (monitor == NULL)
    {
        EV << "!!! DLMaxQ has to be used in conjecture with DLMonitor!" << endl;
    }
}


void DL::processQueues(RMTPort* port, RMTQueueType direction)
{

    if (direction == RMTQueue::OUTPUT)
    {
        if (port->isReady())
        {
            port->setBusy();

            RMTQueue* outQ = monitor->getNextUrgentQ(port);
            if(outQ) {
                outQ->releasePDU();
            } else {
                port->setReady();
            }
        }
        else
        {
            port->addWaitingOnOutput();
        }
    }
    else if (direction == RMTQueue::INPUT)
    {
        if (inputBusy[port] != true)
        {
            inputBusy[port] = true;

            RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
            inQ->releasePDU();
        }
        else
        {
            port->addWaitingOnInput();
        }
    }
}
