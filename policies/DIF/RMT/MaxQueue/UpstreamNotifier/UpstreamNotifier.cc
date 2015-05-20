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

#include <UpstreamNotifier.h>

Define_Module(UpstreamNotifier);

void UpstreamNotifier::onPolicyInit()
{

}

bool UpstreamNotifier::run(RMTQueue* queue)
{
    // simple version:
    // Send out the notification when an output (N-1)-port is overflowing.

    if (queue->getLength() >= queue->getMaxLength())
    {
        if (queue->getType() == RMTQueue::OUTPUT)
        { // (N-1)-port output queues are filling up => stop accepting more PDUs
            notifySenderOfCongestion(queue->getLastPDU());
        }
    }

    return false;
}

