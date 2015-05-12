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
/**
 * @file TxControlPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief
 * @detail
 */

#include "TxControlPolicyBase.h"

TxControlPolicyBase::TxControlPolicyBase()
{


}

TxControlPolicyBase::~TxControlPolicyBase()
{

}

void TxControlPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState){

  PDUQ_t* pduQ;
  if(!dtpState->getGeneratedPDUQ()->empty()){
    pduQ = dtpState->getGeneratedPDUQ();
  }else{
    pduQ = dtcpState->getClosedWindowQ();
  }

  /* Default */
  /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
   And Set the ClosedWindow flag appropriately. */
  PDUQ_t::iterator it;
//    PDUQ_t* pduQ = dtpState->getGeneratedPDUQ();
  for (it = pduQ->begin();
      it != pduQ->end() && (*it)->getSeqNum() <= dtcpState->getSenderRightWinEdge();)
  {

    dtpState->pushBackToPostablePDUQ((*it));
//      dtpState->getGeneratedPDUQ()->erase(it);
    it = pduQ->erase(it);

  }

  if (!dtpState->getGeneratedPDUQ()->empty() || dtcpState->getClosedWinQueLen() >= dtcpState->getMaxClosedWinQueLen())
  {
    dtcpState->setClosedWindow(true);
  }
  /* End default */
}

