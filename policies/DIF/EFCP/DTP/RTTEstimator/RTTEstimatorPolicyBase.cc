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

/*
 * @file DTPRTTEstimatorPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 22, 2015
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h"
#include "DIF/EFCP/DTCP/ControlPDU_m.h"

RTTEstimatorPolicyBase::RTTEstimatorPolicyBase()
{
    RTO = 1;
}

RTTEstimatorPolicyBase::~RTTEstimatorPolicyBase()
{

}

double RTTEstimatorPolicyBase::getRTO() {
    return RTO;
}

void RTTEstimatorPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  double newRtt = dtpState->getRtt();
    double alpha = 0.998;
    /* Default */
    ControlPDU* pdu = (ControlPDU*) dtpState->getCurrentPdu();
    if (pdu->getType() & PDU_SEL_BIT)
    {

    }
    else
    {
      if (pdu->getType() & PDU_ACK_BIT)
      {
        unsigned int seqNum = ((AckOnlyPDU*) pdu)->getAckNackSeqNum();
        std::vector<DTCPRxExpiryTimer*>* pduQ = dtcpState->getRxQ();
        std::vector<DTCPRxExpiryTimer*>::iterator it;
        bool foundAck = false;
        for (it = pduQ->begin(); it != pduQ->end(); ++it)
        {
          if ((*it)->getPdu()->getSeqNum() == seqNum)
          {
            foundAck = true;
            double now = simTime().dbl();
            double sent = (*it)->getSent();
            newRtt = now - sent;

            newRtt = floor(newRtt * 1000000000);
            newRtt = newRtt / 1000000000;

          }
        }
        if (!foundAck)
        {

          EV << "RTTEstimator: Did not find PDU on RxQ to compare times." << endl;
          return;
        }

      }
      else
      {

      }
    }
    double tmp = floor(((alpha * dtpState->getRtt()) + ((1 - alpha) * newRtt)) * 1000000000);
//    dtpState->setRtt(((double) tmp / 1000000000) * 1.1);
    dtpState->setRtt(((double) tmp / 1000000000));  // removing * 1.1
    EV << "Current RTT: " << dtpState->getRtt() << endl;
    RTO = dtpState->getRtt() + (double)dtpState->getQoSCube()->getATime()/(double)1000 + DTP_EPSILON;

}

void RTTEstimatorPolicyBase::setRto(double rto)
{
  RTO = rto;
}
