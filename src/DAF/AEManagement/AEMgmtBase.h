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
#include "Common/ExternConsts.h"
#include "Common/Flow.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/Enrollment/DAFEnrollmentObj.h"
#include "DAF/Enrollment/DAFOperationObj.h"
#include "Common/CongestionDescriptor.h"
#include "Common/PDU.h"
#include "DIF/Routing/IntRoutingUpdate.h"


class AEMgmtBase : public cSimpleModule {
  public:
    AEMgmtBase();
    virtual ~AEMgmtBase();
    virtual void signalizeSendData(CDAPMessage* msg) = 0;
    virtual void receiveData(CDAPMessage* cimsg) = 0;
    void setMyAddress(const Address& addr);
    const APNamingInfo& getSrcNamingInfo() const;
    const APNamingInfo& getDstNamingInfo() const;
    const Address& getMyAddress() const;

  protected:
    Address MyAddress;

    std::string srcApName;
    std::string srcApInstance;
    std::string srcAeName;
    std::string srcAeInstance;

    std::string dstApName;
    std::string dstApInstance;
    std::string dstAeName;
    std::string dstAeInstance;

    APNamingInfo srcApni;
    APNamingInfo dstApni;


    //SimpleModule overloads
    virtual void initialize() = 0;
    void initNamingInfo();
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();
    long getNewInvokeId();

};

#endif /* AEMGMTBASE_H_ */
