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

#include "PDUTableEntry.h"

PDUTableEntry::PDUTableEntry()
{
}

PDUTableEntry::PDUTableEntry(APN destaddr, int qosid, int portid)
:  destAddr(destaddr), qosId(qosid), portId(portid)
{
}

PDUTableEntry::~PDUTableEntry()
{

}

std::string PDUTableEntry::info() const {
    std::stringstream os;
    os << "dest: " << destAddr.getName() << "; qos-id: " << qosId
       << "; port-id: " << portId;
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const PDUTableEntry& cte) {
    return os << cte.info();
}

APN PDUTableEntry::getDestAddr()
{
    return destAddr;
}

int PDUTableEntry::getQosId()
{
    return qosId;
}

int PDUTableEntry::getPortId()
{
    return portId;
}

void PDUTableEntry::setDestAddr(APN destaddr)
{
    this->destAddr = destaddr;
}

void PDUTableEntry::setQosId(int qosid)
{
    this->qosId = qosid;
}

void PDUTableEntry::setPortId(int portid)
{
    this->portId = portid;
}
