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

#include "DIF/EFCP/DTCP/DTCP.h"
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
  sndFcOverrunPolicy = NULL;
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

unsigned int DTCP::getSndLeftWinEdge() const
{
  return dtcpState->getSndLeftWinEdge();
}

void DTCP::setSenderLeftWinEdge(unsigned int senderLeftWinEdge)
{
  dtcpState->setSenderLeftWinEdge(senderLeftWinEdge);
}

void DTCP::setRcvFcOverrunPolicy(RcvFCOverrunPolicyBase* rcvFcOverrunPolicy)
{
  this->rcvFcOverrunPolicy = rcvFcOverrunPolicy;
}

void DTCP::initSignalsAndListeners()
{
  sigStatDTCPRxCount = registerSignal(SIG_STAT_DTCP_RX_SENT);
}

void DTCP::startRendezvousTimer()
{
  Enter_Method_Silent();
  DTCPRendezvousTimer* rendezvousTimer = new DTCPRendezvousTimer();
  rendezvousTimer->setSeqNum(dtcpState->getLastControlSeqNumSent());
  rendezvousTimer->setCounter(0);
  scheduleAt(simTime() + (dtp->state->getRtt() + dtp->state->getMPL()) / 2, rendezvousTimer);
  dtcpState->setRendezvousTimer(rendezvousTimer);
}

void DTCP::initialize(int step)
{
    Enter_Method("initialize");
    if(step == 1){
        cDisplayString& disp = getDisplayString();
        disp.setTagArg("p", 0, 340);
        disp.setTagArg("p", 1, 140);

//        //TODO B1 Not necessary DTP reference is set during DTCP creation. -> IF IT WILL WORK THEN DELETE THE COMMENTED LINES
//        dtp = getRINAModule<DTP*>(this, 1, {MOD_DTP});


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

  flushAllQueuesAndPrepareToDie();

}

void DTCP::setDTP(DTP* dtp)
{
  this->dtp = dtp;
}

bool DTCP::runECNPolicy(DTPState* dtpState)
{

  Enter_Method_Silent("ECNPolicy");
  ecnPolicy->call(dtpState, dtcpState);

  return false;
}



void DTCP::incRcvRtWinEdge()
{
  dtcpState->incRcvRtWinEdge();
}


bool DTCP::runRcvrFCPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("RcvrFCPolicy");
  rcvrFCPolicy->call(dtpState, dtcpState);
  return false;
}

bool DTCP::runRcvrAckPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("RcvrAckPolicy");
  rcvrAckPolicy->call(dtpState, dtcpState);
  return false;
}

bool DTCP::runReceivingFCPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("ReceivingFCPolicy");
  receivingFCPolicy->call(dtpState, dtcpState);

  return false;
}



bool DTCP::runSendingAckPolicy(DTPState* dtpState, ATimer* timer)
{
  Enter_Method_Silent("SendingAckPolicy");
  sendingAckPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runLostControlPDUPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("LostControlPDUPolicy");
  lostControlPDUPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runRcvrControlAckPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("RcvrControlAckPolicy");
  rcvrControlAckPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runSenderAckPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("SenderAckPolicy");
  senderAckPolicy->call(dtpState, dtcpState);

  return false;
}


bool DTCP::runSndFCOverrunPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("SndFCOverrunPolicy");
  sndFcOverrunPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runRcvFCOverrunPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("RcvFCOverrunPolicy");
  rcvFcOverrunPolicy->call(dtpState, dtcpState);
  return false;
}

bool DTCP::runNoOverridePeakPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("NoOverridePeakPolicy");
  noOverridePeakPolicy->call(dtpState, dtcpState);

  return false;
}


bool DTCP::runTxControlPolicy(DTPState* dtpState, PDUQ_t* pduQ)
{
  Enter_Method_Silent("TxControlPolicy");
  txControlPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runNoRateSlowDownPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("NoRateSlowDownPolicy");
  noRateSlowDownPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runReconcileFCPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("ReconcileFCPolicy");
reconcileFCPolicy->call(dtpState, dtcpState);

  return false;
}

bool DTCP::runRateReductionPolicy(DTPState* dtpState)
{
  Enter_Method_Silent("RateReductionPolicy");
  rateReductionPolicy->call(dtpState, dtcpState);

  return false;
}


