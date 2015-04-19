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

#ifndef INTBBROUTING_H_
#define INTBBROUTING_H_

#include <omnetpp.h>

#include "IntRouting.h"

class IntBbPDUFWDG;

class IntRoutingInfo{};

class IntBbRouting  : public IntRouting {
public:
    virtual void insertFlow(const Address &dst);
    virtual void insertFlow(const Address &dst, const unsigned short &qos);
    virtual void insertFlow(const Address &dst, const unsigned short &qos, const unsigned short &metric) = 0;
    virtual void removeFlow(const Address &dst, const unsigned short &qos) = 0;
    virtual IntRoutingInfo getAll() = 0;

protected :
    virtual void onPolicyInit();
};

#endif /* INTBBROUTING_H_ */
