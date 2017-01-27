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

#include "DIF/EFCP/DTP/DTP.h"

const char * SIG_STAT_DTP_RTT = "DTP_RTT";
const char * SIG_STAT_DTP_CLOSED_WIN_Q = "DTP_CLOSED_WIN_Q";
const char * DTP_SEQ_NUM_RCVD = "DTP_SEQ_NUM_RCVD";
const char * DTP_SEQ_NUM_SENT = "DTP_SEQ_NUM_SENT";

Define_Module(DTP);

DTP::DTP()
{
  deletePdu = 0;

  rcvrInactivityTimer = nullptr;
  senderInactivityTimer = nullptr;


  rcvrInactivityPolicy = nullptr;
  senderInactivityPolicy = nullptr;
  initialSeqNumPolicy = nullptr;
  rttEstimatorPolicy = nullptr;

  state = nullptr;

  pduDroppingEnabled = false;

  sduSeqNum = 0;
  //intentionally left out callInitialize

}
DTP::~DTP()
{

  flushAllQueuesAndPrepareToDie();
//  delete state;
  if (state->isDtcpPresent())
  {

  }

}

cModule* DTP::createPolicyModule(const char* prefix, const char* name)
{
  if (std::string(par(name).stringValue()).empty())
  {
    return nullptr;
  }
  else
  {
    std::stringstream moduleName;
    moduleName << prefix << par(name).stringValue();
    cModuleType* policyType = cModuleType::get(moduleName.str().c_str());
    return policyType->createScheduleInit(name, getParentModule());
  }
}

void DTP::runRTTEstimatorPolicy()
{
  Enter_Method
  ("RTTEstimatorPolicy");
  rttEstimatorPolicy->call(state, dtcp->getDTCPState());

  emit(sigStatDTPRTT, state->getRtt());

}

void DTP::runCongestionNotificationPolicy()
{
  dtcp->runECNSlowDownPolicy(state);
}

void DTP::handleQueueInfoFromSocket(QueueInfo* queueInfo)
{
  handleQueueInfo(queueInfo);
}

void DTP::handleQueueInfo(QueueInfo* queueInfo)
{
}

void DTP::initSignalsAndListeners()
{
  //Signals that this module is emmiting
  sigEFCPStahpSending = registerSignal(SIG_EFCP_StopSending);
  sigEFCPStartSending = registerSignal(SIG_EFCP_StartSending);
  sigStatDTPRTT = registerSignal(SIG_STAT_DTP_RTT);
  sigStatDTPClosedWinQ = registerSignal(SIG_STAT_DTP_CLOSED_WIN_Q);
//  sigStatDTPRxCount   = registerSignal(SIG_STAT_DTP_RX_SENT);
  sigStatDTPRecvSeqNum    = registerSignal(DTP_SEQ_NUM_RCVD);
  sigStatDTPSentSeqNum    = registerSignal(DTP_SEQ_NUM_SENT);
}

void DTP::initialize(int step)
{

  if (step == 0)
  {

    initGates();
    initialSeqNumPolicy = getRINAModule<InitialSeqNumPolicyBase*>(this, 1, {INITIAL_SEQ_NUM_POLICY_NAME});
    rcvrInactivityPolicy = getRINAModule<RcvrInactivityPolicyBase*>(this, 1, {RCVR_INACTIVITY_POLICY_NAME});
    senderInactivityPolicy = getRINAModule<SenderInactivityPolicyBase*>(this, 1, {SENDER_INACTIVITY_POLICY_NAME});
    rttEstimatorPolicy = getRINAModule<RTTEstimatorPolicyBase*>(this, 1, {RTT_ESTIMATOR_POLICY_NAME});

    senderInactivityTimer = new SenderInactivityTimer();
    rcvrInactivityTimer = new RcvrInactivityTimer();


    rendezvousEnabled = getModuleByPath(".^.^.efcp")->par("rendezvousEnabled").boolValue();

  }
  else if (step == 1)
  {

    initSignalsAndListeners();

//    if(state->isDtcpPresent()){

//    }else{
//      senderInactivityTimer = nullptr;
//      rcvrInactivityTimer = nullptr;
//    }

//  par(RCVR_INACTIVITY_POLICY_NAME).setStringValue(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par(RCVR_INACTIVITY_POLICY_NAME).stringValue());
//  par(SENDER_INACTIVITY_POLICY_NAME).setStringValue(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par(SENDER_INACTIVITY_POLICY_NAME).stringValue());
//  par(INITIAL_SEQ_NUM_POLICY_NAME).setStringValue(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par(INITIAL_SEQ_NUM_POLICY_NAME).stringValue());
//  par(RTT_ESTIMATOR_POLICY_NAME).setStringValue(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par(RTT_ESTIMATOR_POLICY_NAME).stringValue());

//    rcvrInactivityPolicy = (RcvrInactivityPolicyBase*) createPolicyModule(RCVR_INACTIVITY_POLICY_PREFIX,
//        RCVR_INACTIVITY_POLICY_NAME);
//    senderInactivityPolicy = (SenderInactivityPolicyBase*) createPolicyModule(SENDER_INACTIVITY_POLICY_PREFIX,
//        SENDER_INACTIVITY_POLICY_NAME);
//    initialSeqNumPolicy = (InitialSeqNumPolicyBase*) createPolicyModule(INITIAL_SEQ_NUM_POLICY_PREFIX,
//        INITIAL_SEQ_NUM_POLICY_NAME);
//    rttEstimatorPolicy = (RTTEstimatorPolicyBase*) createPolicyModule(RTT_ESTIMATOR_POLICY_PREFIX,
//        RTT_ESTIMATOR_POLICY_NAME);

//    runInitialSeqNumPolicy();


    bool interrupter = false;
    interrupter = getModuleByPath(".^.^.")->par("interrupter").boolValue();
    if(interrupter){

      TheInterrupterTimer* startR = new TheInterrupterTimer();
      startR->setAction(INTERRUPTER_ZERO_RCV_CREDIT);
      scheduleAt(120, startR);

      TheInterrupterTimer* stopR = new TheInterrupterTimer();
      stopR->setAction(INTERRUPTER_INFLATE_RCV_CREDIT);
      scheduleAt(140, stopR);

    }

    //set initial value for RTO based on RTT from .ned
    rttEstimatorPolicy->setRto(state->getRtt());

  }

}

void DTP::initGates()
{
  northI = this->gateHalf(GATE_DTP_NORTHIO, cGate::INPUT);
  northO = this->gateHalf(GATE_DTP_NORTHIO, cGate::OUTPUT);
  southI = this->gateHalf(GATE_DTP_SOUTHIO, cGate::INPUT);
  southO = this->gateHalf(GATE_DTP_SOUTHIO, cGate::OUTPUT);
}
/**
 * Get reference to the QoSCube active on this flow.
 * @return Reference to the QoSCube active on this flow.
 */
