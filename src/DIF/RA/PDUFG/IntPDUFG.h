// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef PDUFTG_H_
#define PDUFTG_H_

#include <omnetpp.h>

#include "DIF/RA/PDUFG/PDUFGNeighbor.h"
#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"
#include "DAF/DA/DA.h"
#include "Common/QoSCube.h"

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
    void insertFlowInfo(Address addr, QoSCube qos, RMTPort * port);
    // Removes an existing flow from the existing ones.
    void removeFlowInfo(RMTPort * port);

    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port) = 0;
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port) = 0;

    //Routing has processes a routing update
    virtual void routingUpdated() = 0;

protected:
    // Contains the list of N-DIF neighbors of this IPC Address.
    //
    NeighborState neiState;
    Address ipcAddr;

    // Initialize.
    void initialize();

    // Called after initialize
    virtual void onPolicyInit() = 0;

private:
    IntPDUForwarding * fwd;
};

#endif /* PDUFTG_H_ */
