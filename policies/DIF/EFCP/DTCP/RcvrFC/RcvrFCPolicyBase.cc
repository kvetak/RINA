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
 * @file RcvrFCPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyBase.h"

RcvrFCPolicyBase::RcvrFCPolicyBase()
{


}

RcvrFCPolicyBase::~RcvrFCPolicyBase()
{

}

void RcvrFCPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{

  /* Default */

  /* This policy has to be the one to impose the condition to set WindowClosed to True */
  /* Default */
  //TODO A2 Where else are these variables updated?
  if (dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
  {

    //        if(dtcpState->getRcvRightWinEdge() == UINT_MAX){
    //This SHOULD happen only upon flow initialization
    dtcpState->setRcvRtWinEdge(dtpState->getRcvLeftWinEdge() + dtcpState->getRcvCredit());

    //        }
    //        dtcpState->incRcvRtWinEdge();
  }
  else
  {
    /* Buffers are getting low */
    //Leave RightWindowEdge unchanged.
  }
  /* End default */
}
