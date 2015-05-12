//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file DTPRTTEstimatorPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 22, 2015
 * @brief
 * @detail
 */

#include "RTTEstimatorPolicyBase.h"
#include "ControlPDU_m.h"

RTTEstimatorPolicyBase::RTTEstimatorPolicyBase()
{


}

RTTEstimatorPolicyBase::~RTTEstimatorPolicyBase()
{

}

void RTTEstimatorPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  double newRtt = dtpState->getRtt();
    double alpha = 0.5;
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

          EV << "RTTEstimator: Did not found PDU on RxQ to compare times." << endl;
          return;
        }

      }
      else
      {

      }
    }
    double tmp = floor(((alpha * dtpState->getRtt()) + ((1 - alpha) * newRtt)) * 1000000000);
    dtpState->setRtt((double) tmp / 1000000000);
    EV << "Current RTT: " << dtpState->getRtt() << endl;


}
