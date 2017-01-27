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
 * @file RcvrAckPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTCP/RcvrAck/RcvrAckPolicyBase.h"
#include "DIF/EFCP/DTP/DTP.h"

RcvrAckPolicyBase::RcvrAckPolicyBase()
{


}

RcvrAckPolicyBase::~RcvrAckPolicyBase()
{

}

void RcvrAckPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = getRINAModule<DTP*>(this, 1, { MOD_DTP });
  /* Default */

  unsigned int seqNum;
  if (dtp->getQoSCube()->getATime() > 0)
  {
    if (!dtpState->getTmpAtimer())
    {
      if(!dtp->isATimerQEmpty()){
        return;
      }
      seqNum = dtpState->getCurrentPdu()->getSeqNum();
      //set A-timer for this PDU
      dtp->startATimer(seqNum);
    }
    else
    {

      seqNum = dtpState->getTmpAtimer()->getSeqNum();
      //send an Ack/FlowControlPDU
      dtp->sendAckFlowPDU();

      //stop any A-Timers asscociated with this PDU and earlier ones.
      dtp->cancelATimer(seqNum);
      dtpState->setTmpAtimer(nullptr);
    }

  }
  else
  {

    //send an Ack/FlowControlPDU
    dtp->sendAckFlowPDU();

  }

  /* End default */
}
