// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/RA/NM1FlowTable.h"

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
    for(auto& item : flows)
    {
        if (item.getFlow() == flow)
        {
            return &item;
        }
    }
    return nullptr;
}

NM1FlowTableItem* NM1FlowTable::findFlowByDstApni(const std::string& addr,
        const std::string& qosId)
{
    for (auto& item : flows)
    {
        if ((item.getFlow()->getDstApni().getApn().getName() == addr)
                && !item.getFlow()->getConId().getQoSId().compare(qosId))
        {
            return &item;
        }
    }
    return nullptr;
}

NM1FlowTableItem* NM1FlowTable::findFlowByDstAddr(const std::string& addr,
        const std::string& qosId)
{
    for(auto& item : flows)
    {
        if ((item.getFlow()->getDstAddr().getApn().getName() == addr) &&
             !item.getFlow()->getConId().getQoSId().compare(qosId) )
        {
            return &item;
        }
    }
    return nullptr;
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
