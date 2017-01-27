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
 * @file RxExpiryTimerPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 5, 2015
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTCP/RxTimerExpiry/RxTimerExpiryPolicyBase.h"
#include "DIF/EFCP/DTP/DTP.h"


RxTimerExpiryPolicyBase::RxTimerExpiryPolicyBase()
{
}

RxTimerExpiryPolicyBase::~RxTimerExpiryPolicyBase()
{
}

void RxTimerExpiryPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = getRINAModule<DTP*>(this, 1, {MOD_DTP});
  DTCP* dtcp = getRINAModule<DTCP*>(this, 1, {MOD_DTCP});
  DTCPRxExpiryTimer* timer = NULL;

  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;

  for(it = rxQ->begin(); it != rxQ->end(); ++it){
    if(!(*it)->isScheduled()){
      timer = (*it);
      break;
    }
  }

  if(timer == NULL){
    throw cRuntimeError("Error, couldn't find RxTimerExpiry");
  }


  DataTransferPDU* pdu = timer->getPdu();



    if (timer->getExpiryCount() == dtcpState->getDataReXmitMax() + 1)
    {
      dtcp->deleteRxTimer(timer->getPdu()->getSeqNum());
      // Notify User Flow that we were unable to maintain the QoS for this connection
      dtp->notifyAboutUnableMaintain();
  //    throw cRuntimeError("Unable to maintain the QoS for this connection");
      ASSERT2(true,"Unable to maintain the QoS for this connection. Continue at your own risk.");
    }
    else
    {

      DataTransferPDU* dup = pdu->dup();
      dup->setDisplayString("b=15,15,oval,#0099FF,#0099FF,0");
      std::ostringstream out;
      out  << "Sending PDU number " << pdu->getSeqNum() << " from RX Queue";

      bubble(out.str().c_str());
      EV << this->getFullPath() << ": " << out.str().c_str() << " in time " << simTime() << endl;
      dtp->sendToRMT(dup);

      dtcpState->incRxSent();

      timer->setExpiryCount(timer->getExpiryCount() + 1);
      dtcp->scheduleRxTimerExpiry();



    }
}
