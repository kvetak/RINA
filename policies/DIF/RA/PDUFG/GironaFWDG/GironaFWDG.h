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

#include <IntPDUFG.h>

#include "GironaFWD.h"


using namespace std;


class GironaFWDG: public IntPDUFG {
public:
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, port_t port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, port_t port);
    virtual void routingUpdated();

protected:
    virtual void onPolicyInit();

    GironaFWD * Fwd;
    map<string, set<port_t> > neiPorts;
};
