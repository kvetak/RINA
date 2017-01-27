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

#ifndef __PORTSLOADRU_H
#define __PORTSLOADRU_H

#include <string>

#include "DIF/Routing/IntRoutingUpdate.h"
#include "DIF/Routing/PortsLoadRouting/PortsLoadLS/PLLSCommon.h"

class PortsLoadRU : public IntRoutingUpdate
{
public:
    PortsLoadRU(const Address &_addr, const std::string &_qos);

    std::string getQoS();

    void addEntry(const std::string &, linksU);
    void setEntries(linksSt);

    linksStIt entriesBegin();
    linksStIt entriesEnd();

protected:
    std::string qos;
    linksSt entries;
};

#endif // __PORTSLOADRU_H
