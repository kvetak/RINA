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

/*
 * IntRoutingUpdate.h
 *
 *  Created on: Mar 18, 2015
 *      Author: gaixas1
 */

#ifndef INTROUTINGUPDATE_H_
#define INTROUTINGUPDATE_H_

#include "Common/Address.h"

class IntRoutingUpdate : public cObject {
protected:
    Address dstAddr;
    Address srcAddr;

public:
    IntRoutingUpdate();
    IntRoutingUpdate(const Address &addr);
    ~IntRoutingUpdate();

    // Getters.
    Address getDestination();
    Address getSource();

    // Setters.
    void setDestination(Address addr);
    void setSource(Address src);
};

#endif /* INTROUTINGUPDATE_H_ */
