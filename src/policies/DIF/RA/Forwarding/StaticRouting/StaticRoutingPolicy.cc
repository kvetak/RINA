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
#include "PDUFTGUpdate.h"

Define_Module(StaticRoutingPolicy);

//
// Class constructor/destructors stuff.
//

StaticRoutingPolicy::StaticRoutingPolicy()
{
    // Do nothing...
}

StaticRoutingPolicy::~StaticRoutingPolicy()
{
    // Do nothing...
}

//
// Class procedures sorted by name.
//

void StaticRoutingPolicy::computeForwardingTable()
{
    NeighborState * m = fwdtg->getNeighborhoodState();

    for(EIter it = m->begin(); it != m->end(); ++it )
    {
        PDUFTGNeighbor * e = (*it);

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

    difA = check_and_cast<DA *>(
        getModuleByPath("^.^.^.difAllocator.da"));
}

void StaticRoutingPolicy::insertNewFlow(Address addr, short unsigned int qos, RMTPort * port)
{
    // Direct insert the entry into the forwarding table.
    fwdtg->getForwardingTable()->insert(addr, qos, port);

    //
    // Imported from RA to clean the code from policy oriented procedures.
    // This little loop make possible for static routing APs to communicate
    // with each other, using resolution with DA magic procedures.
    //

    const APNList* remoteApps = difA->findNeigborApns(addr.getApname());
    NM1FlowTableItem * item = fwdtg->getNM1FlowTable()->findFlowByDstApni(
        addr.getApname().getName(),
        qos);

    if (remoteApps)
    {
        for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it)
        {
            Address addr = Address(it->getName());
            fwdtg->getForwardingTable()->insert(
                addr,
                qos,
                item->getRmtPort());
        }
    }
}

void StaticRoutingPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{
    // Do nothing...
}

void StaticRoutingPolicy::removeFlow(Address addr, short unsigned int qos)
{
    fwdtg->getForwardingTable()->remove(addr, qos);
}
