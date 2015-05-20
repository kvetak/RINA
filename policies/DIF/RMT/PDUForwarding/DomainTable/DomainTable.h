//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SimpleTable_H_
#define SimpleTable_H_

#include <IntPDUForwarding.h>

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
