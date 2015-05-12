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

#ifndef IntSimpleRouting_H_
#define IntSimpleRouting_H_

#include <IntRouting.h>
#include <string>

typedef std::pair<unsigned short, std::string> qosPaddr;
typedef std::map<qosPaddr, std::string> entries2Next;
typedef std::pair<qosPaddr, std::string> entries2NextItem;
typedef entries2Next::iterator entries2NextIt;

class IntSimpleRouting: public IntRouting {
public:
    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;


    //Flow inserted/removed
    virtual void insertFlow(const Address &addr, const std::string &dst, const unsigned short &qos, const unsigned short &metric) = 0;
    virtual void removeFlow(const Address &addr, const std::string &dst, const unsigned short &qos) = 0;

    //Get Changes
    virtual entries2Next getChanges() = 0;
    virtual entries2Next getAll() = 0;

protected:
    // Called after initialize
    virtual void onPolicyInit() = 0;
};

#endif /* IntSimpleRouting_H_ */
