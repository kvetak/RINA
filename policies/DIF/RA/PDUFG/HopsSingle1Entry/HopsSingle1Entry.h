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

#ifndef SimpleGenerator_H_
#define SimpleGenerator_H_

#include "DIF/RA/PDUFG/IntPDUFG.h"
#include "DIF/RMT/PDUForwarding/IntMiniForwarding.h"
#include "DIF/Routing/TSimpleRouting/IntTSimpleRouting.h"

#include <map>
#include <set>

namespace HopsSingle1Entry {

using namespace std;

typedef unsigned short mType;

class HopsSingle1Entry: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

private:
    DA * difA;
    IntMiniForwarding * fwd;
    IntTSimpleRouting<mType> * rt;

    map<string, set<RMTPort*> > neighbours;
};

}

#endif /* STATICGENERATOR_H_ */
