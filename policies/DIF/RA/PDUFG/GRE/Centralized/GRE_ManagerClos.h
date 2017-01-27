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
#include "DIF/Routing/CentralRouting/RoutingManager.h"
#include "DIF/RMT/PDUForwarding/GREFWD/GRE_Helpers.h"
#include "DIF/RMT/PDUForwarding/DefaultGW/DefaultGW.h"

#include "Addons/Actions/FailureSimulation/FailureSimulation.h"


using namespace std;

class GRE_ManagerClos: public IntPDUFG, public FailureNode {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    virtual void killLink(const string & link);
    virtual void resurrectLink(const string &  link);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();
    RoutingManager * rt;
    DefaultGW * fwd;

    string rawAddr, dif;
    addr_t myaddr, zone, ident;


    map<elink_t, addr_t> link2nei;
    RMTPort * p;

    set<addr_t> managers;
};
