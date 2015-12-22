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

#include <IntPDUForwarding.h>

#include <map>
#include <string>
#include <vector>
#include <map>

namespace NSPSimpleDC {

using namespace std;

    struct DCAddr {
        int type, a, b;

        DCAddr();
        DCAddr(const int & _type, const int & _a, const int & _b);
        DCAddr(const string & s_addr);

        bool operator<( const DCAddr & n ) const;
        bool operator==( const DCAddr & n ) const;
    };

    struct FWDEntry {
        bool inverse;
        bool toUp;
        set<RMTPort *> ports;

        FWDEntry();
    };

    class SimpleDCForwarding: public IntPDUForwarding {

    public:
        // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
        vector<RMTPort * > lookup(const PDU * pdu);
        vector<RMTPort * > lookup(const Address & dst, const std::string & qos);

        vector<RMTPort * > search(const DCAddr & n_addr);

        // Returns a representation of the Forwarding Knowledge
        string toString();

        // PrintAtEnd
        void finish();

        /*
         * type : 0-TOR, 1-AG, 2-Spine
         * TOR : 0.a(rack).b(TOR)
         * AG : 1.a(rack).b(AG)
         * SP : 2.a(AG).b(SP)
         */
        void setNodeInfo(const int & type, const int & a, const int & b);
        void addNeigh(const string & s_addr, RMTPort* port);
        void removeNeigh(const string & s_addr, RMTPort* port);

        void addDst(const string & s_addr, const set<int> & upP, const set<int> & downP);

    protected:
        DCAddr Im;
        map<int, RMTPort *> upN, downN;
        vector<RMTPort *> upV, downV, allV;

        map<DCAddr, FWDEntry> table;

        FWDEntry getUpPorts(const set<int> & pIds);
        FWDEntry getDownPorts(const set<int> & pIds);
        FWDEntry getJoinPorts(const set<int> & upIds, const set<int> & downIds);

        void onPolicyInit();
    };

}
