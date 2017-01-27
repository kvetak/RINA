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

/**
 * @file Enrollment.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment and CACE
 * @detail
 */

#ifndef __RINA_ENROLLMENT_H_
#define __RINA_ENROLLMENT_H_

#include <omnetpp.h>
#include "Common/Utils.h"
#include "Common/RINASignals.h"
#include "Common/Flow.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/IRM/ConnectionTable.h"
#include "Common/ExternConsts.h"
#include "DIF/Enrollment/EnrollmentListeners.h"
#include "DIF/Enrollment/EnrollmentStateTable.h"
#include "Common/Address.h"
#include "DIF/RIB/RIBd.h"
#include "DIF/Enrollment/EnrollmentObj.h"
#include "DIF/Enrollment/OperationObj.h"
#include "DIF/FA/FABase.h"

extern const char* MSG_CONREQ;
extern const char* MSG_CONREQRETRY;
extern const char* MSG_CONRESPOS;
extern const char* MSG_CONRESNEG;
extern const char* MSG_ENRLCON;
extern const char* MSG_ENRLREL;

class LisEnrollmentAllResPosi;
class LisEnrollmentGetFlowFromFaiCreResPosi;
class LisEnrollmentStartEnrollReq;
class LisEnrollmentStartEnrollRes;
class LisEnrollmentStopEnrollReq;
class LisEnrollmentStopEnrollRes;
class LisEnrollmentStopOperationReq;
class LisEnrollmentStartOperationRes;
class LisEnrollmentConResPosi;
class LisEnrollmentConResNega;
class LisEnrollmentConReq;

typedef std::list<APNIPair> APNIPairs;
typedef std::map<simtime_t, APNIPairs*> EnrollCommands;

class Enrollment : public cSimpleModule
{
  public:
    enum IconEnrolStatus {ENICON_ENROLLED, ENICON_FLOWMIS, ENICON_NOTENROLLED};

    Enrollment();
    virtual ~Enrollment();
    void startCACE(APNIPair* apnip);
    void startEnrollment(EnrollmentStateTableEntry* entry);
    void insertStateTableEntry(Flow* flow);
    void receivePositiveConnectResponse(CDAPMessage* msg);
    void receiveNegativeConnectResponse(CDAPMessage* msg);
    void receiveConnectRequest(CDAPMessage* msg);

    void receiveStartEnrollmentRequest(CDAPMessage* msg);
    void receiveStartEnrollmentResponse(CDAPMessage* msg);
    void receiveStopEnrollmentRequest(CDAPMessage* msg);
    void receiveStopEnrollmentResponse(CDAPMessage* msg);
    void receiveStartOperationRequest(CDAPMessage* msg);
    void receiveStartOperationResponse(CDAPMessage* msg);


  protected:
    void initPointers();
    void initSignalsAndListeners();
    virtual void initialize();

    void updateEnrollmentDisplay(Enrollment::IconEnrolStatus status);

    void parseConfig(cXMLElement* config);

    void authenticate(EnrollmentStateTableEntry* entry, CDAP_M_Connect* msg);
    void processConResPosi(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processConResNega(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processNewConReq(EnrollmentStateTableEntry* entry);
    void processStopEnrollmentImmediate(EnrollmentStateTableEntry* entry);
    void processStopEnrollmentResponse(EnrollmentStateTableEntry* entry);

    FABase* FlowAlloc;

    EnrollCommands PreenrollConnects;
    EnrollCommands PreenrollReleases;

    int authType;
    std::string authName;
    std::string authPassword;
    std::string authOther;
    int maxConRetries;
    int numOfConnects;

    simsignal_t sigEnrollmentCACESendData;
    simsignal_t sigEnrollmentSendData;
    simsignal_t sigEnrollmentStartEnrollReq;
    simsignal_t sigEnrollmentStartEnrollRes;
    simsignal_t sigEnrollmentStopEnrollReq;
    simsignal_t sigEnrollmentStopEnrollRes;
    simsignal_t sigEnrollmentStartOperReq;
    simsignal_t sigEnrollmentStartOperRes;
    simsignal_t sigEnrollmentFinish;

    LisEnrollmentAllResPosi* lisEnrollmentAllResPosi;
    LisEnrollmentGetFlowFromFaiCreResPosi* lisEnrollmentGetFlowFromFaiCreResPosi;

    LisEnrollmentStartEnrollReq* lisEnrollmentStartEnrollReq;
    LisEnrollmentStartEnrollRes* lisEnrollmentStartEnrollRes;
    LisEnrollmentStopEnrollReq* lisEnrollmentStopEnrollReq;
    LisEnrollmentStopEnrollRes* lisEnrollmentStopEnrollRes;
    LisEnrollmentStopOperationReq* lisEnrollmentStartOperationReq;
    LisEnrollmentStartOperationRes* lisEnrollmentStartOperationRes;
    LisEnrollmentConResPosi* lisEnrollmentConResPosi;
    LisEnrollmentConResNega* lisEnrollmentConResNega;
    LisEnrollmentConReq* lisEnrollmentConReq;

    EnrollmentStateTable* StateTable;
    RIBd* RibDaemon;

    void signalizeCACESendData(CDAPMessage* cmsg);
    void signalizeStartEnrollmentRequest(EnrollmentObj* obj);
    void signalizeStartEnrollmentResponse(EnrollmentObj* obj);
    void signalizeStopEnrollmentRequest(EnrollmentObj* obj);
    void signalizeStopEnrollmentResponse(EnrollmentObj* obj);
    void signalizeStartOperationRequest(OperationObj* obj);
    void signalizeStartOperationResponse(OperationObj* obj);
    void signalizeEnrollmentFinished(EnrollmentStateTableEntry* entry);

    virtual void handleMessage(cMessage *msg);
};

#endif
