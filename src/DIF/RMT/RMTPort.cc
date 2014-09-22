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

#include "RMTPort.h"


RMTPort::RMTPort()
{

}

RMTPort::~RMTPort()
{

}

bool RMTPort::outboundState()
{
    return outboundActive;
}
void RMTPort::suspendOutbound()
{
    this->outboundActive = false;
}

void RMTPort::resumeOutbound()
{
    this->outboundActive = true;
}


void RMTPort::setOutGate(cGate* val)
{
    this->outGate = val;
}

cGate* RMTPort::getOutGate()
{
    return this->outGate;
}


void RMTPort::addIncomingPDU(PDU_Base* pdu)
{
    inQ.insertPDU(pdu);
}

void RMTPort::addOutgoingPDU(PDU_Base* pdu)
{
    outQ.insertPDU(pdu);
}

PDU_Base* RMTPort::popIncomingPDU()
{
    return inQ.popPDU();
}

PDU_Base* RMTPort::popOutgoingPDU()
{
    return outQ.popPDU();
}

int RMTPort::getIncomingLength()
{
    return inQ.getLength();
}

int RMTPort::getOutgoingLength()
{
    return outQ.getLength();
}



