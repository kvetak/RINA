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

#ifndef FAIBASE_H_
#define FAIBASE_H_

//Standard libraries
#include <omnetpp.h>

class Flow;

class FAIBase : public cSimpleModule {
  public:
    //Signals
    static const simsignal_t allocateRequestSignal;
    static const simsignal_t deallocateRequestSignal;
    static const simsignal_t deallocateResponseSignal;
    static const simsignal_t allocateResponsePositiveSignal;
    static const simsignal_t allocateResponseNegativeSignal;
    static const simsignal_t createRequestSignal;
    static const simsignal_t deleteRequestSignal;
    static const simsignal_t deleteResponseSignal;
    static const simsignal_t createResponseNegativeSignal;
    static const simsignal_t createResponsePositiveSignal;

  protected:
    Flow* flowObject;
    bool degenerateDataTransfer;

  public:
    FAIBase();
    virtual ~FAIBase();

    virtual std::string str() const = 0;

    virtual bool receiveAllocateRequest() = 0;
    virtual bool receiveAllocateResponsePositive() = 0;
    virtual void receiveAllocateResponseNegative() = 0;
    virtual bool receiveCreateRequest() = 0;
    virtual bool receiveCreateResponsePositive(Flow* flow) = 0;
    virtual bool receiveCreateResponseNegative() = 0;
    virtual bool receiveDeallocateRequest() = 0;
    virtual void receiveDeleteRequest(Flow* flow) = 0;
    virtual void receiveDeleteResponse() = 0;

    virtual void receiveCreateFlowResponsePositiveFromNminusOne() = 0;
    virtual void receiveCreateFlowResponseNegativeFromNminusOne() = 0;

    Flow* getFlow() const {
        return flowObject;
    }

    bool isDegenerateDataTransfer() const {
        return degenerateDataTransfer;
    }

    void setDegenerateDataTransfer(bool degenerateDataTransfer) {
        this->degenerateDataTransfer = degenerateDataTransfer;
    }

  protected:
    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
};

#endif /* FAIBASE_H_ */
