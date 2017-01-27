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

#ifndef __PORTSLOADGENERATOR_H
#define __PORTSLOADGENERATOR_H

#include "DIF/RA/PDUFG/IntPDUFG.h"
#include "DIF/RMT/Monitor/PortsLoadMonitor/PortsLoadMonitor.h"
#include "DIF/RMT/PDUForwarding/SimpleTable/SimpleTable.h"
#include "DIF/Routing/PortsLoadRouting/IntPortsLoadRouting.h"

#include <map>
#include <set>

#define SCALE_BYTES(x)   (x)
// Comment it to remove the visual debugging.
#define PORTSLOADGENERATOR_ENHANCED_DEBUG

typedef std::set<RMTPort*> PortsSet;
typedef std::map<std::string, PortsSet> Nentries;
typedef std::map<std::string, Nentries> NTable;

typedef PortsSet::iterator PortsSetIt;
typedef Nentries::iterator NentriesIt;
typedef NTable::iterator NTableIt;

//
// Structures necessary to remember the rates and avoid continue
// routing update.
//

typedef std::map<std::string, unsigned short> QosToRateMap;
typedef std::map<std::string, QosToRateMap> RateMap;

typedef QosToRateMap::iterator QTRIter;
typedef RateMap::iterator RateIter;

// Provides an maintain updated the neighbor state according to the link load
// on them.
class PortsLoadGenerator : public IntPDUFG
{
public:

    // A new port has been inserted to another node.
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    // A previous existing port has been deleted.
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    // Routing policy signal an update.
    virtual void routingUpdated();

protected:

    // Handles messages directed to this module.
    virtual void handleMessage(cMessage *msg);

    // Policy initialization steps.
    virtual void onPolicyInit();

private:
    DA * difA;
    SimpleTable::SimpleTable * fwd;
    IntPortsLoadRouting * rt;
    PortsLoadMonitor * rmtp;
    NTable neighbours;

    // Cache for the rates of the local ports.
    RateMap rateCache;

    // Time between a link load check and another.
    int rtInt;
    // Time between a route update and another.
    int upInt;

    // Does the entry in exists in cache?
    bool rateCacheEntryExists(std::string dest, std::string qos);
};

#endif // __PORTSLOADGENERATOR_H
