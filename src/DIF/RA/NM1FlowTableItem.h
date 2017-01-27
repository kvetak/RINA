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

#ifndef FLOWTABLEITEM_H_
#define FLOWTABLEITEM_H_

#include <omnetpp.h>

#include "Common/Flow.h"
#include "DIF/FA/FABase.h"
#include "DIF/RMT/RMTPort.h"

class NM1FlowTableItem
{
  public:
    NM1FlowTableItem(Flow* flow, FABase* fa, RMTPort* port, std::string gateName);
    virtual ~NM1FlowTableItem();

    enum ConnectionStatus
    {
        CON_ERROR,
        CON_NIL,
        CON_FLOWPENDING,
        CON_CONNECTPENDING,
        CON_AUTHENTICATING,
        CON_ESTABLISHED,
        CON_RELEASING
    };

    std::string info() const;

    Flow* getFlow() const;
    FABase* getFABase() const;
    RMTPort* getRMTPort() const;
    const RMTQueues& getRMTInputQueues() const;
    const RMTQueues& getRMTOutputQueues() const;
    std::string getGateName() const;
    void setConnectionStatus(ConnectionStatus status);
    ConnectionStatus getConnectionStatus();
    std::string getConnectionStatusString() const;

  private:
    Flow* flow;
    FABase* fa;
    RMTPort* rmtPort;
    std::string gateName;
    ConnectionStatus conStatus;
};

std::ostream& operator<< (std::ostream& os, const NM1FlowTableItem& cte);

#endif /* FLOWTABLEITEM_H_ */
