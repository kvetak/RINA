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

#ifndef __RINA_PDUFTGPOLICY_H
#define __RINA_PDUFTGPOLICY_H

#include <omnetpp.h>

#include "Flow.h"
#include "RMTPort.h"
#include "PDUFTGUpdate.h"

// Forwarding declaration.
class PDUFwdTabGenerator;

// Provides a base class for every policy used in the PDUFTG module.
//
class PDUFTGPolicy :
        public cSimpleModule
{
private:

protected:
    PDUFwdTabGenerator * fwdtg;

    void handleMessage(cMessage *msg);
    void initialize();

public:
    PDUFTGPolicy();
    ~PDUFTGPolicy();

    // Computes the initial state of the forwarding table.
    //
    virtual void computeForwardingTable();

    // Evaluated in term of policy defined flow if a flow exists.
    //
    virtual PDUFTGInfo * flowExists(Address addr, unsigned short qos);

    // Insert a new flow which has been open locally to this IPC Process.
    //
    virtual void insertNewFlow(Address addr, unsigned short qos, RMTPort * port);

    // Merge an incoming information with the existing ones.
    //
    virtual void mergeForwardingInfo(PDUFTGUpdate * info);

    // Removes a local opened flow.
    //
    virtual void removeFlow(Address addr, unsigned short qos);
};

#endif // __PDUFTGPOLICY_H
