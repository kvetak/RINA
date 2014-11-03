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

#include <RABase.h>

RABase::RABase() {
    // TODO Auto-generated constructor stub

}

RABase::~RABase() {
    // TODO Auto-generated destructor stub

}

const QosCubeSet& RABase::getQosCubes() const {
    return QosCubes;
}

std::ostream& operator <<(std::ostream& os, const QosCubeSet& cubes) {
    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it)
        os << *it;
    return os;
}

const QosCube* RABase::getQosCubeById(unsigned short qosId) const {
    for (QCubeCItem it = QosCubes.begin(); it != QosCubes.end(); ++it) {
        if (it->getQosId() == qosId)
            return &(*it);
    }
    return NULL;
}