const QoSCube* DTP::getQoSCube() const
{
  return state->getQoSCube();
}

/**
 * Set QoSCube for this flow.
 * @param qosCube QoSCube to be used on this connection.
 */
void DTP::setQoSCube(const QoSCube* qosCube)
{
  //TODO A2 Make copy; ... Why?
  state->setQoSCube(qosCube);
}

/**
 * Sets flag for activating PDU dropping capabilities used purely for testing Retransmission
 * This flag is currently obsolete.
 * @param pduDroppingEnabled
 */
void DTP::setPduDroppingEnabled(bool pduDroppingEnabled)
{
  this->pduDroppingEnabled = pduDroppingEnabled;
}

/**
 * This method is called upon deletion of DTP module.
 * All dynamically components belonging to DTP should be deallocated here.
 */
void DTP::flushAllQueuesAndPrepareToDie()
{
  cancelAndDelete(senderInactivityTimer);
  senderInactivityTimer = nullptr;
  cancelAndDelete(rcvrInactivityTimer);
  rcvrInactivityTimer = nullptr;

  for(auto it = aTimerQ.begin(); it != aTimerQ.end(); )
  {
    cancelAndDelete((*it));
    it = aTimerQ.erase(it);
  }

}

/**
 * Prints important variables on the simulation pane next to the module.
 */
void DTP::redrawGUI()
{
  if (!getEnvir()->isGUI())
  {
    return;
  }

  if (state->isDtcpPresent())
  {
    dtcp->redrawGUI();
  }

  cDisplayString& disp = getDisplayString();
  disp.setTagArg("t", 1, "r");
  std::ostringstream desc;
  desc << "nextSeqNum: " << state->getNextSeqNumToSendWithoutIncrement() << "\n";

  desc << "rLWE: " << state->getRcvLeftWinEdge() << "\n";

  desc << "maxSeqNumRcvd: " << state->getMaxSeqNumRcvd() << "\n";

  std::vector<DataTransferPDU*>::iterator it;
  std::vector<DataTransferPDU*>* pduQ;

  pduQ = state->getReassemblyPDUQ();
  if (pduQ->empty())
  {
    desc << "reassemblyQ: empty" << "\n";
  }
  else
  {
    desc << "reassemblyQ: ";
    std::vector<DataTransferPDU*>::iterator it;
    for (it = pduQ->begin(); it != pduQ->end(); ++it)
    {
      desc << (*it)->getSeqNum() << " | ";
    }
    desc << "\n";
  }

  desc << "droppedPDU: " << state->getDropDup() << "\n";
  desc << "rtt: " << state->getRtt() << "\n";

  disp.setTagArg("t", 0, desc.str().c_str());

}

/**
 * Sets Connection-ID of this connection.
 * @param connId
 */
void DTP::setConnId(const ConnectionId& connId)
{
  this->connId = connId;
}

void DTP::handleRendezvousTimer(DTCPRendezvousTimer* timer)
{
//  timer->setCounter(timer->getCounter() + 1);
  //TODO A2 increment counter to indicate retransmission of RendezvousPDU
  rendezvousCondition();

}

void DTP::changeInBuffers()
{
  dtcp->updateRcvRtWinEdge(state);

  if(state->isDtcpPresent()){
    if(dtcp->dtcpState->isRcvRendez() && (dtcp->dtcpState->getRcvRightWinEdge() >= dtcp->dtcpState->getRendezSeqNum())){
      sendReliableControlPDU();
    }
  }

}

void DTP::sendReliableControlPDU()
{
  sendAckFlowPDU();
  dtcp->startReliableCPDUTimer();
}

void DTP::handleInterrupterTimer(TheInterrupterTimer* interrupter)
{
  switch(interrupter->getAction()){
    case INTERRUPTER_ZERO_RCV_CREDIT:{
      dtcp->getDTCPState()->setRcvCredit(0);
      break;
    }
    case INTERRUPTER_INFLATE_RCV_CREDIT:{
      dtcp->getDTCPState()->setRcvCredit(10);
      changeInBuffers();


    }
  }

  delete interrupter;
}

void DTP::handleMessage(cMessage *msg)
{
  if (msg->isSelfMessage())
  {
    /* Timers */
    DTPTimers* timer = static_cast<DTPTimers*>(msg);
    switch (timer->getType())
    {
      case (DTP_RCVR_INACTIVITY_TIMER): {
        handleDTPRcvrInactivityTimer(static_cast<RcvrInactivityTimer*>(timer));
        break;
      }

      case (DTP_SENDER_INACTIVITY_TIMER): {
        handleDTPSenderInactivityTimer(static_cast<SenderInactivityTimer*>(timer));
        break;
      }

      case (DTP_A_TIMER): {
        handleDTPATimer(static_cast<ATimer*>(timer));
//        delete msg;
        break;
      }

      case (DTP_INTERRUPTER_TIMER): {
        handleInterrupterTimer(static_cast<TheInterrupterTimer*>(msg));
        break;

      }

    }
  }
  else
  {

    /* Either PDUs from RMT or UserDataField from Delimiting */
    if (msg->arrivedOn(northI->getId()))
    {

      handleMsgFromUp(static_cast<UserDataField*>(msg));

    }
    else if (msg->arrivedOn(southI->getId()))
    {
      handleMsgFromRMT((PDU*) msg);
    }
  }

  if (state->isDtcpPresent())
  {
    emit(sigStatDTPClosedWinQ, dtcp->dtcpState->getClosedWinQueLen());
//      emit(sigStatDTPRxCount, dtcp->dtcpState->getRxSent());
  }

  redrawGUI();
}

/**
 * This method fills header fields in given @param pdu
 * @param pdu
 */
void DTP::setPDUHeader(PDU* pdu)
{
  pdu->setConnId(this->flow->getConId());
  pdu->setSrcAddr(this->flow->getSrcAddr());
  pdu->setDstAddr(this->flow->getDstAddr());
  pdu->setSrcApn(this->flow->getDstApni().getApn());
  pdu->setDstApn(this->flow->getSrcApni().getApn());
}


/**   !!!!!!!!!!!!!!!!!!!!!!  Deprecated  !!!!!!!!!!!!!!!
 * Generates new DT-PDU with @param userDataField and puts it on generatedPDUsQ.
 * @param userDataField
 */
void DTP::generateDTPDU(UserDataField* userDataField)
{
  DataTransferPDU* dataPDU = new DataTransferPDU();
  setPDUHeader(dataPDU);
  dataPDU->setSeqNum(state->getNextSeqNumToSend());
  /* Set DRF flag in PDU */
  if (setDRFInPDU(false))
  {
    dataPDU->setFlags(dataPDU->getFlags() | DRF_FLAG);
  }
  dataPDU->encapsulate(userDataField);
  state->pushBackToGeneratedPDUQ(dataPDU);
}

