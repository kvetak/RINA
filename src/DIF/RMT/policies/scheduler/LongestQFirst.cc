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

void LongestQFirst::processQueues(RMTPort* port, RMTQueue::queueType direction)
{
    Enter_Method("processQueues()");

    if (direction == RMTQueue::OUTPUT)
    {
        if (port->isReady())
        {
            port->setBusy();

            RMTQueue* outQ = port->getLongestQueue(RMTQueue::OUTPUT);
            outQ->scheduleServiceEnd();
        }
        else
        {
            waitingOnOutput[port] += 1;
        }
    }
    else if (direction == RMTQueue::INPUT)
    {
        if (!waitingOnInput[port])
        {
            RMTQueue* inQ = port->getLongestQueue(RMTQueue::INPUT);
            inQ->scheduleServiceEnd();
        }
        else
        {
            waitingOnInput[port] += 1;
        }
    }
}
