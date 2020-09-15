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
 * @brief Class representing Flow allocator component
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2015-03-10
 */

#ifndef FA_H_
#define FA_H_

// Standard libraries
#include <omnetpp.h>

// RINASim libraries
#include "DIF/FA/FABase.h"
#include "Common/ExternConsts.h"

// Forward declarations
class DA;
class EFCP;
class EnrollmentStateTable;
class Enrollment;
class FAI;
class Flow;
class NewFlowRequestBase;
class NFlowTable;
class RABase;
class QoSReq;

class FA : public FABase, public cListener
{
  public:
    // Signals
    static const simsignal_t createRequestForwardSignal;
    static const simsignal_t createResponseNegativeSignal;

  private:
    EFCP* efcp = nullptr;
    DA* difAllocator = nullptr;
    RABase* raModule = nullptr;
    NewFlowRequestBase* nFloReqPolicy = nullptr;
    Enrollment* enrollment = nullptr;
    EnrollmentStateTable* enrollmentStateTable = nullptr;

  public:
    FA() = default;

    virtual bool receiveAllocateRequest(Flow* flow);
    virtual bool receiveMgmtAllocateRequest(Flow* mgmtflow);
    virtual bool receiveMgmtAllocateRequest(APNamingInfo src, APNamingInfo dst);
    virtual bool receiveMgmtAllocateFinish();
    virtual void receiveNM1FlowCreated(Flow* flow);
    virtual bool receiveDeallocateRequest(Flow* flow);
    virtual bool receiveCreateFlowRequestFromRibd(Flow* flow);

    virtual void deinstantiateFai(Flow* flow);

    virtual bool setOriginalAddresses(Flow* flow);
    virtual bool setNeighborAddresses(Flow* flow);

    bool invokeNewFlowRequestPolicy(Flow* flow);

    //Signals
    simsignal_t sigFACreReqFwd;
    simsignal_t sigFACreResNega;
    simsignal_t sigFACreResPosiFwd;
    simsignal_t sigFAAllocFinMgmt;

    //Listeners
    //LisFAAllocReq*      lisAllocReq;
    //LisFADeallocReq*    lisDeallocReq;
    LisFAAllocFinMgmt*  lisEnrollFin;
    LisFACreFloPosi*    lisCreFloPosi;
    LisFACreReq*        lisCreReq;

  protected:
    //SimpleModule overloads
    virtual void initialize(int stage);
    virtual int numInitStages() const { return 1; };
    virtual void handleMessage(cMessage *msg);

    //cListener overload
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);

    void initPointers();
    void initSignalsAndListeners();

    bool isMalformedFlow(Flow* flow);
    FAI* createFAI(Flow* flow);

    const Address getAddressFromDa(const APN& apn, bool useNeighbor, bool isMgmtFlow);

    bool changeDstAddresses(Flow* flow, bool useNeighbor);
    bool changeSrcAddress(Flow* flow, bool useNeighbor);
};

#endif /* FLOWALLOCATOR_H_ */
