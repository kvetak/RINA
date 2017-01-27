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

#ifndef __PORTSLOADMONITOR_H
#define __PORTSLOADMONITOR_H

// Comment to remove the enhanced debugging.
//#define PORTSLOADMONITOR_ENHANCED_DEBUG

#include "DIF/RMT/Monitor/RMTQMonitorBase.h"
#include "DIF/RMT/RMTModuleAllocator.h"

// Will map (link --> input + output bytes).
typedef std::map<RMTPort *, int64_t> PortsMap;
// Single entry of the map.
typedef std::pair<RMTPort *, int64_t> PMElem;
// Simply iterator over the map.
typedef PortsMap::iterator PMIter;

// This policy will be in charge of monitoring the receiving/transmission rates
// for the IPC process.
//
class PortsLoadMonitor : public RMTQMonitorBase
{
private:

    // Pointer to the RMT module allocator to resolve queue --> port matching.
    RMTModuleAllocator * rmtA;

    // Accumulation map.
    PortsMap acc;
    // Rates map.
    PortsMap rates;

#ifdef PORTSLOADMONITOR_ENHANCED_DEBUG
    void enhancedDebug();
#endif

protected:

    // Timed operation are handled here.
    virtual void handleMessage(cMessage* msg);

    // Initialization operations.
    virtual void onPolicyInit();

public:

    // Get the load of the port.
    // 0 if no traffic has been detected or if the port does not exists.
    int64_t getByteRate(RMTPort * port);

    // A PDU arrived.
    virtual void postPDUInsertion(RMTQueue* queue);

    // A PDU departed; when this procedure is invoked then the PDU has already
    // left the queue.
    virtual void prePDURelease(RMTQueue* queue);
};

#endif // __PORTSLOADMONITOR_H
