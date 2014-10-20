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
#include "QosCube.h"
#include "Flow.h"

typedef std::list<QosCube> QosCubeSet;
typedef QosCubeSet::const_iterator QCubeCItem;

class RABase : public cSimpleModule
{
  public:
    RABase();
    virtual ~RABase();

    virtual void createFlow(Flow *flow) = 0;
    virtual void createFlowWithoutAllocate(Flow *flow) = 0;
    virtual bool bindToLowerFlow(Flow* flow) = 0;

    const QosCubeSet& getQosCubes() const;

  protected:
    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    QosCubeSet QosCubes;
};

//Free function
std::ostream& operator<< (std::ostream& os, const QosCubeSet& cubes);

#endif /* RABASE_H_ */
