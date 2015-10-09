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
 * @file RcvrControlAckPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "RcvrControlAckPolicyBase.h"
#include "DTP.h"

RcvrControlAckPolicyBase::RcvrControlAckPolicyBase()
{


}

RcvrControlAckPolicyBase::~RcvrControlAckPolicyBase()
{

}

void RcvrControlAckPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = check_and_cast<DTP*>(getRINAModule(this, 1, {MOD_DTP}));
  DTCP* dtcp = check_and_cast<DTCP*>(getRINAModule(this, 1, {MOD_DTCP}));
  /* Default */

 //    bool sendAck = false;
 //    bool sendFC = true;
     /* RcvrControlAck Policy with Default: */
     //"adjust as necessary" :D great advice
     ControlAckPDU* ctrlAckPDU = (ControlAckPDU*)dtpState->getCurrentPdu();
     //      TODO: unsigned int lastCtrlSeqNumRcv;
     if(dtcpState->getNextSndCtrlSeqNumNoInc() != ctrlAckPDU->getLastCtrlSeqNumRcv()){
       // Does not necessary means an error.

     }
     //unsigned int sndLtWinEdge;
     if(ctrlAckPDU->getSndLtWinEdge() > dtpState->getRcvLeftWinEdge()){
       bubble("ControlAckPDU: Missing PDU on the receiver end.");
 //      throw cRuntimeError("ControlAckPDU: Missing PDU on the receiver end.");
     }else if(ctrlAckPDU->getSndLtWinEdge() < dtpState->getRcvLeftWinEdge()){
 //      sendAck = true;
     }

     //unsigned int sndRtWinEdge;
     if(ctrlAckPDU->getSndRtWinEdge() != dtcpState->getRcvRtWinEdge()){
 //      sendFC = true;
     }

     //unsigned int myLtWinEdge;
     if(ctrlAckPDU->getMyLtWinEdge() > dtcpState->getSenderLeftWinEdge()){
       //serves as an ack -> remove PDUs from RxQ
       dtcp->ackPDU(ctrlAckPDU->getMyLtWinEdge() - 1);
       dtcp->updateSenderLWE(ctrlAckPDU->getMyLtWinEdge());
     }else if(ctrlAckPDU->getMyLtWinEdge() < dtcpState->getSenderLeftWinEdge()){
       bubble("ControlAckPDU: Missing PDU on the sender's end.");
 //      throw cRuntimeError("ControlAckPDU: Missing PDU on the sender's end.");
     }

     //      unsigned int myRtWinEdge;
     if(ctrlAckPDU->getMyRtWinEdge() != dtcpState->getSenderRightWinEdge()){
       dtcpState->setSenderRightWinEdge(ctrlAckPDU->getMyRtWinEdge());
     }

     //unsigned int myRcvRate;
     if(ctrlAckPDU->getMyRcvRate() != dtcpState->getSendingRate()){
       dtcpState->setSendingRate(ctrlAckPDU->getMyRcvRate());
     }

     //TODO A2 Verify it one more time
 //    if(sendAck && sendFC){
 //      dtp->sendAckFlowPDU();
 //    }else if (sendAck){
 //      dtp->sendAckOnlyPDU(dtpState->getRcvLeftWinEdge() - 1);
 //    }else{
 //      dtp->sendFCOnlyPDU();
 //    }
     // Send Ack/Flow Control PDU with LWE and RWE
     dtp->sendAckFlowPDU();

     // Send empty Transfer PDU with NextSeqNumToSend-1
     DataTransferPDU* dataPdu = new DataTransferPDU();
     dtp->setPDUHeader(dataPdu);
     unsigned int seqNum = dtpState->getNextSeqNumToSendWithoutIncrement() - 1;
     dataPdu->setSeqNum(seqNum);
     UserDataField* userData = new UserDataField();

     dataPdu->setUserDataField(userData);

     dtp->sendToRMT(dataPdu);


     /* End default */
}
