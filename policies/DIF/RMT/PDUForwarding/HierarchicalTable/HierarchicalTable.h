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

#ifndef HierarchicalTable_H_
#define HierarchicalTable_H_

#include "DIF/RMT/PDUForwarding/IntMMForwarding.h"

#include <map>
#include <string>
#include <vector>

namespace HierarchicalTable {

using namespace std;

typedef map<string, vector<RMTPort*> > FWDTable;
typedef FWDTable::iterator FWDTableIt;

class HierarchicalTable: public IntPDUForwarding {

public:
    HierarchicalTable();

    void addDomain(const string & domId, const string & qos, const string & prefix);
    void addDomain(const string & domId, const string & prefix);

    void removeDomain(string domId);

    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const string& qos);

    // Returns a representation of the Forwarding Knowledge
    string toString();

    //Insert/Remove an entry
    void addReplace(const string &domId, const string &addr, vector<RMTPort *> ports);

    void finish();

    void setAddr(const Address & addr);

    void setTmp(const Address & dst, RMTPort *p);
    void removeTmp(const Address & dst, RMTPort *p);

protected:
    string anyQoS;

    Address myAddr;

    struct domData {
        string domId;
        unsigned int prefLen;
        domData() : domId(""), prefLen(0){}
        domData(const string & id, const unsigned int & len) : domId(id), prefLen(len){}
    };

    // domain -> addr -> list<ports>
    map<string, map<string, vector<RMTPort*>  > > table;

    // prefix -> qos -> domain
    map<string, map<string, domData> > domains;

    // Address port / temporal links
    map<Address, RMTPort* > direct;


    // Called after initialize
    void onPolicyInit();
};

}

#endif /* HierarchicalTable_H_ */
