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

/**
 * @file PDUTableEntry.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief A class representing a single item of the forwarding table.
 * @detail
 */

#include "PDUTableEntry.h"

PDUTableEntry::PDUTableEntry()
{
}


PDUTableEntry::PDUTableEntry(std::string destaddr, int qosid, cModule* ipc)
:  destAddr(destaddr), qosId(qosid), portId(std::make_pair(ipc, -1))
{
}

PDUTableEntry::PDUTableEntry(std::string destaddr, int qosid, cModule* ipc, int portid)
:  destAddr(destaddr), qosId(qosid), portId(std::make_pair(ipc, portid))
{
}

PDUTableEntry::~PDUTableEntry()
{

}

std::string PDUTableEntry::info() const {
    std::stringstream os;

    os << "type: "
       << (portId.second == -1 ? "static" : "dynamic") << endl;

    os << "dest: " << destAddr << endl
       << "qos-id: " << qosId << endl
       << "port-id: " << portId.first->getFullName() << ":" << portId.second;

    return os.str();
}

std::ostream& operator <<(std::ostream& os, const PDUTableEntry& cte) {
    return os << cte.info();
}

std::string PDUTableEntry::getDestAddr()
{
    return destAddr;
}

int PDUTableEntry::getQosId()
{
    return qosId;
}

RMTPortId PDUTableEntry::getPortId()
{
    return portId;
}

void PDUTableEntry::setDestAddr(std::string destaddr)
{
    this->destAddr = destaddr;
}

void PDUTableEntry::setQosId(int qosid)
{
    this->qosId = qosid;
}

void PDUTableEntry::setPortId(RMTPortId portid)
{
    this->portId = portid;
}
