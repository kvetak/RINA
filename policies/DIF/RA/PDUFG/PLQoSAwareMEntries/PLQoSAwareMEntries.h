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
#include "DIF/RMT/PDUForwarding/IntIQoSMForwarding.h"
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"

#include "DIF/RA/QueueIDGen/IDPerNQoSxPLen/IDPerNQoSxPLen.h"

#include <map>
#include <set>


namespace PLQoSAwareMEntries {

using namespace std;

typedef unsigned short mType;

class PLQoSAwareMEntries: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

    void registerQidsGen(IDPerNQoSxPLen * qId);
    void unregisterQidsGen(IDPerNQoSxPLen * qId);

protected:
    // Called after initialize
    virtual void onPolicyInit();

private:
    DA * difA;
    IntIQoSMForwarding * fwd;
    IntTSimpleRouting<mType> * rt;
    set<IDPerNQoSxPLen *> qIds;

    //QoS, Next, Ports
    map<string,  map<string, set<RMTPort*> > > neighbours;
    map<RMTPort*, string > portQoS;

    set<string> urgentQoS;
    map<string, int> dstLat;
    map<string, double> dstDLat;
    //FIXME: Vesely: Unused variable commented
    //bool maUrgent;
    int maxLat;
};

}
