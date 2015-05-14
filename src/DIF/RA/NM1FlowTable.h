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

#ifndef __RINA_FLOWTABLE_H_
#define __RINA_FLOWTABLE_H_

#include <omnetpp.h>

#include "NM1FlowTableItem.h"

typedef std::list<NM1FlowTableItem> FlTable;
typedef FlTable::iterator FlTableIter;

class NM1FlowTable : public cSimpleModule
{
  public:
    void insert(const NM1FlowTableItem* entry);
    void insert(Flow* flow, FABase* fa, RMTPort* port, std::string gateName);
    void remove(Flow* flow);
    NM1FlowTableItem* findFlowByDstApni(std::string addr, std::string qosId);
    NM1FlowTableItem* findFlowByDstAddr(std::string addr, std::string qosId);
    NM1FlowTableItem* lookup(Flow* flow);

  protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);

  private:
    FlTable flows;
};

#endif
