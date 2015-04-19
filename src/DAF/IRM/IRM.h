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

#ifndef IRM_H_
#define IRM_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "IRMListeners.h"
#include "ConnectionTable.h"
#include "ModuleAccess.h"
#include "RINASignals.h"
#include "DA.h"
#include "FABase.h"
#include "ExternConsts.h"

extern const int VAL_UNDEF_HANDLE;
extern const char* SIG_STAT_IRM_UP;
extern const char* SIG_STAT_IRM_DOWN;

class IRM : public cSimpleModule   {
  public:
    IRM();
    virtual ~IRM();

    bool receiveAllocationRequestFromAe(Flow* flow);
    bool receiveDeallocationRequestFromAe(Flow* flow);

    bool receiveAllocationResponsePositiveFromIpc(Flow* flow);

    void newFlow(Flow* flow);
    void changeStatus(Flow* flow, ConnectionTableEntry::ConnectionStatus status);
    int getIrmGateHandle(Flow* flow) const;
    int getApGateHandle(Flow* flow) const;
    void setNorthGates(Flow* flow, cGate* nIn, cGate* nOut);

    ConnectionTable* getConTable() const;
    bool deleteBindings(Flow* flow);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initPointers();

    void updateDisplayString();
    int statPassUp;
    int statPassDown;
    int statDiscarded;

    ConnectionTable* ConTable;
    DA* DifAllocator;

    void initSignalsAndListeners();
    bool createBindings(Flow* flow);


    //Signals
    simsignal_t sigIRMAllocReq;
    simsignal_t sigIRMDeallocReq;

    simsignal_t sigStatIRMPassUp;
    simsignal_t sigStatIRMPassDown;

    //Listeners
    LisIRMAllocReq* lisAllocReq;
    LisIRMDeallocReq* lisDeallocReq;

    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);

};

#endif /* IRM_H_ */
