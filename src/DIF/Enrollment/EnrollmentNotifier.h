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

#ifndef __RINA_ENROLLMENTNOTIFIER_H_
#define __RINA_ENROLLMENTNOTIFIER_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/Enrollment/EnrollmentNotifierBase.h"
#include "DIF/Enrollment/EnrollmentNotifierListeners.h"
#include "DIF/RIB/RIBdBase.h"

extern const char* MSG_ENROLLMENT;

class EnrollmentNotifier : public EnrollmentNotifierBase
{
  public:
    virtual void sendStartEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStartEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStopEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStopEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStartOperationRequest(OperationObj* obj);
    virtual void sendStartOperationResponse(OperationObj* obj);
    virtual void sendCACE(CDAPMessage* msg);

  protected:
    RIBdBase* RIBd;

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

    LisRIBDRcvCACE*             lisRIBDRcvCACE;
    LisRIBDRcvEnrollCACE*       lisRIBDRcvEnrollCACE;
    LisRIBDStaEnrolReq*         lisRIBDStaEnrolReq;
    LisRIBDStaEnrolRes*         lisRIBDStaEnrolRes;
    LisRIBDStoEnrolReq*         lisRIBDStoEnrolReq;
    LisRIBDStoEnrolRes*         lisRIBDStoEnrolRes;
    LisRIBDStaOperReq*          lisRIBDStaOperReq;
    LisRIBDStaOperRes*          lisRIBDStaOperRes;

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

#endif
