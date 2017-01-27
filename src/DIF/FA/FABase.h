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

#ifndef FABASE_H_
#define FABASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/FA/NFlowTable.h"

extern const char* TIM_FAPENDFLOWS;

class FABase : public cSimpleModule {
  public:

    FABase();
    virtual ~FABase();

    std::list<Flow*> PendingFlows;

    virtual bool receiveAllocateRequest(Flow* flow) = 0;
    virtual bool receiveMgmtAllocateRequest(Flow* mgmtflow) = 0;
    virtual bool receiveMgmtAllocateRequest(APNamingInfo src, APNamingInfo dst) = 0;
    virtual bool receiveMgmtAllocateFinish() = 0;
    virtual void receiveNM1FlowCreated(Flow* flow) = 0;
    //virtual void receiveCreateResponseFlowPositiveFromRibd(Flow* flow) = 0;
    virtual bool receiveCreateFlowRequestFromRibd(Flow* flow) = 0;
    virtual bool receiveDeallocateRequest(Flow* flow) = 0;
    virtual void deinstantiateFai(Flow* flow) = 0;
    virtual bool invokeNewFlowRequestPolicy(Flow* flow) = 0;

    virtual bool setOriginalAddresses(Flow* flow) = 0;
    virtual bool setNeighborAddresses(Flow* flow) = 0;

    NFlowTable* getNFlowTable() const;
    const Address& getMyAddress() const;

  protected:
    NFlowTable* N_flowTable;
    Address MyAddress;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();

};


#endif /* FABASE_H_ */
