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

#ifndef __PORTSLOADLS_H
#define __PORTSLOADLS_H

#include "DIF/Routing/PortsLoadRouting/IntPortsLoadRouting.h"
#include "DIF/Routing/PortsLoadRouting/PortsLoadLS/PortsLoadRU.h"
#include "DIF/Routing/PortsLoadRouting/PortsLoadLS/PLLSCommon.h"

class PortsLoadLS : public IntPortsLoadRouting
{
public:
    // Process a Routing Update, return true => inform FWDG of the update.
    bool processUpdate(IntRoutingUpdate * update);

    // New flow inserted.
    virtual void insertFlow(
            const Address &addr,
            const std::string &dst,
            const std::string &qos,
            const unsigned short &metric,
            bool sendUpdate);

    // Existing flow removal.
    virtual void removeFlow(
            const Address &addr,
            const std::string &dst,
            const std::string &qos,
            bool sendUpdate);

    // Get changes.
    entries2Next getChanges();
    entries2Next getAll();

    void handleMessage(cMessage *msg);
    void finish();

    // Force the scheduling of a routing update message.
    virtual void scheduleUpdate();

protected:
    // Called after initialize.
    void onPolicyInit();

private:
    unsigned short infMetric;
    std::string myAddr;
    qosNeighMetric neig;
    linksStCol netState;
    qos2addrSet lastChanges;
    unsigned int secId;
    linksSt getChangedEntries (const std::string &qos);

    // Number of seconds to wait to send the next routing update packet.
    unsigned int updateTimeout;

    TreeNode constructTree(linksSt &ls);
    void addRecursive(
            entries2Next &ret,
            const std::string &qos,
            const std::string &next,
            TreeNode * t);

    bool scheduledUpdate;

    entries2Next table;

    void printTreeNode(TreeNode *t, const std::string &next);
};

#endif // __PORTSLOADLS_H
