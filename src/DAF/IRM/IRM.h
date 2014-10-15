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

class IRM : public cSimpleModule   {
  public:
    IRM();
    virtual ~IRM();

    void receiveAllocationRequest(cObject* obj);
    void receiveDeallocationRequest(cObject* obj);
    void receiveAllocationResponseNegativeAppNotFound(cObject* obj);
    void receiveAllocationResponseNegative(cObject* obj);

    //void receiveAllocationRequestFromFAI(cObject* obj);

    ConnectionTable* getConTable() const;
    DA* getDifAllocator() const;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initPointers();

  private:

    ConnectionTable* ConTable;
    DA* DifAllocator;

    void initSignalsAndListeners();
    bool createBindings(Flow* flow);

    //Signals
    simsignal_t sigIRMAllocReq;
    simsignal_t sigIRMDeallocReq;


    //Listeners
    LisIRMAllocResNegaFa* lisAllocResNegaFa;
    LisIRMAllocResNegaFai* lisAllocResNegaFai;
    LisIRMAllocReqFai* lisAllocReqFai;
    LisIRMAllocReq* lisAllocReq;
    LisIRMDeallocReq* lisDeallocReq;

    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);

};

#endif /* IRM_H_ */
