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

#include "DistanceVectorPolicy.h"
#include "PDUFwdTabGenerator.h"
#include "FSUpdateInfo.h"

Define_Module(DistanceVectorPolicy);

/*
 * Class constructor/destructors stuff.
 */

DistanceVectorPolicy::DistanceVectorPolicy()
{

}

DistanceVectorPolicy::~DistanceVectorPolicy()
{
    // Do nothing...
}

/*
 * Class procedures sorted by name.
 */

void DistanceVectorPolicy::computeForwardingTable()
{
    if(!fwdtg)
    {
        return;
    }

    NetworkState * netState = fwdtg->getNetworkState();
    NeighborState * neiState = fwdtg->getNeighborhoodState();

    /* So, when we need to build up the forwarding table from scratch then
     * we start from our neighbors alone.
     */

    /* Maintain only information about the neighborhood. */
    for(NIter it = netState->begin(); it != netState->end(); ++it )
    {
        bool rem = false;
        FSInfo * i = (*it);

        for(EIter et = neiState->begin(); et != neiState->end(); ++et )
        {
            PDUForwardingTableEntry * e = (*et);

            /* It's not a neighbor. */
            if(!(e->getDestAddr() == i->getDestination()))
            {
                rem = true;
                break;
            }
            /* It's a neighbor! Repopulate the forwarding table. */
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

std::list<FSUpdateInfo *> * DistanceVectorPolicy::getNetworkState()
{
    //NetworkState * netState  = fwdtg->getNetworkState();
    NeighborState * neiState = fwdtg->getNeighborhoodState();

    std::list<FSUpdateInfo *> * ret = new std::list<FSUpdateInfo *>();

    for(EIter it = neiState->begin(); it != neiState->end(); ++it )
    {
        PDUForwardingTableEntry * e = (*it);

        ret->push_back(prepareFSUpdate(e->getDestAddr()));
    }

    return ret;
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
                PDUForwardingTableEntry * info = (*it);

                // Finally send the update.
                fwdtg->signalForwardingInfoUpdate(
                    new FSUpdateInfo(
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
    /* Display active policy name. */
    PDUFTGPolicy::initialize();

    /* Default timeout 30 seconds. */
    setUpdateTimeout(30);

    /* Start the forwarding update timer routine. */
    scheduleAt(
        simTime() + getUpdateTimeout(),
        new cMessage("FwdTimerInit", PDUFTG_SELFMSG_FSUPDATE));
}

void DistanceVectorPolicy::insertNewFlow(Address addr, short unsigned int qos, RMTPort * port)
{
    /* Callable from other modules. */
    Enter_Method("insertNewFlow()");

    if(!fwdtg)
    {
        return;
    }

    Address ipcaddr = fwdtg->getIpcAddress();

    /* Assign a metric in the newly inserted flow... */
    FSInfo * i = fwdtg->netInfoExists(ipcaddr, addr,qos);
    /* This flow has hop 1 because it's a neighbor. */
    i->setMetric(1);

    /* Add the entry in the table. */
    fwdtg->getForwardingTable()->insert(addr, qos, port);
}

void DistanceVectorPolicy::mergeForwardingInfo(FSUpdateInfo * info)
{
    NetworkState * arrived = info->getInfo();

    /* Scan the arrived informations. */
    for(NIter i = arrived->begin(); i != arrived->end(); ++i)
    {
        bool insert = false;

        FSInfo * eval = (*i);
        /* Info here are stored with us as source. */
        FSInfo * info = fwdtg->netInfoExists(
            fwdtg->getIpcAddress(),
            eval->getDestination(),
            eval->getQoSID());

        /* Do not consider info over yourself. */
        if(eval->getDestination().getApname().getName() ==
            fwdtg->getIpcAddress().getApname().getName())
        {
            continue;
        }

        /* We already have such information. */
        if(info)
        {
            /* It's a better metric? */
            if(eval->getMetric() + 1 < info->getMetric())
            {
                fwdtg->getForwardingTable()->remove(info->getDestination(), info->getQoSID());
                fwdtg->removeNetInfo(info);

                insert = true;
            }
        }
        else
        /* The info does not exists. */
        {
            insert = true;
        }

        if(insert)
        {
            /* It's a better metric; pass through this sender from now on... */
            PDUForwardingTableEntry * en = fwdtg->neighborExists(eval->getSource());

            if(!en)
            {
                EV << "Could not reach " << eval->getDestination() << " from " << fwdtg->getIpcAddress().getApname().getName() << "???\n";
                continue;
            }

            RMTPort * p = en->getPort();

            /* Insert the entry into the tables. */
            fwdtg->insertNetInfo(eval->getDestination(), eval->getQoSID(), p, eval->getMetric() + 1);
            fwdtg->getForwardingTable()->insert(eval->getDestination(), eval->getQoSID(), p);
        }
    }

    EV << "Actual state of the network information table:\n" << fwdtg->netInfo();
}

FSUpdateInfo * DistanceVectorPolicy::prepareFSUpdate(Address destination)
{
    FSUpdateInfo * ret = new FSUpdateInfo();
    Address a = fwdtg->getIpcAddress();

    ret->setSource(a);
    ret->setDestination(destination);
    ret->setInfo(fwdtg->getNetworkState());

    return ret;
}

void DistanceVectorPolicy::removeFlow(Address addr, short unsigned int qos)
{
    //if(!fwdtg)
    //{
    //    return;
    //}
}
