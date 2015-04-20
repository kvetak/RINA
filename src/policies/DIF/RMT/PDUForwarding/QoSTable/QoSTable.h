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

#ifndef QoSTable_H_
#define QoSTable_H_

#include <IntPDUForwarding.h>

#include <map>
#include <string>
#include <vector>

namespace QoSTable {

using namespace std;

typedef map<string, RMTPort*> FWDTable;
typedef FWDTable::iterator FWDTableIt;

typedef map<unsigned short, FWDTable> QoSFWDTable;
typedef QoSFWDTable::iterator QoSFWDTableIt;

class QoSTable: public IntPDUForwarding {

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
    void clean();

    void finish();

protected:
    QoSFWDTable table;
    vector<RMTPort * > lookupInt(const string &dst, const unsigned short &qos);

    // Called after initialize
    void onPolicyInit();
};

}

#endif /* QoSTable_H_ */
