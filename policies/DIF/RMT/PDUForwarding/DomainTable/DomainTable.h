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

#ifndef SimpleTable_H_
#define SimpleTable_H_

#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"

#include <map>
#include <string>
#include <vector>

namespace DomainTable {

using namespace std;

typedef vector<string> sList;
typedef sList::iterator sListIt;

typedef map<string, RMTPort*> s2Port;
struct  domainSet {
    unsigned short len;
    s2Port entries;

    domainSet():len(0){}
    domainSet(const unsigned short &_len):len(_len){}
};
typedef map<string, domainSet> FWDTable;

typedef s2Port::iterator s2PortIt;
typedef FWDTable::iterator FWDTableIt;

struct pAddr {
    string domain;
    string addr;
    pAddr (const string &_domain, const string &_addr)
        : domain(_domain), addr(_addr) {}
};

class DomainTable: public IntPDUForwarding {

public:
    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const std::string& qos);

    // Returns a representation of the Forwarding Knowledge
    string toString();

    // Create Domain
    void addDomain(const string &domain);
    void removeDomain(const string &domain);

    //Insert/Remove an entry
    void insert(const string &domain, const string &addr, RMTPort * port);
    void remove(const string &domain, const string &addr);

    void finish();
    pAddr parseAddr(const string &addr);

protected:
    sList domains;
    FWDTable table;

    // Called after initialize
    void onPolicyInit();
};

}

#endif /* SimpleTable_H_ */
