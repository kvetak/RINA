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
#include "Common/Flow.h"
#include "DAF/AP/APIResult.h"
#include "DAF/AP/APIRetObj.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include <map>
#include "Common/ExternConsts.h"
#include "Common/RINASignals.h"

class APBase : public cSimpleModule {
public:
    APBase();
    virtual ~APBase();

    int getCurrentAEInstNum(std::string AEName);

    virtual void onA_getOpen(APIResult* result) = 0;
    virtual void onA_getRead(APIResult* result) = 0;
    virtual void onA_getWrite(APIResult* result) = 0;
    virtual void onClose(APIResult* result) = 0;

protected:
    enum EnrollmentState {NOT_ENROLLED, ENROLLING, ENROLLED};

    virtual bool a_open(int invokeID, std::string APname, std::string APinst, std::string AEname, std::string AEinst) = 0;
    virtual bool a_open(int invokeID, Flow* flow) = 0;
    virtual bool a_close(int CDAPConn, int invokeID = 0) = 0;
    virtual bool a_read(int CDAPConn, std::string objName, int invokeID = 0) = 0;
    virtual bool a_write(int CDAPConn, std::string objName, object_t *obj, int invokeID = 0) = 0;

    virtual APIRetObj* a_getopen_r(int invokeID) = 0;
    virtual APIRetObj* a_getclose_r(int CDAPConn, int invokeID = 0) = 0;
    virtual bool a_read_r(int CDAPconn, int invokeID, std::string objName, object_t *obj, bool complete = true) = 0;
    virtual APIRetObj* a_get_read_r(int CDAPConn, int invokeID) = 0;
    virtual bool a_cancelread_r(int CDAPConn, int invokeID = 0) = 0;
    virtual APIRetObj* a_getwrite_r(int CDAPconn, int invokeID, APIResult* result, std::string objName, object_t *obj = NULL) = 0;

    int getNewInvokeID();

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    int getNewAEInstNum(std::string AEName);

    unsigned long getNewCdapConID();

    EnrollmentState isEnrolled;
private:
    int currentInvokeId;
    unsigned long currentCdapConId;
    std::map<std::string, int> AEInstNumbers;

};

#endif /* APBASE_H_ */
