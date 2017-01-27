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

#ifndef IRM_H_
#define IRM_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/IRM/IRMListeners.h"
#include "DAF/IRM/ConnectionTable.h"
#include "Common/RINASignals.h"
#include "DAF/DA/DA.h"
#include "DIF/FA/FABase.h"
#include "Common/ExternConsts.h"
#include "Common/SDUData_m.h"

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

    /*
    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);
    */

};

#endif /* IRM_H_ */