/**
 * Handles message processing from upper module (delimiting) and
 * tries to send it to RMT.
 * @param sdu
 */
void DTP::handleMsgFromUp(UserDataField* userDataField)
{
  cancelEvent(senderInactivityTimer);

//  delimit(sduData);
  userDataFieldQOut.push_back(userDataField);

  generatePDUsnew();

//  generateDTPDU(userDataField);

  trySendGenPDUs(state->getGeneratedPDUQ());

  schedule(senderInactivityTimer);
}

/**
 * Invokes method of same name in DTPState to add @param pdu
 * to Reassembly Queue for further processing.
 * @param pdu PDU to be put on the Reassembly Queue.
 */
void DTP::addPDUToReassemblyQ(DataTransferPDU* pdu)
{
  state->addPDUToReassemblyQ(pdu);
}

/**
 * Invokes delimiting upon finishing processing incoming PDU from RMT.
 * For now, this method passes only complete, in-order SDUs to the upper flow.
 * @param pdu Can be nullptr.
 */
void DTP::delimitFromRMT()
{
  Enter_Method_Silent();
  PDUQ_t* pduQ = state->getReassemblyPDUQ();

  for (auto it = pduQ->begin();
          it != pduQ->end() && (*it)->getSeqNum() <= state->getRcvLeftWinEdge();)
  {/* DO NOT FORGET TO PUT '++it' in all cases where we DO NOT erase PDUs from queue */
    send((*it)->decapsulate(), northO);
    delete (*it);
    it = pduQ->erase(it);
  }

}

/**
 * Invokes Common checks on incomming Control PDUs.
 * @param pdu Control PDU to be checked.
 * @return Return false if the check fails signaling to stop processing this Control PDU.
 */
bool DTP::commonRcvControl(ControlPDU* pdu)
{
  if (pdu->getSeqNum() <= dtcp->getLastCtrlSeqNumRcv())/* Duplicate ControlPDU */
  {
    if ((pdu->getType() & PDU_ACK_BIT) == PDU_ACK_BIT)
    {
      dtcp->incDupAcks();
    }
    if ((pdu->getType() & PDU_FC_BIT) == PDU_FC_BIT)
    {
      dtcp->incDupFC();
    }
    delete pdu;
    return false;
  }
  else if (pdu->getSeqNum() > dtcp->getLastCtrlSeqNumRcv() + 1)/* Out of order */
  {
    /* LostControlPDU Policy */
    dtcp->runLostControlPDUPolicy(state);
  }
  else
  {
    dtcp->setLastCtrlSeqnumRcvd(pdu->getSeqNum());
  }

  return true;
}

/**
 * This method sends ControlPDU containing only Flow Control information.
 */
void DTP::sendFCOnlyPDU()
{
  Enter_Method_Silent
  ();

  FlowControlOnlyPDU* fcOnlyPdu = new FlowControlOnlyPDU();

  setPDUHeader(fcOnlyPdu);

  fcOnlyPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());

  fillFlowControlPDU(fcOnlyPdu);

  sendToRMT(fcOnlyPdu);
}

/**
 * This methods fill all Flow Control information related fields in Control PDU
 * and updates last sent RRWE.
 * @param flowControlPdu
 */
void DTP::fillFlowControlPDU(FlowControlPDU* flowControlPdu)
{

  flowControlPdu->setRcvRightWinEdge(dtcp->getRcvRightWinEdge());

  flowControlPdu->setRcvRate(dtcp->getRcvrRate());

  flowControlPdu->setTimeUnit(dtcp->getSendingTimeUnit());

  flowControlPdu->setSndLeftWinEdge(dtcp->getSndLeftWinEdge());

  flowControlPdu->setSndRightWinEdge(dtcp->getSndRtWinEdge());

  flowControlPdu->setSndRate(dtcp->getSendingRate());

  dtcp->getDTCPState()->setRcvRightWinEdgeSent(dtcp->getDTCPState()->getRcvRightWinEdge());
}

/**
 * This method sends Ack and Flow Control information based on the presence
 * of Flow Control and Retransmission Control.
 * @param seqNum Explicitly specify the seqNum to be Acked, otherwise the RLWE is Acked.
 * @param seqNumValid Specifies if the seqNum is valid,
 *  or if it is just "default and the RLWE should be used instead".
 */
void DTP::sendAckFlowPDU(unsigned int seqNum, bool seqNumValid)
{
  Enter_Method_Silent();

  if(!state->isDtcpPresent()){
    return;
  }

  if (!seqNumValid)
  {
    seqNum = state->getRcvLeftWinEdge();
  }


  if (dtcp->dtcpState->isFCPresent() && dtcp->dtcpState->isRxPresent())
  {
    // Send Ack/Flow Control PDU with LWE and RWE
    AckFlowPDU* ackFlowPdu = new AckFlowPDU();
    setPDUHeader(ackFlowPdu);
    ackFlowPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());

    ackFlowPdu->setAckNackSeqNum(seqNum);

    fillFlowControlPDU(ackFlowPdu);
    sendToRMT(ackFlowPdu);
  }
  else if (dtcp->dtcpState->isFCPresent())
  {
    sendFCOnlyPDU();
  }
  else if (dtcp->dtcpState->isRxPresent())
  {
    sendAckOnlyPDU(seqNum);
  }

}

