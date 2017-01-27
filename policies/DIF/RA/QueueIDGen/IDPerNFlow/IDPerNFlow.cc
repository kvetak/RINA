// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "DIF/RA/QueueIDGen/IDPerNFlow/IDPerNFlow.h"

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
