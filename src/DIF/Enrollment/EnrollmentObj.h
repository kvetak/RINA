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

#ifndef ENROLLMENTOBJ_H_
#define ENROLLMENTOBJ_H_

#include <string>
#include <sstream>
#include "Address.h"

class EnrollmentObj : public cObject {
public:
    EnrollmentObj();
    EnrollmentObj(const Address& srcAddr, const Address& dstAddr);
    virtual ~EnrollmentObj();

    virtual EnrollmentObj* dup() const;

    void setAddress(const APN& address);
    void setApName(const APN& apName);
    void setCurrentAddress(const APN& currentAddress);
    void setAddressExpirationTime(int addressExpirationTime);
    void setIsImmediate(bool immediate);
    void setSrcAddress(const Address& srcAddr);
    void setDstAddress(const Address& dstAddr);


    const APN& getAddress() const;
    const APN& getApName() const;
    const APN& getCurrentAddress() const;
    int getAddressExpirationTime() const;
    bool getIsImmediate() const;
    const Address& getSrcAddress() const;
    const Address& getDstAddress() const;


private:

    APN address;

    APN apName;

    APN currentAddress;

    int addressExpirationTime;

    bool immediate;

    Address srcAddr;

    Address dstAddr;
};

#endif /* ENROLLMENTOBJ_H_ */
