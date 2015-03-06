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
 * @file PrefixPDUForwardingTable.h
 * @author Sergio Leon (gaixas1@gmail.com)
 * @brief PDU forwarding (routing) table used by RMT relay grouping by prefixes.
 * @detail
 */

#ifndef __RINA_PrefixPDUForwardingTable_H_
#define __RINA_PrefixPDUForwardingTable_H_

#include <omnetpp.h>
#include "IntPDUForwardingTable.h"

#include <map>
#include <set>
#include <vector>
#include <string>

typedef std::set<unsigned short > QoSCollection;
typedef QoSCollection::iterator QoSColIterator;

typedef std::pair<std::string, unsigned short > addrQoS;
typedef std::map<addrQoS, RMTPort*> PFwTable;
typedef PFwTable::iterator PFwTabIterator;
typedef std::pair<addrQoS, RMTPort*> PFwTabEntry;


class PrefixPDUForwardingTable : public IntPDUForwardingTable
{
  public:
    PrefixPDUForwardingTable();

    void clean();
    RMTPort* lookup(Address& destAddr, unsigned short QoSid);
    RMTPort* lookup(Address& destAddr);
    void printAll();

    void setDelimiter(char _delimiter);
    void addEntry(std::string dstAddr, unsigned short QoSid, RMTPort* p);
    void addEntryIfNot(std::string dstAddr, unsigned short QoSid, RMTPort* p);
    void remove(std::string dstAddr, unsigned short QoSid);
    void remove(std::string dstAddr);

  protected:
    char delimiter;
    PFwTable table;
    QoSCollection qosCol;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