void DTP::handleControlPDUFromRMT(ControlPDU* pdu)
{

  if (!commonRcvControl(pdu))
  {
    //The Control PDU has been deleted because of duplicate
    return;
  }

  if (pdu->getType() == CONTROL_ACK_PDU)
  {
    dtcp->runRcvrControlAckPolicy(state);
    if(dtcp->getDTCPState()->isSndRendez()){
      ControlAckPDU* controlAckPDU = static_cast<ControlAckPDU*>(pdu);
      if(dtcp->getDTCPState()->getRendezvousTimer()->getSeqNum() == controlAckPDU->getLastCtrlSeqNumRcv()){
        cancelAndDelete(dtcp->getDTCPState()->getRendezvousTimer());
        dtcp->getDTCPState()->setRendezvousTimer(nullptr);
      }


    }

  }
  else if (pdu->getType() == RENDEZVOUS_PDU)
  {
    RendezvousPDU* rendezPDU = (RendezvousPDU*) pdu;
    dtcp->dtcpState->setRendezSeqNum(rendezPDU->getRendezSeqNum());
//    if(rendezPDU->getLastCtrlSeqNumRcv() == dtcp->dtcpState->getLastControlSeqNumSent()){
      /* The sender sent this RendezvousPDU based on up-to-date information
       * so this C-PDU can be assumed valid.
       */
      dtcp->dtcpState->setRcvRendez(true);
      sendControlAckPDU();
//    }
  }
  else
  {

    if (pdu->getType() & PDU_SEL_BIT)
    {
      /*
        SELECT_ACK_PDU        = 0xC9;
        SELECT_NACK_PDU       = 0xCA;
        SELECT_ACK_FLOW_PDU   = 0xCD;
        SELECT_NACK_FLOW_PDU  = 0xCE;
       */

      //RTT estimator
      runRTTEstimatorPolicy();

      if (pdu->getType() & PDU_NACK_BIT)
      {
        SelectiveNackPDU* selNackPdu = (SelectiveNackPDU*) pdu;

        for (unsigned int i = 0; i < selNackPdu->getNackListLen(); i++)
        {
          unsigned int startSeqNum = selNackPdu->getNackList(i * 2);
          unsigned int endSeqNum = selNackPdu->getNackList((i * 2) + 1);

          dtcp->nackPDU(startSeqNum, endSeqNum);

        }
      }
      else if (pdu->getType() & PDU_ACK_BIT)
      {

        //TODO B1 Shoudn't this be a policy?
        SelectiveAckPDU* selAckPdu = (SelectiveAckPDU*) pdu;
        unsigned int tempSLWE = 0;
        for (unsigned int i = 0; i < selAckPdu->getNackListLen(); i++)
        {
          unsigned int startSeqNum = selAckPdu->getNackList(i * 2);
          unsigned int endSeqNum = selAckPdu->getNackList((i * 2) + 1);

          tempSLWE = std::max(endSeqNum, tempSLWE);

          dtcp->ackPDU(startSeqNum, endSeqNum);

          // min = dtcp->getSmallestSeqNumFromRxQOrNextSeqNumToSend - 1
          //state->setSenderLeftWinEdge(std::min(min, state->getSndLeftWinEdge);

          //            state->setSenderLeftWinEdge(tempSLWE);
          //TODO B2 O'really? Shouldn't it always be nextSeqNum -1?
          dtcp->updateSenderLWE(tempSLWE + 1);

        }
      }

    }
    else

    if (pdu->getType() & (PDU_ACK_BIT | PDU_NACK_BIT))
    {

      //Retrieve the Time of this Ack - RTT estimator policy
      runRTTEstimatorPolicy();

      if (pdu->getType() & PDU_NACK_BIT)
      {

        NackOnlyPDU *nackPdu = (NackOnlyPDU*) pdu;

        dtcp->nackPDU(nackPdu->getAckNackSeqNum());

      }
      else if (pdu->getType() & PDU_ACK_BIT)
      {

        AckOnlyPDU *ackPdu = (AckOnlyPDU*) pdu;
        EV << getFullPath() << ": PDU number: " << ackPdu->getAckNackSeqNum() << " Acked" << endl;

        dtcp->runSenderAckPolicy(state);

      }
      /* End of Ack/Nack */

    }

    if ((pdu->getType() & PDU_FC_BIT))
    {
      FlowControlOnlyPDU *flowPdu = (FlowControlOnlyPDU*) pdu;

      //Update RightWindowEdge and SendingRate.
      dtcp->setSndRtWinEdge(flowPdu->getRcvRightWinEdge());
      dtcp->setSendingRate(flowPdu->getRcvRate());

      if (dtcp->getDTCPState()->getClosedWinQueLen() > 0)
      {
        /* Note: The ClosedWindow flag could get set back to true immediately in trySendGenPDUs */
        dtcp->getDTCPState()->setClosedWindow(false);
        trySendGenPDUs(dtcp->getDTCPState()->getClosedWindowQ());

        if (dtcp->dtcpState->isWinBased())
        {
          if (!dtcp->isClosedWinQClosed())
          {
            notifyStartSending();
          }

        }
      }

      rendezvousCondition();
    }

  }
  delete pdu;
}

/**
 * This method handles incomming PDUs from RMT
 * and passes them to specific methods for further processing.
 * @param msg Incomming msg is either DataTransferPDU or ControlPDU.
 * If it is neither of those, Error is raised.
 */
void DTP::handleMsgFromRMT(PDU* msg)
{

  state->setCurrentPdu(msg);

  if (dynamic_cast<DataTransferPDU*>(msg))
  {
    DataTransferPDU* pdu = (DataTransferPDU*) msg;

    handleDataTransferPDUFromRMT(pdu);

  }
  else if (dynamic_cast<ControlPDU*>(msg))
  {
    ControlPDU* pdu = (ControlPDU*) msg;
    EV << getFullPath() << ": Control PDU number: " << pdu->getSeqNum() << " received" << endl;

    //Putting it before ControlAckPDU might be an issue

    handleControlPDUFromRMT(pdu);
  }
  else
  {

    throw cRuntimeError("Unexptected PDU Type");
  }

  state->setCurrentPdu(nullptr);
}



bool DTP::isATimerQEmpty()
{

  return aTimerQ.empty();
}


/**
 * This method cancels and deletes all A-Timers from aTimerQ up to @param seqNum
 * @param seqNum Maximum sequence number associated with ATimer that will be deleted.
 */
void DTP::cancelATimer(unsigned int seqNum)
{
  Enter_Method_Silent();
  for (auto it = aTimerQ.begin(); it != aTimerQ.end() && (*it)->getSeqNum() <= seqNum;)
  {
    cancelAndDelete((*it));
    it = aTimerQ.erase(it);
  }


}

void DTP::startATimer(unsigned int seqNum)
{

  if(!(state->getQoSCube()->getATime() > 0.0))
  {
    return;
  }
  //TODO A1 Make a vector in DTPState of all active ATimers.
  Enter_Method_Silent();
  ATimer* aTimer = new ATimer();
  aTimer->setSeqNum(seqNum);
  schedule(aTimer);



  auto it = aTimerQ.begin();
  for(; it != aTimerQ.end(); ++it)
  {
    if((*it)->getSeqNum() > seqNum)
    {
      break;
    }
  }
  aTimerQ.insert(it, aTimer);


}

bool DTP::isDuplicate(unsigned int seqNum)
{
  /* Not a true duplicate. (Might be a duplicate among the gaps) */
  bool dup = false;
  PDUQ_t::iterator it;
  PDUQ_t* pduQ = state->getReassemblyPDUQ();
  for (it = pduQ->begin(); it != pduQ->end(); ++it)
  {
    if ((*it)->getSeqNum() == seqNum)
    {
      dup = true;
      break;
    }
  }
  return dup;
}

double DTP::getATime()
{
  return state->getQoSCube()->getATime();
}

