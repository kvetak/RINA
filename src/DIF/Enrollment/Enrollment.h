//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __RINA_ENROLLMENT_H_
#define __RINA_ENROLLMENT_H_

#include <omnetpp.h>
#include "RINASignals.h"
#include "Flow.h"
#include "CDAPMessage_m.h"
#include "ConnectionTable.h"
#include "ExternConsts.h"
#include "EnrollmentListeners.h"
#include "EnrollmentStateTable.h"
#include "Address.h"
#include "RIBd.h"
#include "EnrollmentObj.h"
#include "OperationObj.h"


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
class Enrollment : public cSimpleModule
{
  public:
    Enrollment();
    virtual ~Enrollment();
    void startCACE(Flow* flow);
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

    void authenticate(EnrollmentStateTableEntry* entry, CDAP_M_Connect* msg);
    void processConResPosi(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processConResNega(EnrollmentStateTableEntry* entry, CDAPMessage* cmsg);
    void processNewConReq(EnrollmentStateTableEntry* entry);
    void processStopEnrollmentImmediate(EnrollmentStateTableEntry* entry);
    void processStopEnrollmentResponse(EnrollmentStateTableEntry* entry);



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
    RIBd* ribd;

    void signalizeCACESendData(CDAPMessage* cmsg);
    void signalizeStartEnrollmentRequest(EnrollmentObj* obj);
    void signalizeStartEnrollmentResponse(EnrollmentObj* obj);
    void signalizeStopEnrollmentRequest(EnrollmentObj* obj);
    void signalizeStopEnrollmentResponse(EnrollmentObj* obj);
    void signalizeStartOperationRequest(OperationObj* obj);
    void signalizeStartOperationResponse(OperationObj* obj);

    virtual void handleMessage(cMessage *msg);
};

#endif
