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
 * @author Vladimir Vesely, Kamil Jerabek (ivesely@fit.vutbr.cz, xjerab18@stud.fit.vutbr.cz)
 * @date Oct 2, 2014
 * @brief Kind of a Notification Board for DAF
 * @detail
 */

#ifndef AEMGMT_H_
#define AEMGMT_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/AEManagement/AEMgmtBase.h"
#include "Common/ExternConsts.h"
#include "DAF/AEManagement/AEMgmtListeners.h"
#include "DAF/Enrollment/DAFEnrollmentNotifierBase.h"
#include "DIF/FA/FANotifier.h"
#include "Common/CDAPProcessingBase.h"
#include "Common/RINASignals.h"
#include "Common/PDU.h"
#include "DIF/Routing/IntRoutingUpdate.h"

//Constants
//extern const char* DAF_MSG_ENROLLMENT;

class AEMgmt : public AEMgmtBase {
  public:
    virtual void signalizeSendData(CDAPMessage* msg);
    virtual void receiveData(CDAPMessage* cimsg);

  protected:
    FANotifierBase* FANotif;
    DAFEnrollmentNotifierBase* DAFEnrollNotif;

    bool useFANotifier;
    bool useEnrollmentNotifier;

    virtual void initialize();
    virtual void initPointers();
    virtual void handleMessage(cMessage *msg);

    void initSignalsAndListeners();

    //Signals
    simsignal_t sigRIBDSendData;


    /* Emit update received signal. */

    //Listeners
    LisAEMgmtRcvData*             lisAEMgmtRcvData;
};

#endif /* AEMGMT_H_ */
