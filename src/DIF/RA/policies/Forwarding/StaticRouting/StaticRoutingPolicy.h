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

#ifndef __RINA_STATICROUTINGPOLICY_H
#define __RINA_STATICROUTINGPOLICY_H

#include <omnetpp.h>

#include "DA.h"
#include "PDUFTGPolicy.h"

// Static routing follows the operations already done by the first version of
// rinasim, when no forwarding of information existed. It simply update the
// Forwarding table during the flow creation.
//
// This policy does not apply any logic organization of the data received
// because it assumes that everything has been already done in the definition
// of the base data.
//
class StaticRoutingPolicy :
        public PDUFTGPolicy
{
private:
    DA * difA;

protected:
    void initialize();
    void handleMessage(cMessage *msg);

public:
    StaticRoutingPolicy();
    ~StaticRoutingPolicy();

    // Computes the initial state of the forwarding table.
    //
    void computeForwardingTable();

    // Insert a new flow which has been open locally to this IPC Process.
    //
    void insertNewFlow(Address addr, short unsigned int qos, RMTPort * port);

    // Merge an incoming information with the existing ones.
    //
    void mergeForwardingInfo(PDUFTGUpdate * info);

    // Removes a local opened flow.
    //
    void removeFlow(Address addr, short unsigned int qos);
};

#endif // __RINA_STATICROUTINGPOLICY_H
