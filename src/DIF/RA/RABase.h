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

#ifndef RABASE_H_
#define RABASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "QoSCube.h"
#include "Flow.h"

typedef std::list<QoSCube> QoSCubeSet;
typedef QoSCubeSet::const_iterator QCubeCItem;

class RABase : public cSimpleModule
{
  public:
    RABase();
    virtual ~RABase();

    virtual void createNM1Flow(Flow *flow) = 0;
    virtual void createNM1FlowWithoutAllocate(Flow *flow) = 0;
    virtual void postNFlowAllocation(Flow* flow) = 0;
    virtual void postNM1FlowAllocation(Flow* flow) = 0;
    virtual void removeNM1Flow(Flow *flow) = 0;
    virtual bool bindNFlowToNM1Flow(Flow* flow) = 0;

    const QoSCubeSet& getQoSCubes() const;
    const QoSCube* getQoSCubeById(unsigned short qosId) const;

  protected:
    //SimpleModule overloads
    virtual void initialize(int stage) = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    QoSCubeSet QoSCubes;
};

//Free function
std::ostream& operator<< (std::ostream& os, const QoSCubeSet& cubes);

#endif /* RABASE_H_ */
