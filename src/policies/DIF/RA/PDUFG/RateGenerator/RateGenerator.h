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

#define MBS_FROM_BYTES(x)   (x / 1024)
// Comment it to remove the visual debugging.
#define RATEGENERATOR_ENHANCED_DEBUG

typedef std::set<RMTPort*> PortsSet;
typedef std::map<unsigned short, PortsSet> Nentries;
typedef std::map<std::string, Nentries> NTable;

typedef PortsSet::iterator PortsSetIt;
typedef Nentries::iterator NentriesIt;
typedef NTable::iterator NTableIt;

// Provides an maintain updated the neighbor state according to the link load
// on them.
class RateGenerator: public IntPDUFG
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

    // Ploicy initialization steps.
    virtual void onPolicyInit();

private:
    DA * difA;
    SimpleTable::SimpleTable * fwd;
    IntSimpleRouting * rt;
    RatesMonitor * rmtp;

    NTable neighbours;
};

#endif // __RATEGENERATOR_H
