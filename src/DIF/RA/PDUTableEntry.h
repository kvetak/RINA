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
 * @file PDUTableEntry.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief A class representing a single item of the forwarding table.
 * @detail
 */

#ifndef __RINA_PDUTABLEENTRY_H_
#define __RINA_PDUTABLEENTRY_H_

#include <iostream>
#include <vector>

#include <omnetpp.h>
#include "ConnectionTable.h"


class PDUTableEntry
{
  private:
    std::string destAddr;
    int qosId;
    std::string portId;

  public:
    PDUTableEntry();
    PDUTableEntry(std::string destaddr, int qosid, std::string portid);
    virtual ~PDUTableEntry();

    std::string info() const;

    std::string getDestAddr();
    int getQosId();
    std::string getPortId();

    void setDestAddr(std::string destaddr);
    void setQosId(int qosid);
    void setPortId(std::string portId);

};

std::ostream& operator<< (std::ostream& os, const PDUTableEntry& cte);

#endif

