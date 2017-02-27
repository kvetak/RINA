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
 * @file DAFEnrollment.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief DAFEnrollment and CACE
 * @detail
 */

#ifndef __RINA_DAFENROLLMENT_H_
#define __RINA_DAFENROLLMENT_H_

#include <omnetpp.h>
#include "Common/RINASignals.h"
#include "Common/Flow.h"
#include "DAF/CDAP/CDAPMessage_m.h"
#include "DAF/IRM/ConnectionTable.h"
#include "Common/ExternConsts.h"
#include "DAF/Enrollment/DAFEnrollmentListeners.h"
#include "DAF/Enrollment/DAFEnrollmentStateTable.h"
#include "DAF/Enrollment/DAFEnrollmentNotifier.h"
#include "Common/Address.h"
#include "DAF/AEManagement/AEMgmt.h"
#include "DAF/Enrollment/DAFEnrollmentObj.h"
#include "DAF/Enrollment/DAFOperationObj.h"
#include "DIF/FA/FABase.h"
#include "DAF/IRM/IRM.h"
#include "DAF/Enrollment/DAFEnrollmentBase.h"
#include "DAF/Enrollment/CACEMgmt.h"

extern const char* DAF_MSG_ENRLCON;
extern const char* DAF_MSG_ENRLREL;

class LisDAFEnrollmentAllResPosi;
class LisDAFEnrollmentGetFlowFromFaiCreResPosi;
class LisDAFEnrollmentStartEnrollReq;
class LisDAFEnrollmentStartEnrollRes;
class LisDAFEnrollmentStopEnrollReq;
class LisDAFEnrollmentStopEnrollRes;
class LisDAFEnrollmentStopOperationReq;
class LisDAFEnrollmentStartOperationRes;
class LisDAFEnrollmentConResPosi;
class LisDAFEnrollmentConResNega;
class LisDAFEnrollmentConReq;
class LisDAFEnrollmentRequest;
class LisDAFEnrollmentAllReqFromFai;

class CACEMgmt;
typedef std::list<APNIPair> APNIPairs;
typedef std::map<simtime_t, APNIPairs*> DAFEnrollCommands;

class DAFEnrollment : public DAFEnrollmentBase
{
  friend class CACEMgmt;
  public:
    enum IconEnrolStatus {ENICON_ENROLLED, ENICON_FLOWMIS, ENICON_NOTENROLLED};

    DAFEnrollment();
    virtual ~DAFEnrollment();
    void startCACE(Flow* flow);
    void startEnrollment(DAFEnrollmentStateTableEntry* entry);
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

    void receiveAllocationResponsePositive(Flow* flow);
    void receiveAllocationRequestFromFAI(Flow* flow);

    void createBindings(Flow *flow, DAFEnrollmentNotifier* module);

    void checkEnrolled(APNIPair* apnip);


    IRM* Irm;
    CACEMgmt* cace;
  protected:
    void initPointers();
    void initSignalsAndListeners();
    virtual void initialize();

    void updateEnrollmentDisplay(DAFEnrollment::IconEnrolStatus status);

    void parseConfig(cXMLElement* config);

    void authenticate(DAFEnrollmentStateTableEntry* entry, CDAP_M_Connect* msg);
    void processConResPosi(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processConResNega(DAFEnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processNewConReq(DAFEnrollmentStateTableEntry* entry);
    void processStopEnrollmentImmediate(DAFEnrollmentStateTableEntry* entry);
    void processStopEnrollmentResponse(DAFEnrollmentStateTableEntry* entry);
    void createFlow(APNIPair* apnip);
    DAFEnrollmentNotifier* createMgmtAE(Flow* flow);

    //Vesely -> Jerabek: WTF?
    //FABase* FlowAlloc;

    DAFEnrollCommands PreenrollConnects;
    DAFEnrollCommands PreenrollReleases;

    int authType;
    std::string apName;
    std::string apInstance;
    std::string authName;
    std::string authPassword;
    std::string authOther;
    int maxConRetries;
    int numOfConnects;
    int currentMgmtAEInstanceId;

    simsignal_t sigDAFEnrollmentCACESendData;
    simsignal_t sigDAFEnrollmentSendData;
    simsignal_t sigDAFEnrollmentStartEnrollReq;
    simsignal_t sigDAFEnrollmentStartEnrollRes;
    simsignal_t sigDAFEnrollmentStopEnrollReq;
    simsignal_t sigDAFEnrollmentStopEnrollRes;
    simsignal_t sigDAFEnrollmentStartOperReq;
    simsignal_t sigDAFEnrollmentStartOperRes;
    simsignal_t sigDAFEnrollmentFinish;
    simsignal_t sigDAFEnrollmentEnrollPosi;
    simsignal_t sigDAFEnrollmentAllocResNega;
    simsignal_t sigDAFEnrollmentAllocResPosi;

    LisDAFEnrollmentAllResPosi* lisDAFEnrollmentAllResPosi;
    LisDAFEnrollmentGetFlowFromFaiCreResPosi* lisDAFEnrollmentGetFlowFromFaiCreResPosi;

    LisDAFEnrollmentStartEnrollReq* lisDAFEnrollmentStartEnrollReq;
    LisDAFEnrollmentStartEnrollRes* lisDAFEnrollmentStartEnrollRes;
    LisDAFEnrollmentStopEnrollReq* lisDAFEnrollmentStopEnrollReq;
    LisDAFEnrollmentStopEnrollRes* lisDAFEnrollmentStopEnrollRes;
    LisDAFEnrollmentStopOperationReq* lisDAFEnrollmentStartOperationReq;
    LisDAFEnrollmentStartOperationRes* lisDAFEnrollmentStartOperationRes;
    LisDAFEnrollmentConResPosi* lisDAFEnrollmentConResPosi;
    LisDAFEnrollmentConResNega* lisDAFEnrollmentConResNega;
    LisDAFEnrollmentConReq* lisDAFEnrollmentConReq;
    LisDAFEnrollmentRequest* lisDAFEnrollmentRequest;
    LisDAFEnrollmentAllReqFromFai* lisDAFEnrollmentAllReqFromFai;

    DAFEnrollmentStateTable* StateTable;

    void signalizeCACESendData(CDAPMessage* cmsg);
    void signalizeStartEnrollmentRequest(DAFEnrollmentObj* obj);
    void signalizeStartEnrollmentResponse(DAFEnrollmentObj* obj);
    void signalizeStopEnrollmentRequest(DAFEnrollmentObj* obj);
    void signalizeStopEnrollmentResponse(DAFEnrollmentObj* obj);
    void signalizeStartOperationRequest(DAFOperationObj* obj);
    void signalizeStartOperationResponse(DAFOperationObj* obj);
    void signalizeEnrollmentFinished(DAFEnrollmentStateTableEntry* entry);
    void signalizeEnrolled();


    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);

    virtual void handleMessage(cMessage *msg);
};

#endif
