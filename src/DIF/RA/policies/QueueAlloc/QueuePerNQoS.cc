//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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


RMTQueue* QueuePerNQoS::getSuitableOutputQueue(RMTPort* port, PDU_Base* pdu)
{
    std::ostringstream id;
    id << pdu->getConnId().getQoSId();
    return port->getQueueById(RMTQueue::OUTPUT, id.str().c_str());
}

void QueuePerNQoS::onNFlowAlloc(RMTPort* port, Flow* flow)
{
    std::ostringstream id;
    id << flow->getConId().getQoSId();
    rmtQM->addQueue(RMTQueue::OUTPUT, port, id.str().c_str());
    rmtQM->addQueue(RMTQueue::INPUT, port, id.str().c_str());
}
