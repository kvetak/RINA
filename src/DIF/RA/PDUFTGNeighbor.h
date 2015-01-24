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

// Author: Kewin Rausch (kewin.rausch@create-net.org)

#ifndef __RINA_PDUFTGNEIGHBOR_H
#define __RINA_PDUFTGNEIGHBOR_H

#include <omnetpp.h>

#include "Address.h"
#include "RMTPort.h"

// How is considered a neighbor for the PDUFTG module.
//
class PDUFTGNeighbor
{
private:
    Address dstAddr;
    unsigned short qos;
    RMTPort * port;

public:
    PDUFTGNeighbor();
    PDUFTGNeighbor(Address dst, unsigned short qos, RMTPort * port);
    ~PDUFTGNeighbor();

    Address & getDestAddr();
    RMTPort* getPort();
    unsigned short getQosId();

    void setDestAddr(Address & dstAddr);
    void setPort(RMTPort* p);
    void setQosId(unsigned short qosId);
};

#endif
