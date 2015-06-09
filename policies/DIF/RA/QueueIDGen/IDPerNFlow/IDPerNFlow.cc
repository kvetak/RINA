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

#include "IDPerNFlow.h"

Define_Module(IDPerNFlow);

std::string IDPerNFlow::constructQueueID(const std::string& ipcName, ConnectionId& connID)
{
    // Currently (without CO routing), it's sufficient to identify distinct (N)-flow's
    // traffic by a concatenation of the other endpoint's IPC address and CEP-id.
    // However, we also need to accommodate management PDUs that may arrive without
    // an allocated (N)-flow.

    std::string id;

    if (connID.getQoSId() == VAL_MGMTQOSID)
    {
        id = std::string("noflow");
    }
    else
    {
        std::ostringstream id_ostr;
        id_ostr << ipcName << "_" << connID.getSrcCepId();
        id = id_ostr.str();
    }

    return id;
}

std::string IDPerNFlow::generateOutputQueueID(PDU* pdu)
{
    return constructQueueID(pdu->getSrcAddr().getIpcAddress().getName(),
            pdu->getConnId());
}

std::string IDPerNFlow::generateInputQueueID(PDU* pdu)
{
    return generateOutputQueueID(pdu);
}

std::string IDPerNFlow::generateIDFromFlow(Flow* flow)
{
    return constructQueueID(flow->getSrcAddr().getIpcAddress().getName(),
            flow->getConnectionId());
}
