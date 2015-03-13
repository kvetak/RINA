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

#ifndef __RINA_IntPrefixPDUForwardingTable_H_
#define __RINA_IntPrefixPDUForwardingTable_H_

#include <omnetpp.h>
#include <string>

#include "IntPDUForwardingTable.h"

class IntPrefixPDUForwardingTable : public IntPDUForwardingTable
{
  public:
    virtual void clean() = 0;
    virtual RMTPort* lookup(Address& destAddr, unsigned short QoSid) = 0;
    virtual RMTPort* lookup(Address& destAddr) = 0;
    virtual RMTPort* lookup(const std::string &destAddr, const unsigned short &QoSid) = 0;
    virtual RMTPort* lookup(const std::string &destAddr) = 0;

    virtual void printAll() = 0;

    virtual void setDelimiter(char _delimiter) = 0;
    virtual void addEntry(std::string dstAddr, unsigned short QoSid, RMTPort* p) = 0;
    virtual void addEntryIfNot(std::string dstAddr, unsigned short QoSid, RMTPort* p) = 0;
    virtual void remove(std::string dstAddr, unsigned short QoSid) = 0;
    virtual void remove(std::string dstAddr) = 0;

  protected:
    char delimiter;

    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
};

#endif
