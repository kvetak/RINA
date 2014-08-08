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
#include "AEBase.h"

class ConnectionTableEntry {
  public:
    enum ConnectionStatus {UNKNOWN,
                           NIL,
                           FLOWPENDING,
                           CONNECTPENDING,
                           AUTHENTICATING,
                           ESTABLISHED,
                           RELEASING};

    //De-constructors
    ConnectionTableEntry();
    ConnectionTableEntry(AEBase* nae);
    ConnectionTableEntry(AEBase* nae, cGate* norI, cGate* norO);
    ConnectionTableEntry(AEBase* nae, cGate* norI, cGate* norO, cGate* souI, cGate* souO);
    virtual ~ConnectionTableEntry();

    std::string info() const;
    std::string getConnectionStatusString() const;

    //Getters and Setters
    void setConStatus(ConnectionStatus conStatus);
    AEBase* getAppEntity() const;
    void setAppEntity(AEBase* appEntity);

    //const Flow* getFlowObject() const;
    //void setFlowObject(Flow* flowObject);
    const cGate* getNorthGateIn() const;
    void setNorthGateIn(cGate* northGateIn);
    const cGate* getNorthGateOut() const;
    void setNorthGateOut(cGate* northGateOut);
    const cGate* getSouthGateIn() const;
    void setSouthGateIn(cGate* southGateIn);
    const cGate* getSouthGateOut() const;
    void setSouthGateOut(cGate* southGateOut);

  private:
    ConnectionStatus conStatus;
    AEBase*     AppEntity;
    //Flow*   FlowObject;
    cGate*  northGateIn;
    cGate*  northGateOut;
    cGate*  southGateIn;
    cGate*  southGateOut;

};

//Free function
std::ostream& operator<< (std::ostream& os, const ConnectionTableEntry& cte);

#endif /* CONNECTIONTABLEENTRY_H_ */
