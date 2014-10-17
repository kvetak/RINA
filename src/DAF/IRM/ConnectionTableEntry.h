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

#ifndef CONNECTIONTABLEENTRY_H_
#define CONNECTIONTABLEENTRY_H_

//Standard libraries
#include <string>
//RINASim libraries
#include "Flow.h"
#include "FABase.h"

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
    ConnectionTableEntry(Flow* flow, cGate* nIn, cGate* nOut);
    virtual ~ConnectionTableEntry();

    std::string info() const;
    std::string getConnectionStatusString() const;

    //Getters and Setters
    void setConStatus(ConnectionStatus conStatus);
    FABase* getFlowAlloc() const;
    void setFlowAlloc(FABase* flowAlloc);
    Flow* getFlowObject() const;
    void setFlowObject(Flow* flowObject);
    cGate* getNorthGateIn() const;
    void setNorthGateIn(cGate* northGateIn);
    cGate* getNorthGateOut() const;
    void setNorthGateOut(cGate* northGateOut);
    cGate* getSouthGateIn() const;
    void setSouthGateIn(cGate* southGateIn);
    cGate* getSouthGateOut() const;
    void setSouthGateOut(cGate* southGateOut);

    cModule* getIpc() const;

  private:
    Flow*   FlowObject;
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
