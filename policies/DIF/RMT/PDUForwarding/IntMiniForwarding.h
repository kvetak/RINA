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

#ifndef IntMiniForwarding_H_
#define IntMiniForwarding_H_

#include <omnetpp.h>
#include "IntPDUForwarding.h"

class IntMiniForwarding  : public IntPDUForwarding {
public:

    //Insert/Remove an entry
    virtual void insert(const std::string &addr, RMTPort * port) = 0;
    virtual void insert(const Address &addr, RMTPort * port) = 0;
    virtual void remove(const std::string &addr) = 0;
    virtual void remove(const Address &addr) = 0;
};

#endif /* IntMiniForwarding_H_ */
