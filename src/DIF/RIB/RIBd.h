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
 * @file RIBd.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief Kind of a Notification Board for DIF
 * @detail
 */

#ifndef RIBDAEMON_H_
#define RIBDAEMON_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Utils.h"
#include "CDAPProcessingBase.h"
#include "RIBdBase.h"
#include "ExternConsts.h"
#include "RIBdListeners.h"
#include "RINASignals.h"
#include "PDU.h"
#include "IntRoutingUpdate.h"
#include "FANotifier.h"
#include "EnrollmentNotifier.h"
#include "RoutingNotifier.h"

//Constants
extern const char* MSG_CONGEST;
//extern const char* MSG_ROUTINGUPDATE;
//extern const char* MSG_ENROLLMENT;

class RIBd : public RIBdBase {
  public:
    /*
    virtual void sendCreateRequestFlow(Flow* flow);
    virtual void sendCreateResponseNegative(Flow* flow);
    virtual void sendCreateResponsePostive(Flow* flow);
    virtual void sendDeleteRequestFlow(Flow* flow);
    virtual void sendDeleteResponseFlow(Flow* flow);
    virtual void receiveAllocationRequestFromFai(Flow* flow);
    virtual void receiveCreateFlowPositiveFromRa(Flow* flow);
    virtual void receiveCreateFlowNegativeFromRa(Flow* flow);

    virtual void sendStartEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStartEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStopEnrollmentRequest(EnrollmentObj* obj);
    virtual void sendStopEnrollmentResponse(EnrollmentObj* obj);
    virtual void sendStartOperationRequest(OperationObj* obj);
    virtual void sendStartOperationResponse(OperationObj* obj);
    virtual void receiveCACE(CDAPMessage* msg);
    virtual void sendCACE(CDAPMessage* msg);
    */
    virtual void receiveData(CDAPMessage* cimsg);
    /* Handles information coming from PDUFTG module. */
    //virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * update);

    virtual void sendCongestionNotification(PDU* pdu);

    virtual void signalizeSendData(CDAPMessage* msg);
    /*
    void signalizeCreateRequestFlow(Flow* flow);
    void signalizeDeleteRequestFlow(Flow* flow);
    void signalizeDeleteResponseFlow(Flow* flow);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);
    void signalizeCreateFlow(Flow* flow);
    void signalizeCreateResponseFlowPositive(Flow* flow);
    void signalizeCreateResponseFlowNegative(Flow* flow);
    */
    void signalizeCongestionNotification(CongestionDescriptor* congDesc);

    /*
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
    */
  protected:
    FANotifierBase* FANotif;
    EnrollmentNotifierBase* EnrollNotif;
    RoutingNotifierBase* RoutingNotif;

    bool useFANotifier;
    bool useEnrollmentNotifier;
    bool useRoutingNotifier;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initSignalsAndListeners();
    void initPointers();

    //Signals

    simsignal_t sigRIBDSendData;
    /*
    simsignal_t sigRIBDCreReqFlo;
    simsignal_t sigRIBDDelReqFlo;
    simsignal_t sigRIBDDelResFlo;
    simsignal_t sigRIBDCreResFloPosi;
    simsignal_t sigRIBDCreResFloNega;
    simsignal_t sigRIBDAllocResPosi;
    simsignal_t sigRIBDAllocResNega;
    simsignal_t sigRIBDCreFlow;
    */
    simsignal_t sigRIBDCongNotif;

    /*
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
    */

    /* Emit update received signal. */
    //simsignal_t sigRIBDFwdUpdateRecv;
    //simsignal_t sigRIBDRoutingUpdateRecv;


    //Listeners
    LisRIBDRcvData*             lisRIBDRcvData;
    /*
    LisRIBDCreReq*              lisRIBDCreReq;
    LisRIBDCreReq*              lisRIBDCreReqByForward;
    LisRIBDAllReqFromFai*       lisRIBDAllReqFromFai;
    LisRIBDCreResNega*          lisRIBDCreResNega;
    LisRIBDCreResNega*          lisRIBDCreResNegaFromFa;
    LisRIBDCreResPosi*          lisRIBDCreResPosi;
    LisRIBDCreResPosi*          lisRIBDCreResPosiForward;
    LisRIBDDelReq*              lisRIBDDelReq;
    LisRIBDDelRes*              lisRIBDDelRes;
    LisRIBDCreFloPosi*          lisRIBDCreFloPosi;
    LisRIBDCreFloNega*          lisRIBDCreFloNega;
    */
    LisRIBDCongesNotif*         lisRIBDCongNotif;
    /*
    LisRIBDRcvCACE*             lisRIBDRcvCACE;
    LisRIBDRcvEnrollCACE*       lisRIBDRcvEnrollCACE;
    LisRIBDStaEnrolReq*         lisRIBDStaEnrolReq;
    LisRIBDStaEnrolRes*         lisRIBDStaEnrolRes;
    LisRIBDStoEnrolReq*         lisRIBDStoEnrolReq;
    LisRIBDStoEnrolRes*         lisRIBDStoEnrolRes;
    LisRIBDStaOperReq*          lisRIBDStaOperReq;
    LisRIBDStaOperRes*          lisRIBDStaOperRes;
     */
    /* Listen for PDUFTG update messages. */
    //LisRIBDRoutingUpdate*       lisRIBDRoutingUpdate;

    /*
    void processMCreate(CDAPMessage* msg);
    void processMCreateR(CDAPMessage* msg);
    void processMDelete(CDAPMessage* msg);
    void processMDeleteR(CDAPMessage* msg);

    void processMConnect(CDAPMessage* msg);
    void processMConnectR(CDAPMessage* msg);
    void processMStart(CDAPMessage* msg);
    void processMStartR(CDAPMessage* msg);
    void processMStop(CDAPMessage* msg);
    void processMStopR(CDAPMessage* msg);
    */
    void processMStart(CDAPMessage* msg);
//    void processMWrite(CDAPMessage* msg);

};

#endif /* RIBDAEMON_H_ */
