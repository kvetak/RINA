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

#ifndef __RINA_PDUFTGINFO_H
#define __RINA_PDUFTGINFO_H

//Standard libraries
#include <omnetpp.h>
#include "Address.h"
#include "RMTPort.h"

// Provides a base for information exchanged during PDUFTG updates.
//
class PDUFTGInfo
{
protected:

    // Address of the info destination.
    // Usually a neighbor of the source.
    //
    Address dstAddr;

    // Weight of this connection depending on the metric used during
    // routing policy evaluation.
    //
    unsigned int metricWeight;

    // QoSID associated to the flow from source to destination.
    // For the moment this field is unused.
    //
    unsigned short QoSID;

    // Address of the info source.
    //
    Address srcAddr;

public:

    PDUFTGInfo();
    PDUFTGInfo(Address src, Address dst, unsigned short QoSID, unsigned int metric);
    ~PDUFTGInfo();

    // Getters.

    Address getDestination();
    unsigned int getMetric();
    short unsigned int getQoSID();
    Address getSource();


    // Setters.

    void setDestination(Address dest);
    void setMetric(unsigned int weight);
    void setQoSID(unsigned short id);
    void setSource(Address src);

    // Overloading of the == operator for element compare.
    //
    bool operator == (const PDUFTGInfo& info) const;
};

#endif // __RINA_PDUFTGINFO_H
