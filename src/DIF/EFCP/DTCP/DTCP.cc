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

#include "DTCP.h"
const char * SIG_STAT_DTCP_RX_SENT = "DTCP_RX_SENT";

Define_Module(DTCP);

DTCP::DTCP() {
//  rxControl = NULL;
//  flowControl = NULL;

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
  ecnSlowDownPolicy = NULL;
  rxTimerExpiryPolicy = NULL;




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

cModule* DTCP::createPolicyModule(const char* prefix, const char* name)
{
  if (std::string(par(name).stringValue()).empty())
  {
    return NULL;
  }else{
    std::stringstream moduleName;
    moduleName << prefix << par(name).stringValue();
    cModuleType* policyType = cModuleType::get(moduleName.str().c_str());
    return policyType->createScheduleInit(name, getParentModule());
  }
}

unsigned int DTCP::getSenderLeftWinEdge() const
{
  return dtcpState->getSenderLeftWinEdge();
}

void DTCP::setSenderLeftWinEdge(unsigned int senderLeftWinEdge)
{
  dtcpState->setSenderLeftWinEdge(senderLeftWinEdge);
}

void DTCP::initSignalsAndListeners()
{
  sigStatDTCPRxCount = registerSignal(SIG_STAT_DTCP_RX_SENT);
}

void DTCP::initialize(int step)
{
    Enter_Method("initialize");
    if(step == 1){
        cDisplayString& disp = getDisplayString();
        disp.setTagArg("p", 0, 340);
        disp.setTagArg("p", 1, 140);

        //TODO A1 Not necessary DTP reference is set during DTCP creation.
        dtp = (DTP*)this->getParentModule()->getModuleByPath((std::string(".") + std::string(MOD_DTP)).c_str());

        //  dtcpState = new DTCPState();

        //  dtcpState->callInitialize();




        //TODO A1 Load list of policies
//        ecnPolicy             = (DTCPECNPolicyBase*) createPolicyModule(ECN_POLICY_PREFIX, ECN_POLICY_NAME);
//        rcvrFCPolicy          = (RcvrFCPolicyBase*) createPolicyModule(RCVR_FC_POLICY_PREFIX, RCVR_FC_POLICY_NAME);
//        rcvrAckPolicy         = (RcvrAckPolicyBase*) createPolicyModule(RCVR_ACK_POLICY_PREFIX, RCVR_ACK_POLICY_NAME);
//        receivingFCPolicy     = (ReceivingFCPolicyBase*) createPolicyModule(RECEIVING_FC_POLICY_PREFIX, RECEIVING_FC_POLICY_NAME);
//        sendingAckPolicy      = (SendingAckPolicyBase*) createPolicyModule(SENDING_ACK_POLICY_PREFIX, SENDING_ACK_POLICY_NAME);
//        lostControlPDUPolicy  = (LostControlPDUPolicyBase*) createPolicyModule(LOST_CONTROL_PDU_POLICY_PREFIX, LOST_CONTROL_PDU_POLICY_NAME);
//        rcvrControlAckPolicy  = (RcvrControlAckPolicyBase*) createPolicyModule(RCVR_CONTROL_ACK_POLICY_PREFIX, RCVR_CONTROL_ACK_POLICY_NAME);
//        senderAckPolicy       = (SenderAckPolicyBase*) createPolicyModule(SENDER_ACK_POLICY_PREFIX, SENDER_ACK_POLICY_NAME);
//        fcOverrunPolicy       = (FCOverrunPolicyBase*) createPolicyModule(FC_OVERRUN_POLICY_PREFIX, FC_OVERRUN_POLICY_NAME);
//        noOverridePeakPolicy  = (NoOverridePeakPolicyBase*) createPolicyModule(NO_OVERRIDE_PEAK_POLICY_PREFIX, NO_OVERRIDE_PEAK_POLICY_NAME);
//        txControlPolicy       = (TxControlPolicyBase*) createPolicyModule(TX_CONTROL_POLICY_PREFIX, TX_CONTROL_POLICY_NAME);
//        noRateSlowDownPolicy  = (NoRateSlowDownPolicyBase*) createPolicyModule(NO_RATE_SLOW_DOWN_POLICY_PREFIX, NO_RATE_SLOW_DOWN_POLICY_NAME);
//        reconcileFCPolicy     = (ReconcileFCPolicyBase*) createPolicyModule(RECONCILE_FC_POLICY_PREFIX, RECONCILE_FC_POLICY_NAME);
//        rateReductionPolicy   = (RateReductionPolicyBase*) createPolicyModule(RATE_REDUCTION_POLICY_PREFIX, RATE_REDUCTION_POLICY_NAME);
//  			ecnSlowDownPolicy			= (DTCPECNSlowDownPolicyBase*) createPolicyModule(ECN_SLOW_DOWN_POLICY_PREFIX, ECN_SLOW_DOWN_POLICY_NAME);


  			initSignalsAndListeners();
    }
}

void DTCP::flushAllQueuesAndPrepareToDie()
{
  clearRxQ();
//  delete dtcpState;
}

DTCP::~DTCP()
{
//  if (rxControl != NULL)
//  {
//    delete rxControl;
//  }
//  if (flowControl != NULL)
//  {
//    delete flowControl;
//  }
  flushAllQueuesAndPrepareToDie();
//  if(dtcpState!=NULL){
//    delete dtcpState;
//  }

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
  rcvrFCPolicy->call(dtpState, dtcpState);
//    /* Default */
//
//    /* This policy has to be the one to impose the condition to set WindowClosed to True */
//    /* Default */
//    //TODO A2 Where else are these variables updated?
//    if (dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
//    {
//
//      incRcvRtWinEdge();
//    }
//    else
//    {
//      /* Buffers are getting low */
//      //Leave RightWindowEdge unchanged.
//    }
//    /* End default */
//
//  }
  return false;
}

bool DTCP::runRcvrAckPolicy(DTPState* dtpState)
{
  Enter_Method("RcvrAckPolicy");
  rcvrAckPolicy->call(dtpState, dtcpState);
//    /* Default */
//
//    unsigned int seqNum = dtpState->getRcvLeftWinEdge() - 1;
//
//    if(dtpState->getRcvLeftWinEdge() == 0){
//      seqNum = 0;
//    }
//
//    if (dtcpState->isImmediate())
//    {
//      //Update LeftWindowEdge removing allowed gaps;
//      dtpState->updateRcvLWE(seqNum);
////      unsigned int sduGap =  dtpState->getQoSCube()->getMaxAllowGap();
////
////      PDUQ_t::iterator it;
////      PDUQ_t* pduQ = dtpState->getReassemblyPDUQ();
////      for (it = pduQ->begin(); it != pduQ->end(); ++it)
////      {
////        if((*it)->getSeqNum() == dtpState->getRcvLeftWinEdge()){
////          dtpState->incRcvLeftWindowEdge();
////
////        }else if((*it)->getSeqNum() < dtpState->getRcvLeftWinEdge()){
////          continue;
////        }else {
////          if(pduQ->size() == 1 || it == pduQ->begin()){
////            if((*it)->getSDUSeqNum() <= dtpState->getLastSduDelivered() + sduGap){
////              dtpState->setRcvLeftWinEdge((*it)->getSeqNum());
////            }
////          }else{
////            (*(it-1))->getSDUGap((*it));
////          }
////          break;
////        }
////      }
//
//      //send an Ack/FlowControlPDU
//      dtp->sendAckFlowPDU(seqNum, true);
//
//
//      //stop any A-Timers asscociated with !!! this PDU !!! and earlier ones.
//      //XXX How could there be any A-Timer when isImmediate returned true?
//
//    }
//    else
//    {
//      //set A-timer for this PDU
//      dtp->startATimer(seqNum);
//    }
//
//    /* End default */
//  }
  return false;
}

bool DTCP::runReceivingFCPolicy(DTPState* dtpState)
{
  Enter_Method("ReceivingFCPolicy");
  receivingFCPolicy->call(dtpState, dtcpState);
    /* Default */
//    if (dtpState->isWinBased())
//    {
//
//      //Send FlowControl PDU /* Already updated the window and not sending Ack */
//      dtp->sendFCOnlyPDU();
//
//    }

    /* End default */

//  }
  return false;
}



bool DTCP::runSendingAckPolicy(DTPState* dtpState, ATimer* timer)
{
  Enter_Method("SendingAckPolicy");
  sendingAckPolicy->call(dtpState, dtcpState);
//    /* Default */
//
//    //Update RcvLetWindowEdge
//    dtpState->updateRcvLWE(timer->getSeqNum());
//
//    //Invoke Delimiting
//    dtp->delimitFromRMT(NULL);
//
//    //resetSenderInactivity
//    dtp->resetSenderInactivTimer();
//
//    /* End default */

//  }
  return false;
}

bool DTCP::runLostControlPDUPolicy(DTPState* dtpState)
{
  Enter_Method("LostControlPDUPolicy");
  lostControlPDUPolicy->call(dtpState, dtcpState);
//    /* Default */
//    dtp->sendControlAckPDU();
//    dtp->sendEmptyDTPDU();
//    setLastCtrlSeqnumRcvd(dtpState->getCurrentPdu()->getSeqNum());
//
//    /* End default */
//
//  }
  return false;
}

bool DTCP::runRcvrControlAckPolicy(DTPState* dtpState)
{
  Enter_Method("RcvrControlAckPolicy");
  rcvrControlAckPolicy->call(dtpState, dtcpState);
//    /* Default */
//
////    bool sendAck = false;
////    bool sendFC = true;
//    /* RcvrControlAck Policy with Default: */
//    //"adjust as necessary" :D great advice
//    ControlAckPDU* ctrlAckPDU = (ControlAckPDU*)dtpState->getCurrentPdu();
//    //      TODO: unsigned int lastCtrlSeqNumRcv;
//    if(dtcpState->getNextSndCtrlSeqNumNoInc() != ctrlAckPDU->getLastCtrlSeqNumRcv()){
//      // Does not necessary means an error.
//
//    }
//    //unsigned int sndLtWinEdge;
//    if(ctrlAckPDU->getSndLtWinEdge() > dtpState->getRcvLeftWinEdge()){
//      bubble("ControlAckPDU: Missing PDU on the receiver end.");
////      throw cRuntimeError("ControlAckPDU: Missing PDU on the receiver end.");
//    }else if(ctrlAckPDU->getSndLtWinEdge() < dtpState->getRcvLeftWinEdge()){
////      sendAck = true;
//    }
//
//    //unsigned int sndRtWinEdge;
//    if(ctrlAckPDU->getSndRtWinEdge() != dtcpState->getRcvRtWinEdge()){
////      sendFC = true;
//    }
//
//    //unsigned int myLtWinEdge;
//    if(ctrlAckPDU->getMyLtWinEdge() > dtcpState->getSenderLeftWinEdge()){
//      //serves as an ack -> remove PDUs from RxQ
//      ackPDU(ctrlAckPDU->getMyLtWinEdge() - 1);
//      updateSenderLWE(ctrlAckPDU->getMyLtWinEdge());
//    }else if(ctrlAckPDU->getMyLtWinEdge() < dtcpState->getSenderLeftWinEdge()){
//      bubble("ControlAckPDU: Missing PDU on the sender's end.");
////      throw cRuntimeError("ControlAckPDU: Missing PDU on the sender's end.");
//    }
//
//    //      unsigned int myRtWinEdge;
//    if(ctrlAckPDU->getMyRtWinEdge() != dtcpState->getSenderRightWinEdge()){
//      dtcpState->setSenderRightWinEdge(ctrlAckPDU->getMyRtWinEdge());
//    }
//
//    //unsigned int myRcvRate;
//    if(ctrlAckPDU->getMyRcvRate() != dtcpState->getSendingRate()){
//      dtcpState->setSendingRate(ctrlAckPDU->getMyRcvRate());
//    }
//
//    //TODO A2 Verify it one more time
////    if(sendAck && sendFC){
////      dtp->sendAckFlowPDU();
////    }else if (sendAck){
////      dtp->sendAckOnlyPDU(dtpState->getRcvLeftWinEdge() - 1);
////    }else{
////      dtp->sendFCOnlyPDU();
////    }
//    // Send Ack/Flow Control PDU with LWE and RWE
//    dtp->sendAckFlowPDU();
//
//    // Send empty Transfer PDU with NextSeqNumToSend-1
//    DataTransferPDU* dataPdu = new DataTransferPDU();
//    dtp->setPDUHeader(dataPdu);
//    unsigned int seqNum = dtpState->getNextSeqNumToSendWithoutIncrement() - 1;
//    dataPdu->setSeqNum(seqNum);
//    UserDataField* userData = new UserDataField();
//
//    dataPdu->setUserDataField(userData);
//
//    dtp->sendToRMT(dataPdu);
//
//
//    /* End default */
//
//  }
  return false;
}

bool DTCP::runSenderAckPolicy(DTPState* dtpState)
{
  Enter_Method("SenderAckPolicy");
  senderAckPolicy->call(dtpState, dtcpState);
//    /* Default */
//    unsigned int seqNum = ((NAckPDU*)dtpState->getCurrentPdu())->getAckNackSeqNum();
//    ackPDU(seqNum);
//
//    //update SendLeftWindowEdge
//    dtcpState->updateSndLWE(seqNum + 1);
//
//    /* End default */
//
//  }
  return false;
}


bool DTCP::runFCOverrunPolicy(DTPState* dtpState)
{
  Enter_Method("FCOverrunPolicy");
  fcOverrunPolicy->call(dtpState, dtcpState);
//    /* Default */
//    dtcpState->pushBackToClosedWinQ((DataTransferPDU*) dtpState->getCurrentPdu());
//    //Block further Write API calls on this port-id
//    dtp->notifyStopSending();
//    /* End default */
//
//  }
  return false;
}

bool DTCP::runNoOverridePeakPolicy(DTPState* dtpState)
{
  Enter_Method("NoOverridePeakPolicy");
  noOverridePeakPolicy->call(dtpState, dtcpState);
//  {
//    /* Default */
//    setSendingRateFullfilled(true);
//    if (dtcpState->getClosedWinQueLen() < dtcpState->getMaxClosedWinQueLen() - 1)
//    {
//      dtcpState->pushBackToClosedWinQ((DataTransferPDU*) dtpState->getCurrentPdu());
//
//    }
//    /* End default */
//
//  }
  return false;
}


bool DTCP::runTxControlPolicy(DTPState* dtpState, PDUQ_t* pduQ)
{
  Enter_Method("TxControlPolicy");
  txControlPolicy->call(dtpState, dtcpState);
//  {
//    /* Default */
//    /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
//     And Set the ClosedWindow flag appropriately. */
//    std::vector<DataTransferPDU*>::iterator it;
////    PDUQ_t* pduQ = dtpState->getGeneratedPDUQ();
//    for (it = pduQ->begin();
//        it != pduQ->end() && (*it)->getSeqNum() <= getSndRtWinEdge();)
//    {
//
//      dtpState->pushBackToPostablePDUQ((*it));
////      dtpState->getGeneratedPDUQ()->erase(it);
//      it = pduQ->erase(it);
//
//    }
//
//    if (!dtpState->getGeneratedPDUQ()->empty() || dtcpState->getClosedWinQueLen() >= dtcpState->getMaxClosedWinQueLen())
//    {
//      dtcpState->setClosedWindow(true);
//    }
//    /* End default */

//  }
  return false;
}

bool DTCP::runNoRateSlowDownPolicy(DTPState* dtpState)
{
  Enter_Method("NoRateSlowDownPolicy");
  noRateSlowDownPolicy->call(dtpState, dtcpState);
//  {
//    /* Default */
//    //TODO A1 Do I need to propagate the pduQ (gneratedPDUs vs closedWindowQ
//    /* Default */
//
//    dtpState->pushBackToPostablePDUQ(dtpState->getGeneratedPDUQ()->front());
//    dtpState->getGeneratedPDUQ()->erase(dtpState->getGeneratedPDUQ()->begin());
//    incPdusSentInTimeUnit();
//    /* End default */
//
//  }
  return false;
}

bool DTCP::runReconcileFCPolicy(DTPState* dtpState)
{
  Enter_Method("ReconcileFCPolicy");
reconcileFCPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runRateReductionPolicy(DTPState* dtpState)
{
  Enter_Method("RateReductionPolicy");
  rateReductionPolicy->call(dtpState, dtcpState);
//  {
//    /* Default */
//    if (dtcpState->getRcvBuffersPercentFree() <= dtcpState->getRcvBufferPercentThreshold())
//    {
////      flowControl->rcvrRate *= 0.9; //Reduce Rate 10%
//      dtcpState->setRcvrRate(dtcpState->getRcvrRate() *0.9);
//
//    }
//    else
//    {
//      if (dtcpState->getRcvrRate() < dtcpState->getConfigRcvrRate()
//          && dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
//      {
//        //set rate back to config rate
//        dtcpState->setRcvrRate(dtcpState->getConfigRcvrRate());
//      }
//    }
//    dtp->sendAckFlowPDU();
//    /* End default */
//
//  }
  return false;
}


bool DTCP::runECNSlowDownPolicy(DTPState* dtpState)
{
  Enter_Method("ECNSlowDownPolicy");
  if (ecnSlowDownPolicy == NULL || ecnSlowDownPolicy->run(dtpState, dtcpState))
  {
    /* Default */

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

  for (unsigned int index = 0; index < rxQ->size(); )
  {
    DTCPRxExpiryTimer* timer = rxQ->at(index);
    unsigned int seqNum =(timer->getPdu())->getSeqNum();
    unsigned int gap = dtp->state->getQoSCube()->getMaxAllowGap();
    //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
    if ((seqNum >= startSeqNum || startTrue) && seqNum <= endSeqNum + gap)
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
//TODO A! Make it Module-based policy
void DTCP::runRxTimerExpiryPolicy(DTCPRxExpiryTimer* timer)
{

  rxTimerExpiryPolicy->call(dtp->state, dtcpState);

  emit(sigStatDTCPRxCount, dtcpState->getRxSent());

//  DataTransferPDU* pdu = timer->getPdu();
//
//  if (timer->getExpiryCount() == dtcpState->getDataReXmitMax() + 1)
//  {
//    dtcpState->deleteRxTimer(timer->getPdu()->getSeqNum());
//    // Notify User Flow that we were unable to maintain the QoS for this connection
//    dtp->notifyAboutUnableMaintain();
////    throw cRuntimeError("Unable to maintain the QoS for this connection");
//    ASSERT2(true,"Unable to maintain the QoS for this connection. Continue at your own risk.");
//  }
//  else
//  {
//
//    DataTransferPDU* dup = pdu->dup();
//    dup->setDisplayString("b=15,15,oval,#0099FF,#0099FF,0");
//    std::ostringstream out;
//    out  << "Sending PDU number " << pdu->getSeqNum() << " from RX Queue";
//
//    bubble(out.str().c_str());
//    EV << this->getFullPath() << ": " << out.str().c_str() << " in time " << simTime() << endl;
//    dtp->sendToRMT(dup);
//
//    dtcpState->incRxSent();
//
//    timer->setExpiryCount(timer->getExpiryCount() + 1);
//    schedule(timer);
//
//
//    emit(sigStatDTCPRxCount, dtcpState->getRxSent());
//  }


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
      DTCPRxExpiryTimer* rxExpTimer = (DTCPRxExpiryTimer*)timer;
      if(rxExpTimer->getExpiryCount() == 0){
        rxExpTimer->setSent(simTime().dbl());
      }
      //TODO B1 (RTT + A + epsilon)
//      double aTime = dtp->state->getQoSCube()->getATime();
//      double rtt = dtp->state->getRtt();
      scheduleAt(simTime() + dtp->state->getRtt() + (double)dtp->state->getQoSCube()->getATime()/(double)1000 + DTP_EPSILON, rxExpTimer);
      break;
    }
    case(DTCP_SENDING_RATE_TIMER):{
      scheduleAt(simTime() + dtcpState->getTimeUnit() / 1000, timer);
      break;
    }
  }

}

void DTCP::scheduleRxTimerExpiry()
{
  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  for (it = rxQ->begin(); it != rxQ->end(); ++it)
  {
    if (!(*it)->isScheduled())
    {
      schedule((*it));
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
      case(DTCP_SENDING_RATE_TIMER):{
        handleSendingRateTimer((DTCPSendingRateTimer*)timer);
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

void DTCP::handleSendingRateTimer(DTCPSendingRateTimer* timer)
{
  dtcpState->setPdusSentInTimeUnit(0);

  dtcpState->setSendingRateFullfilled(false);
  schedule(timer);
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
   return dtcpState->getSendingTimeUnit();
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
    return;
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
  desc << "rxSent: " << dtcpState->getRxSent() <<endl;

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

bool DTCP::isClosedWinQClosed()
{
  return dtcpState->isClosedWinQClosed();
}

void DTCP::updateSenderLWE(unsigned int seqNum)
{
  dtcpState->updateSndLWE(seqNum);
}

void DTCP::setFcOverrunPolicy(FCOverrunPolicyBase* fcOverrunPolicy)
{
  this->fcOverrunPolicy = fcOverrunPolicy;
}

void DTCP::setLostControlPduPolicy(LostControlPDUPolicyBase* lostControlPduPolicy)
{
  lostControlPDUPolicy = lostControlPduPolicy;
}

void DTCP::setNoOverridePeakPolicy(NoOverridePeakPolicyBase* noOverridePeakPolicy)
{
  this->noOverridePeakPolicy = noOverridePeakPolicy;
}

void DTCP::setNoRateSlowDownPolicy(NoRateSlowDownPolicyBase* noRateSlowDownPolicy)
{
  this->noRateSlowDownPolicy = noRateSlowDownPolicy;
}

void DTCP::setRateReductionPolicy(RateReductionPolicyBase* rateReductionPolicy)
{
  this->rateReductionPolicy = rateReductionPolicy;
}

void DTCP::setRcvrAckPolicy(RcvrAckPolicyBase* rcvrAckPolicy)
{
  this->rcvrAckPolicy = rcvrAckPolicy;
}

void DTCP::setRcvrControlAckPolicy(RcvrControlAckPolicyBase* rcvrControlAckPolicy)
{
  this->rcvrControlAckPolicy = rcvrControlAckPolicy;
}

void DTCP::setRcvrFcPolicy(RcvrFCPolicyBase* rcvrFcPolicy)
{
  rcvrFCPolicy = rcvrFcPolicy;
}

void DTCP::setReceivingFcPolicy(ReceivingFCPolicyBase* receivingFcPolicy)
{
  receivingFCPolicy = receivingFcPolicy;
}

void DTCP::setReconcileFcPolicy(ReconcileFCPolicyBase* reconcileFcPolicy)
{
  reconcileFCPolicy = reconcileFcPolicy;
}

void DTCP::setRxTimerExpiryPolicy(RxTimerExpiryPolicyBase* rxTimerExpiryPolicy)
{
  this->rxTimerExpiryPolicy = rxTimerExpiryPolicy;
}

void DTCP::setSenderAckPolicy(SenderAckPolicyBase* senderAckPolicy)
{
  this->senderAckPolicy = senderAckPolicy;
}

void DTCP::setSendingAckPolicy(SendingAckPolicyBase* sendingAckPolicy)
{
  this->sendingAckPolicy = sendingAckPolicy;
}

void DTCP::setTxControlPolicy(TxControlPolicyBase* txControlPolicy)
{
  this->txControlPolicy = txControlPolicy;
}

void DTCP::setDtcpState(DTCPState* dtcpState)
{
  this->dtcpState = dtcpState;
}
