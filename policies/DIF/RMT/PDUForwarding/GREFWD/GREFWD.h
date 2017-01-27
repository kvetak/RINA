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

#pragma once

#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"
#include "DIF/RMT/PDUForwarding/GREFWD/GRE_Helpers.h"

namespace GRE {

using namespace std;

class GREFWD: public IntPDUForwarding {
public:
    // Lookup functions for PDU and destination
    // Instead of a cache, it provides the same paths using a "hash" of the flow instead of random values for decisions
    vPorts lookup(const PDU * pdu);
    vPorts lookup(const Address &dst, const std::string& qos);

    // Setting group i, ensures that all groups j<i are at least created (list exists)
    // Group 0 is reserved for "ANY", should not be used
    // Unsetting group i by default clears it lists and only remove it if there are no groups j > i
    void setGroup(const index_t & groupId, const vPortsIndex & neis);
    void unsetGroup(const index_t & groupId);

    // Add or remove mappings between neighbour addresses and their port index
    void setNeighbour(const addr_t dst, const index_t & index);
    void unsetNeighbour(const addr_t dst);

    // Setting or unsetting port i, ensures that all ports j<=i are at least reserved (null)
    // Unsetting port i only makes it null, note removes it from the list of ports
    void addPort(const index_t & index, const port_t port);
    void removePort(const index_t & index);

    //Adding or removing exceptions
    void addException(const mask_t & mask, const exception_t & e);
    void setExceptions(const map<mask_t, exception_t> & _exceptions);
    void removeException(const mask_t & mask);

protected:
    // Setting own address - post
    void onPolicyInit();
    // * Virtual function for extra init
    virtual void postPolicyInit() {};

    // pre - Clear info
    void finish();
    // * Virtual function for extra finish
    virtual void preFinish() {};

    // Query for next hop given destination address and "flow hash"
    port_t getNext(const addr_t & a, const rand_t & r);

    // * Virtual function for printing useful info
    virtual string toString();

    // Address of the node
    addr_t myaddr;

    // List of output ports
    vPorts ports;

    // List of port groups
    // groups[0] reserved for any
    vector<vPortsIndex> groups;

    // Mapping from neighbour address to port index
    map<addr_t, index_t> neiId;

    // Query if a node address is a neighbour and for neighbour port index
    // * Virtual function, optional rule based decision
    virtual bool isNeighbour(const addr_t & a) { return neiId.find(a) != neiId.end(); };
    virtual index_t getNeighbourId(const addr_t & a) { return neiId[a]; };

    //Exceptions, forwarding table with groups and inverse storage
    map<mask_t, exception_t> exceptions;

    // Query for the best exception for a given address
    // null if no exception found
    exception_p getException(const addr_t & a);

    // * Virtual function for computing possible out ports
    // Default rule : not found (*,*,0)
    virtual grouprange_t execRule(const addr_t & a) { return grouprange_t(0,0,0); }
};

}
