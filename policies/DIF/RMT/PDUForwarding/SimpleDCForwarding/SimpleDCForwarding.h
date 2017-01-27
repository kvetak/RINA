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

#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"

#include <map>
#include <string>
#include <vector>
#include <map>

#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/DCAddr.h"

namespace NSPSimpleDC {

using namespace std;

    typedef RMTPort* Port;

    class iSimpleDCForwarding: public IntPDUForwarding {

    public:
        // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
        vector<Port> lookup(const PDU * pdu);
        vector<Port> lookup(const Address & dst, const std::string & qos);

        // Returns a representation of the Forwarding Knowledge
        virtual string toString();

        void setNodeInfo(const string & n_addr);
        void setNodeInfo(const int & type, const int & a, const int & b);

        virtual bool setNeigh(const DCAddr & n_addr, Port port) = 0;
        virtual void setDst(const DCAddr & n_addr, const set<DCAddr> & next) = 0;

    protected:
        DCAddr Im;

        virtual void onPolicyInit() = 0;
        virtual vector<Port> search(const DCAddr & n_addr) = 0;

        virtual void refreshCache(Port oldP, Port newP);
        virtual void refreshCache(const DCAddr & addr);
    };

}
