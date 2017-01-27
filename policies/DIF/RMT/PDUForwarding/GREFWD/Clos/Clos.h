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

#pragma once

#include "DIF/RMT/PDUForwarding/GREFWD/GREFWD.h"

namespace GRE {
/**
 * Groups:
 * 0 - Reserved
 * 1 - To reach nodes in the same Pod
 * 2 - To reach nodes in other Pods
 */
class Clos0: public GREFWD {
public:
    void setZone(const addr_t &);
    void setSpines(const  index_t &);

protected:
    // * Virtual function for computing possible out ports
    virtual grouprange_t execRule(const addr_t & a);

    addr_t A;
    index_t B;
};

/**
 * Groups:
 * 0 - Reserved
 * 1 - To reach non-neighbour nodes in the same Pod
 * 2 - To reach nodes in other Pods
 */
class Clos1: public GREFWD {
public:
    void setZone(const addr_t &);
    void setIdentifier(const  addr_t &);
    void setNumSpines(const  addr_t &);


protected:
    // * Virtual function for computing possible out ports
    virtual grouprange_t execRule(const addr_t & a);

    addr_t A, B, C;
};


/**
 * Groups:
 * 0 - Reserved
 */
class Clos2: public GREFWD {
public:
    void setPadding(const index_t &);
    void setNumPods(const index_t &);

protected:
    // * Virtual function for computing possible out ports
    virtual grouprange_t execRule(const addr_t & a);

    index_t A, B;
};

}
