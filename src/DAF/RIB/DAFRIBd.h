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

#ifndef DAFRIBD_H_
#define DAFRIBD_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Common/Utils.h"
#include "Common/CDAPProcessingBase.h"
#include "DAF/RIB/DAFRIBdBase.h"
#include "Common/ExternConsts.h"
#include "DAF/RIB/DAFRIBdListeners.h"
#include "Common/RINASignals.h"
#include "Common/PDU.h"
#include "DIF/Enrollment/EnrollmentNotifier.h"
#include "DAF/AE/AEBase.h"

class DAFRIBd : public DAFRIBdBase {
    enum SubscriptionOption {READ, WRITE};
    enum SubscriptionOperation {NOTIFY, STORE};
    enum SubscriptionWhen {ON_REQUEST, ON_CHANGE};
public:
  virtual void receiveData(CDAPMessage* cimsg);

  virtual void signalizeSendData(CDAPMessage* msg);


  /* subscription API */
  void createSubscription(DAFRIBd::SubscriptionOption option,
          DAFRIBd::SubscriptionWhen when,
          DAFRIBd::SubscriptionOperation operation,
          std::string obj,
          std::string member,
          int subscId);

  void deleteSubscription(int subscId);
  void readSubscription(int subscId);

  /* create&delete IAE in RIB */
  void createIAE(AEBase* iae);
  void deleteIAE(AEBase* iae);

protected:
  EnrollmentNotifierBase* EnrollNotif;

  bool useEnrollmentNotifier;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);

  void initSignalsAndListeners();
  void initPointers();

  void createObj(AEBase* iae, std::string objName, object_t *obj);
  void deleteObj(AEBase* iae, std::string objName);

  void sendMsg(int CDAPConn, CDAPMessage* msg);
  void recvMsg(int CDAPConn, CDAPMessage* msg);

  //Signals
  //simsignal_t sigDAFRIBDSendData;

  simsignal_t sigRIBDAE;


  //Listeners
  //LisDAFRIBDRcvData*             lisDAFRIBDRcvData;
  LisDAFAERIBD* lisDAFAERIBD;

  LisDAFIAECreate* lisDAFIAECreate;
  LisDAFIAEDelete* lisDAFIAEDelete;

};

#endif /* DAFRIBD_H_ */
