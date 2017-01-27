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

#ifndef DAFENROLLMENTNOTIFIER_H_
#define DAFENROLLMENTNOTIFIER_H_

#include <omnetpp.h>
#include "DAF/AEManagement/AEMgmtBase.h"
#include "DAF/Enrollment/DAFEnrollmentNotifierListeners.h"
#include "DAF/Enrollment/DAFEnrollmentNotifierBase.h"
#include "Common/Flow.h"

extern const char* DAF_MSG_ENROLLMENT;
extern const int DAF_VAL_DEFINSTANCE;

class DAFEnrollmentNotifier : public DAFEnrollmentNotifierBase
{
  public:
    virtual void sendStartEnrollmentRequest(DAFEnrollmentObj* obj);
    virtual void sendStartEnrollmentResponse(DAFEnrollmentObj* obj);
    virtual void sendStopEnrollmentRequest(DAFEnrollmentObj* obj);
    virtual void sendStopEnrollmentResponse(DAFEnrollmentObj* obj);
    virtual void sendStartOperationRequest(DAFOperationObj* obj);
    virtual void sendStartOperationResponse(DAFOperationObj* obj);
    virtual void sendCACE(CDAPMessage* msg);
    virtual void setFlow(Flow* flow);
    virtual Flow* getFlow();

  protected:
    AEMgmtBase* RIBd;
    Flow* FlowObj;

    simsignal_t sigRIBDStartEnrollReq;
    simsignal_t sigRIBDStartEnrollRes;
    simsignal_t sigRIBDStopEnrollReq;
    simsignal_t sigRIBDStopEnrollRes;
    simsignal_t sigRIBDStartOperationReq;
    simsignal_t sigRIBDStartOperationRes;
    simsignal_t sigRIBDConResPosi;
    simsignal_t sigRIBDConResNega;
    simsignal_t sigRIBDConReq;
    simsignal_t sigRIBDCACESend;


    LisDAFEnrollmentNotifierRcvCACE*             lisDAFEnrollmentNotifierRcvCACE;
    LisDAFEnrollmentNotifierRcvEnrollCACE*       lisDAFEnrollmentNotifierRcvEnrollCACE;
    LisDAFEnrollmentNotifierStaEnrolReq*         lisDAFEnrollmentNotifierStaEnrolReq;
    LisDAFEnrollmentNotifierStaEnrolRes*         lisDAFEnrollmentNotifierStaEnrolRes;
    LisDAFEnrollmentNotifierStoEnrolReq*         lisDAFEnrollmentNotifierStoEnrolReq;
    LisDAFEnrollmentNotifierStoEnrolRes*         lisDAFEnrollmentNotifierStoEnrolRes;
    LisDAFEnrollmentNotifierStaOperReq*          lisDAFEnrollmentNotifierStaOperReq;
    LisDAFEnrollmentNotifierStaOperRes*          lisDAFEnrollmentNotifierStaOperRes;

    void initPointers();
    void initSignalsAndListeners();

    //SimpleModule overloads
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    //CDAPProcessingBase overload
    virtual void signalizeMessage(CDAPMessage* msg);

    virtual void processMConnect(CDAP_M_Connect* msg);
    virtual void processMConnectR(CDAP_M_Connect_R* msg);
    virtual void processMStart(CDAP_M_Start* msg);
    virtual void processMStartR(CDAP_M_Start_R* msg);
    virtual void processMStop(CDAP_M_Stop* msg);
    virtual void processMStopR(CDAP_M_Stop_R* msg);

    void signalizeConnectResponsePositive(CDAPMessage* msg);
    void signalizeConnectResponseNegative(CDAPMessage* msg);
    void signalizeConnectRequest(CDAPMessage* msg);
    void signalizeSendCACE(CDAPMessage* msg);
    void signalizeStartEnrollmentRequest(CDAPMessage* msg);
    void signalizeStartEnrollmentResponse(CDAPMessage* msg);
    void signalizeStopEnrollmentRequest(CDAPMessage* msg);
    void signalizeStopEnrollmentResponse(CDAPMessage* msg);
    void signalizeStartOperationRequest(CDAPMessage* msg);
    void signalizeStartOperationResponse(CDAPMessage* msg);
};

#endif /* DAFENROLLMENTNOTIFIER_H_ */
