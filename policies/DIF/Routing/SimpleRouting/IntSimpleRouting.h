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

#ifndef IntSimpleRouting_H_
#define IntSimpleRouting_H_

#include "DIF/Routing/IntRouting.h"
#include <string>


struct entType{
    unsigned short metric;
    std::set<std::string> nh;
};
typedef std::pair<std::string, std::string> qosPaddr;
typedef std::map<qosPaddr, entType> entries2Next;
typedef std::pair<qosPaddr, std::string> entries2NextItem;
typedef entries2Next::iterator entries2NextIt;

class IntSimpleRouting: public IntRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;


    //Flow inserted/removed
    virtual void insertFlow(const Address &addr, const std::string &dst, const std::string& qos, const unsigned short &metric) = 0;
    virtual void removeFlow(const Address &addr, const std::string &dst, const std::string& qos) = 0;

    //Get Changes
    virtual entries2Next getChanges() = 0;
    virtual entries2Next getAll() = 0;

protected:
    // Called after initialize
    virtual void onPolicyInit() = 0;
};

#endif /* IntSimpleRouting_H_ */
