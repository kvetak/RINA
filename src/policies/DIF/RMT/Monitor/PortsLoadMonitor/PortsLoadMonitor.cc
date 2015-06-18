//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
//
// NOTE:The procedures are sorted by name.

#define RATESMONITOR_SELFMSG "RMT_MonitorPolicy_PortsLoad"

#include <stdio.h>
#include <PortsLoadMonitor.h>

Define_Module(PortsLoadMonitor);

#ifdef PORTSLOADMONITOR_ENHANCED_DEBUG
void PortsLoadMonitor::enhancedDebug()
{
    std::ostringstream str;

    for(PMIter i = rates.begin(); i != rates.end(); ++i)
    {
        str << i->first->info() << ", " << i->second << "\n";
    }

    EV << "***** Loads on ports *****" << endl << str.str();

    if(ev.isGUI())
    {
        cModule * ipcm = check_and_cast<cModule *>(getModuleByPath("^.^.^"));
        cDisplayString & cs = ipcm->getDisplayString();

        cs.setTagArg("t", 1, "l");
        cs.setTagArg("t", 0, str.str().c_str());
    }
}
#endif

int64 PortsLoadMonitor::getByteRate(RMTPort * port)
{
    PMIter i = rates.find(port);

    // Be sure that the key exists.
    if(i != rates.end())
    {
        return i->second;
    }

    // Error value.
    return 0;
}

void PortsLoadMonitor::handleMessage(cMessage* msg)
{
    // Only consider messages which you send to yourself.
    if(msg->isSelfMessage())
    {
        // Save the current rate and reset every entry in the accumulation map.
        for(PMIter i = acc.begin(); i != acc.end(); ++i)
        {
            //EV << "New rate computed: " << i->first->info() << " have " << i->second << endl;
            rates[i->first] = i->second;
            i->second = 0;
        }

#ifdef PORTSLOADMONITOR_ENHANCED_DEBUG
        enhancedDebug();
#endif

        // Renew the rate scheduling.
        scheduleAt(simTime() + 1, new cMessage(RATESMONITOR_SELFMSG));
    }
}

void PortsLoadMonitor::onMessageArrival(RMTQueue* queue)
{
    // Get the arrived message.
    const cPacket * pdu = queue->getLastPDU();
    RMTPort * port = 0;

    if(!rmtA)
    {
        EV << "[Rate monitor policy] ERROR: "
            "No RMT allocator detected.";

        return; // Exit before crashing all.
    }

    port = rmtA->getQueueToPortMapping(queue);

    if(!port)
    {
        EV << "[Rate monitor policy] ERROR: "
            "Could not resolve the queue.";

        return; // Exit before crashing all.
    }

    // Accumulates the bytes. Input and output usage is accumulated
    // together.
    acc[port] += pdu->getByteLength();
}

void PortsLoadMonitor::onMessagePreDeparture(RMTQueue* queue)
{
    // Get the departing message.
    const cPacket * pdu = queue->getFirstPDU();
    RMTPort * port = 0;

    if(!rmtA)
    {
        EV << "[Rate monitor policy] ERROR: "
            "No RMT allocator detected.";

        return; // Exit before crashing all.
    }

    port = rmtA->getQueueToPortMapping(queue);

    if(!port)
    {
        EV << "[Rate monitor policy] ERROR: "
            "Could not resolve the queue.";

        return; // Exit before crashing all.
    }

    // Accumulates the bytes. Input and output usage is accumulated
    // together.
    acc[port] += pdu->getByteLength();
}

void PortsLoadMonitor::onPolicyInit()
{
    // Get a pointer to the allocator.
    rmtA = check_and_cast<RMTModuleAllocator *>(
        getModuleByPath("^.allocator"));

    // Just activate the rate scheduling.
    scheduleAt(simTime() + 1, new cMessage(RATESMONITOR_SELFMSG));
}
