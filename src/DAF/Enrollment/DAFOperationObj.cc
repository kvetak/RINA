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
 * @file DAFOperationObj.cc
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Operation object
 * @detail
 */


#include "DAF/Enrollment/DAFOperationObj.h"

DAFOperationObj::DAFOperationObj() {
}

DAFOperationObj::~DAFOperationObj() {
}

void DAFOperationObj::setSrcAddress(const Address& srcAddr) {
    this->srcAddr = srcAddr;
}

void DAFOperationObj::setDstAddress(const Address& dstAddr) {
    this->dstAddr = dstAddr;
}

DAFOperationObj* DAFOperationObj::dup() const {

    DAFOperationObj* obj = new DAFOperationObj();
    obj->setSrcAddress(this->getSrcAddress());
    obj->setDstAddress(this->getDstAddress());

    return obj;
}

const Address& DAFOperationObj::getSrcAddress() const {
    return srcAddr;
}

const Address& DAFOperationObj::getDstAddress() const {
    return dstAddr;
}
