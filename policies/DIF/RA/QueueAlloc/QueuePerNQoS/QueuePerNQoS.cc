//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "QueuePerNQoS.h"

Define_Module(QueuePerNQoS);


void QueuePerNQoS::onNM1PortInit(RMTPort* port)
{
    // get a list of QoS cubes
    const QoSCubeSet& cubes = ra->getQoSCubes();

    // create a pair of queues for each available data QoS cube
    std::ostringstream idString;
    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it)
    {
        // exclude management QoS, this is handled in a different way
        if (it->getQosId() == VAL_MGMTQOSID) continue;

        idString << it->getQosId();
        rmtAllocator->addQueue(RMTQueue::OUTPUT, port, idString.str().c_str());
        rmtAllocator->addQueue(RMTQueue::INPUT, port, idString.str().c_str());
        // clear the buffer
        idString.str(std::string());
        idString.clear();
    }
}
