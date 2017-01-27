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
 * @file TxControlPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTCP/TxControl/TxControlPolicyBase.h"

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
      it != pduQ->end() && (*it)->getSeqNum() <= dtcpState->getSndRightWinEdge();)
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

