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
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());
  DTCP* dtcp = (DTCP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTCP)).c_str());
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
