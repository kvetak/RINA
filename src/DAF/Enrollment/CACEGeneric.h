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

#ifndef DAF_ENROLLMENT_CACEGENERIC_H_
#define DAF_ENROLLMENT_CACEGENERIC_H_

#include "DAF/Enrollment/CACEBase.h"
#include "DAF/AE/AE.h"

class AE;

class CACEGeneric : public CACEBase {
public:
    CACEGeneric();
    CACEGeneric(AE *outerClass);
    void startCACE(Flow* flow);
    void insertStateTableEntry(Flow* flow);
    void authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg);
    void receivePositiveConnectResponse(CDAPMessage* msg);
    void receiveNegativeConnectResponse(CDAPMessage* msg);
    void receiveConnectRequest(CDAPMessage* msg);

    void processConResPosi(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processConResNega(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processNewConReq(DAFEnrollmentStateTableEntry* entry);
    virtual ~CACEGeneric();
protected:
    AE* outerClass;
};

#endif /* DAF_ENROLLMENT_CACEGENERIC_H_ */
