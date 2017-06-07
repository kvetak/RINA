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

#ifndef DAFRIBDBASE_H_
#define DAFRIBDBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries

#include "Common/ExternConsts.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/Enrollment/DAFEnrollmentObj.h"
#include "DAF/Enrollment/DAFOperationObj.h"
#include "Common/PDU.h"
#include "DAF/RIB/RIB/RIBBase.h"

class DAFRIBdBase : public cSimpleModule {
public:
    enum SubscriptionOption {READ, WRITE};
    enum SubscriptionOperation {NOTIFY, STORE};
    enum SubscriptionWhen {ON_REQUEST, ON_CHANGE};
    DAFRIBdBase();
    virtual ~DAFRIBdBase();

    virtual void receiveData(CDAPMessage* flow) = 0;
    virtual void signalizeSendData(CDAPMessage* msg) = 0;

    /* subscription API */
    virtual void createSubscription(DAFRIBdBase::SubscriptionOption option,
            DAFRIBdBase::SubscriptionWhen when,
            DAFRIBdBase::SubscriptionOperation operation,
            std::string obj,
            std::string member,
            int subscId) = 0;

    virtual void deleteSubscription(int subscId) = 0;
    virtual void readSubscription(int subscId) = 0;

    virtual void createObj(AEBase* iae, std::string objName, object_t *obj) = 0;
    virtual void deleteObj(AEBase* iae, std::string objName) = 0;

    /* create&delete IAE in RIB */
    virtual void createIAE(AEBase* iae) = 0;
    virtual void deleteIAE(AEBase* iae) = 0;

    long getNewInvokeId();
protected:

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;



    RIBBase* rib;
};

#endif /* DAFRIBDBASE_H_ */
