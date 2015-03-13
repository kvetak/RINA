//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
 * @file SimplePDUForwardingTable.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief PDU forwarding (routing) table used by RMT relay.
 * @detail
 */

#include "SimplePDUForwardingTable.h"

Define_Module(SimplePDUForwardingTable);

void SimplePDUForwardingTable::initialize()
{
    WATCH_LIST(fwTable);
}

SimplePDUForwardingTable::SimplePDUForwardingTable()
{

}


void SimplePDUForwardingTable::handleMessage(cMessage *msg)
{

}

/**
* Dumps the contents of the forwarding table to OMNeT++ output console.
*
*/
void SimplePDUForwardingTable::printAll()
{
    EV << "Printing the whole forwarding table: " << endl;

    for(PDUFwdTable::iterator it = this->fwTable.begin(); it!= fwTable.end(); ++it)
    {
        PDUForwardingTableEntry a = *it;
        EV << this->getFullPath()
           << " dstAddr: " << a.getDestAddr().getApname().getName()
           << "; QoS ID: " << a.getQosId()
           << "; port-id: " << a.getPort()->getFullName() << endl;
    }
}

/**
* Looks up a port-id to be used for given address and Qos-id.
*
* @param destAddr destination IPC process address
* @param QoSid QoS-id
* @return port-id
*/
RMTPort* SimplePDUForwardingTable::lookup(Address& destAddr, unsigned short QoSid)
{
    for(PDUFwdTableIter it = fwTable.begin(); it != fwTable.end(); ++it )
    {
        PDUForwardingTableEntry a = *it;
        if ((a.getDestAddr().getApname() == destAddr.getApname()) && (a.getQosId() == QoSid))
        {
            return a.getPort();
        }
    }
    return NULL;
}

RMTPort* SimplePDUForwardingTable::lookup(Address& destAddr)
{
    for(PDUFwdTableIter it = fwTable.begin(); it != fwTable.end(); ++it )
    {
        PDUForwardingTableEntry a = *it;
        if (a.getDestAddr().getApname() == destAddr.getApname())
        {
            return a.getPort();
        }
    }
    return NULL;
}

/**
* Inserts a prepared forwarding table entry into the table.
*
* @param entry table entry to be inserted
*/
void SimplePDUForwardingTable::insert(const PDUForwardingTableEntry* entry)
{
    Enter_Method("insert()");
    fwTable.push_back(*entry);
}

/**
* Constructs a new forwarding table entry and adds it into the table.
*
* @param destAddr destination IPC process address
* @param qosId flow QoS ID
*/
void SimplePDUForwardingTable::insert(Address destAddr, unsigned short qosId, RMTPort* port)
{
    Enter_Method("insert()");

    // multiple ports per item aren't supported at the moment
    if (lookup(destAddr, qosId) == NULL)
    {
        PDUForwardingTableEntry entry = PDUForwardingTableEntry(destAddr, qosId, port);
        fwTable.push_back(entry);
    }
}

/**
* Removes entries with matching port-id from the forwarding table.
*
* @param portId target port-id
*/
void SimplePDUForwardingTable::remove(Address destAddr, int qosId)
{
    PDUFwdTableIter i = fwTable.begin();

    while (i != fwTable.end())
    {
        if (i->getDestAddr() == destAddr && i->getQosId() == qosId)
        {
            i = fwTable.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void SimplePDUForwardingTable::clean()
{
    /* Q: How to handle memory here? */
    fwTable.clear();
}
