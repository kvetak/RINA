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

#include <RateGenerator.h>
#include "APN.h"

#define RATE_GENERATOR_TIMEOUT  "PDUFG_RateGenerator"

Define_Module(RateGenerator);

#ifdef RATEGENERATOR_ENHANCED_DEBUGa
void RateGenerator::enhancedDebug()
{
    if(ev.isGUI())
    {
        //cModule * ipcm = check_and_cast<cModule *>(getModuleByPath("^.^.^"));
        //cDisplayString & cs = ipcm->getDisplayString();

        //cs.setTagArg("t", 1, "l");
        //cs.setTagArg("t", 0, fwd->toString().c_str());
    }

    EV << fwd->toString();
}
#endif

void RateGenerator::handleMessage(cMessage *msg)
{
    // React to self message only.
    if(msg->isSelfMessage())
    {
#ifdef RATEGENERATOR_ENHANCED_DEBUG
        std::ostringstream str;
#endif

        for(
            NTableIt t = neighbours.begin();
            t != neighbours.end();
            ++t)
        {
            for(
                NentriesIt e = t->second.begin();
                e != t->second.end();
                ++e)
            {
                for(
                    PortsSetIt p = e->second.begin();
                    p != e->second.end();
                    ++p)
                {
                    // Acquire the rate of the port.
                    unsigned short rate = (unsigned short)(MBS_FROM_BYTES(
                        rmtp->getByteRate(*p)));
                    const Address addr =
                        Address((*p)->getFlow()->getDstApni().getApn().getName());

#ifdef RATEGENERATOR_ENHANCED_DEBUG
                      str << t->first << ", " << rmtp->getByteRate(*p) <<"\n";
#endif

                    rt->insertFlow(addr, t->first, e->first, rate);
                }
            }
        }

#ifdef RATEGENERATOR_ENHANCED_DEBUG
        cModule * ipcm = check_and_cast<cModule *>(getModuleByPath("^.^.^"));
        cDisplayString & cs = ipcm->getDisplayString();
        cs.setTagArg("t", 1, "l");
        cs.setTagArg("t", 0, str.str().c_str());
#endif

        scheduleAt(simTime() + 0.5, new cMessage(RATE_GENERATOR_TIMEOUT));
    }
}

void RateGenerator::insertedFlow(
    const Address &addr,
    const unsigned short &qos,
    RMTPort * port)
{
    std::string dst = addr.getIpcAddress().getName();

    // Acquire the rate of the port.
    unsigned short rate = (unsigned short)MBS_FROM_BYTES(
        rmtp->getByteRate(port));

    neighbours[dst][qos].insert(port);

    if(neighbours[dst][qos].size() == 1)
    {
        rt->insertFlow(addr, dst, qos, rate);

        routingUpdated();
    }
}

// Called after initialize
void RateGenerator::onPolicyInit(){

    // Obtain a pointer to the forwarding policy.
    fwd = check_and_cast<SimpleTable::SimpleTable *>(
        getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    // Obtain a pointer to the routing policy.
    rt = check_and_cast<IntSimpleRouting *>(
        getModuleByPath("^.^.routingPolicy"));

    // Obtain a pointer to the queue monitor policy.
    rmtp = check_and_cast<RatesMonitor *>(
            getModuleByPath("^.^.relayAndMux.queueMonitorPolicy"));

    // Obtain a pointer to the DIF allocator module.
    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    // Start the rate updating timeout.
    scheduleAt(simTime() + 0.5, new cMessage(RATE_GENERATOR_TIMEOUT));
}

void RateGenerator::removedFlow(const Address &addr, const unsigned short &qos, RMTPort * port)
{
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst][qos].erase(port);

    if(neighbours[dst][qos].size() <= 0)
    {
        neighbours[dst].erase(qos);
        rt->removeFlow(addr, dst, qos);

        if(neighbours[dst].size() <= 0)
        {
            neighbours.erase(dst);
        }

        routingUpdated();
    }
}

void RateGenerator::routingUpdated()
{
    entries2Next changes = rt->getChanges();

    for(entries2NextIt it = changes.begin(); it!= changes.end(); it++)
    {
        qosPaddr dst = it->first;
        std::string nextHop = it->second;
        RMTPort * p = NULL;

        if(nextHop != "")
        {
            NTableIt n = neighbours.find(nextHop);

            if(n != neighbours.end())
            {
                NentriesIt pit = n->second.find(dst.first);

                if(pit != n->second.end())
                {
                    if(pit->second.size()>0)
                    {
                        p = *(pit->second.begin());
                    }
                }
            }
        }

        if(p == NULL)
        {
            fwd->remove(dst.second, dst.first);
        }
        else
        {
            fwd->insert(dst.second, dst.first, p);
        }
    }
}
