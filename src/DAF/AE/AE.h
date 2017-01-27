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

#ifndef __RINA_AE_H_
#define __RINA_AE_H_

//Standard libraries
#include <omnetpp.h>
#include <sstream>
//RINASim libraries
#include "Common/Utils.h"
#include "DAF/AE/AEBase.h"
#include "DAF/AE/AEListeners.h"
#include "Common/RINASignals.h"
#include "DAF/IRM/IRM.h"
#include "DAF/IRM/ConnectionTable.h"
#include "Common/ExternConsts.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/AP/APIReqObj.h"
#include "DAF/AP/APIResult.h"
#include "DAF/Enrollment/CACEGeneric.h"

class CACEGeneric;

class AE : public AEBase
{
  friend class CACEGeneric;
  public:
    AE();
    virtual ~AE();
    void receiveData(CDAPMessage* obj);
    void sendData(Flow* flow, CDAPMessage* msg);
    void apiSwitcher(APIReqObj *obj);

    void sendAllocationRequest(Flow* flow);
    void sendDeallocationRequest(Flow* flow);

    void receiveAllocationRequestFromFAI(Flow* flow);
    void receiveDeallocationRequestFromFAI(Flow* flow);

    void receiveAllocationResponseNegative(Flow* flow);
    void receiveAllocationResponsePositive(Flow* flow);

    virtual void afterOnStart();
    void CACEFinished();
    void start(Flow *flow);



    virtual bool onA_read(APIReqObj* obj);
    virtual bool onA_write(APIReqObj* obj);

  protected:
    IRM* Irm;
    cModule* Cdap;
    CACEGeneric* Cace;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initPointers();
    void initSignalsAndListeners();

    void insertFlow();
    bool createBindings(Flow& flow);
    bool deleteBindings(Flow& flow);

    //Signals
    simsignal_t sigAEAllocReq;
    simsignal_t sigAEDeallocReq;
    simsignal_t sigAESendData;
    simsignal_t sigAEAllocResPosi;
    simsignal_t sigAEAllocResNega;
    simsignal_t sigAEConReq;
    simsignal_t sigAERelReq;
    simsignal_t sigAEEnrolled;

    //API AE-AP Signals
    simsignal_t sigAEAPAPI;

    //Listeners
    LisAEReceiveData* lisAERcvData;
    LisAEAllReqFromFai* lisAEAllReqFromFai;
    LisAEAllResPosi* lisAEAllResPosi;
    LisAEAllResNega* lisAEAllResNega;
    LisAEDeallReqFromFai* lisAEDeallReqFromFai;
    LisAEDeallReqFromFai* lisAEDeallResFromFai;
    LisAEConResPosi* lisAEConResPosi;
    LisAEConResNega* lisAEConResNega;
    LisAERelRes* lisAERelRes;
    LisAEEnrolled* lisAEEnrolled;

    //API AP-AE Listeners
    LisAPAEAPI* lisAPAEAPI;

    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);
    void signalizeSendData(cMessage* msg);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);
    void signalizeConnectionRequest(CDAPMessage* msg);
    void signalizeReleaseRequest(CDAPMessage* msg);
    void signalizeAEAPAPI(APIResult* obj);
    virtual void connect();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);
    virtual void processMWrite(CDAPMessage* msg);
    virtual void processMWriteR(CDAPMessage* msg);

};

#endif
