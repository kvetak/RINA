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

// Author: Kewin Rausch (kewin.rausch@create-net.org)

#include "PDUFTGNeighbor.h"

PDUFTGNeighbor::PDUFTGNeighbor()
{

}

PDUFTGNeighbor::PDUFTGNeighbor(Address addr, unsigned short qosId, RMTPort * p)
{
    dstAddr = addr;
    qos = qosId;
    port = p;
}

PDUFTGNeighbor::~PDUFTGNeighbor()
{

}

Address& PDUFTGNeighbor::getDestAddr()
{
    return dstAddr;
}

RMTPort * PDUFTGNeighbor::getPort()
{
    return port;
}

unsigned short PDUFTGNeighbor::getQosId()
{
    return qos;
}

void PDUFTGNeighbor::setDestAddr(Address & addr)
{
    dstAddr = addr;
}

void PDUFTGNeighbor::setPort(RMTPort * p)
{
    port = p;
}

void PDUFTGNeighbor::setQosId(unsigned short qosId)
{
    qos = qosId;
}
