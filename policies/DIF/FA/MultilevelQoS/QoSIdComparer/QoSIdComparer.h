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

#ifndef QoSIdComparer_H_
#define QoSIdComparer_H_

#include <MultilevelQoS/MultilevelQoS.h>

class QoSIdComparer : public MultilevelQoS {
  public:
    bool isValid(const QoSCube &upperQoS, const QoSCube &lowerQoS);
    void setRequirements(Flow * lowerflow, const QoSCube &upperQoS);
protected:
    int mHops;
    int mlBandw;
    void initialize();
};

#endif /* QoSIdComparer_H_ */
