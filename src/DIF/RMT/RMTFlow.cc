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

#include "RMTFlow.h"


RMTFlow::RMTFlow()
{

}

RMTFlow::~RMTFlow()
{

}

bool RMTFlow::outboundState()
{
    return outboundActive;
}
void RMTFlow::suspendOutbound()
{
    this->outboundActive = false;
}

void RMTFlow::resumeOutbound()
{
    this->outboundActive = true;
}


void RMTFlow::setEfcpiGateId(int val)
{
    this->efcpId = val;
}

int RMTFlow::getEfcpiGateId()
{
    return this->efcpId;
}

void RMTFlow::setSouthGateId(int val)
{
    this->outGateId = val;
}

int RMTFlow::getSouthGateId()
{
    return this->outGateId;
}

void RMTFlow::addIncomingPDU(DataTransferPDU* pdu)
{
    inQ.insertPDU(pdu);
}

void RMTFlow::addOutgoingPDU(DataTransferPDU* pdu)
{
    outQ.insertPDU(pdu);
}

DataTransferPDU* RMTFlow::popIncomingPDU()
{
    return inQ.popPDU();
}

DataTransferPDU* RMTFlow::popOutgoingPDU()
{
    return outQ.popPDU();
}

int RMTFlow::getIncomingLength()
{
    return inQ.getLength();
}

int RMTFlow::getOutgoingLength()
{
    return outQ.getLength();
}



