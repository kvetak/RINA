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
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"
#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/SimpleDCForwarding.h"

#include <map>
#include <set>


namespace NSPSimpleDC {

using namespace std;

typedef unsigned short mType;

class SimpleDCGenerator: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

    DCAddr Im;

    DA * difA;
    iSimpleDCForwarding * fwd;
    IntTSimpleRouting<mType> * rt;

    //s_Addr -> DCAddr
    map<string, DCAddr > neighsAddr;

    //int -> portsSet || up and down by sub-id
    map<DCAddr, set<RMTPort*> > ports;

    void handleMessage(cMessage *msg);
    bool updateRoutes;
};

}
