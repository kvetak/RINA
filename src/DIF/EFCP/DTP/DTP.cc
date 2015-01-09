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

#include "DTP.h"

Define_Module(DTP);

DTP::DTP()
{
  deletePdu = 0;
  txControlPolicy = NULL;

}
DTP::~DTP()
{

  flushAllQueuesAndPrepareToDie();
  if(state.isDtcpPresent()){

  }

}

void DTP::initGates()
{
  northI = this->gateHalf(GATE_DTP_NORTHIO, cGate::INPUT);
  northO = this->gateHalf(GATE_DTP_NORTHIO, cGate::OUTPUT);
  southI = this->gateHalf(GATE_DTP_SOUTHIO, cGate::INPUT);
  southO = this->gateHalf(GATE_DTP_SOUTHIO, cGate::OUTPUT);
}

const QosCube& DTP::getQosCube() const
{
  return qosCube;
}

void DTP::setQosCube(const QosCube& qosCube)
{
  this->qosCube = qosCube;
  if(qosCube.isForceOrder()){
    state.setRxPresent(true);
  }
}

void DTP::setPduDroppingEnabled(bool pduDroppingEnabled)
{
  this->pduDroppingEnabled = pduDroppingEnabled;
}

void DTP::flushAllQueuesAndPrepareToDie()
{
    std::vector<DataTransferPDU*>* pduQ;
    std::vector<DataTransferPDU*>::iterator itP;

    pduQ = &generatedPDUs;

    for (itP = pduQ->begin(); itP != pduQ->end();)
    {
      delete (*itP);
  //    delete (*it);
      itP = pduQ->erase(itP);
    }

    pduQ = &postablePDUs;

    for (itP = pduQ->begin(); itP != pduQ->end();)
    {
      delete (*itP);
  //    delete (*it);
      itP = pduQ->erase(itP);
    }

    cancelAndDelete(senderInactivityTimer);
    senderInactivityTimer = NULL;
    cancelAndDelete(rcvrInactivityTimer);
    rcvrInactivityTimer = NULL;


}

