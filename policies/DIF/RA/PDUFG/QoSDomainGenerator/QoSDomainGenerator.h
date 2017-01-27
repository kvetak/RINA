// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef QoSDomainGenerator_H_
#define QoSDomainGenerator_H_

#include "Common/Utils.h"
#include "DIF/RA/PDUFG/IntPDUFG.h"
#include "DIF/RMT/PDUForwarding/QoSTable/QoSTable.h"
#include "DIF/Routing/DomainRouting/Routing.h"
#include "Common/QoSCube.h"
#include "DIF/RA/RA.h"
#include "DIF/FA/MultilevelQoS/MultilevelQoS.h"


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
    virtual void insertedFlow(const Address& addr, const QoSCube & qos, RMTPort* port);
    virtual void removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port);

    //Routing has processes a routing update
    virtual void routingUpdated();

protected:
    // Called after initialize
    virtual void onPolicyInit();

private:
    DA * difA;
    QoSTable::QoSTable * fwd;
    DMRnms::Routing * rt;
    //FIXME: Vesely: Unused variable commented
    //int nDom;

    QNTable neighbours;
    QoSCubeSet cubes;
    MultilevelQoS * comparer;
};

}

#endif /* STATICGENERATOR_H_ */
