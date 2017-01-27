//
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
#include "DIF/FA/FAIBase.h"
#include "DIF/FA/FABase.h"
#include "DIF/FA/FAIListeners.h"
#include "Common/RINASignals.h"
#include "DIF/EFCP/EFCP.h"
#include "DIF/FA/AllocateRetry/AllocateRetryBase.h"

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
    virtual bool receiveAllocateResponsePositive();
    virtual void receiveAllocateResponseNegative();
    virtual bool receiveCreateRequest();
    virtual bool receiveCreateResponsePositive(Flow* flow);
    virtual bool receiveCreateResponseNegative();
    virtual bool receiveDeallocateRequest();
    virtual void receiveDeleteRequest(Flow* flow);
    virtual void receiveDeleteResponse();

    virtual void receiveCreateFlowResponsePositiveFromNminusOne();
    virtual void receiveCreateFlowResponseNegativeFromNminusOne();


    void postInitialize(FABase* fa, Flow* fl, EFCP* efcp);

    const FABase* getFa() const {
        return FaModule;
    }

    int getLocalCepId() const;
    void setLocalCepId(int localCepId);
    int getLocalPortId() const;
    void setLocalPortId(int localPortId);
    int getRemoteCepId() const;
    void setRemoteCepId(int remoteCepId);
    int getRemotePortId() const;
    void setRemotePortId(int remotePortId);

  protected:
    int localPortId;
    int localCEPId;
    int remotePortId;
    int remoteCEPId;

    AllocateRetryBase* AllocRetryPolicy;

    cMessage* creReqTimer;
    //double creReqTimeout;

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
    LisFAICreResNega*    lisCreResNega;
    LisFAICreResPosi*    lisCreResPosi;
    LisFAIDelReq*        lisDelReq;
    LisFAIDelRes*        lisDelRes;
    LisFAICreResPosiNminusOne* lisCreResPosiNmO;
    LisFAICreResNegaNminusOne* lisCreResNegaNmO;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    EFCP* EfcpModule;

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
    void signalizeAllocateRequestToOtherFais(Flow* flow);

};

//Free function
std::ostream& operator<< (std::ostream& os, const FAI& fai);

#endif /* FAI_H_ */
