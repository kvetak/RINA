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

PDUTableEntry::PDUTableEntry(Address& destaddr, int qosid, RMTQueue* queue)
:  destAddr(destaddr), qosId(qosid), rmtQueue(queue)
{
}

//PDUTableEntry::PDUTableEntry(Address& destaddr, int qosid, cModule* ipc)
//:  destAddr(destaddr), qosId(qosid), portId(std::make_pair(ipc, -1))
//{
//}
//
//PDUTableEntry::PDUTableEntry(Address& destaddr, int qosid, cModule* ipc, int portid)
//:  destAddr(destaddr), qosId(qosid), portId(std::make_pair(ipc, portid))
//{
//}

PDUTableEntry::~PDUTableEntry()
{

}

std::string PDUTableEntry::info() const {
    std::ostringstream os;

    os << "dest: " << destAddr << endl
       << "qos-id: " << qosId << endl
       << "output queue: " << rmtQueue->getFullName();

    return os.str();
}

std::ostream& operator <<(std::ostream& os, const PDUTableEntry& cte) {
    return os << cte.info();
}

Address& PDUTableEntry::getDestAddr()
{
    return destAddr;
}

int PDUTableEntry::getQosId()
{
    return qosId;
}

RMTQueue* PDUTableEntry::getQueueId()
{
    return rmtQueue;
}

void PDUTableEntry::setDestAddr(Address& destaddr)
{
    this->destAddr = destaddr;
}

void PDUTableEntry::setQosId(int qosid)
{
    this->qosId = qosid;
}

void PDUTableEntry::setPortId(RMTQueue* portid)
{
    this->rmtQueue = portid;
}
