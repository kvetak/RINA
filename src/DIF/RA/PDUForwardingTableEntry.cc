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
 * @file PDUForwardingTableEntry.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief A class representing a single item of the forwarding table.
 * @detail
 */

#include "PDUForwardingTableEntry.h"

PDUForwardingTableEntry::PDUForwardingTableEntry()
{
}

PDUForwardingTableEntry::PDUForwardingTableEntry
    (Address& destaddr, unsigned short qosid, RMTPort* port)
:  destAddr(destaddr), qosId(qosid), rmtPort(port)
{
}

PDUForwardingTableEntry::~PDUForwardingTableEntry()
{
}

std::string PDUForwardingTableEntry::info() const
{
    std::ostringstream os;

    os << "dest: " << destAddr << endl
       << "qos-id: " << qosId << endl
       << "RMT port: " << rmtPort->getFullName();

    return os.str();
}

std::ostream& operator <<(std::ostream& os, const PDUForwardingTableEntry& cte)
{
    return os << cte.info();
}

const Address& PDUForwardingTableEntry::getDestAddr() const
{
    return destAddr;
}

unsigned short PDUForwardingTableEntry::getQosId() const
{
    return qosId;
}

RMTPort* PDUForwardingTableEntry::getPort() const
{
    return rmtPort;
}