void DTP::handleDataTransferPDUFromRMT(DataTransferPDU* pdu)
{

  EV << getFullPath() << ": PDU number: " << pdu->getSeqNum() << " received" << endl;

  emit(sigStatDTPRecvSeqNum, pdu->getSeqNum());

  cancelEvent(rcvrInactivityTimer);
  /*
   * What to do when you want to discard the incomming PDU?
   * How to handle both cases - you want to keep it for further processing/ you want to drop it.
   */
  if (state->isDtcpPresent())
  {
    if (dtcp->dtcpState->isWinBased())
    {
      if (pdu->getSeqNum() > dtcp->getRcvRightWinEdge())
      {
        schedule(rcvrInactivityTimer);
        dtcp->runRcvFCOverrunPolicy(state);
        if (state->getCurrentPdu() == nullptr)
        {
          return;
        }
      }
    }
    else if (dtcp->dtcpState->isRateBased())
    {
      if (dtcp->getPdusRcvdInTimeUnit() + 1 > dtcp->getRcvrRate())
      {
        schedule(rcvrInactivityTimer);
        dtcp->runRcvFCOverrunPolicy(state);
        if (state->getCurrentPdu() == nullptr)
        {
          return;
        }
      }
    }

    if (dtcp->dtcpState->isFCPresent())
    {
      //    dtcp->resetWindowTimer();

      /* Run ECN policy */
      dtcp->runECNPolicy(state);

    }
  }

  // if PDU.DRF == true
  if (pdu->getFlags() & DRF_FLAG)
  {
    bubble("Received PDU with DRF set");
    /* Case 1) DRF is set - either first PDU or new run */

    delimitFromRMT();

    //Flush the PDUReassemblyQueue
    flushReassemblyPDUQ();

    state->setMaxSeqNumRcvd(pdu->getSeqNum());
    state->setRcvLeftWinEdge(state->getMaxSeqNumRcvd());

    //Put PDU on ReassemblyQ
    addPDUToReassemblyQ(pdu);

    /* I guess i did not think this through (will be removed) */
//    if (getATime() > 0)
//    {
//      startATimer(pdu->getSeqNum());
//    }
//    else
//    {
//      svUpdate(pdu->getSeqNum());
//    }

    if (state->isDtcpPresent())
    {
      svUpdate(pdu->getSeqNum());

    }
    else
    {
      state->setRcvLeftWinEdge(pdu->getSeqNum());
      //TODO A2: No A-Timer?
    }
    delimitFromRMT();

    schedule(rcvrInactivityTimer);

  }
  else
  {

    /* Not the start of a run */
    if (pdu->getSeqNum() <= state->getRcvLeftWinEdge() || pdu->getSeqNum() == state->getMaxSeqNumRcvd())
    {
      bubble("Dropping duplicate PDU");
      EV << getFullPath() << ":Duplicated PDU number: " << pdu->getSeqNum() << " received - DROPPING!" << endl;
      /* Case 2) A Real Duplicate */
      //Discard PDU and increment counter of dropped duplicates PDU
      delete pdu;

      state->incDropDup();

      sendAckFlowPDU();

      return;
    }
    if (state->getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() < state->getMaxSeqNumRcvd())
    {
      /* Not a true duplicate. (Might be a duplicate among the gaps) */
      if (isDuplicate(pdu->getSeqNum()))
      {
        /* Case 3) Duplicate Among gaps */
        EV << getFullPath() << ":Duplicated PDU number: " << pdu->getSeqNum() << " received - DROPPING!" << endl;
        //Discard PDU and increment counter of dropped duplicates PDU
        delete pdu;
        //increment counter of dropped duplicates PDU
        state->incDropDup();

        //send an Ack/Flow Control PDU with current window values
        sendAckFlowPDU();
        return;
      }
      else
      {
        /* Case 3) This goes in a gap */
        /* Put at least the User-Data of the PDU with its Sequence Number on PDUReassemblyQueue in Sequence Number order */
        addPDUToReassemblyQ(pdu);

//        svUpdate(state->getMaxSeqNumRcvd()); /* Update left edge, etc */

        if (state->isDtcpPresent())
        {
          svUpdate(state->getMaxSeqNumRcvd()); /* Update left edge, etc */
        }
        else
        {
          state->setRcvLeftWinEdge(state->getMaxSeqNumRcvd());
          /* No A-Timer necessary, already running */
        }

        delimitFromRMT();
        schedule(rcvrInactivityTimer);
        return;
      }
    }
    /* Case 4) This is in order */
    if (pdu->getSeqNum() == state->getMaxSeqNumRcvd() + 1)
//    if (pdu->getSeqNum() == state->getRcvLeftWinEdge())
    {
      state->incMaxSeqNumRcvd();
      addPDUToReassemblyQ(pdu);

//      if (getATime() > 0)
//      {
//        startATimer(pdu->getSeqNum());
//      }
//      else
//      {
//        svUpdate(state->getMaxSeqNumRcvd());
//      }

      if (state->isDtcpPresent())
      {
        svUpdate(state->getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
      }
      else
      {
        state->setRcvLeftWinEdge(state->getMaxSeqNumRcvd());
        //start A-Timer (for this PDU)
        startATimer(pdu->getSeqNum());
      }

      delimitFromRMT();/* Create as many whole SDUs as possible */

      schedule(rcvrInactivityTimer);

    }
    else
    {
      /* Case 5) it is out of order */
      if (pdu->getSeqNum() > state->getMaxSeqNumRcvd() + 1)
      {
        state->setMaxSeqNumRcvd(pdu->getSeqNum());
        addPDUToReassemblyQ(pdu);

//        if (getATime() > 0)
//        {
//          startATimer(state->getMaxSeqNumRcvd());
//        }
//        else
//        {
//          svUpdate(state->getMaxSeqNumRcvd());
//        }

        if (state->isDtcpPresent())
        {
          svUpdate(state->getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
        }
        else
        {
          startATimer(state->getMaxSeqNumRcvd());
        }

        delimitFromRMT();
        schedule(rcvrInactivityTimer);

      }
//  /* Backstop timer */
//  schedule(rcvrInactivityTimer);
    }

    //TODO C1 DIF.integrity
    /* If we are encrypting, we can't let PDU sequence numbers roll over */

    //If DIF.Integrity and PDU.SeqNum > SequenceNumberRollOverThreshhold Then
    ///* Security requires a new flow */
    //RequestFAICreateNewConnection( PDU.FlowID )
    //Fi
  }

}

void DTP::handleDTPRcvrInactivityTimer(RcvrInactivityTimer* timer)
{

  runRcvrInactivityTimerPolicy();

}

void DTP::handleDTPSenderInactivityTimer(SenderInactivityTimer* timer)
{
  runSenderInactivityTimerPolicy();

}

void DTP::resetSenderInactivTimer()
{
  Enter_Method_Silent();
  cancelEvent(senderInactivityTimer);
  schedule(senderInactivityTimer);
}

void DTP::handleDTPATimer(ATimer* timer)
{

  state->setTmpAtimer(timer);

  if (state->isDtcpPresent())
  {
    //    runSendingAckPolicy(timer);
    dtcp->runSendingAckPolicy(state, timer);
  }
  else
  {

    //Update RcvLeftWindowEdge
    PDUQ_t* pduQ = state->getReassemblyPDUQ();

    // Advance RLWE as much as possible
    for (auto it = pduQ->begin(); it != pduQ->end() && (*it)->getSeqNum() <= timer->getSeqNum(); ++it)
    {
      if((state->getRcvLeftWinEdge() + 1) + state->getQoSCube()->getMaxAllowGap() >= (*it)->getSeqNum())
      {
        state->setRcvLeftWinEdge((*it)->getSeqNum());
      }
      else
      {
        break;
      }
    }
    //Discard any PDUs that are bigger than RLWE but smaller than A-Timer seqNum
    for (auto it = pduQ->begin(); it != pduQ->end() && (*it)->getSeqNum() <= timer->getSeqNum();)
    {
      if((*it)->getSeqNum() > state->getRcvLeftWinEdge())
      {
        delete (*it);
        it = pduQ->erase(it);
      }

    }

    if (state->getRcvLeftWinEdge() > timer->getSeqNum())
    {
      bubble("RcvLeftWindowEdge SHOULD not be bigger than seqNum in A-Timer, right?");
      //      throw cRuntimeError("RcvLeftWindowEdge SHOULD not be bigger than seqNum in A-Timer, right?");
    }


    state->setRcvLeftWinEdge(timer->getSeqNum());

    cancelATimer(timer->getSeqNum());


    //Invoke delimiting
    delimitFromRMT();


    //reset SenderInactivity timer
    //    resetSenderInactivTimer();


  }

  state->setTmpAtimer(nullptr);
}

unsigned int DTP::delimit(SDUData* sduData)
{


  //TODO A1 update return statement
return 1;

//  //TODO B2 Does PDU header counts to MaxFlowPDUSize? edit: yes, it does!
//  if (sdu->getSize() > state->getMaxFlowPduSize())
//  {
//    unsigned int size = state->getMaxFlowPduSize();
//    //SDU is bigger than Max Allowed PDU
//    //S/DUFrag *frag = new SDUFrag
//
//    SDU* tmp;
//    unsigned int i;
//    for (i = 0; i * size < sdu->getSize(); i++)
//    {
//      tmp = sdu->genFragment(size, i, i * size);
//      dataQ.push_back(tmp);
//
//    }
//    return i;
//  }
//  else
//  {
//    dataQ.push_back(sdu);
//    return 1;
//  }

}

unsigned int DTP::delimitFromRMT(PDU *pdu, unsigned int len)
{
  unsigned int counter = 0;

//  if()

  return counter;
}

bool DTP::setDRFInPDU(bool override)
{
  if (state->isSetDrfFlag() || override)
  {
    state->setSetDrfFlag(false);
    return true;
  }
  else
  {
    return false;
  }
}

void DTP::generatePDUsnew()
{
  DataTransferPDU* baseDataPDU = new DataTransferPDU();
  setPDUHeader(baseDataPDU);

//  //invoke SDU protection so we don't have to bother with it afterwards; EDIT: sduQ is not used anymore!!!
//  for (std::vector<SDU*>::iterator it = dataQ.begin(); it != dataQ.end(); ++it)
//  {
//    sduProtection(*it);
//  }

  while (!userDataFieldQOut.empty())
  {
    DataTransferPDU* genPDU = baseDataPDU->dup();
    genPDU->setSeqNum(state->getNextSeqNumToSend());

    /* Set DRF flag in PDU */
    if (setDRFInPDU(false))
    {
      genPDU->setFlags(genPDU->getFlags() | DRF_FLAG);
    }

    genPDU->encapsulate(userDataFieldQOut.front());
    userDataFieldQOut.erase(userDataFieldQOut.begin());

    state->pushBackToGeneratedPDUQ(genPDU);
  }

  //HOTFIX
  if(!state->isDtcpPresent()){
    state->setSetDrfFlag(true);
  }

  delete baseDataPDU;
}

void DTP::fillRendezvousPDU(RendezvousPDU* rendezPDU)
{
  /* Fill in Rendezvous PDU */
  fillControlAckPDU(rendezPDU);
  if(dtcp->dtcpState->isRxPresent()){
    rendezPDU->setRendezSeqNum(dtcp->dtcpState->getSndLeftWinEdge() + 1);
  }else{
    rendezPDU->setRendezSeqNum(state->getNextSeqNumToSendWithoutIncrement());
  }
}

void DTP::sendRendezvousPDU()
{
  /* Send Rendezvous PDU */
  RendezvousPDU* rendezPDU = new RendezvousPDU();
  setPDUHeader(rendezPDU);
  /* Fill in Rendezvous PDU */
  fillRendezvousPDU(rendezPDU);
  sendToRMT(rendezPDU);
  //TODO A! restart SenderInactivity Timer
}

void DTP::rendezvousCondition()
{
  Enter_Method_Silent();

  //TODO A1 Remove after sucessfull testing
  if(!rendezvousEnabled){
    return;
  }

  /* Rendezvous condition */
  if (!dtcp->getDTCPState()->isSndRendez())
  {
//    if (((state->isDtcpPresent() && dtcp->getDTCPState()->isRxPresent() && dtcp->getDTCPState()->getRxQLen() == 0) || (!dtcp->getDTCPState()->isRxPresent())) && (dtcp->getDTCPState()->getClosedWinQueLen() != 0))
    if ((state->isDtcpPresent() && (!dtcp->getDTCPState()->isRxPresent() || dtcp->getDTCPState()->getRxQLen() == 0)) && (dtcp->getDTCPState()->getClosedWinQueLen() != 0))
    {//condition is satisfied if all DT-PDUs are Acked or Retransmission is not present; AND there is DT-PDU on closedWindowQ (we have something to send)


      if (dtcp->getDTCPState()->getSndRightWinEdge() < state->getNextSeqNumToSendWithoutIncrement())
      {
        /* Send Rendezvous PDU */
        sendRendezvousPDU();
        dtcp->getDTCPState()->setSndRendez(true);

        dtcp->startRendezvousTimer();

      }
    }
  }else{
    /* Sender is in rendez_at_sender state */
    if(dtcp->getDTCPState()->getSndRightWinEdge() > state->getLastSeqNumSent()){
      dtcp->getDTCPState()->setSndRendez(false);
      cancelAndDelete(dtcp->getDTCPState()->getRendezvousTimer());
      dtcp->getDTCPState()->setRendezvousTimer(nullptr);
    }
  }
}

/**
 *
 */
void DTP::trySendGenPDUs(std::vector<DataTransferPDU*>* pduQ)
{

  if (state->isDtcpPresent())
  {
    //postablePDUs = empty;

    //if flowControl present
    if (dtcp->dtcpState->isWinBased() || dtcp->dtcpState->isRateBased())
    {
      std::vector<DataTransferPDU*>::iterator it;
      for (it = pduQ->begin(); it != pduQ->end(); it = pduQ->begin())
      {
        if (dtcp->dtcpState->isWinBased())
        {
          if (((*it)->getSeqNum() <= dtcp->getSndRtWinEdge()) && !dtcp->getDTCPState()->isClosedWindow())
          {
            /* The Window is Open. */
            dtcp->runTxControlPolicy(state, pduQ);
            /* Watchout because the current 'it' could be freed */
          }
          else
          {
            /* The Window is Closed */
            dtcp->getDTCPState()->setClosedWindow(true);

            if (pduQ == dtcp->getDTCPState()->getClosedWindowQ())
            {
              /* It indicates that trySendGenPDUs method has been called for closedWindowQ
               * So no point of trying to put the DT-PDU on closedWindowQ (again).
               */
              break;
            }

            if (dtcp->getDTCPState()->getClosedWinQueLen() < dtcp->getDTCPState()->getMaxClosedWinQueLen() - 1)
            {
              /* Put PDU on the closedWindowQueue */
              dtcp->getDTCPState()->pushBackToClosedWinQ((*it));
              /* I know it is nasty to access it directly */
              state->getGeneratedPDUQ()->erase(it);

            }
            else
            {
              state->setCurrentPdu(*it);
              state->getGeneratedPDUQ()->erase(it);

              dtcp->runSndFCOverrunPolicy(state);

            }

            /* Rendezvous condition */
            rendezvousCondition();
          }
        }    // end of Window based

        if (dtcp->dtcpState->isRateBased())
        {
          if (dtcp->getPdusSentInTimeUnit() < dtcp->getSendingRate())
          {
            dtcp->runNoRateSlowDownPolicy(state);
          }
          else
          {
            /* Exceeding Sending Rate */

            dtcp->runNoOverridePeakPolicy(state);
          }
        }    // end of RateBased

        if ((dtcp->getDTCPState()->isRateBased() && dtcp->getDTCPState()->isWinBased()) && (dtcp->getDTCPState()->isClosedWindow() ^ dtcp->isSendingRateFullfilled()))
        {
          dtcp->runReconcileFCPolicy(state);
        }

      }    //end of for

    }
    else
    {
      /* FlowControl is not present */
      std::vector<DataTransferPDU*>::iterator it;
      PDUQ_t* pduQ = state->getGeneratedPDUQ();
      for (it = pduQ->begin(); it != pduQ->end();)
      {
        state->pushBackToPostablePDUQ((*it));
        it = pduQ->erase(it);
      }
    }

    /* Iterate over postablePDUs and give them to the RMT */
    if (dtcp->dtcpState->isRxPresent())
    {
      std::vector<DataTransferPDU*>::iterator it;
      PDUQ_t* pduQ = state->getPostablePDUQ();
      for (it = pduQ->begin(); it != pduQ->end();)
      {
        /* Put a copy of each PDU in the RetransmissionQueue */
        dtcp->pushBackToRxQ((*it)->dup());

        sendToRMT((*it));

        it = pduQ->erase(it);
      }

    }
    else
    {
      /*No Retransmission Control is present, but FlowControl */
      /* Post all postablePDUs to RMT */
      std::vector<DataTransferPDU*>::iterator it;
      PDUQ_t* pduQ = state->getPostablePDUQ();
      for (it = pduQ->begin(); it != pduQ->end();)
      {

        sendToRMT((*it));
        it = pduQ->erase(it);
      }

    }

  }
  else
  {
    /* DTCP is not present */
    /* Post all generatedPDUs to RMT */
    std::vector<DataTransferPDU*>::iterator it;
    PDUQ_t* pduQ = state->getGeneratedPDUQ();
    for (it = pduQ->begin(); it != pduQ->end();)
    {
      sendToRMT((*it));
      it = pduQ->erase(it);
    }
  }
}

/**
 * This method calls specified function to perform SDU protection.
 * SDU size will probably change because of the added CRC or whatnot.
 * @param sdu is the SDU being protected eg added CRC or otherwise
 */
void DTP::sduProtection(SDU *sdu)
{
  //TODO C1

}

bool DTP::runInitialSeqNumPolicy()
{
  Enter_Method("InitialSeqNumPolicy");

//  if(initialSeqNumPolicy->run(state, dtcp->getDTCPState())){
//    initialSeqNumPolicy->defaultAction(state, dtcp->getDTCPState());
//  }

  if (state->isDtcpPresent())
  {
    initialSeqNumPolicy->call(state, dtcp->getDTCPState());
  }
  else
  {
    initialSeqNumPolicy->call(state, nullptr);
  }

  return false;
}

void DTP::sendAckOnlyPDU(unsigned int seqNum)
{

  //send an Ack/FlowControlPDU
  AckOnlyPDU* ackPDU = new AckOnlyPDU();
  setPDUHeader(ackPDU);
  ackPDU->setSeqNum(dtcp->getNextSndCtrlSeqNum());
  ackPDU->setAckNackSeqNum(seqNum);
  EV << getFullPath() << ": Sending Ack for PDU number: " << seqNum << endl;
  //    send(ackPDU, southO);
  sendToRMT(ackPDU);
}

void DTP::fillControlAckPDU(ControlAckPDU* ctrlAckPdu)
{
  ctrlAckPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());
  ctrlAckPdu->setLastCtrlSeqNumRcv(dtcp->getLastCtrlSeqNumRcv());
  ctrlAckPdu->setRcvLeftWinEdge(dtcp->getSndLeftWinEdge());
  ctrlAckPdu->setRcvRightWinEdge(dtcp->getSndRtWinEdge());
  ctrlAckPdu->setSndLeftWinEdge(state->getRcvLeftWinEdge());
  ctrlAckPdu->setSndRightWinEdge(dtcp->getRcvRightWinEdge());
  ctrlAckPdu->setRcvRate(dtcp->getRcvrRate());
}

void DTP::sendControlAckPDU()
{
  Enter_Method_Silent();

  ControlAckPDU* ctrlAckPdu = new ControlAckPDU();
  setPDUHeader(ctrlAckPdu);
  fillControlAckPDU(ctrlAckPdu);

  sendToRMT(ctrlAckPdu);
}

void DTP::sendEmptyDTPDU()
{
  Enter_Method_Silent
  ();

  //Send Transfer PDU With Zero length
  DataTransferPDU* dataPdu = new DataTransferPDU();
  setPDUHeader(dataPdu);
  unsigned int seqNum = state->getNextSeqNumToSend();
  dataPdu->setSeqNum(seqNum);

  if (setDRFInPDU(false))
  {
    dataPdu->setFlags(dataPdu->getFlags() | DRF_FLAG);
  }
  Data* data = new Data();
  data->setDataType(DATA_SDU_COMPLETE);

  PDUData* pduData = new PDUData();
  pduData->encapsulate(data);


  UserDataField* userData = new UserDataField();
  userData->encapsulate(pduData);
  userData->setCompleteSDU(true);

  dataPdu->encapsulate(userData);

  if (dtcp->dtcpState->isRxPresent())
  {
//    RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
//    rxExpTimer->setPdu(dataPdu->dup());
//    rxQ.push_back(rxExpTimer);
//    schedule(rxExpTimer);
    dtcp->pushBackToRxQ(dataPdu->dup());
  }

  sendToRMT(dataPdu);
}

void DTP::notifyAboutUnableMaintain()
{
  //FIX A2 - activate when CDAP Splitter is ready
  return;
  // Notify User Flow that we were unable to maintain the QoS for this connection
  //CDAPMessage* uMaintainMsg = new CDAP_M_Unable_Maintain;
  //SDU* sdu = new SDU();
  //sdu->addUserData(uMaintainMsg);
  //send(sdu, northO);
}

/**
 * This methods is invoked when number of PDUs on closedWindowQueue
 * gets reduced under maxClosedWinQLen. It indicates to the upper flow
 * that it can start sending again.
 */
void DTP::notifyStartSending()
{
  if (state->isBlockingPort())
  {
    emit(sigEFCPStartSending, flow);
    state->setBlockingPort(false);
  }
}

/**
 * This method is invoked upon reaching limit on closedWindowQueue
 * and causes the upper flow (whether it is AE or another IPCP).
 */
void DTP::notifyStopSending()
{

  // Notify User Flow to Stop sending due to closed window and full closedWindowQ.

  if (!state->isBlockingPort())
  {
    emit(sigEFCPStahpSending, flow);
    state->setBlockingPort(true);
  }

}

void DTP::notifyAboutInactivity()
{
  //FIX A2 - activate when CDAP Splitter is ready
  return;
  // Notify User Flow there has been no activity for awhile.
  //CDAPMessage* inactivMsg = new CDAP_M_Inactiv();
  //SDU* sdu = new SDU();
  //sdu->addUserData(inactivMsg);
  //send(sdu, northO);

}

void DTP::runRcvrInactivityTimerPolicy()
{
  Enter_Method
  ("RcvrInactivityPolicy");
  if (state->isDtcpPresent())
  {
    rcvrInactivityPolicy->call(state, dtcp->getDTCPState());
  }
  else
  {
    rcvrInactivityPolicy->call(state, nullptr);
  }
}

void DTP::runSenderInactivityTimerPolicy()
{
  Enter_Method
  ("SenderInactivityPolicy");

  if (state->isDtcpPresent())
  {
    senderInactivityPolicy->call(state, dtcp->getDTCPState());
  }
  else
  {
    senderInactivityPolicy->call(state, nullptr);
  }

}

void DTP::sendToRMT(PDU* pdu)
{
  Enter_Method_Silent("SendToRMT");
  take(pdu);
  if (pdu->getType() == DATA_TRANSFER_PDU)
  {
      emit(sigStatDTPSentSeqNum, pdu->getSeqNum());
    //TODO B1 What to do in case of retransmission?
    state->setLastSeqNumSent(pdu->getSeqNum());
    EV << getFullPath() << ": PDU number: " << pdu->getSeqNum() << " sent in time: " << simTime() << endl;
  }
  else
  {
    //This should be controlPDU so do not have to increment LastSeqNumSent
    dtcp->dtcpState->setLastControlSeqNumSent(pdu->getSeqNum());
    EV << getFullPath() << ": Control PDU number: " << pdu->getSeqNum() << " sent in time: " << simTime() << endl;
  }

  send(pdu, southO);
}

double DTP::getRxTime()
{
  //TODO A2 Epsilon
  // RTT + A + epsilon

  return state->getRtt() + getQoSCube()->getATime() / 1000;
}

unsigned int DTP::getAllowableGap()
{

  getQoSCube()->getMaxAllowGap();
  return 4;
}

//TODO B! When to call it?
void DTP::rcvrBufferStateChange()
{
  if (dtcp->dtcpState->isRateBased())
  {
    dtcp->runRateReductionPolicy(state);
  }
}

void DTP::svUpdate(unsigned int seqNum)
{


  if(dtcp->dtcpState->isRcvRendez()){
    dtcp->stopReliableCPDUTimer();
    dtcp->dtcpState->setRcvRendez(false);
  }
  //update RcvLeftWindoEdge
   state->updateRcvLWE(seqNum);

  if (dtcp->dtcpState->isFCPresent())
  {
    if (dtcp->dtcpState->isWinBased())
    {
      dtcp->runRcvrFCPolicy(state);
    }
  }

  if (dtcp->dtcpState->isRxPresent())
  {
    dtcp->runRcvrAckPolicy(state);
  }

  if (dtcp->dtcpState->isFCPresent() && !dtcp->dtcpState->isRxPresent())
  {

    dtcp->runReceivingFCPolicy(state);
  }

}

void DTP::flushReassemblyPDUQ()
{
  state->clearReassemblyPDUQ();
}

void DTP::clearRxQ()
{
  dtcp->clearRxQ();
}

void DTP::schedule(DTPTimers *timer, double time)
{
  //TODO A1 Can't have MPL = 0
  double MPL = (state->getMPL() > 0) ? state->getMPL() : 0;

//    (state->isDtcpPresent() && dtcp->dtcpState->isRxPresent() )? dtcp->getDataReXmitMax() : 0;
  unsigned int rxCount = (state->isDtcpPresent() && dtcp->dtcpState->isRxPresent()) ? dtcp->getDataReXmitMax() : 0;
  double R = (state->getRtt() > 0 && rxCount > 0) ? state->getRtt() * rxCount : 0;
  double A = (state->getQoSCube()->getATime() > 0) ? state->getQoSCube()->getATime() / 1000 : 0;

  switch (timer->getType())
  {

    case (DTP_SENDER_INACTIVITY_TIMER):
      //3(MPL+R+A)
      scheduleAt(simTime() + 3 * (MPL + R + A), timer);
      break;
    case (DTP_RCVR_INACTIVITY_TIMER):
      //2(MPL+R+A)
      scheduleAt(simTime() + 2 * (MPL + R + A), timer);
      break;
    case (DTP_A_TIMER):

      scheduleAt(simTime() + A, timer);
      break;
//    case (DTP_DELIMITING_TIMER):
//        if(!timer->isScheduled()){
//          scheduleAt(simTime() + state->getDelimitDelay(), timer);
//        }
//     break;
  }
}

void DTP::setFlow(const Flow* flow)
{
  this->flow = flow;
}

void DTP::setDTCP(DTCP* dtcp)
{
  this->dtcp = dtcp;
  if (dtcp != nullptr)
  {
    dtcp->setDTP(this);
  }
}

void DTP::setState(DTPState* state)
{
  this->state = state;
}

void DTP::handleQueueInfoFromRMT(QueueInfo* queueInfo)
{
  handleQueueInfo(queueInfo);
}
