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

#include "DistanceVectorPolicy.h"
#include "PDUFwdTabGenerator.h"
#include "PDUFTGUpdate.h"
#include "DVPInfo.h"

Define_Module(DistanceVectorPolicy);

//
// Class constructor/destructors stuff.
//

DistanceVectorPolicy::DistanceVectorPolicy()
{

}

DistanceVectorPolicy::~DistanceVectorPolicy()
{
    // Do nothing...
}

//
// Class procedures sorted by name.
//

void DistanceVectorPolicy::computeForwardingTable()
{
    if(!fwdtg)
    {
        return;
    }

    NetworkState * netState = fwdtg->getNetworkState();
    NeighborState * neiState = fwdtg->getNeighborhoodState();

    // So, when we need to build up the forwarding table from scratch then
    // we start from our neighbors alone.
    //

    // Maintain only information about the neighborhood.
    for(NIter it = netState->begin(); it != netState->end(); ++it )
    {
        bool rem = false;

        DVPInfo * i = (DVPInfo *)(*it);

        for(EIter et = neiState->begin(); et != neiState->end(); ++et )
        {
            PDUFTGNeighbor * e = (*et);

            // It's not a neighbor.
            if(!(e->getDestAddr() == i->getDestination()))
            {
                rem = true;
                break;
            }
            // It's a neighbor! Repopulate the forwarding table.
            else
            {
                fwdtg->getForwardingTable()->insert(e->getDestAddr(), e->getQosId(), e->getPort());
            }
        }

        if(rem)
        {
            // Remove this information from our network state.
            netState->remove(i);
        }
    }
}

PDUFTGInfo * DistanceVectorPolicy::flowExists(Address addr, unsigned short qos)
{
    for(NIter it = fwdtg->getNetworkState()->begin(); it != fwdtg->getNetworkState()->end(); ++it )
    {
        DVPInfo * fsi = (DVPInfo * )(*it);

        // Equal condition; same source reach same destination with same qos constrain.
        if(fsi->getDestination() == addr &&
            fsi->getQoSID() == qos)
        {
            return fsi;
        }
    }

    return NULL;
}

unsigned int DistanceVectorPolicy::getUpdateTimeout()
{
    return updateT;
}

void DistanceVectorPolicy::handleMessage(cMessage *msg)
{
    NeighborState * n;

    if(msg->isSelfMessage())
    {
        switch(msg->getKind())
        {
        case PDUFTG_SELFMSG_FSUPDATE:
            /* Stop condition. */
            if(getUpdateTimeout() == 0)
            {
                break;
            }

            n = fwdtg->getNeighborhoodState();

            for(EIter it = n->begin(); it != n->end(); ++it)
            {
                PDUFTGNeighbor * info = (*it);

                // Finally send the update.
                fwdtg->signalForwardingInfoUpdate(
                    new PDUFTGUpdate(
                        fwdtg->getIpcAddress(),
                        info->getDestAddr(),
                        fwdtg->getNetworkState()));
            }

            scheduleAt(
                simTime() + getUpdateTimeout(),
                new cMessage("UpdateRequested", PDUFTG_SELFMSG_FSUPDATE));

            break;
        default:
            break;
        }

        delete msg;
    }
}

void DistanceVectorPolicy::initialize()
{
    // Display active policy name.
    PDUFTGPolicy::initialize();

    // Default timeout 30 seconds.
    setUpdateTimeout(par("updateTimeout"));

    // Start the forwarding update timer routine.
    scheduleAt(
        simTime() + getUpdateTimeout(),
        new cMessage("FwdTimerInit", PDUFTG_SELFMSG_FSUPDATE));
}

void DistanceVectorPolicy::insertNewFlow(Address addr, short unsigned int qos, RMTPort * port)
{
    // Callable from other modules.
    Enter_Method("insertNewFlow()");

    if(!fwdtg)
    {
        return;
    }

    // We're interested in flows to element of my DIF.
    if(addr.getDifName() == fwdtg->getIpcAddress().getDifName())
    {
        DVPInfo * flowInfo;

        flowInfo = (DVPInfo *)flowExists(addr, qos);

        // Flow present? Strange!!!
        if(flowInfo)
        {
            pduftg_debug("Flow for " << addr << " already present!");
        }

        flowInfo = new DVPInfo(
            fwdtg->getIpcAddress(),
            addr,
            qos,
            1);

        // Update the network state too.
        fwdtg->getNetworkState()->push_back(flowInfo);

        // Insert what you consider a neighbor.
        fwdtg->insertNeighbor(addr, qos, port);

        // Add the entry in the table.
        fwdtg->getForwardingTable()->insert(addr, qos, port);

        // Debug the actual state of the network.
        pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
            fwdtg->netInfo());
    }
}

void DistanceVectorPolicy::mergeForwardingInfo(PDUFTGUpdate * info)
{
    NetworkState * arrived = info->getInfo();

    // Scan the arrived informations.
    for(NIter i = arrived->begin(); i != arrived->end(); ++i)
    {
        bool insert = false;

        DVPInfo * eval = (DVPInfo *)(*i);
        // Info here are stored with us as source.
        DVPInfo * info = (DVPInfo *)flowExists(
            eval->getDestination(),
            eval->getQoSID());

        // Do not consider info over yourself.
        if(eval->getDestination().getApname().getName() ==
            fwdtg->getIpcAddress().getApname().getName())
        {
            continue;
        }

        // We already have such information.
        if(info)
        {
            // It's a better metric?
            if(eval->getMetric() + 1 < info->getMetric())
            {
                fwdtg->getForwardingTable()->remove(info->getDestination(), info->getQoSID());
                removeFlow(eval->getDestination(), eval->getQoSID());

                insert = true;
            }
        }
        else
        // The info does not exists.
        {
            insert = true;
        }

        if(insert)
        {
            // It's a better metric; pass through this sender from now on...
            PDUFTGNeighbor * en = fwdtg->neighborExists(eval->getSource());

            if(!en)
            {
                EV << "Could not reach " << eval->getDestination() << " from " << fwdtg->getIpcAddress().getApname().getName() << "???\n";
                continue;
            }

            RMTPort * p = en->getPort();
            DVPInfo * newi = new DVPInfo(
                fwdtg->getIpcAddress(),
                eval->getDestination(),
                eval->getQoSID(),
                eval->getMetric() + 1);

            // Insert the entry into the tables.
            fwdtg->getNetworkState()->push_back(newi);
            fwdtg->getForwardingTable()->insert(eval->getDestination(), eval->getQoSID(), p);
        }
    }

    // Debug the actual state of the network.
    pduftg_debug(fwdtg->getIpcAddress().info() << "> " <<
        fwdtg->netInfo());
}

PDUFTGUpdate * DistanceVectorPolicy::prepareFSUpdate(Address destination)
{
    PDUFTGUpdate * ret = new PDUFTGUpdate();
    Address a = fwdtg->getIpcAddress();

    ret->setSource(a);
    ret->setDestination(destination);
    ret->setInfo(fwdtg->getNetworkState());

    return ret;
}

void DistanceVectorPolicy::removeFlow(Address addr, unsigned short qos)
{
    // Select the info with your information evaluation procedure.
    PDUFTGInfo * netinfo = flowExists(addr, qos);

    if(!netinfo)
    {
        fwdtg->getNetworkState()->remove(netinfo);
    }
}


void DistanceVectorPolicy::setUpdateTimeout(unsigned int sec)
{
    updateT = sec;
}
