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
// NOTE: Procedures are sorted by name.

#include "DIF/RA/PDUFG/PortsLoadGenerator/PortsLoadGenerator.h"
#include "Common/APN.h"

#define PORTSLOAD_GENERATOR_TIMEOUT     "PDUFG_RateGenerator"
#define PORTSLOAD_GENERATOR_UPDATE      0
#define PORTSLOAD_GENERATOR_LOCAL       1

Define_Module(PortsLoadGenerator);

void PortsLoadGenerator::handleMessage(cMessage *msg)
{
    // React to self message only.
    if(msg->isSelfMessage())
    {

#ifdef PORTSLOADGENERATOR_ENHANCED_DEBUG
        std::ostringstream str;
#endif

        for(NTableIt t = neighbours.begin(); t != neighbours.end(); ++t)
        {
            for(NentriesIt e = t->second.begin(); e != t->second.end(); ++e)
            {
                for(
                        PortsSetIt p = e->second.begin();
                        p != e->second.end();
                        ++p)
                {
                    // Acquire the rate of the port.
                    unsigned short rate = (unsigned short)(SCALE_BYTES(
                        rmtp->getByteRate(*p)));
                    const Address addr =
                        Address((*p)->getFlow()->getDstApni().getApn().
                                getName());

#ifdef PORTSLOADGENERATOR_ENHANCED_DEBUG
                    str << t->first << ", " <<
                            SCALE_BYTES(rmtp->getByteRate(*p)) <<"\n";
#endif

                    // Do not update if the rate does not change.
                    if(rateCacheEntryExists(t->first, e->first))
                    {
                        if(rateCache[t->first][e->first] != rate)
                        {
                            rateCache[t->first][e->first] = rate;

                            // This do not cause an update to be dispatched.
                            rt->insertFlow(addr, t->first, e->first, rate, false);

                            EV << "Rate to " << t->first << ", " << e->first
                                    << " updated to " << rate << "." << endl;
                        }
                        else
                        {
                            EV << "Rate to " << t->first << ", " << e->first
                                    << " is the same(at " << rate << ")." << endl;
                        }
                    }
                    else
                    {
                        rateCache[t->first][e->first] = rate;

                        // This do not cause an update to be dispatched.
                        rt->insertFlow(addr, t->first, e->first, rate, false);

                        EV << "Rate to " << t->first << ", " << e->first
                                << " updated to " << rate << "." << endl;
                    }
                }
            }
        }

        // Update the fwd table using the local infos.
        routingUpdated();

#ifdef PORTSLOADGENERATOR_ENHANCED_DEBUG
        cModule * ipcm = check_and_cast<cModule *>(getModuleByPath("^.^.^"));
        cDisplayString & cs = ipcm->getDisplayString();
        cs.setTagArg("t", 1, "l");
        cs.setTagArg("t", 0, str.str().c_str());
#endif

        if(msg->getKind() == PORTSLOAD_GENERATOR_UPDATE)
        {
            rt->scheduleUpdate();

            // Schedule the next routing update.
            scheduleAt(
                simTime() + upInt,
                new cMessage(PORTSLOAD_GENERATOR_TIMEOUT, PORTSLOAD_GENERATOR_UPDATE));
        }
        else if(msg->getKind() == PORTSLOAD_GENERATOR_LOCAL)
        {
            // Schedule the next rate update.
            scheduleAt(
                simTime() + rtInt,
                new cMessage(PORTSLOAD_GENERATOR_TIMEOUT, PORTSLOAD_GENERATOR_LOCAL));
        }
    }
}

void PortsLoadGenerator::insertedFlow(
    const Address &addr,
    const QoSCube& qos,
    RMTPort * port)
{
    std::string dst = addr.getIpcAddress().getName();

    // Acquire the rate of the port.
    unsigned short rate = (unsigned short)SCALE_BYTES(
        rmtp->getByteRate(port));

    neighbours[dst][qos.getQosId()].insert(port);

    if(neighbours[dst][qos.getQosId()].size() == 1)
    {
        // Add to cache.
        rateCache[dst][qos.getQosId()] = rate;
        rt->insertFlow(addr, dst, qos.getQosId(), rate, true);

        routingUpdated();
    }
}

void PortsLoadGenerator::onPolicyInit()
{
    rtInt = par("rateInterval");
    upInt = par("updateInterval");

    // Obtain a pointer to the forwarding policy.
    fwd = check_and_cast<SimpleTable::SimpleTable *>(
        getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    // Obtain a pointer to the routing policy.
    rt = check_and_cast<IntPortsLoadRouting *>(
        getModuleByPath("^.^.routingPolicy"));

    // Obtain a pointer to the queue monitor policy.
    rmtp = check_and_cast<PortsLoadMonitor *>(
            getModuleByPath("^.^.relayAndMux.queueMonitorPolicy"));

    // Obtain a pointer to the DIF allocator module.
    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    // 0 means do not send periodic routing updates.
    if(upInt > 0)
    {
        // Start the route update timeout.
        scheduleAt(
            simTime() + upInt,
            new cMessage(PORTSLOAD_GENERATOR_TIMEOUT, PORTSLOAD_GENERATOR_UPDATE));
    }

    // 0 means do not do mix routing with local and remote info.
    // Use only routing updates.
    if(rtInt > 0)
    {
        // Start the rate updating timeout.
        scheduleAt(
            simTime() + rtInt,
            new cMessage(PORTSLOAD_GENERATOR_TIMEOUT, PORTSLOAD_GENERATOR_LOCAL));
    }
}

bool PortsLoadGenerator::rateCacheEntryExists(
    std::string dest,
    std::string qos)
{
    RateIter ri = rateCache.find(dest);

    // First level entry found.
    if(ri != rateCache.end())
    {
        QTRIter qi = ri->second.find(qos);

        // Second level entry found.
        if(qi != ri->second.end())
        {
            return true;
        }
    }

    return false;
}

void PortsLoadGenerator::removedFlow(
        const Address &addr,
        const QoSCube& qos,
        RMTPort * port)
{
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst][qos.getQosId()].erase(port);

    if(neighbours[dst][qos.getQosId()].size() <= 0)
    {
        neighbours[dst].erase(qos.getQosId());
        rt->removeFlow(addr, dst, qos.getQosId(), true);

        if(neighbours[dst].size() <= 0)
        {
            neighbours.erase(dst);
        }

        if(rateCacheEntryExists(dst, qos.getQosId()))
        {
            // Removes the entry from the cache.
            rateCache[dst].erase(qos.getQosId());
            rateCache.erase(dst);
        }

        routingUpdated();
    }
}

void PortsLoadGenerator::routingUpdated()
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