void DTP::redrawGUI()
{
  if (!ev.isGUI())
  {
      return;
  }

  dtcp->redrawGUI();

  cDisplayString& disp = getDisplayString();
  disp.setTagArg("t", 1, "r");
  std::ostringstream desc;
  desc << "nextSeqNum: " << state.getNextSeqNumToSendWithoutIncrement() <<"\n";
  desc << "sLWE: " << state.getSenderLeftWinEdge() <<"\n";
  if(state.isDtcpPresent() && state.isFCPresent()){
    desc << "sRWE: " << dtcp->getSndRtWinEdge() << "\n";
  }
  desc << "rLWE: " << state.getRcvLeftWinEdge() <<"\n";
  if(state.isDtcpPresent() && state.isFCPresent()){
    desc << "rRWE: " << dtcp->getRcvRtWinEdge() << "\n";
  }

  std::vector<DataTransferPDU*>::iterator it;
  std::vector<DataTransferPDU*>* pduQ;

  pduQ = state.getReassemblyPDUQ();
  if(pduQ->empty()){
      desc << "reassemblyQ: empty"<< "\n";
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
  if(state.isDtcpPresent() && state.isWinBased()){
    if (!state.getClosedWinQueLen())
    {
      desc << "closedWinQ: empty" << "\n";
    }
    else
    {
      desc << "closedWinQQ: ";
      std::vector<DataTransferPDU*>::iterator it;
      std::vector<DataTransferPDU*>* pduQ;
      pduQ = state.getClosedWindowQ();
      for (it = pduQ->begin(); it != pduQ->end(); ++it)
      {
        desc << (*it)->getSeqNum() << " | ";
      }
      desc << "\n";
    }
  }

  disp.setTagArg("t", 0, desc.str().c_str());

}

void DTP::initialize(int step)
{

  initGates();
  state.initDefaults();

  //FIXME A! Set it based on QoS parameters
  state.setWinBased(true);
  state.setRxPresent(false);

  if(state.isDtcpPresent()){
    senderInactivityTimer = new SenderInactivityTimer();
    rcvrInactivityTimer = new RcvrInactivityTimer();
  }else{
    senderInactivityTimer = NULL;
    rcvrInactivityTimer = NULL;
  }

//  redrawGUI();

}

/**
 *
 * @param connId
 */
void DTP::setConnId(const ConnectionId& connId)
{
  this->connId = connId;
}

void DTP::handleMessage(cMessage *msg)
{
  if (msg->isSelfMessage())
  {
    /* Timers */
    DTPTimers* timer = static_cast<DTPTimers*>(msg);
    switch(timer->getType()){
      case(DTP_RCVR_INACTIVITY_TIMER):{
        handleDTPRcvrInactivityTimer(static_cast<RcvrInactivityTimer*>(timer));
        break;
      }

      case(DTP_SENDER_INACTIVITY_TIMER):{
        handleDTPSenderInactivityTimer(static_cast<SenderInactivityTimer*>(timer));
        break;
      }

      case(DTP_A_TIMER):{
        handleDTPATimer(static_cast<ATimer*>(timer));
        break;
      }
    }
  }
  else
  {

    /* Either PDUs from RMT or SDUs from AP */
    if (msg->arrivedOn(northI->getId()))
    {
      //handle SDUs
//          handleSDUs((CDAPMessage*) msg);
//      handleMsgFromDelimiting((Data*) msg);
      handleMsgFromDelimitingnew((SDU*) msg);

    }
    else if (msg->arrivedOn(southI->getId()))
    {
//      handleMsgFromRmt((PDU*) msg);
      handleMsgFromRmtnew((PDU*) msg);
    }
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

void DTP::handleMsgFromDelimitingnew(SDU* sdu){
  cancelEvent(senderInactivityTimer);

  delimit(sdu);

  generatePDUsnew();

  this->trySendGenPDUs(&generatedPDUs);

  schedule(senderInactivityTimer);
}

void DTP::addPDUToReassemblyQ(DataTransferPDU* pdu)
{

 state.addPDUToReassemblyQ(pdu);
}


void DTP::delimitFromRMT(DataTransferPDU* pdu)
{
  PDUQ_t* pduQ = state.getReassemblyPDUQ();

  for (PDUQ_t::iterator it = pduQ->begin(); it != pduQ->end(); )
  {/* DO NOT FORGET TO PUT '++it' in all cases where we DO NOT erase PDUs from queue */

    //TODO B1 add support for out of order SDU delivery
    // negative implication
    unsigned int seqNum = (*it)->getSeqNum();
    if((qosCube.isForceOrder() && ! (seqNum < state.getRcvLeftWinEdge()))){
      return;
    }


    unsigned int delimitFlags = (*it)->getUserDataField()->getSduDelimitFlags();
    if((delimitFlags & SDU_NO_LENGTH) == SDU_NO_LENGTH){
//      if(delimitFlags & SDU_)
      EV << getFullPath() << ": Unhandled condition in delimiting !!!!!!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
    }else{
      if((delimitFlags & SDU_L_COMP_SDU) == SDU_L_COMP_SDU){
        /* PDU contain ZERO or more complete SDUs */
        /*  TODO PUT this in separate method */

        UserDataField* userData = (*it)->getUserDataField();

        SDU* sdu;
        if(userData != NULL){
        while ((sdu = userData->getData()) != NULL)
        {
          //TODO Delimiting/de-fragmentation
//          take(sdu);
          take(sdu);

          send(sdu, northO);
        }
        }
//        delete userData;

        delete (*it);

        it = pduQ->erase(it);
      }
    }
  }
}

bool DTP::commonRcvControl(ControlPDU* pdu)
{
  if (pdu->getSeqNum() < dtcp->getLastCtrlSeqNumRcv())/* Duplicate ControlPDU */
  {
    if ((pdu->getType() & PDU_ACK_BIT) == PDU_ACK_BIT)
    {
      dtcp->rxControl->incDupAcks();
    }
    if ((pdu->getType() & PDU_FC_BIT) == PDU_FC_BIT)
    {
      dtcp->flowControl->incDupFC();
    }
    delete pdu;
    return false;
  }
  else if (pdu->getSeqNum() > dtcp->getLastCtrlSeqNumRcv() + 1)/* Out of order */
  {
    /* LostControlPDU Policy */
    dtcp->runLostControlPDUPolicy(&state);
  }
  else
  {
    dtcp->setLastCtrlSeqnumRcvd(pdu->getSeqNum());
  }

  return true;
}

void DTP::sendFCOnlyPDU()
{
  //TODO A1 send FC
  FlowControlOnlyPDU* fcOnlyPdu = new FlowControlOnlyPDU();

  setPDUHeader(fcOnlyPdu);

  fcOnlyPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());

  fillFlowControlPDU(fcOnlyPdu);

  sendToRMT(fcOnlyPdu);
}

void DTP::fillFlowControlPDU(FlowControlPDU* flowControlPdu)
{

  //      unsigned int newRightWinEdge;
  /****************************************/
  //TODO A! is this the correct variable??
  /****************************************/
  flowControlPdu->setNewRightWinEdge(state.getRcvLeftWinEdge() + dtcp->getRcvCredit());
  //        unsigned int newRate;
  flowControlPdu->setNewRate(dtcp->getSndRate());
  //          unsigned int timeUnit;
  flowControlPdu->setTimeUnit(dtcp->getSendingTimeUnit());
  //          unsigned int myLeftWinEdge;
  flowControlPdu->setMyLeftWinEdge(state.getRcvLeftWinEdge());
  //          unsigned int myRightWinEdge;
  //TODO A1 Change it. Get value from dtcp flowControl rcvRightWindowEdge
  // Also make sure the rcvRightWindowEdge is properly updated whenever rcvLeftWindowEdge gets updated
  flowControlPdu->setMyRightWinEdge(dtcp->getSndRtWinEdge());
  //          unsigned int myRcvRate;
  flowControlPdu->setMyRcvRate(dtcp->getRcvRate());
}

void DTP::sendAckFlowPDU(unsigned int seqNum, bool seqNumValid)
{


  if(!seqNumValid){
    seqNum = state.getRcvLeftWinEdge() - 1;
  }

  if(state.isFCPresent() && state.isRxPresent()){
    //TODO A1 Send Ack/Flow Control PDU with LWE and RWE
    AckFlowPDU* ackFlowPdu = new AckFlowPDU();
    setPDUHeader(ackFlowPdu);
    ackFlowPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());

    //TODO A2 verify it and update handling of ackFlowPdu
    ackFlowPdu->setAckNackSeqNum(state.getRcvLeftWinEdge() - 1);

    fillFlowControlPDU(ackFlowPdu);
    sendToRMT(ackFlowPdu);
  }else if(state.isFCPresent()){
    //TODO A1 send FC

    sendFCOnlyPDU();
  }else if(state.isRxPresent()){
    sendAckOnlyPDU(seqNum);
  }


}

void DTP::handleMsgFromRmtnew(PDU* msg){

  state.setCurrentPdu(msg);

  if (dynamic_cast<DataTransferPDU*>(msg))
  {
    DataTransferPDU* pdu = (DataTransferPDU*) msg;

    /* This is here just for testing RX */
    if (pduDroppingEnabled)
    {
      if (((deletePdu++ + 1) % 5) == 0)
      {
        std::ostringstream out;
        out << "Dropping PDU number " << pdu->getSeqNum();
        bubble(out.str().c_str());
        EV << this->getFullPath() << "; " << out.str().c_str() << " in time: " << simTime() << endl;
        delete pdu;
        return;
      }
    }

    /* End */

    cancelEvent(rcvrInactivityTimer);
    handleDataTransferPDUFromRmtnew(pdu);
    schedule(rcvrInactivityTimer);


  }
  else if (dynamic_cast<ControlPDU*>(msg))
  {
    ControlPDU* pdu = (ControlPDU*) msg;
    EV << getFullPath() <<": Control PDU number: " << pdu->getSeqNum() <<" received" << endl;


    //Putting it before ControlAckPDU might be an issue
    if(!commonRcvControl(pdu)){
      //The Control PDU has been deleted because of duplicate
      return;
    }


    if(dynamic_cast<ControlAckPDU*>(pdu))
    {
      dtcp->runRcvrControlAckPolicy(&state);
    }
    else
    {

      if (pdu->getType() & PDU_SEL_BIT)
      {
        /*
         SELECT_ACK_PDU        = 0x8806;
         SELECT_NACK_PDU       = 0x8807;
         SELECT_ACK_FLOW_PDU   = 0x880E;
         SELECT_NACK_FLOW_PDU  = 0x880F;
         */

        //TODO A1 RTT estimator
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
          SelectiveAckPDU* selAckPdu = (SelectiveAckPDU*) pdu;
          unsigned int tempSLWE = 0;
          for (unsigned int i = 0; i < selAckPdu->getNackListLen(); i++)
          {
            unsigned int startSeqNum = selAckPdu->getNackList(i * 2);
            unsigned int endSeqNum = selAckPdu->getNackList((i * 2) + 1);

            tempSLWE = std::max(endSeqNum, tempSLWE);

            dtcp->ackPDU(startSeqNum, endSeqNum);

            //TODO A!
            // min = dtcp->getSmallestSeqNumFromRxQOrNextSeqNumToSend - 1
            //state.setSenderLeftWinEdge(std::min(min, state.getSenderLeftWinEdge);

            state.setSenderLeftWinEdge(tempSLWE);

          }
        }

      }
      else
      /* TODO B3 Make it prettier ;) */
      if (pdu->getType() & (PDU_ACK_BIT | PDU_NACK_BIT))
      {


        //TODO A1 Retrieve the Time of this Ack - RTT estimator policy

        if (pdu->getType() & PDU_NACK_BIT)
        {

          NackOnlyPDU *nackPdu = (NackOnlyPDU*) pdu;

          dtcp->nackPDU(nackPdu->getAckNackSeqNum());

        }
        else if (pdu->getType() & PDU_ACK_BIT)
        {
          AckOnlyPDU *ackPdu = (AckOnlyPDU*) pdu;
          EV << getFullPath() <<": PDU number: " << ackPdu->getAckNackSeqNum() <<" Acked"<<endl;

          dtcp->runSenderAckPolicy(&state);


          //TODO A! What about senderRightWindowEdge? it should be updated to 'sndLWE+sndCredit'

        }
        /* End of Ack/Nack */

      }

      if ((pdu->getType() & PDU_FC_BIT))
      {
        FlowControlOnlyPDU *flowPdu = (FlowControlOnlyPDU*) pdu;

        //Update RightWindowEdge and SendingRate.
        dtcp->setSndRtWinEdge(flowPdu->getNewRightWinEdge());
        dtcp->setSndRate(flowPdu->getNewRate());

        if (state.getClosedWinQueLen() > 0)
        {
          /* Note: The ClosedWindow flag could get set back to true immediately in trySendGenPDUs */
          state.setClosedWindow(false);
          trySendGenPDUs(state.getClosedWindowQ());

        }
      }

    }
    delete pdu;
  }else{
    EV << getFullPath() << "Unhandeled PDU!!!!!!"<<endl;
  }



  //TODO A1 not sure about this scheduling; yeah it will be deleted
//  schedule(rcvrInactivityTimer);


  state.setCurrentPdu(NULL);
}

