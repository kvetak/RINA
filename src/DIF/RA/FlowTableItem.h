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

#ifndef FLOWTABLEITEM_H_
#define FLOWTABLEITEM_H_

#include <omnetpp.h>

#include "Flow.h"
#include "FABase.h"
#include "RMTPort.h"

class FlowTableItem {
  public:
    FlowTableItem(Flow* flow, FABase* fa, RMTPort* port, std::string gateName);
    virtual ~FlowTableItem();

    std::string info() const;

    Flow* getFlow() const;
    FABase* getFaBase() const;
    RMTQueue* getRmtInputQueue() const;
    void setRmtInputQueue(RMTQueue* queue);
    RMTQueues& getRmtOutputQueues() const;
    void addRmtOutputQueue(RMTQueue* queue);
    std::string getGateName() const;

  private:
    Flow* flow;
    FABase* fa;
    RMTPort* rmtPort;
    std::string gateName;
};

std::ostream& operator<< (std::ostream& os, const FlowTableItem& cte);

#endif /* FLOWTABLEITEM_H_ */
