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
#include "FA.h"
#include "Flow.h"

class IRM : public cSimpleModule   {
  public:
    IRM();
    virtual ~IRM();

    void receiveAllocationResponseNegative(cObject* obj);
    void receiveAllocationRequestFromFAI(cObject* obj);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    void registerFASigs();

    void prepareTestMessage(simtime_t tim);
    void handleTestMessage(cMessage* msg);

    //Signals
    simsignal_t sigIRMAllocReq;
    simsignal_t sigFAIAllocReq;
    simsignal_t sigIRMAllocResPosi;
    simsignal_t sigIRMAllocResNega;
    simsignal_t sigIRMDeallocReq;
    simsignal_t sigFAIDeallocReq;
    //Listeners
    LisIRMAllocResNega* lisAllocResNega;
    LisIRMAllocReqFromFAI* lisAllocReqFromFai;
    //Signaling
    void signalizeFAAllocateRequest(Flow* flow);
    //Listeners


};

#endif /* IRM_H_ */
