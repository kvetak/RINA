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

#include "DIF/Routing/PortsLoadRouting/PortsLoadLS/PortsLoadRU.h"

PortsLoadRU::PortsLoadRU(
        const Address &_addr,
        const std::string &_qos):IntRoutingUpdate(_addr)
{
    qos = _qos;
}

std::string PortsLoadRU::getQoS()
{
    return qos;
}

void PortsLoadRU::addEntry(
        const std::string & id,
        linksU links)
{
    entries.insert(linksStEntry(id, links));
}

void PortsLoadRU::setEntries(
        linksSt _entries)
{
    entries = _entries;
}

linksStIt PortsLoadRU::entriesBegin()
{
    return entries.begin();
}
linksStIt PortsLoadRU::entriesEnd()
{
    return entries.end();
}
