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

#ifndef QoSTable_H_
#define QoSTable_H_

#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"

#include <map>
#include <string>
#include <vector>

namespace QoSTable {

using namespace std;

typedef map<string, RMTPort*> FWDTable;
typedef FWDTable::iterator FWDTableIt;

typedef map<std::string, FWDTable> QoSFWDTable;
typedef QoSFWDTable::iterator QoSFWDTableIt;

class QoSTable: public IntPDUForwarding {

public:
    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const std::string &qos);

    // Returns a representation of the Forwarding Knowledge
    string toString();

    //Insert/Remove an entry
    void insert(const std::string &addr, const std::string &qos, RMTPort * port);
    void insert(const Address &addr, const std::string &qos, RMTPort * port);
    void remove(const std::string &addr, const std::string &qos);
    void remove(const Address &addr, const std::string &qos);
    void clean();

    void finish();

protected:
    QoSFWDTable table;
    vector<RMTPort * > lookupInt(const string &dst, const std::string &qos);

    // Called after initialize
    void onPolicyInit();
};

}

#endif /* QoSTable_H_ */
