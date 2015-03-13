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

/* Author: Kewin Rausch (kewin.rausch@create-net.org) */

#ifndef __RINA_DVPINFO_H
#define __RINA_DVPINFO_H

#include <omnetpp.h>

#include "PDUFTGInfo.h"

// Every policy can have additional information that want to share.
// If the offered base class is not enough, just extend like this the base information
// message and add your extra fields.
//
class DVPInfo :
        public PDUFTGInfo
{
protected:
    int dummy;

public:
    DVPInfo();
    DVPInfo(Address src, Address dst, unsigned short QoSID, unsigned int metric);
    ~DVPInfo();

    // Getters.
    int getDummy();


    // Setters.
    void setDummy(int d);
};

#endif
