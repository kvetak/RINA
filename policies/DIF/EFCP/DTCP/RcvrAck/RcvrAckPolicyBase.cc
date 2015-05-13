//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file RcvrAckPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "RcvrAckPolicyBase.h"
#include "DTP.h"

RcvrAckPolicyBase::RcvrAckPolicyBase()
{


}

RcvrAckPolicyBase::~RcvrAckPolicyBase()
{

}

void RcvrAckPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());
  /* Default */

      unsigned int seqNum = dtpState->getRcvLeftWinEdge() - 1;

      if(dtpState->getRcvLeftWinEdge() == 0){
        seqNum = 0;
      }

      if (dtcpState->isImmediate())
      {
        //Update LeftWindowEdge removing allowed gaps;
        dtpState->updateRcvLWE(seqNum);
  //      unsigned int sduGap =  dtpState->getQoSCube()->getMaxAllowGap();
  //
  //      PDUQ_t::iterator it;
  //      PDUQ_t* pduQ = dtpState->getReassemblyPDUQ();
  //      for (it = pduQ->begin(); it != pduQ->end(); ++it)
  //      {
  //        if((*it)->getSeqNum() == dtpState->getRcvLeftWinEdge()){
  //          dtpState->incRcvLeftWindowEdge();
  //
  //        }else if((*it)->getSeqNum() < dtpState->getRcvLeftWinEdge()){
  //          continue;
  //        }else {
  //          if(pduQ->size() == 1 || it == pduQ->begin()){
  //            if((*it)->getSDUSeqNum() <= dtpState->getLastSduDelivered() + sduGap){
  //              dtpState->setRcvLeftWinEdge((*it)->getSeqNum());
  //            }
  //          }else{
  //            (*(it-1))->getSDUGap((*it));
  //          }
  //          break;
  //        }
  //      }

        //send an Ack/FlowControlPDU
        dtp->sendAckFlowPDU(seqNum, true);


        //stop any A-Timers asscociated with !!! this PDU !!! and earlier ones.
        //XXX How could there be any A-Timer when isImmediate returned true?

      }
      else
      {
        //set A-timer for this PDU
        dtp->startATimer(seqNum);
      }

      /* End default */
}
