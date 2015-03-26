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

namespace SimpleTable {

using namespace std;

typedef map<unsigned short, RMTPort*> qos2Port;
typedef map<string, qos2Port> FWDTable;

typedef qos2Port::iterator qos2PortIt;
typedef FWDTable::iterator FWDTableIt;

class SimpleTable: public IntPDUForwarding {

public:
    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    vector<RMTPort * > lookup(const PDU * pdu);
    vector<RMTPort * > lookup(const Address &dst, const unsigned short &qos);

    // Returns a representation of the Forwarding Knowledge
    string toString();

    //Insert/Remove an entry
    void insert(const std::string &addr, const unsigned short &qos, RMTPort * port);
    void insert(const Address &addr, const unsigned short &qos, RMTPort * port);
    void remove(const std::string &addr, const unsigned short &qos);
    void remove(const Address &addr, const unsigned short &qos);

    void finish();

protected:
    FWDTable table;

    // Called after initialize
    void onPolicyInit();
};

}

#endif /* SimpleTable_H_ */
