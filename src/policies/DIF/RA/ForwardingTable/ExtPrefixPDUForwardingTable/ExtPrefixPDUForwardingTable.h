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
 * @file ExtPrefixPDUForwardingTable.h
 * @author Sergio Leon (gaixas1@gmail.com)
 * @brief PDU forwarding (routing) table used by RMT relay grouping by prefixes.
 * @detail
 */

#ifndef __RINA_ExtPrefixPDUForwardingTable_H_
#define __RINA_ExtPrefixPDUForwardingTable_H_

#include <omnetpp.h>
#include "IntPrefixPDUForwardingTable.h"

#include <map>
#include <set>
#include <string>


typedef std::map<unsigned char, RMTPort*> type2Port;
typedef type2Port::iterator type2PortIt;

typedef std::map<std::string, type2Port> FWDTable;
typedef FWDTable::iterator FWDTableIt;

typedef std::vector<unsigned short> typeList;
typedef typeList::iterator typeListIt;
typedef typeList::const_iterator typeListCIt;
typedef std::map<unsigned short, typeList> Type2List;
typedef Type2List::iterator Type2ListIt;




class ExtPrefixPDUForwardingTable : public IntPrefixPDUForwardingTable
{
  public:
    ExtPrefixPDUForwardingTable();

    void clean();
    RMTPort* lookup(Address& destAddr, unsigned short QoSid);
    RMTPort* lookup(Address& destAddr);
    RMTPort* lookup(const std::string& destAddr, const unsigned short &QoSid);
    RMTPort* lookup(const std::string& destAddr);

    void printAll();

    void setDelimiter(char _delimiter);
    void addEntry(std::string dstAddr, unsigned short QoSid, RMTPort* p);
    void addEntryIfNot(std::string dstAddr, unsigned short QoSid, RMTPort* p);
    void remove(std::string dstAddr, unsigned short QoSid);
    void remove(std::string dstAddr);

  protected:
    FWDTable table;
    Type2List qos2Valid;
    unsigned short beQoSId;

    RMTPort * search(const std::string & pref, const unsigned short & QoSid, const typeList * accepted);

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void finish();
};

#endif
