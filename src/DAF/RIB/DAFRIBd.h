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

class DAFRIBd : public DAFRIBdBase {
public:
  virtual void receiveData(CDAPMessage* cimsg);

  virtual void signalizeSendData(CDAPMessage* msg);

protected:
  EnrollmentNotifierBase* EnrollNotif;

  bool useEnrollmentNotifier;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);

  void initSignalsAndListeners();
  void initPointers();

  //Signals
  simsignal_t sigDAFRIBDSendData;

  //Listeners
  LisDAFRIBDRcvData*             lisDAFRIBDRcvData;

};

#endif /* DAFRIBD_H_ */
