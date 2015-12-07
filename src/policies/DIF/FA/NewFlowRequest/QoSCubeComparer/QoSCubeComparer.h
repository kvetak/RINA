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

#ifndef QOSCUBECOMPARER_H_
#define QOSCUBECOMPARER_H_

#include <NewFlowRequest/NewFlowRequestBase.h>

class QoSCubeComparer : public NewFlowRequestBase {
  public:
    virtual bool run(Flow& flow);
};

#endif /* QOSCUBECOMPARER_H_ */
