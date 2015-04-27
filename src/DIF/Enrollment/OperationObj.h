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

#ifndef OPERATIONOBJ_H_
#define OPERATIONOBJ_H_

#include <string>
#include <sstream>
#include "Address.h"

class OperationObj : public cObject {
public:
    OperationObj();
    virtual ~OperationObj();
    void setSrcAddress(const Address& srcAddr);
    void setDstAddress(const Address& dstAddr);

    virtual OperationObj* dup() const;

    const Address& getSrcAddress() const;
    const Address& getDstAddress() const;

private:

    Address srcAddr;

    Address dstAddr;
};

#endif /* OPERATIONOBJ_H_ */
