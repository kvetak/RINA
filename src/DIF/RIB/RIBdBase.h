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

#ifndef RIBDBASE_H_
#define RIBDBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries

#include "ExternConsts.h"
#include "CDAPMessage_m.h"
#include "EnrollmentObj.h"
#include "OperationObj.h"
#include "CongestionDescriptor.h"
#include "PDU.h"
#include "IntRoutingUpdate.h"


class RIBdBase : public cSimpleModule {
  public:
    RIBdBase();
    virtual ~RIBdBase();
    /*
    virtual void sendCreateRequestFlow(Flow* flow) = 0;
    virtual void sendCreateResponseNegative(Flow* flow) = 0;
    virtual void sendCreateResponsePostive(Flow* flow) = 0;
    virtual void sendDeleteRequestFlow(Flow* flow) = 0;
    virtual void sendDeleteResponseFlow(Flow* flow) = 0;
    virtual void receiveAllocationRequestFromFai(Flow* flow) = 0;
    virtual void receiveCreateFlowPositiveFromRa(Flow* flow) = 0;
    virtual void receiveCreateFlowNegativeFromRa(Flow* flow) = 0;

    virtual void sendStartEnrollmentRequest(EnrollmentObj* obj) = 0;
    virtual void sendStartEnrollmentResponse(EnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentRequest(EnrollmentObj* obj) = 0;
    virtual void sendStopEnrollmentResponse(EnrollmentObj* obj) = 0;
    virtual void sendStartOperationRequest(OperationObj* obj) = 0;
    virtual void sendStartOperationResponse(OperationObj* obj) = 0;
    virtual void sendCACE(CDAPMessage* msg) = 0;
    virtual void receiveCACE(CDAPMessage* msg) = 0;
    */
    virtual void receiveData(CDAPMessage* flow) = 0;
    /* Handles information coming from PDUFTG module. */
    virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * flow) = 0;

    virtual void sendCongestionNotification(PDU* pdu) = 0;

    virtual void signalizeSendData(CDAPMessage* msg) = 0;

    void setMyAddress(const Address& addr);
    const Address& getMyAddress() const;
    long getNewInvokeId();
  protected:
    Address MyAddress;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();
};

#endif /* RIBDBASE_H_ */
