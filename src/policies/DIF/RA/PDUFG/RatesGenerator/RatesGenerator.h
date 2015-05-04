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

#ifndef __RATEGENERATOR_H
#define __RATEGENERATOR_H

#include <IntPDUFG.h>
#include <Monitor/RatesMonitor/RatesMonitor.h>
#include <SimpleTable/SimpleTable.h>
#include <SimpleRouting/IntSimpleRouting.h>

#include <map>
#include <set>

#define SCALE_BYTES(x)   (x / 1024)
// Comment it to remove the visual debugging.
#define RATESGENERATOR_ENHANCED_DEBUG

typedef std::set<RMTPort*> PortsSet;
typedef std::map<unsigned short, PortsSet> Nentries;
typedef std::map<std::string, Nentries> NTable;

typedef PortsSet::iterator PortsSetIt;
typedef Nentries::iterator NentriesIt;
typedef NTable::iterator NTableIt;

//
// Structures necessary to remember the rates and avoid continue
// routing update.
//

typedef std::map<unsigned short, unsigned short> QosToRateMap;
typedef std::map<std::string, QosToRateMap> RateMap;

typedef QosToRateMap::iterator QTRIter;
typedef RateMap::iterator RateIter;

// Provides an maintain updated the neighbor state according to the link load
// on them.
class RatesGenerator: public IntPDUFG
{
public:

    // A new port has been inserted to another node.
    virtual void insertedFlow(const Address &addr, const unsigned short &qos, RMTPort * port);

    // A previous existing port has been deleted.
    virtual void removedFlow(const Address &addr, const unsigned short &qos, RMTPort * port);

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
    IntSimpleRouting * rt;
    RatesMonitor * rmtp;
    NTable neighbours;

    // Cache for the rates.
    RateMap rateCache;

    // Time between a link load check and another.
    int interval;

    // Does the entry in exists in cache?
    bool rateCacheEntryExists(std::string dest, unsigned short qos);
};

#endif // __RATEGENERATOR_H
