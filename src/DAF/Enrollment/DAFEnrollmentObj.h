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

/**
 * @file DAFEnrollmentObj.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment object
 * @detail
 */


#ifndef DAFENROLLMENTOBJ_H_
#define DAFENROLLMENTOBJ_H_

#include <string>
#include <sstream>
#include "Common/Address.h"

class DAFEnrollmentObj : public cObject {
public:
    DAFEnrollmentObj();
    DAFEnrollmentObj(const Address& srcAddr, const Address& dstAddr);
    virtual ~DAFEnrollmentObj();

    virtual DAFEnrollmentObj* dup() const;

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
