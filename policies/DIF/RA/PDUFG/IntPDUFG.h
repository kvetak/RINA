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

#ifndef PDUFTG_H_
#define PDUFTG_H_

#include <omnetpp.h>

#include "PDUFGNeighbor.h"
#include "IntPDUForwarding.h"
#include "DA.h"

// This is mapped as string --> port because Address do not have <, > operators overloads.
typedef std::list<PDUFGNeighbor *> NeighborState;
typedef NeighborState::iterator EIter;


class IntPDUFG  : public cSimpleModule {
public:

    //Constructor/Destructor
    IntPDUFG();
    ~IntPDUFG();

    // Find the next known neighbor to reach the destination.
    virtual PDUFGNeighbor * getNextNeighbor(const Address &destination, const std::string& qos);

    //
    // Flow up/down operations:
    //

    // Inserts a new flow through which a neighbor can be reached.
    void insertFlowInfo(Address addr, std::string qos, RMTPort * port);
    // Removes an existing flow from the existing ones.
    void removeFlowInfo(RMTPort * port);

    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const std::string &qos, RMTPort * port) = 0;
    virtual void removedFlow(const Address &addr, const std::string &qos, RMTPort * port) = 0;

    //Routing has processes a routing update
    virtual void routingUpdated() = 0;

protected:
    // Contains the list of N-DIF neighbors of this IPC Address.
    //
    NeighborState neiState;

    // Initialize.
    void initialize();

    // Called after initialize
    virtual void onPolicyInit() = 0;

private:
    IntPDUForwarding * fwd;
};

#endif /* PDUFTG_H_ */
