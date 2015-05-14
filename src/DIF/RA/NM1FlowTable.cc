//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#include "NM1FlowTable.h"

Define_Module(NM1FlowTable);

void NM1FlowTable::initialize()
{
    WATCH_LIST(flows);
}

void NM1FlowTable::handleMessage(cMessage *msg)
{
}

void NM1FlowTable::insert(const NM1FlowTableItem* entry)
{
    flows.push_back(*entry);
}

void NM1FlowTable::insert(Flow* flow, FABase* fa, RMTPort* port, std::string gateName)
{
    NM1FlowTableItem entry = NM1FlowTableItem(flow, fa, port, gateName);
    flows.push_back(entry);
}

NM1FlowTableItem* NM1FlowTable::lookup(Flow* flow)
{
    for(FlTableIter it = flows.begin(); it != flows.end(); ++it )
    {
        NM1FlowTableItem a = *it;
        if (a.getFlow() == flow)
        {
            return &(*it);
        }
    }
    return NULL;
}

NM1FlowTableItem* NM1FlowTable::findFlowByDstApni(std::string addr, std::string qosId)
{
    for(FlTableIter it = flows.begin(); it != flows.end(); ++it )
    {
        NM1FlowTableItem a = *it;
        if ((a.getFlow()->getDstApni().getApn().getName() == addr) &&
             !a.getFlow()->getConId().getQoSId().compare(qosId) )
        {
            return &(*it);
        }
    }
    return NULL;
}

NM1FlowTableItem* NM1FlowTable::findFlowByDstAddr(std::string addr, std::string qosId)
{
    for(FlTableIter it = flows.begin(); it != flows.end(); ++it )
    {
        NM1FlowTableItem a = *it;
        if ((a.getFlow()->getDstAddr().getApname().getName() == addr) &&
             !a.getFlow()->getConId().getQoSId().compare(qosId) )
        {
            return &(*it);
        }
    }
    return NULL;
}

void NM1FlowTable::remove(Flow* flow)
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
