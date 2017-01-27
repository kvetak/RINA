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
#include "DIF/Routing/eRouting/eRouting.h"
#include "Addons/Actions/FailureSimulation/FailureSimulation.h"

#include "DIF/RMT/PDUForwarding/IntMMForwarding.h"
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"

#include <map>
#include <set>
#include <string>

namespace GRE_Clos {

using namespace GRE;
using namespace std;

typedef unsigned short mType;

struct Errors {
    map<addr_t, map<addr_t, set<addr_t> > > PT2F;
    map<addr_t, map<addr_t, set<addr_t> > > PF2T;
    map<addr_t, map<addr_t, set<addr_t> > > PF2S;
    map<addr_t, map<addr_t, set<addr_t> > > FP2T;
    map<addr_t, map<addr_t, set<addr_t> > > FP2S;
    map<addr_t, map<addr_t, set<addr_t> > > FS2P;
    map<addr_t, set<addr_t> > F2P;
    map<addr_t, set<addr_t> > P2F;
    map<addr_t, vector<bool> > P;
};

class GRE_ClosR: public IntPDUFG, public FailureNode {
public:
    virtual void insertedFlow(const Address & addr, const QoSCube & qos, port_t port);
    virtual void removedFlow(const Address & addr, const QoSCube & qos, port_t port);

    virtual void routingUpdated();

    void killLink(const string & link);
    void resurrectLink(const string &  link);

    string getRaw(const addr_t & dst_addr);

protected:
    virtual void onPolicyInit();

    virtual void postPolicyInit() = 0;
    virtual void resetNeiGroups() = 0;
    virtual index_t getNeiId(const addr_t & d) = 0;

    GREFWD * fwd;
    eRouting * rt;

    string rawAddr, dif;
    addr_t myaddr, zone, ident;
    index_t f, p, s, t;

    map<addr_t, port_t > neiPorts;
    map<addr_t, elink_t > neiLinks;
    map<elink_t, addr_t > linkNei;

    vector<bool> aliveNeis;
};

}
