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
 * @file PDUForwardingTableEntry.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief A class representing a single item of the forwarding table.
 * @detail
 */

#ifndef __RINA_PDUForwardingTableEntry_H_
#define __RINA_PDUForwardingTableEntry_H_

#include <omnetpp.h>
#include "RMTPort.h"

class PDUForwardingTableEntry
{
  public:
    PDUForwardingTableEntry();
    PDUForwardingTableEntry(Address& destaddr, unsigned short qosid, RMTPort* port);
    virtual ~PDUForwardingTableEntry();

    std::string info() const;

    const Address& getDestAddr() const;
    unsigned short getQosId() const;
    RMTPort* getPort() const;

  private:
    Address destAddr;
    unsigned short qosId;
    RMTPort* rmtPort;
};

std::ostream& operator<< (std::ostream& os, const PDUForwardingTableEntry& cte);

#endif

