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

#include "DTCP.h"

Define_Module(DTCP);

DTCP::DTCP() {
  rxControl = NULL;
  flowControl = NULL;

  ecnSetPolicy = NULL;
  ecnClearPolicy = NULL;
  rcvrFCPolicy = NULL;
  rcvrAckPolicy = NULL;
  receivingFCPolicy = NULL;
  sendingAckPolicy = NULL;
  lostControlPDUPolicy = NULL;
  rcvrControlAckPolicy = NULL;
  senderAckPolicy = NULL;


}

void DTCP::initialize(int step)
{
  Enter_Method("initialize");
  dtp = (DTP*)this->getParentModule()->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());

//TODO A1 Fill it with appropriate values
  dtcpState = new DTCPState();

//TODO A2 based on DTPState create appropriate components
  if (dtp->state.isRxPresent())
  {
    rxControl = new RXControl();
  }

  if (dtp->state.isFCPresent())
  {
    flowControl = new FlowControl();
    flowControl->initialize();
    if (dtp->state.isWinBased())
    {
      windowTimer = new WindowTimer();
      schedule(windowTimer);
    }
  }


  //TODO A1 Load list of policies
  if(true){

    std::stringstream moduleName;
    moduleName << ECN_SET_POLICY_PREFIX << par("ecnSetPolicy").stringValue();

    cModuleType* ecnSetPolicyType = cModuleType::get(moduleName.str().c_str());
    ecnSetPolicy = (DTCPECNSetPolicyBase*)ecnSetPolicyType->createScheduleInit(ECN_SET_POLICY_NAME, getParentModule());

    moduleName.str("");
    moduleName.clear();
    moduleName << ECN_CLEAR_POLICY_PREFIX << par("ecnClearPolicy").stringValue();

    cModuleType* ecnClearPolicyType = cModuleType::get(moduleName.str().c_str());
    ecnClearPolicy = (DTCPECNClearPolicyBase*)ecnClearPolicyType->createScheduleInit(ECN_CLEAR_POLICY_NAME, getParentModule());

  }

}


DTCP::~DTCP()
{
  if (rxControl != NULL)
  {
    delete rxControl;
  }
  if (flowControl != NULL)
  {
    delete flowControl;
  }

  delete dtcpState;
}

void DTCP::setDTP(DTP* dtp)
{
  this->dtp = dtp;
}

bool DTCP::runECNSetPolicy(DTPState* dtpState)
{
  Enter_Method("ECNSetPolicy");
  if(ecnSetPolicy != NULL){
    return ecnSetPolicy->run(dtpState, dtcpState);
  }
  return false;
}

void DTCP::incRcvRtWinEdge()
{
  dtcpState->incRcvRtWinEdge();
}

bool DTCP::runECNClearPolicy(DTPState* dtpState)
{
  Enter_Method("ECNClearPolicy");
  if(ecnClearPolicy != NULL){
    return ecnClearPolicy->run(dtpState, dtcpState);
  }
  return false;

}