bool DTCP::runECNSlowDownPolicy(DTPState* dtpState)
{

  Enter_Method_Silent("ECNSlowDownPolicy");
  ecnSlowDownPolicy->call(dtpState, dtcpState);

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
    unsigned int seqNum = (timer->getPdu())->getSeqNum();

    if (seqNum >= startSeqNum  && (seqNum <= endSeqNum || startTrue) )
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

void DTCP::deleteRxTimer(unsigned int seqNum) {
    std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
    std::vector<DTCPRxExpiryTimer*>::iterator it;
    for (it = rxQ->begin(); it != rxQ->end();) {
        if (seqNum == (*it)->getPdu()->getSeqNum()) {
            delete (*it)->getPdu();
            //      take((*it));
            cancelEvent((*it));
            delete (*it);
            rxQ->erase(it);
            return;
        }
        ++it;
    }
    return;
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

    if ((seqNum >= startSeqNum || startTrue) && seqNum <= endSeqNum)
    {
      deleteRxTimer(seqNum);
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

  rxTimerExpiryPolicy->call(dtp->state, dtcpState);

  emit(sigStatDTCPRxCount, dtcpState->getRxSent());

}

void DTCP::pushBackToRxQ(DataTransferPDU* pdu)
{
  Enter_Method_Silent();
  DTCPRxExpiryTimer* rxExpTimer = new DTCPRxExpiryTimer("DTCPRxExpiryTimer");
  take(pdu);
  rxExpTimer->setPdu(pdu);
  schedule(rxExpTimer);
  dtcpState->pushBackToRxQ(rxExpTimer);

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

    case (DTCP_RX_EXPIRY_TIMER): {
      DTCPRxExpiryTimer* rxExpTimer = (DTCPRxExpiryTimer*)timer;
      if(rxExpTimer->getExpiryCount() == 0){
        rxExpTimer->setSent(simTime().dbl());
      }
      //TODO B1 (RTT + A + epsilon)
//      double aTime = dtp->state->getQoSCube()->getATime();
//      double rtt = dtp->state->getRtt();
//      scheduleAt(simTime() + dtp->state->getRtt() + (double)dtp->state->getQoSCube()->getATime()/(double)1000 + DTP_EPSILON, rxExpTimer);
      scheduleAt(simTime() + dtp->rttEstimatorPolicy->getRTO(), rxExpTimer);
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

//void DTCP::resetWindowTimer(){
//  Enter_Method_Silent();
//  cancelEvent(windowTimer);
//      schedule(windowTimer);
//}

void DTCP::updateRcvRtWinEdge(DTPState* dtpState)
{
  dtcpState->updateRcvRtWinEdge(dtpState->getRcvLeftWinEdge());
}

void DTCP::handleRendezvousTimer(DTCPRendezvousTimer* rendezTimer)
{
  //        handleRendezvousTimer(static_cast<DTCPRendezvousTimer*>(timer));
  dtp->rendezvousCondition();
}

void DTCP::stopReliableCPDUTimer()
{
  cancelAndDelete(dtcpState->getReliableCpduTimer());
}

void DTCP::startReliableCPDUTimer()
{
  Enter_Method_Silent();
  DTCPReliableControlPDUTimer* reliableCPDUTimer = new DTCPReliableControlPDUTimer();
  dtcpState->setReliableCpduTimer(reliableCPDUTimer);
  scheduleAt(simTime() + (dtp->state->getMPL() + dtp->state->getRtt()) / 2, dtcpState->getReliableCpduTimer());


}

void DTCP::handleMessage(cMessage *msg){
  if(msg->isSelfMessage()){
    /* Self message */
    DTCPTimers* timer = static_cast<DTCPTimers*>(msg);

    switch(timer->getType()){
//      case(DTCP_WINDOW_TIMER):{
//        handleWindowTimer(static_cast<WindowTimer*>(timer));
//        break;
//      }
      case(DTCP_RX_EXPIRY_TIMER):{
        handleDTCPRxExpiryTimer(static_cast<DTCPRxExpiryTimer*>(timer));
        break;
      }
      case(DTCP_SENDING_RATE_TIMER):{
        handleSendingRateTimer((DTCPSendingRateTimer*)timer);
        break;
      }

      case (DTCP_RENDEZVOUS_TIMER): {
        handleRendezvousTimer(static_cast<DTCPRendezvousTimer*>(timer));
        delete msg;
        break;
      }

      case (DTCP_REL_C_PDU_TIMER): {
        dtp->sendAckFlowPDU();
        startReliableCPDUTimer();
        //TODO A! restart SenderInactivity Timer
        delete msg;
        break;
      }

    }
  }else{

    /* PANIC!! */
  }

}

//void DTCP::handleWindowTimer(WindowTimer* timer){
//  resetWindowTimer();
//  dtp->sendControlAckPDU();
//
//}

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
  return dtcpState->getSndRightWinEdge();

}

void DTCP::setRcvRtWinEdge(unsigned int rcvRtWinEdge)
{

  dtcpState->setRcvRtWinEdge(rcvRtWinEdge);

}

unsigned int DTCP::getRcvRightWinEdge()
{
  return dtcpState->getRcvRightWinEdge();
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

unsigned int DTCP::getPdusRcvdInTimeUnit() const
{
  return dtcpState->getPdusRcvdInTimeUnit();
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
//    return;
  Enter_Method_Silent();
  if (!getEnvir()->isGUI())
  {
      return;
  }

  cDisplayString& disp = getDisplayString();
  disp.setTagArg("t", 1, "r");
  std::ostringstream desc;


  desc << "rRWE: " << getRcvRightWinEdge() << "\n";
  desc << "sLWE: " << getSndLeftWinEdge() << "\n";
  desc << "sRWE: " << getSndRtWinEdge() << "\n";


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

void DTCP::setSndFcOverrunPolicy(SndFCOverrunPolicyBase* sndFcOverrunPolicy)
{
  this->sndFcOverrunPolicy = sndFcOverrunPolicy;
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

void DTCP::setECNPolicy(ECNPolicyBase* ecnPolicy)
{
  this->ecnPolicy = ecnPolicy;
}

void DTCP::setECNSlowDownPolicy(ECNSlowDownPolicyBase* ecnSlowDownPolicy)
{
  this->ecnSlowDownPolicy = ecnSlowDownPolicy;
}

void DTCP::setDtcpState(DTCPState* dtcpState)
{
  this->dtcpState = dtcpState;
}
