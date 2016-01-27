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
 * @file OperationObj.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Operation object
 * @detail
 */


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
