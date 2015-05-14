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

#ifndef QoSDomainGenerator_H_
#define QoSDomainGenerator_H_

#include <IntPDUFG.h>
#include <QoSTable/QoSTable.h>
#include <DomainRouting/Routing.h>

#include <map>
#include <set>

namespace QoSDomainGenerator {

typedef std::set<RMTPort*> PortsSet;
typedef std::map<std::string, PortsSet> NTable;
typedef std::map<std::string, NTable> QNTable;

typedef PortsSet::iterator PortsSetIt;
typedef NTable::iterator NTableIt;
typedef QNTable::iterator QNTableIt;


class QoSDomainGenerator: public IntPDUFG {
public:
    // A new flow has been inserted/or removed
    // A new flow has been inserted/or removed
    virtual void insertedFlow(const Address& addr, const std::string & qos,
            RMTPort* port) {
        std::string dst = addr.getIpcAddress().getName();
        neighbours[qos][dst].insert(port);
        if (neighbours[qos][dst].size() == 1) {
            //char intStr[10];
            //sprintf(intStr, "%d", qos);
            //string str = string(intStr);
            rt->addFlow(addr, qos, dst, 1);
            routingUpdated();
        }
    }
    virtual void removedFlow(const Address &addr, const std::string &qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

private:
    DA * difA;
    QoSTable::QoSTable * fwd;
    DMRnms::Routing * rt;
    int nDom;

    QNTable neighbours;
};

}

#endif /* STATICGENERATOR_H_ */
