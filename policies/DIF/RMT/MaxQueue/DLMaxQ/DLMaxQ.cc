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

#include <DLMaxQ.h>

Define_Module(DLMaxQ);

void DLMaxQ::onPolicyInit()
{
    monitor = dynamic_cast<DLMonitor*>(qMonPolicy);
    if (monitor == NULL)
    {
        EV << "!!! DLMaxQ has to be used in conjecture with DLMonitor!" << endl;
    }
}

bool DLMaxQ::run(RMTQueue* queue)
{
    if(queue->getType() == RMTQueue::INPUT){
        if(queue->getLength() >= queue->getMaxLength()){
            EV << "DLMaxQ: dropping message for IN queue " << queue->getName() << endl;
            return true;
        } else {
            return false;
        }
    }

    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(monitor->getPortCount(port) < monitor->getThreshold(queue)){
            return false;
        }
    }

    EV << "DLMaxQ: dropping message for OUT queue " << queue->getName() << endl;
    return true;
}

