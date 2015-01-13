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

  ecnPolicy = NULL;
  rcvrFCPolicy = NULL;
  rcvrAckPolicy = NULL;
  receivingFCPolicy = NULL;
  sendingAckPolicy = NULL;
  lostControlPDUPolicy = NULL;
  rcvrControlAckPolicy = NULL;
  senderAckPolicy = NULL;
  fcOverrunPolicy = NULL;
  noOverridePeakPolicy = NULL;
  txControlPolicy = NULL;
  noRateSlowDownPolicy = NULL;
  reconcileFCPolicy = NULL;
  rateReductionPolicy = NULL;




}

DTCPState* DTCP::getDTCPState() const
{
  return dtcpState;
}

unsigned int DTCP::getSendingRate() const
{
  return dtcpState->getSendingRate();
}

void DTCP::setSendingRate(unsigned int sendingRate)
{
  dtcpState->setSendingRate(sendingRate);
}

unsigned int DTCP::getRcvrRate() const
{
  return dtcpState->getRcvrRate();
}

void DTCP::createPolicyModule(cModule* policy, const char* prefix, const char* name)
{
  if (std::string(par(name).stringValue()).empty())
  {
    policy = NULL;
  }else{
  std::stringstream moduleName;
  moduleName << prefix << par(name).stringValue();
  cModuleType* policyType = cModuleType::get(moduleName.str().c_str());
  policy = policyType->createScheduleInit(name, getParentModule());
  }
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
//      windowTimer = new WindowTimer();
//      schedule(windowTimer);
    }
  }


  //TODO A1 Load list of policies
  createPolicyModule(ecnPolicy, ECN_POLICY_PREFIX, ECN_POLICY_NAME);
  createPolicyModule(rcvrFCPolicy, RCVR_FC_POLICY_PREFIX, RCVR_FC_POLICY_NAME);
  createPolicyModule(rcvrAckPolicy, RCVR_ACK_POLICY_PREFIX, RCVR_ACK_POLICY_NAME);
  createPolicyModule(receivingFCPolicy, RECEIVING_FC_POLICY_PREFIX, RECEIVING_FC_POLICY_NAME);
  createPolicyModule(sendingAckPolicy, SENDING_ACK_POLICY_PREFIX, SENDING_ACK_POLICY_NAME);
  createPolicyModule(lostControlPDUPolicy, LOST_CONTROL_PDU_POLICY_PREFIX, LOST_CONTROL_PDU_POLICY_NAME);
  createPolicyModule(rcvrControlAckPolicy, RCVR_CONTROL_ACK_POLICY_PREFIX, RCVR_CONTROL_ACK_POLICY_NAME);
  createPolicyModule(senderAckPolicy, SENDER_ACK_POLICY_PREFIX, SENDER_ACK_POLICY_NAME);
  createPolicyModule(fcOverrunPolicy, FC_OVERRUN_POLICY_PREFIX, FC_OVERRUN_POLICY_NAME);
  createPolicyModule(noOverridePeakPolicy, NO_OVERRIDE_PEAK_POLICY_PREFIX, NO_OVERRIDE_PEAK_POLICY_NAME);
  createPolicyModule(txControlPolicy, TX_CONTROL_POLICY_PREFIX, TX_CONTROL_POLICY_NAME);
  createPolicyModule(noRateSlowDownPolicy, NO_RATE_SLOW_DOWN_POLICY_PREFIX, NO_RATE_SLOW_DOWN_POLICY_NAME);
  createPolicyModule(reconcileFCPolicy, RECONCILE_FC_POLICY_PREFIX, RECONCILE_FC_POLICY_NAME);
  createPolicyModule(rateReductionPolicy, RATE_REDUCTION_POLICY_PREFIX, RATE_REDUCTION_POLICY_NAME);


}

void DTCP::flushAllQueuesAndPrepareToDie()
{
  clearRxQ();
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
  flushAllQueuesAndPrepareToDie();
  delete dtcpState;
}

void DTCP::setDTP(DTP* dtp)
{
  this->dtp = dtp;
}

bool DTCP::runECNPolicy(DTPState* dtpState)
{
  Enter_Method("ECNPolicy");
  if(ecnPolicy == NULL || ecnPolicy->run(dtpState, dtcpState)){
    /* Default */
    if(dtpState->getCurrentPdu()->getFlags()  & ECN_FLAG){
      dtpState->setEcnSet(true);
    }else{
      dtpState->setEcnSet(false);
    }
    /* End default */
  }
  return false;
}

