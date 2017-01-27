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

using namespace std;

typedef RMTPort * port_t;
typedef vector<port_t> vPorts;

class Q2FwdT: public IntPDUForwarding {
public:
    vPorts lookup(const PDU * _pdu);
    vPorts lookup(const Address &_dst, const std::string& _qos);

    void iniStructs(const map<string, int> & _Q2T, const int & _nT, const int & _Ts);
    void setTentry(const int & _T, const int & _addr, port_t _p);
    void setTable(const int & _T, const vPorts & _cont);
    void setQ2T(const map<string, int> & _Q2T);

protected:
    void finish();

    port_t search(const string & _raddr, const string & _qos);
    string toString();
    void onPolicyInit() {};

    map<string, int> Q2T;
    vector< vPorts > Tables;
};

