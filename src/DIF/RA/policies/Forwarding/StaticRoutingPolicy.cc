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

#include "StaticRoutingPolicy.h"
#include "PDUFwdTabGenerator.h"
#include "FSUpdateInfo.h"

Define_Module(StaticRoutingPolicy);

/*
 * Class constructor/destructors stuff.
 */

StaticRoutingPolicy::StaticRoutingPolicy()
{

}

StaticRoutingPolicy::~StaticRoutingPolicy()
{
    // Do nothing...
}

/*
 * Class procedures sorted by name.
 */

void StaticRoutingPolicy::computeForwardingTable()
{
    if(!fwdtg)
    {
        EV << "For Forwarding Table Generator selected in Static Routing Policy. Did you call empty constructor?\n";
        return;
    }

    NeighborState * m = fwdtg->getNeighborhoodState();

    for(EIter it = m->begin(); it != m->end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        fwdtg->getForwardingTable()->insert(
            e->getDestAddr(),
            e->getQosId(),
            e->getPort());
    }
}

void StaticRoutingPolicy::handleMessage(cMessage *msg)
{
    // Do nothing...
}

void StaticRoutingPolicy::initialize()
{
    PDUFTGPolicy::initialize();

    /* This avoid the start of update timeout. */
    updateT = 0;
}

void StaticRoutingPolicy::insertNewFlow(Address addr, short unsigned int qos, RMTPort * port)
{
    /* Direct insert the entry into the forwarding table. */
    fwdtg->getForwardingTable()->insert(addr, qos, port);
}

void StaticRoutingPolicy::mergeForwardingInfo(FSUpdateInfo * info)
{
    // Do nothing...
}

void StaticRoutingPolicy::removeFlow(Address addr, short unsigned int qos)
{
    fwdtg->getForwardingTable()->remove(addr, qos);
}
