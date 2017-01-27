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
#include "DIF/RMT/PDUForwarding/IntMMForwarding.h"
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"

#include "DIF/RA/QueueIDGen/IDPerNQoSxPLen/IDPerNQoSxPLen.h"

#include <map>
#include <set>


namespace NSPSimpleHopMEntries {

using namespace std;

typedef unsigned short mType;

class SimpleHopMEntries: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

    DA * difA;
    IntMMForwarding * fwd;
    IntTSimpleRouting<mType> * rt;

    //Next, Ports
    map<string, set<RMTPort*> > neighbours;

    set<string> hopQoS;
    bool maUrgent;
};

}
