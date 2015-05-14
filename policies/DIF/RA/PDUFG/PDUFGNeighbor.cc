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

#include "PDUFGNeighbor.h"

PDUFGNeighbor::PDUFGNeighbor()
{

}

PDUFGNeighbor::PDUFGNeighbor(Address addr, std::string qosId, RMTPort * p)
{
    dstAddr = addr;
    qos = qosId;
    port = p;
}

PDUFGNeighbor::~PDUFGNeighbor()
{

}

Address& PDUFGNeighbor::getDestAddr()
{
    return dstAddr;
}

RMTPort * PDUFGNeighbor::getPort()
{
    return port;
}

std::string PDUFGNeighbor::getQosId()
{
    return qos;
}

void PDUFGNeighbor::setDestAddr(Address & addr)
{
    dstAddr = addr;
}

void PDUFGNeighbor::setPort(RMTPort * p)
{
    port = p;
}

void PDUFGNeighbor::setQosId(std::string qosId)
{
    qos = qosId;
}
