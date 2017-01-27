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

#ifndef __INTPORTSLOADROUTING_H
#define __INTPORTSLOADROUTING_H

#include "DIF/Routing/IntRouting.h"
#include <string>

typedef std::pair<std::string, std::string> qosPaddr;
typedef std::map<qosPaddr, std::string> entries2Next;
typedef std::pair<qosPaddr, std::string> entries2NextItem;
typedef entries2Next::iterator entries2NextIt;

class IntPortsLoadRouting: public IntRouting
{
public:

    // Process a Routing Update, return true => inform FWDG of the update.
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;

    // New flow inserted.
    virtual void insertFlow(
            const Address &addr,
            const std::string &dst,
            const std::string &qos,
            const unsigned short &metric,
            bool sendUpdate) = 0;

    // Existing flow removal.
    virtual void removeFlow(
            const Address &addr,
            const std::string &dst,
            const std::string &qos,
            bool sendUpdate) = 0;

    // Get Changes.
    virtual entries2Next getChanges() = 0;
    virtual entries2Next getAll() = 0;

    // Force the scheduling of a routing update message.
    virtual void scheduleUpdate() = 0;

protected:
    // Called after initialize.
    virtual void onPolicyInit() = 0;
};

#endif // __INTPORTSLOADROUTING_H
