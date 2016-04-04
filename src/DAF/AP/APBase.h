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

#ifndef APBASE_H_
#define APBASE_H_

#include <omnetpp.h>
#include <string>
#include "Flow.h"
#include "APIResult.h"
#include "CDAPMessage_m.h"

class APBase : public cSimpleModule {
public:
    APBase();
    virtual ~APBase();

    virtual void A_GETOPEN_R(APIResult* result) = 0;
    virtual void A_GETREAD_R(APIResult* result) = 0;
    virtual void A_GETWRITE_R(APIResult* result) = 0;

protected:
    virtual bool A_OPEN(int invokeID, std::string APname, std::string APinst, std::string AEname, std::string AEinst) = 0;
    virtual bool A_OPEN(int invokeID, Flow* flow);
    virtual bool A_CLOSE(int CDAPConn, int invokeID = 0) = 0;
    virtual bool A_READ(int CDAPConn, std::string objName, int invokeID) = 0;
    virtual bool A_WRITE(int CDAPConn, object_t *obj, int invokeID) = 0;

};

#endif /* APBASE_H_ */
