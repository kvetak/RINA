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

#ifndef DAF_ENROLLMENT_CACEBASE_H_
#define DAF_ENROLLMENT_CACEBASE_H_

#include "Common/Flow.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/Enrollment/DAFEnrollmentStateTableEntry.h"
#include "DAF/Enrollment/DAFEnrollmentStateTable.h"

extern const char* DAF_MSG_CONREQ;
extern const char* DAF_MSG_CONREQRETRY;
extern const char* DAF_MSG_CONRESPOS;
extern const char* DAF_MSG_CONRESNEG;

class CACEBase {
public:
    CACEBase();
    virtual void startCACE(Flow* flow) = 0;
    virtual void insertStateTableEntry(Flow* flow) = 0;
    virtual void authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg) = 0;
    virtual void receivePositiveConnectResponse(CDAPMessage* msg) = 0;
    virtual void receiveNegativeConnectResponse(CDAPMessage* msg) = 0;
    virtual void receiveConnectRequest(CDAPMessage* msg) = 0;

    virtual void processConResPosi(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) = 0;
    virtual void processConResNega(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg) = 0;
    virtual void processNewConReq(DAFEnrollmentStateTableEntry* entry) = 0;
    virtual ~CACEBase();

protected:
    DAFEnrollmentStateTable* StateTable;
};

#endif /* DAF_ENROLLMENT_CACEBASE_H_ */
