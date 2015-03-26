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

#include "LongestQFirst.h"

Define_Module(LongestQFirst);

void LongestQFirst::processQueues(RMTPort* port, RMTQueueType direction)
{
    Enter_Method("processQueues()");

    if (direction == RMTQueue::OUTPUT)
    {
        if (port->isReady() && port->getWaiting(RMTQueue::OUTPUT))
        {
            // management PDU should have bigger priority for now
            RMTQueue* outQ = port->getManagementQueue(RMTQueue::OUTPUT);
            if (outQ->getLength() > 0)
            {
                outQ->releasePDU();
            }
            else
            {
                outQ = port->getLongestQueue(RMTQueue::OUTPUT);
                outQ->releasePDU();
            }
        }
    }
    else if (direction == RMTQueue::INPUT)
    {
        if (port->getWaiting(RMTQueue::INPUT))
        {
            RMTQueue* inQ = port->getManagementQueue(RMTQueue::INPUT);
            if (inQ->getLength() > 0)
            {
                inQ->releasePDU();
            }
            else
            {
                inQ = port->getLongestQueue(RMTQueue::INPUT);
                inQ->releasePDU();
            }
        }
    }
}
