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

#include <REDMonitor.h>

Define_Module(REDMonitor);

void REDMonitor::postQueueCreation(RMTQueue* queue)
{
    qAvgLengths[queue] = 0.0;
    qCounters[queue] = -1;

    qWeights[queue] = par("queueWeight").doubleValue();
}

void REDMonitor::preQueueRemoval(RMTQueue* queue)
{
    qAvgLengths.erase(queue);
    qWeights.erase(queue);
    qCounters.erase(queue);
}


void REDMonitor::onMessageArrival(RMTQueue* queue)
{
    int length = queue->getLength();

    double avg = qAvgLengths[queue];
    double weight = qWeights[queue];

    simtime_t qTime = queue->getQTime();

    if (length > 0)
    {
        avg = (1 - weight) * avg + weight * length;
    }
    else
    {
        const double m = SIMTIME_DBL(simTime() - qTime);
        avg = pow(1 - weight, m) * avg;
    }

    qAvgLengths[queue] = avg;
}

