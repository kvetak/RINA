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

#include <ReadRateReducer.h>

Define_Module(ReadRateReducer);

void ReadRateReducer::onPolicyInit()
{
    fwd = check_and_cast<IntPDUForwarding*>
        (getModuleByPath("^.pduForwardingPolicy"));
}

bool ReadRateReducer::run(RMTQueue* queue)
{
    if (queue->getLength() >= queue->getMaxLength())
    {
        if (queue->getType() == RMTQueue::OUTPUT)
        {
            const PDU* pdu = dynamic_cast<const PDU*>(queue->getLastPDU());

            // this isn't optimal, but there doesn't seem to be a better way to
            // get output->input port mapping in connection-less forwarding
            RMTPorts inputPorts = fwd->lookup(pdu);

            if (!inputPorts.front()->hasBlockedInput())
            { // block read from the input port
                inputPorts.front()->blockInput();
            }

        }
    }

    return false;
}

void ReadRateReducer::onQueueLengthDrop(RMTQueue* queue)
{
    const PDU* pdu = dynamic_cast<const PDU*>(queue->getLastPDU());
    RMTPorts inputPorts = fwd->lookup(pdu);

    if (inputPorts.front()->hasBlockedInput())
    { // the output buffers are keeping up again, continue receiving on input
        inputPorts.front()->unblockInput();
    }
}
