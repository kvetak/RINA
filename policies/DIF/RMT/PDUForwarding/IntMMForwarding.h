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

#ifndef IntMMForwarding_H_
#define IntMMForwarding_H_

#include <omnetpp.h>
#include "IntPDUForwarding.h"
#include <vector>

class IntMMForwarding  : public IntPDUForwarding {
public:

    //Insert/Remove an entry
    virtual void addReplace(const std::string &addr, std::vector<RMTPort * > ports) = 0;
};

#endif /* IntMMForwarding_H_ */
