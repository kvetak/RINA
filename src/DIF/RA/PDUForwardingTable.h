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
 * @file PDUForwardingTable.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief PDU forwarding (routing) table used by RMT relay.
 * @detail
 */

#ifndef __RINA_PDUFORWARDINGTABLE_H_
#define __RINA_PDUFORWARDINGTABLE_H_

#include <omnetpp.h>
#include "ConnectionId.h"

#include "PDUForwardingTable.h"
#include "PDUTableEntry.h"

typedef std::list<PDUTableEntry> PDUFwTable;
typedef PDUFwTable::iterator PDUFwIter;

class PDUForwardingTable : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    PDUFwTable FwTable;
    void printAll();

  public:
    PDUForwardingTable();

    void insert(const PDUTableEntry* entry);
    void insert(Address destAddr, int qosId, cModule* ipc, int portId);
    RMTPortId lookup(Address& destAddr, int QoSid);
    void remove(std::string portId);
};

#endif
