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

#ifndef __RINA_PDUFTGUPDATE_H
#define __RINA_PDUFTGUPDATE_H

#include <omnetpp.h>

#include "Address.h"
#include "PDUFTGInfo.h"

// Updates exchanged by the PDUFTG modules.
//
class PDUFTGUpdate :
        public cObject
{
protected:

    // The address of the ipc which will receive such information.
    //
    Address dstAddr;

    // The address of the ipc which will send such information.
    //
    Address srcAddr;

    // The transmitted information.
    //
    std::list<PDUFTGInfo *> * info;

    // Free info data.
    void disposeInfo();

public:

    PDUFTGUpdate();
    PDUFTGUpdate(Address from, Address to, std::list<PDUFTGInfo *> * info);
    ~PDUFTGUpdate();

    // Getters.

    Address getDestination();
    std::list<PDUFTGInfo *> *  getInfo();
    Address getSource();

    // Setters.

    void setDestination(Address addr);
    // This will create a copy of the list instead of addressing the passed one.
    void setInfo(std::list<PDUFTGInfo *> * info);
    void setSource(Address src);
};

#endif // __RINA_PDUFTGUPDATE_H
