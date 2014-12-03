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

#include "FlowTable.h"

Define_Module(FlowTable);

void FlowTable::initialize()
{
    WATCH_LIST(flows);
}

void FlowTable::handleMessage(cMessage *msg)
{
}

void FlowTable::insert(const FlowTableItem* entry)
{
    flows.push_back(*entry);
}

void FlowTable::insert(Flow* flow, FABase* fa, RMTPort* port, std::string gateName)
{
    FlowTableItem entry = FlowTableItem(flow, fa, port, gateName);
    flows.push_back(entry);
}

FlowTableItem* FlowTable::lookup(Flow* flow)
{
    for(FlTableIter it = flows.begin(); it != flows.end(); ++it )
    {
        FlowTableItem a = *it;
        if (a.getFlow() == flow)
        {
            return &(*it);
        }
    }
    return NULL;
}

FlowTableItem* FlowTable::lookup(std::string addr, short qosId)
{
    for(FlTableIter it = flows.begin(); it != flows.end(); ++it )
    {
        FlowTableItem a = *it;
        if ((a.getFlow()->getDstApni().getApn().getName() == addr) &&
             a.getFlow()->getConId().getQoSId() == qosId)
        {
            return &(*it);
        }
    }
    return NULL;
}

void FlowTable::remove(Flow* flow)
{
    FlTableIter i = flows.begin();
    while (i != flows.end())
    {
        if (i->getFlow() == flow)
        {
            i = flows.erase(i);
        }
        else
        {
            ++i;
        }
    }
}
