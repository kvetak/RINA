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

#ifndef AEMGMTBASE_H_
#define AEMGMTBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "ExternConsts.h"
#include "Flow.h"
#include "CDAPMessage_m.h"
#include "DAFEnrollmentObj.h"
#include "DAFOperationObj.h"
#include "CongestionDescriptor.h"
#include "PDU.h"
#include "IntRoutingUpdate.h"


class AEMgmtBase : public cSimpleModule {
  public:
    AEMgmtBase();
    virtual ~AEMgmtBase();

    virtual void sendStartEnrollmentRequest(DAFEnrollmentObj* obj) = 0;
    virtual void sendStartEnrollmentResponse(DAFEnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentRequest(DAFEnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentResponse(DAFEnrollmentObj* obj) = 0;
    virtual void sendStartOperationRequest(DAFOperationObj* obj) = 0;
    virtual void sendStartOperationResponse(DAFOperationObj* obj) = 0;
    virtual void sendCACE(CDAPMessage* msg) = 0;
    virtual void receiveData(CDAPMessage* flow) = 0;
    virtual void receiveCACE(CDAPMessage* msg) = 0;

    void setMyAddress(const Address& addr);
    const Address& getMyAddress() const;

  protected:
    Address MyAddress;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();
    long getNewInvokeId();

};

#endif /* AEMGMTBASE_H_ */
