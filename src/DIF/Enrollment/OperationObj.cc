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

#include <OperationObj.h>

OperationObj::OperationObj() {
}

OperationObj::~OperationObj() {
}

void OperationObj::setSrcAddress(const Address& srcAddr) {
    this->srcAddr = srcAddr;
}

void OperationObj::setDstAddress(const Address& dstAddr) {
    this->dstAddr = dstAddr;
}

OperationObj* OperationObj::dup() const {

    OperationObj* obj = new OperationObj();
    obj->setSrcAddress(this->getSrcAddress());
    obj->setDstAddress(this->getDstAddress());

    return obj;
}

const Address& OperationObj::getSrcAddress() const {
    return srcAddr;
}

const Address& OperationObj::getDstAddress() const {
    return dstAddr;
}