void DTP::handleDataTransferPDUFromRmtnew(DataTransferPDU* pdu){


  EV << getFullPath() << ": PDU number: " << pdu->getSeqNum() << " received" << endl;

  if (state.isFCPresent())
  {
    dtcp->resetWindowTimer();

    if(pdu->getFlags() & ECN_FLAG){
      /* Run ECNSet Policy */
      if(dtcp->runECNSetPolicy(&state)){
        /* Default action */
        state.setEcnSet(true);
      }

      /* Run ECNClear Policy */
      if(dtcp->runECNClearPolicy(&state)){
        /* Default action */
        state.setEcnSet(false);
      }
    }

  }
  // if PDU.DRF == true
  if (pdu->getFlags() & DRF_FLAG)
  {
    bubble("Received PDU with DRF set");
    /* Case 1) DRF is set - either first PDU or new run */

    delimitFromRMT(NULL);

    //Flush the PDUReassemblyQueue
    flushReassemblyPDUQ();

//    state.setMaxSeqNumRcvd(pdu->getSeqNum());

    //Put PDU on ReassemblyQ
    addPDUToReassemblyQ(pdu);

    //XXX Setting DRF would create infinity loop of setting DRF for every PDU, right?
    /* Initialize the other direction */
//    state.setSetDrfFlag(true);
    /* If this is a new run then I should set my rcvrLeftWindowEdge to pdu->seqNum +1 */
    state.setRcvLeftWinEdge(pdu->getSeqNum());

    //XXX WHY???
//    runInitialSequenceNumberPolicy();

    if (state.isDtcpPresent())
    {
      svUpdate(pdu->getSeqNum());

    }
    delimitFromRMT(NULL);

  }
  else
  {

    /* Not the start of a run */
    if (pdu->getSeqNum() < state.getRcvLeftWinEdge())
    {
      bubble("Dropping duplicate PDU");
      EV << getFullPath() << ":Duplicated PDU number: " << pdu->getSeqNum() << " received - DROPPING!" << endl;
      /* Case 2) A Real Duplicate */
      //Discard PDU and increment counter of dropped duplicates PDU
      delete pdu;

      state.incDropDup();


      sendAckFlowPDU();

      return;
    }
//  if (state.getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() <= state.getMaxSeqNumRcvd())
    if (state.getRcvLeftWinEdge() < pdu->getSeqNum())
    {
      /* Not a true duplicate. (Might be a duplicate among the gaps) */

      bool dup = false;
      PDUQ_t::iterator it;
      PDUQ_t* pduQ =  state.getReassemblyPDUQ();
      for (it = pduQ->begin(); it != pduQ->end(); ++it)
      {
        if ((*it)->getSeqNum() == pdu->getSeqNum())
        {
          dup = true;
          break;
        }
      }
      if (dup)
      {
        /* Case 3) Duplicate Among gaps */
        EV << getFullPath() << ":Duplicated PDU number: " << pdu->getSeqNum() << " received - DROPPING!" << endl;
        //Discard PDU and increment counter of dropped duplicates PDU
        delete pdu;
        //increment counter of dropped duplicates PDU
        state.incDropDup();

        //send an Ack/Flow Control PDU with current window values
        sendAckFlowPDU();
        return;
      }
      else
      {
        /* Case 3) This goes in a gap */
        /* Put at least the User-Data of the PDU with its Sequence Number on PDUReassemblyQueue in Sequence Number order */

//      reassemblyPDUQ.push_back(pdu);
        addPDUToReassemblyQ(pdu);
        if (state.isDtcpPresent())
        {
          //svUpdate(state.getMaxSeqNumRcvd()); /* Update left edge, etc */
          svUpdate(state.getRcvLeftWinEdge() - 1); /* Update left edge, etc */
        }
        else
        {
          state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
          /* No A-Timer necessary, already running */
        }

        delimitFromRMT(NULL);
        return;
      }
    }
    /* Case 4) This is in order */
//  if (pdu->getSeqNum() == state.getMaxSeqNumRcvd() + 1)
    if (pdu->getSeqNum() == state.getRcvLeftWinEdge())
    {
//    state.incMaxSeqNumRcvd();
      //XXX This is not mentioned in the specs. IMHO this is the most important part ;)
      addPDUToReassemblyQ(pdu);

      if (state.isDtcpPresent())
      {
//      svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
        svUpdate(pdu->getSeqNum()); /* Update Left Edge, etc. */
      }
      else
      {
        //state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
        state.incRcvLeftWindowEdge();
        //TODO A! start A-Timer (for this PDU)
        //FIX: @Marek Why start A-timer when DTCP is not present?
      }
//    delimitFromRMT(pdu, pdu->getUserDataArraySize()); /* Create as many whole SDUs as possible */
      delimitFromRMT(NULL);

    }
    else
    {
      //XXX After removing the MaxSeqNumRcvd, this case no longer makes sense.
      //This assumption needs to be verified with somebody (John, Michael, Leo, Miguel, ...?)

      /* Case 5) it is out of order */
      //if (pdu->getSeqNum() > state.getMaxSeqNumRcvd() + 1)
      if (pdu->getSeqNum() > state.getRcvLeftWinEdge() + 1)
      {
        if (state.isDtcpPresent())
        {
//        svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
          svUpdate(state.getRcvLeftWinEdge()); /* Update Left Edge, etc. */
        }
        else
        {
          //LeftWindowEdge = MaxSeqNumRcvd;
          //TODO A! start A-timer
        }

        delimitFromRMT(pdu);
      }
      //TODO Find out why there is sequenceNumber -> Start RcvrInactivityTimer(PDU.SequenceNumber) /* Backstop timer */
    }
//    schedule(rcvrInactivityTimer);
    //TODO A1 DIF.integrity
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

  cancelEvent(senderInactivityTimer);
  schedule(senderInactivityTimer);
}

void DTP::handleDTPATimer(ATimer* timer)
{

  if(state.isDtcpPresent()){
//    runSendingAckPolicy(timer);
    dtcp->runSendingAckPolicy(&state, timer);
  }else{

    //TODO A1
    //Update LeftWindowEdge

    //Invoke delimiting
    delimitFromRMT(NULL);

    //reset SenderInactivity timer
    resetSenderInactivTimer();
  }
}

//void DTP::handleDTPWindowTimer(WindowTimer* timer){
//  sendAckPDU();
//}
//bool DTP::write(int portId, unsigned char* buffer, int len)
//{
//
//  cancelEvent(senderInactivityTimer);
//
//  this->delimit(buffer, len);
//  /* Now the data from buffer are copied to SDUs so we can free the memory */
//  free(buffer);
//
//  this->generatePDUs();
//
//  /* Iterate over generated PDUs and decide if we can send them */
//  this->trySendGenPDUs(&generatedPDUs);
//
////  /* iterate over postablePDUs */
////  this->sendPostablePDUsToRMT();
//
//  schedule(senderInactivityTimer);
//  return true;
//}

unsigned int DTP::delimit(SDU* sdu)
{

  //TODO B2 Does PDU header counts to MaxFlowPDUSize? edit: yes, it does!
  if (sdu->getSize() > state.getMaxFlowPduSize())
  {
    unsigned int size = state.getMaxFlowPduSize();
    //SDU is bigger than Max Allowed PDU
    //S/DUFrag *frag = new SDUFrag

    SDU* tmp;
    unsigned int i;
    for (i = 0; i * size < sdu->getSize(); i++)
    {
      tmp = sdu->genFragment(size, i, i * size);
      dataQ.push_back(tmp);

    }
    return i;
  }
  else
  {
    dataQ.push_back(sdu);
    return 1;
  }

}


unsigned int DTP::delimitFromRMT(PDU *pdu, unsigned int len)
{
  unsigned int counter = 0;

//  if()

  return counter;
}

bool DTP::setDRFInPDU(bool override)
{
  if (state.isSetDrfFlag() || override)
  {
    state.setSetDrfFlag(false);
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

  //invoke SDU protection so we don't have to bother with it afterwards; EDIT: sduQ is not used anymore!!!
  for (std::vector<SDU*>::iterator it = sduQ.begin(); it != sduQ.end(); ++it){
    sduProtection(*it);
  }

  while (!dataQ.empty())
  {
    DataTransferPDU* genPDU = baseDataPDU->dup();
    genPDU->setSeqNum(state.getNextSeqNumToSend());


    /* Set DRF flag in PDU */
    if(setDRFInPDU(false)){
      genPDU->setFlags(genPDU->getFlags() | DRF_FLAG);
    }


    UserDataField* userData = new UserDataField();

    while (!dataQ.empty() && dataQ.front()->getSize() <= MAX_PDU_SIZE - userData->getSize())
    {
      userData->addData((dataQ.front()));

      dataQ.erase(dataQ.begin());

    }

    genPDU->setUserDataField(userData);

    generatedPDUs.push_back(genPDU);

  }

  delete baseDataPDU;
}




/**
 *
 */
void DTP::trySendGenPDUs(std::vector<DataTransferPDU*>* pduQ)
{

  if (state.isDtcpPresent())
  {
    //postablePDUs = empty;

    //if flowControl present
    if (state.isWinBased() || state.isRateBased())
    {
      std::vector<DataTransferPDU*>::iterator it;
      for (it = pduQ->begin(); it != pduQ->end(); it = pduQ->begin())
      {
        if (state.isWinBased())
        {
          if ((*it)->getSeqNum() <= dtcp->getSndRtWinEdge())
          {
            /* The Window is Open. */
            runTxControlPolicy(pduQ);
            /* Watchout because the current 'it' could be freed */
          }
          else
          {
            /* The Window is Closed */
            state.setClosedWindow(true);

          if(pduQ == state.getClosedWindowQ()){
              break;
            }

            if (state.getClosedWinQueLen() < state.getMaxClosedWinQueLen() - 1)
            {
              /* Put PDU on the closedWindowQueue */
              state.getClosedWindowQ()->push_back((*it));
              generatedPDUs.erase(it);


            }
            else
            {
              state.setCurrentPdu(*it);
              generatedPDUs.erase(it);

              dtcp->runFCOverrunPolicy(&state);

            }
          }
        }// end of Window based

        if (state.isRateBased())
        {
          if (dtcp->flowControl->pdusSentInTimeUnit < dtcp->flowControl->sendingRate)
          {
            runNoRateSlowDownPolicy();
          }
          else
          {
            /* Exceeding Sending Rate */

            dtcp->runNoOverridePeakPolicy(&state);
          }
        }// end of RateBased


      }//end of for

      // It makes better sense to have it after the for
      if (state.isClosedWindow() ^  dtcp->isSendingRateFullfilled())
      {
        runReconcileFlowControlPolicy();
      }

    }else{
      std::vector<DataTransferPDU*>::iterator it;
      for (it = generatedPDUs.begin(); it != generatedPDUs.end();)
      {
        postablePDUs.push_back((*it));
        it = generatedPDUs.erase(it);
      }
    }

    /* Iterate over postablePDUs and give them to the RMT */
    if (state.isRxPresent())
    {
      std::vector<DataTransferPDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();)
      {
        /* Put a copy of each PDU in the RetransmissionQueue */
        //new rxTimerMessage
        dtcp->pushBackToRxQ((*it)->dup());

        sendToRMT((*it));

        it = postablePDUs.erase(it);
      }
    }
    else
    {
      /*No Retransmission Control is present, but FlowControl */
      /* Post all postablePDUs to RMT */
      std::vector<DataTransferPDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();)
      {
        sendToRMT((*it));
        it = postablePDUs.erase(it);
      }

    }
  }
  else
  {
    /* DTCP is not present */
    /* Post all generatedPDUs to RMT */
    std::vector<DataTransferPDU*>::iterator it;
    for (it = generatedPDUs.begin(); it != generatedPDUs.end();)
    {
      sendToRMT((*it));
      it = generatedPDUs.erase(it);
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
  //TODO A1

}


/*
 * We assume that this policy is used only under flowControl, it doesn't check presence
 * of flowControl object - it might be NULL
 */
void DTP::runTxControlPolicy(std::vector<DataTransferPDU*>* pduQ)
{
  /* Default */
  if (this->txControlPolicy == NULL)
  {
    /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
     And Set the ClosedWindow flag appropriately. */
    std::vector<DataTransferPDU*>::iterator it;
    for (it = pduQ->begin();
        it != pduQ->end() && (*it)->getSeqNum() <= dtcp->getSndRtWinEdge();)
    {
      postablePDUs.push_back((*it));
      it = pduQ->erase(it);

    }

    if (!generatedPDUs.empty())
    {
      state.setClosedWindow(true);
    }
  }
  else
  {
    //TODO A! Change to unified policy style
    txControlPolicy->run((cObject *) this);
  }

}

void DTP::runNoRateSlowDownPolicy()
{
  //TODO A1 Do I need to propagate the pduQ (gneratedPDUs vs closedWindowQ
  /* Default */
  postablePDUs.push_back(generatedPDUs.front());
  generatedPDUs.erase(generatedPDUs.begin());
  dtcp->flowControl->pdusSentInTimeUnit++;
}

void DTP::runReconcileFlowControlPolicy()
{
  /* Default (is empty) */
}

bool DTP::runInitialSequenceNumberPolicy()
{

  /*Default*/
  //TODO B1 set it to random number
  state.setNextSeqNumToSend(DEFAULT_INIT_SEQUENCE_NUMBER);
  return false;
}


void DTP::runRateReductionPolicy()
{
  /* Default */
  if (dtcp->dtcpState->getRcvBuffersPercentFree() <= dtcp->dtcpState->getRcvBufferPercentThreshold())
  {
    dtcp->flowControl->rcvrRate *= 0.9; //Reduce Rate 10%
  }
  else
  {
    if (dtcp->flowControl->rcvrRate < dtcp->flowControl->configRcvrRate
        && dtcp->dtcpState->getRcvBuffersPercentFree() > dtcp->dtcpState->getRcvBufferPercentThreshold())
    {
      //set rate back to config rate
      dtcp->flowControl->rcvrRate = dtcp->flowControl->configRcvrRate;
    }
  }
  /* End Default */
}

void DTP::sendAckOnlyPDU(unsigned int seqNum)
{
  //TODO A2 How to remove allowed gaps?
  //Update LeftWindowEdge removing allowed gaps;

  //send an Ack/FlowControlPDU
  AckOnlyPDU* ackPDU = new AckOnlyPDU();
  setPDUHeader(ackPDU);
  ackPDU->setSeqNum(dtcp->getNextSndCtrlSeqNum());
  ackPDU->setAckNackSeqNum(seqNum);
  EV << getFullPath() << ": Sending Ack for PDU number: " << seqNum << endl;
  //    send(ackPDU, southO);
  sendToRMT(ackPDU);
}

void DTP::sendControlAckPDU()
{
  Enter_Method_Silent();


  ControlAckPDU* ctrlAckPdu = new ControlAckPDU();
  setPDUHeader(ctrlAckPdu);
  ctrlAckPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());
  ctrlAckPdu->setLastCtrlSeqNumRcv(dtcp->getLastCtrlSeqNumRcv());
  ctrlAckPdu->setSndLtWinEdge(state.getRcvLeftWinEdge());
  //TODO A! Fix it to the form of getRcvRightWindowEdge
  ctrlAckPdu->setSndRtWinEdge(dtcp->getRcvRtWinEdge());
  ctrlAckPdu->setMyLtWinEdge(state.getSenderLeftWinEdge());
  ctrlAckPdu->setMyRtWinEdge(dtcp->getSndRtWinEdge());
  //TODO A1 rate?

  sendToRMT(ctrlAckPdu);
}

void DTP::sendEmptyDTPDU()
{
  //TODO RcvRates
  //TODO A! Send Transfer PDU With Zero length
  DataTransferPDU* dataPdu = new DataTransferPDU();
  setPDUHeader(dataPdu);
  unsigned int seqNum = state.getNextSeqNumToSend();
  dataPdu->setSeqNum(seqNum);

  if(setDRFInPDU(false)){
    dataPdu->setFlags(dataPdu->getFlags() | DRF_FLAG);
  }
  UserDataField* userData = new UserDataField();
  dataPdu->setUserDataField(userData);

  if(state.isRxPresent()){
//    RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
//    rxExpTimer->setPdu(dataPdu->dup());
//    rxQ.push_back(rxExpTimer);
//    schedule(rxExpTimer);
    dtcp->pushBackToRxQ(dataPdu->dup());
  }

  sendToRMT(dataPdu);
}

void DTP::runRcvrInactivityTimerPolicy()
{
  bubble("RcvrInactivityTimerPolicy()");

  //XXX Why reset my sending direction when I am not receiving anything?
  // I can still be sending load of PDUs
  /* Default */

  /*
  state.setSetDrfFlag(true);
  if (runInitialSequenceNumberPolicy())
  {
    state.setNextSeqNumToSend(DEFAULT_INIT_SEQUENCE_NUMBER); //TODO A2 It SHOULD return random value;
  }

  //Discard any PDUs on the PDUretransmissionQueue
  clearRxQ();

  //Discard any PDUs on the ClosedWindowQueue
  clearClosedWindowQ();
*/
  //XXX Ok, we can send ControlAck. It won't hurt.
  //Send Control Ack PDU
  sendControlAckPDU();
 //TODO RcvRates

  //Send Transfer PDU With Zero length
  sendEmptyDTPDU();

  //TODO A! Notify User Flow there has been no activity for awhile.

}

void DTP::runSenderInactivityTimerPolicy()
{
  bubble("SenderInactivityTimerPolicy()");
//TODO A! Move SenderInactivityTimer, DRF to DT-SV
  /* Default */
  state.setSetDrfFlag(true);
  if (runInitialSequenceNumberPolicy())
  {
    state.setNextSeqNumToSend(DEFAULT_INIT_SEQUENCE_NUMBER); //TODO A2 It SHOULD return random value;
  }

  //Discard any PDUs on the PDUretransmissionQueue
  clearRxQ();

  //Discard any PDUs on the ClosedWindowQueue
  state.clearClosedWindowQ();


  //Send Control Ack PDU
  sendControlAckPDU();

  //Send Transfer PDU With Zero length
  sendEmptyDTPDU();

  //TODO A! Notify User Flow there has been no activity for awhile.

}



void DTP::sendToRMT(PDU* pdu)
{
  Enter_Method("SendToRMT");
  take(pdu);
  if(pdu->getType() == DATA_TRANSFER_PDU){
    state.setLastSeqNumSent(pdu->getSeqNum());
    EV << getFullPath() <<": PDU number: " << pdu->getSeqNum() <<" sent in time: " << simTime() << endl;
  }else{
    //This should be controlPDU so do not have to increment LastSeqNumSent
    EV << getFullPath() <<": Control PDU number: " << pdu->getSeqNum() <<" sent in time: " << simTime() << endl;
  }

  send(pdu, southO);
}

double DTP::getRxTime()
{
  //TODO A! 2MPL + A + epsilon
  //This might be job for a policy, presumably RTT estimator policy?
  /* 2MPL == RTT
   * A == ?
   * epsilon ?
   */
  return state.getRtt() + 0.1;
}

unsigned int DTP::getAllowableGap()
{
  //TODO A! This is placeholder for calling QoSCube::getAllowableGapSize
  /*This method is used as a middle-man so when location of QoSCube changes,
   * I will have to change it only in one place.
   */

  //TODO A! find QoSCube
//  return connId.getQosCube()->getMaxAllowGap();
  this->qosCube.getMaxAllowGap();
  return 4;
}

void DTP::svUpdate(unsigned int seqNum)
{
//  state.setRcvLeftWinEdge(seqNum);
//  uint ackSeqNum = state.getRcvLeftWinEdge();
  /* XXX Don't know where else to put */
  if(state.getRcvLeftWinEdge()  == seqNum){
    state.incRcvLeftWindowEdge();

    PDUQ_t::iterator it;
    PDUQ_t* pduQ = state.getReassemblyPDUQ();
    for (it = pduQ->begin(); it != pduQ->end(); ++it)
    {
      if((*it)->getSeqNum() == state.getRcvLeftWinEdge()){
        state.incRcvLeftWindowEdge();

      }else if((*it)->getSeqNum() < state.getRcvLeftWinEdge()){
        continue;
      }else {
        break;
      }
    }

  }


  if (state.isFCPresent())
  {
    if (state.isWinBased())
    {
//      runRcvrFlowControlPolicy();

     dtcp->runRcvrFCPolicy(&state);


    }

    /* Commented due to a change in specs */ //TODO A1 Move it to its new place (see new specs)
//    if (state.isRateBased())
//    {
//      runRateReductionPolicy();
//    }
  }

  if (state.isRxPresent())
  {
//    runRcvrAckPolicy(state.getRcvLeftWinEdge() - 1);
    dtcp->runRcvrAckPolicy(&state);
  }

  if (state.isFCPresent() && !state.isRxPresent())
  {
//    runReceivingFlowControlPolicy();
    dtcp->runReceivingFCPolicy(&state);
  }

}

void DTP::flushReassemblyPDUQ()
{

  state.clearReassemblyPDUQ();

}



void DTP::clearRxQ()
{
  dtcp->clearRxQ();
}

void DTP::schedule(DTPTimers *timer, double time)
{

  switch (timer->getType())
  {

    case (DTP_SENDER_INACTIVITY_TIMER): {

      //TODO A1 Why schedule inactivity timer when there is not RxControl? -> Don't!

      //TODO A! 3(MPL+R+A)
      unsigned int rxCount = 1;
      if(state.isRxPresent()){
        rxCount = dtcp->getDataReXmitMax();


      scheduleAt(simTime() + 3 * (state.getRtt() + (state.getRtt() * rxCount)) + 0 , timer);
      }
//      scheduleAt(simTime() + 10, timer);
      break;
    }
    case (DTP_RCVR_INACTIVITY_TIMER): {

      //TODO A1 Why schedule inactivity timer when there is not RxControl? -> Don't!
      unsigned int rxCount = 1;
      if(state.isRxPresent()){
        rxCount = dtcp->getDataReXmitMax();
        //TODO A!
        scheduleAt(simTime() + 2 * (state.getRtt() + (state.getRtt() * rxCount)) + 0 , timer);
      }
      break;
    }
//    case (DTP_SENDING_RATE_TIMER): {
//
//      scheduleAt(simTime() + (dtcp->flowControl->timeUnit * 1000), timer);
//      break;
//    }
  }

}

void DTP::setFlow(Flow* flow)
{
  this->flow = flow;
}

void DTP::setDTCP(DTCP* dtcp){
  this->dtcp = dtcp;
  if(dtcp!= NULL){
    dtcp->setDTP(this);
  }
}

