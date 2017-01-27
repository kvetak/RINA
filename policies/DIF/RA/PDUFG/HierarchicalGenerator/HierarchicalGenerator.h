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

#ifndef HierarchicalGenerator_H_
#define HierarchicalGenerator_H_

#include "DIF/RA/PDUFG/IntPDUFG.h"
#include "DIF/RMT/PDUForwarding/HierarchicalTable/HierarchicalTable.h"
#include "DIF/Routing/TDomainRouting/TDomainRouting.h"

#include <map>
#include <set>

namespace HierarchicalGenerator {

using namespace std;

typedef unsigned short mType;

struct pAddr {
    string domId;
    string addr;
    pAddr (const string &_domId, const string _addr) :domId(_domId), addr(_addr){}
};

typedef set<RMTPort*> PortsSet;
typedef map<string, PortsSet> NTable;

typedef PortsSet::iterator PortsSetIt;
typedef NTable::iterator NTableIt;


class HierarchicalGenerator: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

private:
    DA * difA;
    HierarchicalTable::HierarchicalTable * fwd;
    tDomain::TDomainRouting<mType> * rt;

    string myAddr;
    vector<string> parsStr;
    vector<string> domains;
    pAddr parseAddr(const string &addr);

    map<string,NTable> domNeighbours;
};

}

#endif /* STATICGENERATOR_H_ */
