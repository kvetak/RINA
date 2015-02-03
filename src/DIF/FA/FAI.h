//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2014-11-19
 * @brief FlowAllocatorInstance class
 */
#ifndef FAI_H_
#define FAI_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "FAIBase.h"
#include "FABase.h"
#include "FAIListeners.h"
#include "RINASignals.h"
#include "EFCP.h"
#include "ModuleAccess.h"
#include "RABase.h"
#include "AllocateRetryBase.h"

//#include "PushBackChannel.h"

//Constants
extern const char* TIM_CREREQ;
extern const char* MOD_ALLOCRETRYPOLICY;

class FAI : public FAIBase  {
  public:
    FAI();
    virtual ~FAI();

    std::string info() const;

    virtual bool receiveAllocateRequest();
    virtual bool processDegenerateDataTransfer();
    virtual bool receiveAllocateResponsePositive();
    virtual void receiveAllocateResponseNegative();
    virtual bool receiveCreateRequest();
    virtual bool receiveCreateResponsePositive(Flow* flow);
    virtual bool receiveCreateResponseNegative();
    virtual bool receiveDeallocateRequest();
    virtual void receiveDeleteRequest();
    virtual void receiveDeleteResponse();

    virtual void receiveCreateFlowResponsePositiveFromNminusOne();
    virtual void receiveCreateFlowResponseNegativeFromNminusOne();


    void postInitialize(FABase* fa, Flow* fl, EFCP* efcp);

    const FABase* getFa() const {
        return FaModule;
    }

  protected:
    int portId;
    int cepId;
    AllocateRetryBase* AllocRetryPolicy;

    //TODO: Vesely - What about timeouts for M_DELETE and other control messages?
    cMessage* creReqTimer;
    double creReqTimeout;

    FABase* FaModule;

    //Signals
    simsignal_t sigFAIAllocReq;
    simsignal_t sigFAIDeallocReq;
    simsignal_t sigFAIDeallocRes;
    simsignal_t sigFAIAllocResPosi;
    simsignal_t sigFAIAllocResNega;
    simsignal_t sigFAICreReq;
    simsignal_t sigFAIDelReq;
    simsignal_t sigFAIDelRes;
    simsignal_t sigFAICreResNega;
    simsignal_t sigFAICreResPosi;
    //Listeners
    LisFAIAllocReq*      lisAllocReq;
    LisFAIAllocResNega*  lisAllocResNega;
    LisFAIAllocResPosi*  lisAllocResPosi;
    LisFAICreReq*        lisCreReq;
    LisFAICreResNega*    lisCreResNega;
    LisFAICreResPosi*    lisCreResPosi;
    LisFAIDelReq*        lisDelReq;
    LisFAIDelRes*        lisDelRes;
    LisFAICreResPosiNminusOne* lisCreResPosiNmO;
    LisFAICreResNegaNminusOne* lisCreResNegaNmO;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    EFCP* efcp;
    cGate* southI;
    cGate* southO;
    cGate* northI;
    cGate* northO;

    void initSignalsAndListeners();

    bool createEFCPI();
    void createNorthGates();
    bool createBindings();
    bool deleteBindings();

    bool invokeAllocateRetryPolicy();

    void signalizeCreateFlowRequest();
    void signalizeCreateFlowResponsePositive();
    void signalizeCreateFlowResponseNegative();
    void signalizeDeleteFlowRequest();
    void signalizeDeleteFlowResponse();
    void signalizeAllocationRequestFromFai();
    void signalizeDeallocateRequestFromFai();
    void signalizeDeallocateResponseFromFai();
    void signalizeAllocateResponseNegative();
    void signalizeAllocateResponsePositive();

};

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai);

#endif /* FAI_H_ */
