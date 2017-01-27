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
#include "Common/Utils.h"
#include "Common/CDAPProcessingBase.h"
#include "DIF/RIB/RIBdBase.h"
#include "Common/ExternConsts.h"
#include "DIF/RIB/RIBdListeners.h"
#include "Common/RINASignals.h"
#include "Common/PDU.h"
#include "DIF/Routing/IntRoutingUpdate.h"
#include "DIF/FA/FANotifier.h"
#include "DIF/Enrollment/EnrollmentNotifier.h"
#include "DIF/Routing/RoutingNotifier.h"

//Constants
extern const char* MSG_CONGEST;
//extern const char* MSG_ROUTINGUPDATE;
//extern const char* MSG_ENROLLMENT;

class RIBd : public RIBdBase {
  public:
    virtual void receiveData(CDAPMessage* cimsg);
    /* Handles information coming from PDUFTG module. */
    //virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * update);

    virtual void sendCongestionNotification(PDU* pdu);

    virtual void signalizeSendData(CDAPMessage* msg);

    void signalizeCongestionNotification(CongestionDescriptor* congDesc);

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
    simsignal_t sigRIBDCongNotif;

    /* Emit update received signal. */
    //simsignal_t sigRIBDFwdUpdateRecv;
    //simsignal_t sigRIBDRoutingUpdateRecv;


    //Listeners
    LisRIBDRcvData*             lisRIBDRcvData;
    LisRIBDCongesNotif*         lisRIBDCongNotif;

    /* Listen for PDUFTG update messages. */
    //LisRIBDRoutingUpdate*       lisRIBDRoutingUpdate;

    void processMStart(CDAPMessage* msg);
//    void processMWrite(CDAPMessage* msg);

};

#endif /* RIBDAEMON_H_ */
