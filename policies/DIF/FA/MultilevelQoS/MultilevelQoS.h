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

#ifndef MultilevelQoS_H_
#define MultilevelQoS_H_

#include <omnetpp.h>

#include "QoSCube.h"
#include "Flow.h"

class MultilevelQoS : public cSimpleModule {
  public:
    virtual bool isValid(const QoSCube &upperQoS, const QoSCube &lowerQoS) = 0;
    virtual void setRequirements(Flow * lowerflow, const QoSCube &upperQoS) = 0;
};

#endif /* MultilevelQoS_H_ */
