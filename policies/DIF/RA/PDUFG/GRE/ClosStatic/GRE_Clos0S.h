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

#pragma once

#include "DIF/RA/PDUFG/IntPDUFG.h"
#include "DIF/RMT/PDUForwarding/GREFWD/Clos/Clos.h"

#include "DIF/RMT/PDUForwarding/IntMMForwarding.h"
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"

#include <map>
#include <set>

namespace GRE_Clos {

using namespace GRE;
using namespace std;

typedef unsigned short mType;

class GRE_ClosS0: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address & addr, const QoSCube & qos, port_t port);
    virtual void removedFlow(const Address & addr, const QoSCube & qos, port_t port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

    void resetNeiGroups();

    Clos0 * fwd;

    map<addr_t, set<port_t> > neiPorts;
    map<addr_t, port_t > neiPortsCurrent;

    index_t f;
    string rawAddr;
    addr_t myaddr, zone;
    vector<bool> aliveNeis;
};

}
