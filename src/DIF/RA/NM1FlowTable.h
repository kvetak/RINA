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

#ifndef __RINA_FLOWTABLE_H_
#define __RINA_FLOWTABLE_H_

#include <omnetpp.h>

#include "DIF/RA/NM1FlowTableItem.h"

typedef std::list<NM1FlowTableItem> FlTable;
typedef FlTable::iterator FlTableIter;

class NM1FlowTable : public cSimpleModule
{
  public:
    void insert(const NM1FlowTableItem* entry);
    void insert(Flow* flow, FABase* fa, RMTPort* port, std::string gateName);
    void remove(Flow* flow);
    NM1FlowTableItem* findFlowByDstApni(const std::string& addr,
            const std::string& qosId);
    NM1FlowTableItem* findFlowByDstAddr(const std::string& addr,
            const std::string& qosId);
    NM1FlowTableItem* lookup(Flow* flow);

  protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);

  private:
    FlTable flows;
};

#endif
