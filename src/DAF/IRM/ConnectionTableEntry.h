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

#ifndef CONNECTIONTABLEENTRY_H_
#define CONNECTIONTABLEENTRY_H_

//Standard libraries
#include <string>
//RINASim libraries
#include "Common/Flow.h"
#include "DIF/FA/FABase.h"

class ConnectionTableEntry {
  public:
    enum ConnectionStatus {CON_ERROR,
                           CON_NIL,
                           CON_FLOWPENDING,
                           CON_CONNECTPENDING,
                           CON_AUTHENTICATING,
                           CON_ESTABLISHED,
                           CON_RELEASING};

    //De-constructors
    ConnectionTableEntry();
    ConnectionTableEntry(Flow* flow);
    virtual ~ConnectionTableEntry();

    std::string info() const;
    std::string getConnectionStatusString() const;

    //Getters and Setters
    void setConStatus(ConnectionStatus conStatus);
    ConnectionTableEntry::ConnectionStatus getConStatus() const;
    FABase* getFlowAlloc() const;
    void setFlowAlloc(FABase* flowAlloc);
    cGate* getNorthGateIn() const;
    void setNorthGateIn(cGate* northGateIn);
    cGate* getNorthGateOut() const;
    void setNorthGateOut(cGate* northGateOut);
    cGate* getSouthGateIn() const;
    void setSouthGateIn(cGate* southGateIn);
    cGate* getSouthGateOut() const;
    void setSouthGateOut(cGate* southGateOut);
    const APNamingInfo& getApni() const;
    void setApni(const APNamingInfo& apni);

    cModule* getIpc() const;

  private:
    //Flow*   FlowObject;
    APNamingInfo apni;
    ConnectionStatus conStatus;
    cGate*  northGateIn;
    cGate*  northGateOut;
    cGate*  southGateIn;
    cGate*  southGateOut;
    FABase* FlowAlloc;
};

//Free function
std::ostream& operator<< (std::ostream& os, const ConnectionTableEntry& cte);

#endif /* CONNECTIONTABLEENTRY_H_ */