bool DTCP::runRcvrFCPolicy(DTPState* dtpState)
{
  Enter_Method("RcvrFCPolicy");
  if(rcvrFCPolicy == NULL || rcvrFCPolicy->run(dtpState, dtcpState)){
    /* Default */

    /* This policy has to be the one to impose the condition to set WindowClosed to True */
    /* Default */ //FIXME A1 set value to these variables!
    if (dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
    {

      incRcvRtWinEdge();
    }
    else
    {
      /* Buffers are getting low */
      //Leave RightWindowEdge unchanged.
    }
    /* End default */

  }
  return false;
}

bool DTCP::runRcvrAckPolicy(DTPState* dtpState)
{
  Enter_Method("RcvrAckPolicy");
  if(rcvrAckPolicy == NULL || rcvrAckPolicy->run(dtpState, dtcpState)){
    /* Default */


    //TODO A3 Which one?
    unsigned int seqNum = dtpState->getRcvLeftWinEdge() - 1;
//    unsigned int seqNum = dtpState->getCurrentPdu()->getSeqNum();
    if (dtcpState->isImmediate())
    {
      //TODO A2 How to remove allowed gaps?
      //Update LeftWindowEdge removing allowed gaps;

      //send an Ack/FlowControlPDU
      dtp->sendAckFlowPDU(seqNum, true);

      //TODO A1 Add handling for A-timer != 0
      //stop any A-Timers asscociated with !!! this PDU !!! and earlier ones.

    }
    else
    {
      //TODO A2
      //set A-timer for this PDU
    }

    /* End default */
  }
  return false;
}

bool DTCP::runReceivingFCPolicy(DTPState* dtpState)
{
  Enter_Method("ReceivingFCPolicy");
  if(receivingFCPolicy == NULL || receivingFCPolicy->run(dtpState, dtcpState)){
    /* Default */
    if (dtpState->isWinBased())
    {

      //Send FlowControl PDU /* Already updated the window and not sending Ack */
      dtp->sendFCOnlyPDU();

    }

    /* End default */

  }
  return false;
}



bool DTCP::runSendingAckPolicy(DTPState* dtpState, ATimer* timer)
{
  Enter_Method("SendingAckPolicy");
  if(sendingAckPolicy == NULL || sendingAckPolicy->run(dtpState, dtcpState, timer)){
    /* Default */
    //TODO A!
    //Update LetWindowEdge

    //Invoke Delimiting
    dtp->delimitFromRMT(NULL);

    //resetSenderInactivity
    dtp->resetSenderInactivTimer();

    /* End default */

  }
  return false;
}

bool DTCP::runLostControlPDUPolicy(DTPState* dtpState)
{
  Enter_Method("LostControlPDUPolicy");
  if(lostControlPDUPolicy == NULL || lostControlPDUPolicy->run(dtpState, dtcpState)){
    /* Default */
    dtp->sendControlAckPDU();
    dtp->sendEmptyDTPDU();
    setLastCtrlSeqnumRec(dtpState->getCurrentPdu()->getSeqNum());

    /* End default */

  }
  return false;
}

bool DTCP::runRcvrControlAckPolicy(DTPState* dtpState)
{
  Enter_Method("RcvrControlAckPolicy");
  if(rcvrControlAckPolicy == NULL || rcvrControlAckPolicy->run(dtpState, dtcpState)){
    /* Default */

    //      /* RcvrControlAck Policy with Default: */
    //      //"adjust as necessary" :D great advice
    //      ControlAckPDU* ctrlAckPDU = (ControlAckPDU*)pdu;
    ////      TODO: unsigned int lastCtrlSeqNumRcv;
    //
    ////      unsigned int sndLtWinEdge;
    ////      if(state.getNextSeqNumToSend() < ctrlAckPDU->getSndLtWinEdge()){
    //      state.setNextSeqNumToSend(ctrlAckPDU->getSndLtWinEdge());
    ////      }
    ////      unsigned int sndRtWinEdge;
    //
    //      dtcp->setSndRtWinEdge(ctrlAckPDU->getSndRtWinEdge());
    ////      unsigned int myLtWinEdge;
    ////      if(state.getRcvLeftWinEdge() < ctrlAckPDU->getMyLtWinEdge()){
    //      state.setRcvLeftWinEdge(ctrlAckPDU->getMyLtWinEdge());
    ////      }
    ////      unsigned int myRtWinEdge;
    //      //TODO verify this
    //      dtcp->setRcvRtWinEdge(ctrlAckPDU->getMyRtWinEdge());
    ////      unsigned int myRcvRate;
    //      //TODO handle RcvRate
    //
    //      //TODO A1 Send Ack/Flow Control PDU with LWE and RWE
    //
    //      sendAckFlowPDU();
    //      //TODO A1 Send empty Transfer PDU with NextSeqNumToSend-1
    //
    //      DataTransferPDU* dataPdu = new DataTransferPDU();
    //      setPDUHeader(dataPdu);
    //      unsigned int seqNum = state.getNextSeqNumToSend();
    //      dataPdu->setSeqNum(seqNum - 1);
    //      state.setNextSeqNumToSend(seqNum);
    //      UserDataField* userData = new UserDataField();
    //      dataPdu->setUserDataField(userData);
    //
    //      sendToRMT(dataPdu);
    //
    //      //dataPdu->setSeqNum(state.getLastSeqNumSent());
    //
    //      /* End default RcvrControlAck policy */

    /* End default */

  }
  return false;
}

bool DTCP::runSenderAckPolicy(DTPState* dtpState)
{
  Enter_Method("SenderAckPolicy");
  if(senderAckPolicy == NULL || senderAckPolicy->run(dtpState, dtcpState)){
    /* Default */
    unsigned int seqNum = ((NAckPDU*)dtpState->getCurrentPdu())->getAckNackSeqNum();
    ackPDU(seqNum);
    //TODO A!
    //updateLeftWindowEdge
    if(!dtcpState->getRxQ()->empty()){
        dtpState->setSenderLeftWinEdge(dtcpState->getRxQ()->front()->getPdu()->getSeqNum());
      }else{
        dtpState->setSenderLeftWinEdge(seqNum + 1);
      }
    /* End default */

  }
  return false;
}

void DTCP::nackPDU(unsigned int startSeqNum, unsigned int endSeqNum)
{

  bool endTrue = false;
  if(!endSeqNum){
    endTrue = true;
  }

  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  unsigned int lastLen;
  lastLen = rxQ->size();
  for (unsigned int index = lastLen; index < rxQ->size(); )
  {
    DTCPRxExpiryTimer* timer = rxQ->at(index);
    unsigned int seqNum =(timer->getPdu())->getSeqNum();
    //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
    if (seqNum >= startSeqNum && (seqNum <= endSeqNum || endTrue))
    {
      handleDTCPRxExpiryTimer(timer);

      /* Timer might get deleted so we do not want to increment index */
      if(lastLen != rxQ->size()){
        continue;
      }
    }
    index++;
  }
}


void DTCP::ackPDU(unsigned int startSeqNum, unsigned int endSeqNum)
{

  bool endTrue = false;
  if(!endSeqNum){
    endTrue = true;
  }


  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  unsigned int lastLen;
  lastLen = rxQ->size();
  for (unsigned int index = lastLen; index < rxQ->size(); )
  {
    DTCPRxExpiryTimer* timer = rxQ->at(index);
    unsigned int seqNum =(timer->getPdu())->getSeqNum();
    //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
    if (seqNum >= startSeqNum && (seqNum <= endSeqNum || endTrue))
    {
      dtcpState->deleteRxTimer(seqNum);

    }
    index++;
  }
}


/**
 *
 * @param timer
 */
void DTCP::handleDTCPRxExpiryTimer(DTCPRxExpiryTimer* timer)
{
  /* Canceling event is not needed for usual timer expiration but for direct calling this method */
  cancelEvent(timer);
  runRxTimerExpiryPolicy(timer);

}

void DTCP::runRxTimerExpiryPolicy(DTCPRxExpiryTimer* timer)
{

  DataTransferPDU* pdu = timer->getPdu();

  if (timer->getExpiryCount() == dtcpState->getDataReXmitMax() + 1)
  {
    //TODO A1 Indicate an error "Unable to maintain the QoS for this connection"

    dtcpState->deleteRxTimer(timer->getPdu()->getSeqNum());
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

    timer->setExpiryCount(timer->getExpiryCount() + 1);
    schedule(timer);
  }


}

void DTCP::pushBackToRxQ(DataTransferPDU* pdu)
{
  DTCPRxExpiryTimer* rxExpTimer = new DTCPRxExpiryTimer("DTCPRxExpiryTimer");
  rxExpTimer->setPdu(pdu);
  dtcpState->pushBackToRxQ(rxExpTimer);
  schedule(rxExpTimer);
}

void DTCP::clearRxQ(){
  dtcpState->clearRxQ();
}

unsigned int DTCP::getDataReXmitMax() const{
  return dtcpState->getDataReXmitMax();
}

void DTCP::schedule(DTCPTimers* timer, double time){

  switch (timer->getType())
  {
    case (DTCP_WINDOW_TIMER): {
      time = 0;
      // TODO B1 Make #define for "3"
      scheduleAt(simTime() + (1 / flowControl->getSendingRate()) + 3, timer);
      break;
    }
    case (DTCP_RX_EXPIRY_TIMER): {
      //TODO A! Expiry Timer time interval
      DTCPRxExpiryTimer* rxExpTimer = (DTCPRxExpiryTimer*)timer;
      rxExpTimer->setSent(simTime().dbl());
      scheduleAt(simTime() + dtp->getRxTime(), rxExpTimer); //TODO A! simTime() + something. Find the SOMETHING!

      break;
    }
  }

}



void DTCP::resetWindowTimer(){
  Enter_Method_Silent();
  cancelEvent(windowTimer);
      schedule(windowTimer);
}

void DTCP::updateRcvRtWinEdge(DTPState* dtpState)
{
  dtcpState->updateRcvRtWinEdge(dtpState->getRcvLeftWinEdge());
}

void DTCP::handleMessage(cMessage *msg){
  if(msg->isSelfMessage()){
    /* Self message */
    DTCPTimers* timer = static_cast<DTCPTimers*>(msg);

    switch(timer->getType()){
      case(DTCP_WINDOW_TIMER):{
        handleWindowTimer(static_cast<WindowTimer*>(timer));
      }
    }
  }else{

    /* PANIC!! */
  }

}

void DTCP::handleWindowTimer(WindowTimer* timer){
  resetWindowTimer();
  //TODO A1 Uncomment
//  dtp->sendControlAckPDU();

}

unsigned int DTCP::getNextSndCtrlSeqNum(){
//  return rxControl->getNextSndCtrlSeqNum();
  return dtcpState->getNextSndCtrlSeqNum();
}

unsigned int DTCP::getLastCtrlSeqNumRcv(){
//  return rxControl->getLastCtrlSeqNumRcv();
  return dtcpState->getLastCtrlSeqNumRcv();
}

void DTCP::setLastCtrlSeqnumRec(unsigned int ctrlSeqNum){
//  rxControl->setLastCtrlSeqNumRcv(ctrlSeqNum);
  dtcpState->setLastCtrlSeqNumRcv(ctrlSeqNum);
}

void DTCP::setSndRtWinEdge(unsigned int sndRtWinEdge)
{
//  flowControl->setSendRightWindowEdge(sndRtWinEdge);
  dtcpState->setSenderRightWinEdge(sndRtWinEdge);
}

unsigned int DTCP::getSndRtWinEdge()
{

//  return flowControl->getSendRightWindowEdge();
  return dtcpState->getSenderRightWinEdge();

}

void DTCP::setRcvRtWinEdge(unsigned int rcvRtWinEdge)
{

  dtcpState->setRcvRtWinEdge(rcvRtWinEdge);


}

unsigned int DTCP::getRcvRtWinEdge()
{
  return dtcpState->getRcvRtWinEdge();
}

void DTCP::setSndRate(unsigned int sendingRate)
{
  flowControl->setSendingRate(sendingRate);
}
unsigned int DTCP::getSndRate(){
  return flowControl->getSendingRate();
}

void DTCP::setRcvRate(unsigned int rcvrRate)
{
  flowControl->setRcvrRate(rcvrRate);
}
unsigned int DTCP::getRcvRate(){
  return flowControl->getRcvrRate();
}

unsigned int DTCP::getRcvCredit()
{
  return dtcpState->getRcvCredit();
}


unsigned long DTCP::getSendingTimeUnit()
{
   return flowControl->getSendingTimeUnit();
}


bool DTCP::isSendingRateFullfilled() const
{
  return flowControl->isSendingRateFullfilled();
}

void DTCP::setSendingRateFullfilled(bool rateFullfilled)
{
  flowControl->setSendingRateFullfilled(rateFullfilled);
}

void DTCP::redrawGUI()
{
  if (!ev.isGUI())
  {
      return;
  }

  cDisplayString& disp = getDisplayString();
  disp.setTagArg("t", 1, "r");
  std::ostringstream desc;


  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();

    if (rxQ->empty())
    {
      desc << "rxQ: empty" << "\n";
    }
    else
    {
      desc << "rxQ: ";
      std::vector<DTCPRxExpiryTimer*>::iterator it;
      for (it = rxQ->begin(); it != rxQ->end(); ++it)
      {
        desc << (*it)->getPdu()->getSeqNum() << " | ";
      }
      desc << "\n";
    }



  disp.setTagArg("t", 0, desc.str().c_str());

}
