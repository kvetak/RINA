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
 * @file PDUForwardingTable.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief PDU forwarding (routing) table used by RMT relay.
 * @detail
 */

#include "PDUForwardingTable.h"

Define_Module(PDUForwardingTable);

void PDUForwardingTable::initialize()
{
    WATCH_LIST(FwTable);
}

PDUForwardingTable::PDUForwardingTable()
{

}


void PDUForwardingTable::handleMessage(cMessage *msg)
{

}

/**
* Dumps the contents of the forwarding table to OMNeT++ output console.
*
*/
void PDUForwardingTable::printAll() {
    EV << this->getFullPath() << " Printing the whole forwarding table: " << endl;

    for(PDUFwTable::iterator it = this->FwTable.begin(); it!= FwTable.end(); ++it)
    {
        PDUTableEntry a = *it;
        EV << this->getFullPath() << " destination: " << a.getDestAddr()
                << "; QoS ID: " << a.getQosId() << "; port-id: " << a.getPortId() << endl;
    }
}

/**
* Looks up a port-id to be used for given address and Qos-id.
*
* @param destAddr destination IPC process address
* @param QoSid QoS-id
* @return port-id
*/
std::string PDUForwardingTable::lookup(std::string destAddr, int QoSid) {
    for(PDUFwIter it = FwTable.begin(); it != FwTable.end(); ++it )
    {
        PDUTableEntry a = *it;
        if ((a.getDestAddr() == destAddr) && a.getQosId() == QoSid)
        {
            //EV << this->getFullPath() << " found a match: " << a.getPortId() << endl;
            return a.getPortId();
        }
    }

    throw;
}

/**
* Inserts a prepared forwarding table entry into the table.
*
* @param entry table entry to be inserted
*/
void PDUForwardingTable::insert(const PDUTableEntry* entry) {
    Enter_Method("insert()");
    FwTable.push_back(*entry);
}

/**
* Constructs a new forwarding table entry and adds it into the table.
*
* @param destAddr destination IPC process address
* @param qosId flow QoS ID
*/
void PDUForwardingTable::insert(std::string destAddr, int qosId, std::string portId) {
    Enter_Method("insert()");
    PDUTableEntry entry = PDUTableEntry(destAddr, qosId, portId);
    FwTable.push_back(entry);
}

/**
* Removes entries with matching port-id from the forwarding table.
*
* @param portId target port-id
*/
void PDUForwardingTable::remove(std::string portId)
{
    PDUFwIter i = FwTable.begin();
    while (i != FwTable.end())
    {
        if (i->getPortId() == portId)
        {
            i = FwTable.erase(i);
        }
        else
        {
            ++i;
        }
    }
}


