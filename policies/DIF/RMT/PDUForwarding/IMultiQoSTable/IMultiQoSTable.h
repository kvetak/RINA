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

#ifndef IMultiQoSTable_H_
#define IMultiQoSTable_H_

#include "DIF/RMT/PDUForwarding/IntIQoSMForwarding.h"

#include <map>
#include <string>
#include <vector>

namespace IMultiQoSTable {

using namespace std;

struct FlowIdent {
    string qosId;
    string srcAddr, dstAddr;
    int srcCepId, dstCepId;

    FlowIdent(const string & _qosId, const string & _srcAddr, const string & _dstAddr, const int & _srcCepId, const int & _dstCepId);

    bool operator<( const FlowIdent & n ) const;
};

struct CacheData {
    RMTPort * next;
    simtime_t expiration;

    CacheData(RMTPort *  _next, const simtime_t & _expiration);
    CacheData();
};


class IMultiQoSTable: public IntIQoSMForwarding {

public:
    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const std::string& qos);

    RMTPort * search(const string & dst, const string & qos);

    // Returns a representation of the Forwarding Knowledge
    string toString();

    //Insert/Remove an entry
    void addReplace(const std::string &addr, const std::string &qosId, std::vector<RMTPort * > ports);

    void finish();

    void setPortDelay(RMTPort* port, double delay);

protected:
    //QoS, Dst, Ports
    map<string, map<string, vector<RMTPort*> > > table;

    map<FlowIdent, CacheData> cache;

    // Called after initialize
    void onPolicyInit();

    string MA2QoS;
    double exTime;

    map<RMTPort*, double> portDelay;
};

}

#endif /* IMultiQoSTable_H_ */