void DTCP::incRcvRtWinEdge()
{
  dtcpState->incRcvRtWinEdge();
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
    setLastCtrlSeqnumRcvd(dtpState->getCurrentPdu()->getSeqNum());

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


bool DTCP::runFCOverrunPolicy(DTPState* dtpState)
{
  Enter_Method("FCOverrunPolicy");
  if(fcOverrunPolicy == NULL || fcOverrunPolicy->run(dtpState, dtcpState)){
    /* Default */
    dtcpState->pushBackToClosedWinQ((DataTransferPDU*) dtpState->getCurrentPdu());
    //TODO A2 Block further Write API calls on this port-id
    // eg. -> Create new CDAP Message type and send it upwards
    /* End default */

  }
  return false;
}

bool DTCP::runNoOverridePeakPolicy(DTPState* dtpState)
{
  Enter_Method("NoOverridePeakPolicy");
  if (noOverridePeakPolicy == NULL || noOverridePeakPolicy->run(dtpState, dtcpState))
  {
    /* Default */
    setSendingRateFullfilled(true);
    if (dtcpState->getClosedWinQueLen() < dtcpState->getMaxClosedWinQueLen() - 1)
    {
      dtcpState->pushBackToClosedWinQ((DataTransferPDU*) dtpState->getCurrentPdu());

    }
    /* End default */

  }
  return false;
}


bool DTCP::runTxControlPolicy(DTPState* dtpState, PDUQ_t* pduQ)
{
  Enter_Method("TxControlPolicy");
  if (txControlPolicy == NULL || txControlPolicy->run(dtpState, dtcpState))
  {
    /* Default */
    /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
     And Set the ClosedWindow flag appropriately. */
    std::vector<DataTransferPDU*>::iterator it;
//    PDUQ_t* pduQ = dtpState->getGeneratedPDUQ();
    for (it = pduQ->begin();
        it != pduQ->end() && (*it)->getSeqNum() <= getSndRtWinEdge();)
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
  return false;
}

bool DTCP::runNoRateSlowDownPolicy(DTPState* dtpState)
{
  Enter_Method("NoRateSlowDownPolicy");
  if (noRateSlowDownPolicy == NULL || noRateSlowDownPolicy->run(dtpState, dtcpState))
  {
    /* Default */
    //TODO A1 Do I need to propagate the pduQ (gneratedPDUs vs closedWindowQ
    /* Default */

    dtpState->pushBackToPostablePDUQ(dtpState->getGeneratedPDUQ()->front());
    dtpState->getGeneratedPDUQ()->erase(dtpState->getGeneratedPDUQ()->begin());
    incPdusSentInTimeUnit();
    /* End default */

  }
  return false;
}

bool DTCP::runReconcileFCPolicy(DTPState* dtpState)
{
  Enter_Method("ReconcileFCPolicy");
  if (reconcileFCPolicy == NULL || reconcileFCPolicy->run(dtpState, dtcpState))
  {
    /* Default */
    /* Default is empty :)*/
    /* End default */

  }
  return false;
}

bool DTCP::runRateReductionPolicy(DTPState* dtpState)
{
  Enter_Method("RateReductionPolicy");
  if (rateReductionPolicy == NULL || rateReductionPolicy->run(dtpState, dtcpState))
  {
    /* Default */
    if (dtcpState->getRcvBuffersPercentFree() <= dtcpState->getRcvBufferPercentThreshold())
    {
//      flowControl->rcvrRate *= 0.9; //Reduce Rate 10%
      dtcpState->setRcvrRate(dtcpState->getRcvrRate() *0.9);

    }
    else
    {
      if (dtcpState->getRcvrRate() < dtcpState->getConfigRcvrRate()
          && dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
      {
        //set rate back to config rate
        dtcpState->setRcvrRate(dtcpState->getConfigRcvrRate());
      }
    }
    dtp->sendAckFlowPDU();
    /* End default */

  }
  return false;
}


void DTCP::nackPDU(unsigned int startSeqNum, unsigned int endSeqNum)
{
  Enter_Method_Silent();

  bool startTrue = false;
  if(!endSeqNum){
    startTrue = true;
    endSeqNum = startSeqNum;
  }

  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  unsigned int lastLen;
  lastLen = rxQ->size();
  for (unsigned int index = 0; index < rxQ->size(); )
  {
    DTCPRxExpiryTimer* timer = rxQ->at(index);
    unsigned int seqNum =(timer->getPdu())->getSeqNum();
    //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
    if ((seqNum >= startSeqNum || startTrue) && seqNum <= endSeqNum )
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
  Enter_Method_Silent();
  bool startTrue = false;
  if(!endSeqNum){
    startTrue = true;
    endSeqNum = startSeqNum;
  }


  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  unsigned int lastLen;
  lastLen = rxQ->size();
  for (unsigned int index = 0; index < rxQ->size(); )
  {
    DTCPRxExpiryTimer* timer = rxQ->at(index);
    unsigned int seqNum =(timer->getPdu())->getSeqNum();
    //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
    if ((seqNum >= startSeqNum || startTrue) && seqNum <= endSeqNum )
    {
      dtcpState->deleteRxTimer(seqNum);

      continue;

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
    throw cRuntimeError("Unable to maintain the QoS for this connection");
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
  Enter_Method_Silent();
  DTCPRxExpiryTimer* rxExpTimer = new DTCPRxExpiryTimer("DTCPRxExpiryTimer");
  take(pdu);
  rxExpTimer->setPdu(pdu);
  dtcpState->pushBackToRxQ(rxExpTimer);
  schedule(rxExpTimer);
}

void DTCP::clearRxQ(){
  Enter_Method_Silent();
  dtcpState->clearRxQ();
}

unsigned int DTCP::getDataReXmitMax() const{
  return dtcpState->getDataReXmitMax();
}

void DTCP::schedule(DTCPTimers* timer, double time){

  Enter_Method_Silent();
  switch (timer->getType())
  {
    case (DTCP_WINDOW_TIMER): {
      time = 0;
      // TODO B1 Make #define for "3"
      scheduleAt(simTime() + (1 / dtcpState->getSendingRate()) + 3, timer);
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
        break;
      }
      case(DTCP_RX_EXPIRY_TIMER):{
        handleDTCPRxExpiryTimer(static_cast<DTCPRxExpiryTimer*>(timer));
        break;
      }

    }
  }else{

    /* PANIC!! */
  }

}

void DTCP::handleWindowTimer(WindowTimer* timer){
  resetWindowTimer();
  dtp->sendControlAckPDU();

}

unsigned int DTCP::getNextSndCtrlSeqNum(){
//  return rxControl->getNextSndCtrlSeqNum();
  return dtcpState->getNextSndCtrlSeqNum();
}

unsigned int DTCP::getLastCtrlSeqNumRcv(){
//  return rxControl->getLastCtrlSeqNumRcv();
  return dtcpState->getLastCtrlSeqNumRcv();
}

void DTCP::setLastCtrlSeqnumRcvd(unsigned int ctrlSeqNum){
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
  return dtcpState->isSendingRateFullfilled();
}

void DTCP::setSendingRateFullfilled(bool rateFullfilled)
{
  dtcpState->setSendingRateFullfilled(rateFullfilled);
}

unsigned int DTCP::getPdusSentInTimeUnit() const
{
  return dtcpState->getPdusSentInTimeUnit();
}

void DTCP::incPdusSentInTimeUnit()
{
  dtcpState->setPdusSentInTimeUnit(dtcpState->getPdusSentInTimeUnit() + 1);
}

void DTCP::setPdusSentInTimeUnit(unsigned int pdusSentInTimeUnit)
{
  dtcpState->setPdusSentInTimeUnit(pdusSentInTimeUnit);
}

void DTCP::redrawGUI()
{
  Enter_Method_Silent();
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
    desc << "RxQ: empty" << "\n";
  }
  else
  {
    desc << "RxQ: ";
    std::vector<DTCPRxExpiryTimer*>::iterator it;
    for (it = rxQ->begin(); it != rxQ->end(); ++it)
    {
      desc << (*it)->getPdu()->getSeqNum() << " | ";
    }
    desc << "\n";
  }

  if (!dtcpState->getClosedWinQueLen())
  {
    desc << "closedWinQ: empty" << "\n";
  }
  else
  {
    desc << "closedWinQ: ";
    std::vector<DataTransferPDU*>::iterator it;
    std::vector<DataTransferPDU*>* pduQ;
    pduQ = dtcpState->getClosedWindowQ();
    for (it = pduQ->begin(); it != pduQ->end(); ++it)
    {
      desc << (*it)->getSeqNum() << " | ";
    }
    desc << "\n";
  }


  desc << "dup Acks: " << getDupAcks() << "\n";


  disp.setTagArg("t", 0, desc.str().c_str());

}

void DTCP::incDupAcks()
{
  dtcpState->incDupAcks();
}

unsigned int DTCP::getDupAcks() const
{
  return dtcpState->getDupAcks();
}


void DTCP::incDupFC()
{
  dtcpState->incDupFC();
}

unsigned int DTCP::getDupFC() const
{
  return dtcpState->getDupFC();
}
