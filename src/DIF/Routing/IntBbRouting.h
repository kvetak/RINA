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

#ifndef INTBBROUTING_H_
#define INTBBROUTING_H_

#include <omnetpp.h>

#include "DIF/Routing/IntRouting.h"

class IntBbPDUFWDG;

class IntRoutingInfo{};

class IntBbRouting  : public IntRouting {
public:
    virtual void insertFlow(const Address &dst);
    virtual void insertFlow(const Address &dst, const unsigned short &qos);
    virtual void insertFlow(const Address &dst, const unsigned short &qos, const unsigned short &metric) = 0;
    virtual void removeFlow(const Address &dst, const unsigned short &qos) = 0;
    virtual IntRoutingInfo getAll() = 0;

protected :
    virtual void onPolicyInit();
};

#endif /* INTBBROUTING_H_ */
