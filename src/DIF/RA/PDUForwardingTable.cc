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


void PDUForwardingTable::printAll() {
    EV << this->getFullPath() << " Printing the whole forwarding table: " << endl;

    for(PDUFwTable::iterator it = this->FwTable.begin(); it!= FwTable.end(); ++it)
    {
        PDUTableEntry a = *it;
        EV << this->getFullPath() << " destination: " << a.getDestAddr().getName()
                << "; QoS ID: " << a.getQosId() << "; port-id: " << a.getPortId() << endl;
    }
}

int PDUForwardingTable::lookup(APN destAddr, int QoSid) {
    //EV << this->getFullPath() << " lookin' up" << endl;
    for(PDUFwIter it = FwTable.begin(); it != FwTable.end(); ++it )
    {
        PDUTableEntry a = *it;
        if ((a.getDestAddr().getName() == destAddr.getName()) && a.getQosId() == QoSid)
        {
            //EV << this->getFullPath() << " found a match: " << a.getPortId() << endl;
            return a.getPortId();
        }
    }
    return -1;
}

void PDUForwardingTable::insert(const PDUTableEntry* entry) {
    Enter_Method("insert()");
    FwTable.push_back(*entry);
    //EV << this->getFullPath() << " inserted an item" << endl;
}

void PDUForwardingTable::remove(int portId)
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


