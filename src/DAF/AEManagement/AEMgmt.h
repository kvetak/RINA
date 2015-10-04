//
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
 * @file AEMgmt.h
 * @author Vladimir Vesely, Kamil Jerabek (ivesely@fit.vutbr.cz, Kamil Jerabek)
 * @date Oct 2, 2014
 * @brief Kind of a Notification Board for DAF
 * @detail
 */

#ifndef AEMGMT_H_
#define AEMGMT_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AEMgmtBase.h"
#include "ExternConsts.h"
#include "AEMgmtListeners.h"
#include "RINASignals.h"
#include "PDU.h"
#include "IntRoutingUpdate.h"

//Constants
extern const char* DAF_MSG_CONGEST;
extern const char* DAF_MSG_FLO;
extern const char* DAF_MSG_FLOPOSI;
extern const char* DAF_MSG_FLONEGA;
extern const int   DAF_VAL_DEFINSTANCE;
extern const int   DAF_VAL_FLOWPOSI;
extern const int   DAF_VAL_FLOWNEGA;
extern const char* DAF_VAL_FLREQ;
extern const char* DAF_VAL_FLREQPOSI;
extern const char* DAF_VAL_FLREQNEGA;
extern const char* DAF_MSG_ROUTINGUPDATE;
extern const char* DAF_MSG_ENROLLMENT;

class AEMgmt : public AEMgmtBase {
  public:
    virtual void sendStartEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStartEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStopEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStopEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStartOperationRequest(OperationObj* obj);
    virtual void sendStartOperationResponse(OperationObj* obj);
    virtual void receiveData(CDAPMessage* cimsg);
    virtual void receiveCACE(CDAPMessage* msg);
    virtual void sendCACE(CDAPMessage* msg);

    void signalizeSendData(CDAPMessage* msg);

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

  protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initCdapBindings();
    void initSignalsAndListeners();

    //Signals
    simsignal_t sigRIBDSendData;
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

    /* Emit update received signal. */
    //simsignal_t sigRIBDFwdUpdateRecv;
    simsignal_t sigRIBDRoutingUpdateRecv;

    //Listeners
    LisAEMgmtRcvData*             lisAEMgmtRcvData;
    LisAEMgmtRcvCACE*             lisAEMgmtRcvCACE;
    LisAEMgmtRcvEnrollCACE*       lisAEMgmtRcvEnrollCACE;
    LisAEMgmtStaEnrolReq*         lisAEMgmtStaEnrolReq;
    LisAEMgmtStaEnrolRes*         lisAEMgmtStaEnrolRes;
    LisAEMgmtStoEnrolReq*         lisAEMgmtStoEnrolReq;
    LisAEMgmtStoEnrolRes*         lisAEMgmtStoEnrolRes;
    LisAEMgmtStaOperReq*          lisAEMgmtStaOperReq;
    LisAEMgmtStaOperRes*          lisAEMgmtStaOperRes;

    void processMConnect(CDAPMessage* msg);
    void processMConnectR(CDAPMessage* msg);

    void processMStart(CDAPMessage* msg);
    void processMStartR(CDAPMessage* msg);
    void processMStop(CDAPMessage* msg);
    void processMStopR(CDAPMessage* msg);

};

#endif /* AEMGMT_H_ */
