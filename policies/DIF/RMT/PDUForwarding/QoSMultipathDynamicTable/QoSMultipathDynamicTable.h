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

#include "IntPDUForwarding.h"

#include <map>
#include <string>
#include <vector>

namespace QoSMultipathDynamicTable {

    using namespace std;

    struct entryT {
        RMTPort * p;
        int BW;
        entryT();
        entryT(RMTPort * _p, int _bw);
    };

    class iQoSMultipathDynamicTable: public IntPDUForwarding {
    public:
        //Insert/Remove an entry
        void setPort(RMTPort * p, const int bw);
        void replacePort(RMTPort * oldP, RMTPort * newP, const int bw);

        //Insert/Remove an entry
        virtual void addReplace(const string &addr, vector<entryT> ports) = 0;

    protected:
        map<string, int> QoS_BWreq;
        map<RMTPort *, int> Port_avBW;

        // Called after initialize
        void onPolicyInit();

        virtual void onMainPolicyInit() = 0;
        virtual void onSetPort(RMTPort * p, const int bw) = 0;
        virtual void preReplacePort(RMTPort * oldP, RMTPort * newP, const int bw) = 0;

    };

}
