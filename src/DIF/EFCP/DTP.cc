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
  // TODO Auto-generated constructor stub

}
DTP::~DTP()
{

  flushAllQueuesAndPrepareToDie();

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
  std::vector<RxExpiryTimer*>::iterator it;
    for (it = rxQ.begin(); it != rxQ.end();)
    {
      delete (*it)->getPdu();
      cancelAndDelete(*it);
  //    delete (*it);
      it = rxQ.erase(it);
    }

    std::vector<DataTransferPDU*>::iterator itP;
    for (itP = reassemblyPDUQ.begin(); itP != reassemblyPDUQ.end();)
    {
      delete (*itP);
  //    delete (*it);
      itP = reassemblyPDUQ.erase(itP);
    }

    std::vector<DataTransferPDU*>* pduQ;

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

void DTP::initialize(int step)
{

  initGates();
  state.initDefaults();

  senderInactivityTimer = new SenderInactivityTimer();
  rcvrInactivityTimer = new RcvrInactivityTimer();


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
      case(DTP_RX_EXPIRY_TIMER):{
        handleDTPRxExpiryTimer(static_cast<RxExpiryTimer*>(timer));


        break;
      }

      case(DTP_SENDING_RATE_TIMER):{
        handleDTPSendingRateTimer(static_cast<SendingRateTimer*>(timer));
        schedule(timer);
        break;
      }

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

//      case(DTP_WINDOW_TIMER):{
//        handleDTPWindowTimer(static_cast<WindowTimer*>(timer));
//
//        break;
//      }
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

//void DTP::handleMsgFromDelimiting(Data* msg)
//{
//
//  cancelEvent(senderInactivityTimer);
//
//  DataTransferPDU* pdu = new DataTransferPDU();
//  pdu->setMUserData(msg);
//  setPDUHeader(pdu);
//  pdu->setSeqNum(this->state.getNextSeqNumToSend());
//
//  send(pdu, southO);
//
//}

void DTP::handleMsgFromDelimitingnew(SDU* sdu){
  cancelEvent(senderInactivityTimer);

  delimit(sdu);

  generatePDUsnew();

  this->trySendGenPDUs(&generatedPDUs);

  schedule(senderInactivityTimer);
}

//void DTP::handleMsgFromRmt(PDU* msg)
//{
//
//  if (dynamic_cast<DataTransferPDU*>(msg))
//  {
//    DataTransferPDU* pdu = (DataTransferPDU*) msg;
//    cMessage* sdu = pdu->getMUserData();
//    take(check_and_cast<cOwnedObject*>(sdu) );
//    send(pdu->getMUserData(), northO);
//  }
//}

void DTP::delimitFromRMT(DataTransferPDU* pdu)
{
  /* Maybe it is good idea to split this method into two
   * The first one would put PDU on reassemblyQ and
   * the second one would create as many whole SDUs from reassemblyQ as possible */
  if(pdu!=NULL){
    if(reassemblyPDUQ.empty()){
      reassemblyPDUQ.push_back(pdu);
    }else{
      if(reassemblyPDUQ.front()->getSeqNum() > pdu->getSeqNum()){
        reassemblyPDUQ.insert(reassemblyPDUQ.begin(), pdu);
      }
      else
      {
        for (std::vector<DataTransferPDU*>::iterator it = reassemblyPDUQ.begin(); it != reassemblyPDUQ.end(); ++it)
        {
          if ((*it)->getSeqNum() == pdu->getSeqNum()){
            //Not sure if this case could ever happen
            state.incDropDup();
            delete pdu;
            return;
          }else if ((*it)->getSeqNum() > pdu->getSeqNum()){
            /* Put the incoming PDU before one with bigger seqNum */
            reassemblyPDUQ.insert(it, pdu);
            break;
          }else if(it == --reassemblyPDUQ.end()){
            //'it' is last element
            reassemblyPDUQ.insert(it, pdu);
            break;
          }
        }
      }
    }
  }

  for (std::vector<DataTransferPDU*>::iterator it = reassemblyPDUQ.begin(); it != reassemblyPDUQ.end(); )
  {/* DO NOT FORGET TO PUT '++it' in all cases where we DO NOT erase PDUs from queue */

    //TODO B1 add support for out of order SDU delivery
    // neg implication
    uint seqNum = (*it)->getSeqNum();
    if((qosCube.isForceOrder() && ! (seqNum < state.getRcvLeftWinEdge()))){
      return;
    }


    unsigned int delimitFlags = (*it)->getUserDataField()->getSduDelimitFlags();
    if((delimitFlags & SDU_NO_LENGTH) == SDU_NO_LENGTH){
//      if(delimitFlags & SDU_)
      EV << getFullPath() << ": unhandled condition in delimiting !!!!!!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
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

        it = reassemblyPDUQ.erase(it);
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
    //TODO A! Send Control Ack and empty TransferPDU
    sendControlAckPDU();
    sendEmptyDTPDU();
    dtcp->setLastCtrlSeqnumRec(pdu->getSeqNum());
  }
  else
  {
    dtcp->setLastCtrlSeqnumRec(pdu->getSeqNum());
  }

  return true;
}

void DTP::sendAckFlowPDU()
{
  //      unsigned int myRcvRate;
  //TODO handle RcvRate
  //TODO A1 Send Ack/Flow Control PDU with LWE and RWE
  AckFlowPDU* ackFlowPdu = new AckFlowPDU();
  setPDUHeader(ackFlowPdu);
  ackFlowPdu->setSeqNum(dtcp->getNextSndCtrlSeqNum());
  //      unsigned int newRightWinEdge;
  /****************************************/
  //TODO A! is this the correct variable??
  /****************************************/
  ackFlowPdu->setNewRightWinEdge(dtcp->getSndRtWinEdge());
  //        unsigned int newRate;
  ackFlowPdu->setNewRate(dtcp->getSndRate());
  //          unsigned int timeUnit;
  ackFlowPdu->setTimeUnit(dtcp->getSendingTimeUnit());
  //          unsigned int myLeftWinEdge;
  ackFlowPdu->setMyLeftWinEdge(state.getRcvLeftWinEdge());
  //          unsigned int myRightWinEdge;
  //TODO A1 Change it. Get value from dtcp flowControl rcvRightWindowEdge
  // Also make sure the rcvRightWindowEdge is properly updated whenever rcvLeftWindowEdge gets updated
  ackFlowPdu->setMyRightWinEdge(state.getRcvLeftWinEdge() + dtcp->getRcvCredit());
  //          unsigned int myRcvRate;
  ackFlowPdu->setMyRcvRate(dtcp->getRcvRate());

  sendToRMT(ackFlowPdu);
}

void DTP::handleMsgFromRmtnew(PDU* msg){

  if (dynamic_cast<DataTransferPDU*>(msg))
  {
    DataTransferPDU* pdu = (DataTransferPDU*) msg;
    handleDataTransferPDUFromRmtnew(pdu);


  }
  else if (dynamic_cast<ControlPDU*>(msg))
  {
    ControlPDU* pdu = (ControlPDU*) msg;
    EV << getFullPath() <<": Control PDU number: " << pdu->getSeqNum() <<" received" << endl;

    // TODO A! Ask if commonRcvControl should be run on ControlAckPDU
    // TODO A! commonRcvControl will probably be first step in handling of all controlPDUs
    //Putting it before ControlAckPDU might be an issue
    if(!commonRcvControl(pdu)){
      //The Control PDU has been deleted because of Duplicate
      return;
    }


    if(dynamic_cast<ControlAckPDU*>(pdu))
    {

      /* RcvrControlAck Policy with Default: */
      //"adjust as necessary" :D great advice
      ControlAckPDU* ctrlAckPDU = (ControlAckPDU*)pdu;
//      TODO: unsigned int lastCtrlSeqNumRcv;

//      unsigned int sndLtWinEdge;
//      if(state.getNextSeqNumToSend() < ctrlAckPDU->getSndLtWinEdge()){
      state.setNextSeqNumToSend(ctrlAckPDU->getSndLtWinEdge());
//      }
//      unsigned int sndRtWinEdge;

      dtcp->setSndRtWinEdge(ctrlAckPDU->getSndRtWinEdge());
//      unsigned int myLtWinEdge;
//      if(state.getRcvLeftWinEdge() < ctrlAckPDU->getMyLtWinEdge()){
      state.setRcvLeftWinEdge(ctrlAckPDU->getMyLtWinEdge());
//      }
//      unsigned int myRtWinEdge;
      //TODO verify this
      dtcp->setRcvRtWinEdge(ctrlAckPDU->getMyRtWinEdge());
//      unsigned int myRcvRate;
      //TODO handle RcvRate

      //TODO A1 Send Ack/Flow Control PDU with LWE and RWE

      sendAckFlowPDU();
      //TODO A1 Send empty Transfer PDU with NextSeqNumToSend-1

      DataTransferPDU* dataPdu = new DataTransferPDU();
      setPDUHeader(dataPdu);
      uint seqNum = state.getNextSeqNumToSend();
      dataPdu->setSeqNum(seqNum - 1);
      state.setNextSeqNumToSend(seqNum);
      UserDataField* userData = new UserDataField();
      dataPdu->setUserDataField(userData);

      sendToRMT(dataPdu);

      //dataPdu->setSeqNum(state.getLastSeqNumSent());

      /* End default RcvrControlAck policy */
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

          for (uint i = 0; i < selNackPdu->getNackListLen(); i++)
          {
            uint startSeqNum = selNackPdu->getNackList(i * 2);
            uint endSeqNum = selNackPdu->getNackList((i * 2) + 1);
            std::vector<RxExpiryTimer*>::iterator it;
            for (it = rxQ.begin(); it != rxQ.end(); ++it)
            {
              //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
              if (((*it)->getPdu())->getSeqNum() >= startSeqNum && ((*it)->getPdu())->getSeqNum() <= endSeqNum)
              {
                handleDTPRxExpiryTimer((*it));
              }
            }
          }
        }
        else if (pdu->getType() & PDU_ACK_BIT)
        {
          SelectiveAckPDU* selAckPdu = (SelectiveAckPDU*) pdu;

          for (unsigned int i = 0; i < selAckPdu->getNackListLen(); i++)
          {
            uint startSeqNum = selAckPdu->getNackList(i * 2);
            uint endSeqNum = selAckPdu->getNackList((i * 2) + 1);

            std::vector<RxExpiryTimer*>::iterator it;
            for (it = rxQ.begin(); it != rxQ.end();)
            {
              //FIXME B1 "including any gaps less than allowable Gap and"
              if (((*it)->getPdu())->getSeqNum() >= startSeqNum && ((*it)->getPdu())->getSeqNum() <= endSeqNum)
              {
                /* This condition relies on sorted rxQ by seqNum */
                if (state.getSenderLeftWinEdge() == (*it)->getPdu()->getSeqNum())
                {
                  state.setSenderLeftWinEdge((*it)->getPdu()->getSeqNum() + 1);
                }

                delete (*it)->getPdu();
                cancelEvent((*it));
                delete (*it);
                it = rxQ.erase(it);
              }else{
                ++it;
              }
            }
            //SenderLWE is updated inside for loop
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

          std::vector<RxExpiryTimer*>::iterator it;
          for (it = rxQ.begin(); it != rxQ.end(); ++it)
          {
            //TODO A2 This is weird. Why value from MAX(Ack/Nack, NextAck -1) What does NextAck-1 got to do with it?
            if (((*it)->getPdu())->getSeqNum() > nackPdu->getAckNackSeqNum())
            {
              handleDTPRxExpiryTimer((*it));
            }
          }

        }
        else if (pdu->getType() & PDU_ACK_BIT)
        {
          AckOnlyPDU *ackPdu = (AckOnlyPDU*) pdu;
          EV << getFullPath() <<": PDU number: " << ackPdu->getAckNackSeqNum() <<" Acked"<<endl;
          /* Policy SenderAck with default: */
          std::vector<RxExpiryTimer*>::iterator it;
          for (it = rxQ.begin(); it != rxQ.end();)
          {
            //FIXME B1 "including any gaps less than allowable Gap and"
            if (((*it)->getPdu())->getSeqNum() <= ackPdu->getAckNackSeqNum())
            {
              EV << getFullPath() <<": PDU number: " << (*it)->getPdu()->getSeqNum() <<" deleted from RX_Q" << endl;
              delete (*it)->getPdu();
              cancelEvent((*it));
              delete (*it);
              it = rxQ.erase(it);

            }else{
              ++it;
            }
          }
          //Update LeftWindowEdge accordingly
          //TODO A1 set it to lowest seqNum on RX queue
          if(!rxQ.empty()){
            state.setSenderLeftWinEdge(rxQ.front()->getPdu()->getSeqNum());
          }else{
            state.setSenderLeftWinEdge(ackPdu->getAckNackSeqNum() + 1);
          }
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
          trySendGenPDUs(&closedWindowQ);
        }
      }

    }
    delete pdu;
  }else{
    EV << getFullPath() << "Unhandeled PDU!!!!!!"<<endl;
  }



  //TODO A1 not sure about this scheduling; yeah it will be deleted
//  schedule(rcvrInactivityTimer);
}

void DTP::handleDataTransferPDUFromRmtnew(DataTransferPDU* pdu){

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

  if(pdu->getSeqNum() == 0){
    int i = 5;
  }

  EV << getFullPath() <<": PDU number: " << pdu->getSeqNum() <<" received" << endl;
  //Canceling  rcvrInactivityTimer should stay here. In the specs the canceling is only for DataTransferPDUs
  cancelEvent(rcvrInactivityTimer);
  if (state.isFCPresent())
  {
    dtcp->resetWindowTimer();

  }
  // if PDU.DRF == true
  if (pdu->getFlags() & ECN_FLAG)
  {
    /* Case 1) DRF is set - either first PDU or new run */
    //TODO A! Invoke delimiting delimitFromRMT()

    delimitFromRMT(NULL);

    //Flush the PDUReassemblyQueue
    flushReassemblyPDUQ();

//    state.setMaxSeqNumRcvd(pdu->getSeqNum());
    /* Initialize the other direction */
    state.setSetDrfFlag(true);

    /* If this is a new run then I should set my rcvrLeftWindowEdge to pdu->seqNum +1 */
    state.setRcvLeftWinEdge(pdu->getSeqNum());

    runInitialSequenceNumberPolicy();

    if (state.isDtcpPresent())
    {
      /* Update RxControl */
      //TODO A3 Mark this change in specifications.
      //Clearing RxQ
      clearRxQ();
      svUpdate(pdu->getSeqNum());

    }
    delimitFromRMT(pdu);

  }
  else
  {



  /* Not the start of a run */
  if (pdu->getSeqNum() < state.getRcvLeftWinEdge())
  {
    EV << getFullPath() <<":Duplicated PDU number: " << pdu->getSeqNum() <<" received - DROPPING!" << endl;
    /* Case 2) A Real Duplicate */
    //Discard PDU and increment counter of dropped duplicates PDU
    delete pdu;
    //TODO A1 increment counter of dropped duplicates PDU
    state.incDropDup();

    //TODO A! send an Ack/Flow Control PDU with current window values
    sendAckFlowPDU();

    return;
  }
//  if (state.getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() <= state.getMaxSeqNumRcvd())
  if (state.getRcvLeftWinEdge() < pdu->getSeqNum())
  {
    /* Not a true duplicate. (Might be a duplicate amongst the gaps) */
    //TODO A!
    //if a duplicate among the gaps then // search reassemblyQ?
    bool dup = false;
    std::vector<RxExpiryTimer*>::iterator it;
    for (it = rxQ.begin(); it != rxQ.end(); ++it)
    {
     if((*it)->getPdu()->getSeqNum() == pdu->getSeqNum()){
       dup = true;
       break;
     }
    }
    if (dup)
    {
      /* Case 3) Duplicate Among gaps */
      EV << getFullPath() <<":Duplicated PDU number: " << pdu->getSeqNum() <<" received - DROPPING!" << endl;
      //Discard PDU and increment counter of dropped duplicates PDU
      delete pdu;
      //TODO A1 increment counter of dropped duplicates PDU
      state.incDropDup();

      //TODO A! send an Ack/Flow Control PDU with current window values
      sendAckFlowPDU();
      return;
    }
    else
    {
      /* Case 3) This goes in a gap */
      /* Put at least the User-Data of the PDU with its Sequence Number on PDUReassemblyQueue in Sequence Number order */
      //TODO it is already happening in delimitFromRMT right?
//      reassemblyPDUQ.push_back(pdu);
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
      //TODO A1
//      delimitFromRMT(pdu, pdu->getUserDataArraySize());
      delimitFromRMT(pdu);
      return;
    }
  }
  /* Case 4) This is in order */
//  if (pdu->getSeqNum() == state.getMaxSeqNumRcvd() + 1)
  if (pdu->getSeqNum() == state.getRcvLeftWinEdge())
  {
//    state.incMaxSeqNumRcvd();

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
    delimitFromRMT(pdu);

  }
  else{

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
      //TODO A1
//      delimitFromRMT(pdu, pdu->getUserDataArraySize());
      delimitFromRMT(pdu);
    }
    schedule(rcvrInactivityTimer); //TODO Find out why there is sequenceNumber -> Start RcvrInactivityTimer(PDU.SequenceNumber) /* Backstop timer */
  }


  //TODO A1 DIF.integrity
  /* If we are encrypting, we can't let PDU sequence numbers roll over */

  //If DIF.Integrity and PDU.SeqNum > SequenceNumberRollOverThreshhold Then
  ///* Security requires a new flow */
  //RequestFAICreateNewConnection( PDU.FlowID )
  //Fi
  }
}

//void DTP::handleSDUs(CDAPMessage* cdap)
//{
//
//  cancelEvent(senderInactivityTimer);
//
////    this->delimit(buffer, len);
////  delimit(cdap);
//
//  /* Now tae data from buffer are copied to SDUs so we can free the memory */
////    free(buffer);
//  this->generatePDUs();
//
//  /* Iterate over generated PDUs and decide if we can send them */
//  this->trySendGenPDUs(&generatedPDUs);
//
//  //  /* iterate over postablePDUs */
//  //  this->sendPostablePDUsToRMT();
//
//  schedule(senderInactivityTimer);
//
//}
/**
 *
 * @param timer
 */
void DTP::handleDTPRxExpiryTimer(RxExpiryTimer* timer)
{
  /* Canceling event is not needed for usual timer expiration but for direct calling this method */
  cancelEvent(timer);
  runRxTimerExpiryPolicy(timer);

}

void DTP::handleDTPSendingRateTimer(SendingRateTimer* timer)
{
  //TODO A! Every time SendingRate is reseted/updated this timer is reseted (or at least SHOULD be!)
  dtcp->flowControl->pdusSentInTimeUnit = 0;
  state.setRateFullfilled(false);

}

void DTP::handleDTPRcvrInactivityTimer(RcvrInactivityTimer* timer)
{

  runRcvrInactivityTimerPolicy();

}

void DTP::handleDTPSenderInactivityTimer(SenderInactivityTimer* timer)
{
  runSenderInactivityTimerPolicy();

}

void DTP::handleDTPATimer(ATimer* timer)
{

  if(state.isDtcpPresent()){
    runSendingAckPolicy(timer);
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
    for (unsigned int i = 0; i * size < sdu->getSize(); i++)
    {
      tmp = sdu->genFragment(size, i, i * size);
      dataQ.push_back(tmp);
      return i;
    }
  }
  else
  {
    dataQ.push_back(sdu);
    return 1;
  }

  //old
//  unsigned int offset = 0, size = 0, counter = 0;
//
//  if (size + sdu->getSize() < state.getMaxFlowSduSize())
//  {
////    SDU *sdu = new SDU();
//    sdu->addUserData(sdu);
//
//    sduQ.push_back(sdu);
//
//    counter++;
//  }
//  else
//  {
//    do
//    {
//
//      counter++;
//    } while (size < sdu->getSize());
//  }
//
//  return counter;

  //discard rest of this method
//    do
//    {
////        if()
//
//    } while (offset < len);
}

/**
 * Delimits @param len bytes of buffer into User-data parts and put them on generated PDU
 * @param buffer pointer to incoming data buffer
 * @param len size of incoming data
 * @return number of created SDUs
 */
unsigned int DTP::delimit(unsigned char *buffer, unsigned int len)
{

  unsigned int offset = 0, size = 0, counter = 0;

  do
  {
    if (len - offset > state.getMaxFlowSduSize())
    {
      size = state.getMaxFlowSduSize();
    }
    else
    {
      size = len;
    }
    SDU *sdu = new SDU();
    sdu->setUserData(&buffer[offset], size);

    sduQ.push_back(sdu);

    offset += size;
    counter++;

  } while (offset < len);

  //TODO A1 If len is zero then create empty SDU?
//  if(len == 0){
//    SDU sdu;
//    sduQ.push(sdu);
//    counter = 1;
//  }
  return counter;
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

///**
// * This method takes all SDUs from sduQ and generates PDUs by filling appropriate header fields
// */
//void DTP::generatePDUs()
//{
//
//  DataTransferPDU* dataPDU = new DataTransferPDU();
//
//  dataPDU->setConnId((const ConnectionId) (*connId.dup()));
//  //setDestAddr... APN
//  //setSrcAddr ... APN
//
//  //invoke SDU protection so we don't have to bother with it afterwards
//  for (std::vector<SDU*>::iterator it = sduQ.begin(); it != sduQ.end(); ++it)
//  {
//    sduProtection(*it);
//  }
//
//  SDU *sdu = NULL;
//  DataTransferPDU* genPDU = dataPDU->dup();
//  bool fragment = false;
//  int delimitFlags = 0;
//  do
//  {
//    //This method fetches next SDU if current one has been put to some PDU(s) (offset = size)
//    this->getSDUFromQ(sdu);
//
//    unsigned int copySize = 0;
//    /* TODO We should take into account also SDUDelimiterFlags etc */
//    unsigned int pduAvailSize = state.getMaxFlowPduSize() - genPDU->getPduLen();
//    /* if the rest of the SDU is bigger than empty space in PDU then fill-up PDU */
//    copySize = (sdu->getRestSize() >= pduAvailSize) ? pduAvailSize : sdu->getRestSize();
//
//    if (genPDU->getPduLen() == PDU_HEADER_LEN)
//    {
//      //PDU is empty
//      //set noLength flag
//      delimitFlags |= 0x04;
//      if (sdu->getRestSize() > pduAvailSize)
//      {
//        //(rest of) SDU is bigger than PDU
//        //set noLength flag
//        delimitFlags |= 0x04;
//        if (sdu->getSize() > sdu->getRestSize())
//        {
//          //not first segment, something has been read from SDU
//          //and since it won't fit cannot be last
//          //this is middle segment
//          delimitFlags |= 0x00;
//        }
//        else
//        {
//          //this is first segment of next SDU
//          delimitFlags |= 0x01;
//        }
//      }
//      else
//      {
//        //(rest of) SDU is smaller than available space in PDU
//        if (sdu->getSize() > sdu->getRestSize())
//        {
//          //last fragment of previous SDU
//          delimitFlags |= 0x02;
//        }
//        else
//        {
//          //this is complete SDU
//          delimitFlags |= 0x03;
//        }
//      }
//
//    }
//    else
//    {
//      //clear noLength flag
//      delimitFlags &= 0xFB;
//
//      if (sdu->getRestSize() > pduAvailSize)
//      {
//        //(rest of) SDU won't fit into rest of PDU
//        if (sdu->getSize() > sdu->getRestSize())
//        {
//          //this is not first segment
//          if (copySize == sdu->getRestSize())
//          {
//            //this is last segment
//            delimitFlags |= 0x02;
//          }
//          else
//          {
//            //this is middle segment
//            //not permitted
//            throw cRuntimeError("This type of PDU delimiting is not permitted!");
//          }
//        }
//        else
//        {
//          //adding first segment
//          delimitFlags |= 0x01;
//        }
//      }
//      else
//      {
//        //(rest of) SDU will fit into rest of PDU
//        //complete sdu
//        if ((delimitFlags & 0x03) == 3)
//        {
//          //since i'm adding complete SDU, this flag is possible only when adding complete SDU to one (or more)complete SDU
//          delimitFlags &= 0xFC;
//        }
//      }
//    }
//
//    //add whole SDU or fragment to PDU
//    genPDU->addUserData(sdu->getUserData(copySize), copySize, &fragment);
////    fragment = true;
//
//    if (sdu->getRestSize() == 0)
//    {
//      delete sduQ.front();
//      sduQ.erase(sduQ.begin());
//    }
//
//    //if genPDU is full or SDU queue is empty, 'close' PDU and put it to generated PDUs and create new PDU
//    if (genPDU->getPduLen() >= this->state.getMaxFlowPduSize() || sduQ.empty())
//    {
//      //TODO A2 what else to do before sending?
//      //what about formating SDUDelimitersFlags in userData?
//      genPDU->putDelimitFlags(delimitFlags, fragment);
//
//      //put genPDU to generatedPDUs
//      generatedPDUs.push_back(genPDU);
//
//      if (!sduQ.empty())
//      {
//        genPDU = dataPDU->dup();
//        fragment = false;
//        //set DRF(false) -> not needed (false is default)
//        genPDU->setSeqNum(this->state.getNextSeqNumToSend());
//      }
//    }
//
//  } while (!sduQ.empty());
//}

void DTP::generatePDUsnew()
{
  std::ostringstream name;
  name << "DataTransferPDU in time " << simTime()*1;

  DataTransferPDU* baseDataPDU = new DataTransferPDU(name.str().c_str());
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
      genPDU->setFlags(genPDU->getFlags() | ECN_FLAG);
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

            if(pduQ == &closedWindowQ){
              break;
            }

            if (state.getClosedWinQueLen() < state.getMaxClosedWinQueLen() - 1)
            {
              /* Put PDU on the closedWindowQueue */
              closedWindowQ.push_back((*it));
              generatedPDUs.erase(it);
            }
            else
            {
              runFlowControlOverrunPolicy();
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
            runNoOverrideDefaultPeakPolicy();
          }
        }// end of RateBased


      }//end of for

      // It makes better sense to have it after the for
      if (state.isClosedWindow() ^ state.isRateFullfilled())
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
        RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
        rxExpTimer->setPdu((*it)->dup());

        rxQ.push_back(rxExpTimer);

        schedule(rxExpTimer);


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









//void DTP::fromRMT(DataTransferPDU* pdu)
//{
//
//  if (state.isFCPresent())
//  {
//    dtcp->resetWindowTimer();
//
//  }
//  // if PDU.DRF == true
//  if ((pdu->getFlags() & 0x80) == 0x80)
//  {
//    /* Case 1) DRF is set - either first PDU or new run */
//    //TODO A! Invoke delimiting delimitFromRMT()
//    delimitFromRMT(pdu, pdu->getUserDataArraySize());
//
//    //Flush the PDUReassemblyQueue
//    flushReassemblyPDUQ();
//
//    state.setMaxSeqNumRcvd(pdu->getSeqNum());
//    /* Initialize the other direction */
//    state.setSetDrfFlag(true);
//
//
//    runInitialSequenceNumberPolicy();
//
//    if (state.isDtcpPresent())
//    {
//      /* Update RxControl */
//      svUpdate(pdu->getSeqNum());
//    }
//
//  }
//  else
//
//  /* Not the start of a run */
//  if (pdu->getSeqNum() < state.getRcvLeftWinEdge())
//  {
//    /* Case 2) A Real Duplicate */
//    //Discard PDU and increment counter of dropped duplicates PDU
//    delete pdu;
//    //TODO A1 increment counter of dropped duplicates PDU
//    state.incDropDup();
//
//    //TODO A! send an Ack/Flow Control PDU with current window values
//
//    return;
//  }
//
//  if (state.getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() <= state.getMaxSeqNumRcvd())
//  {
//    /* Not a true duplicate. (Might be a duplicate amongst the gaps) */
//    //TODO A!
//    //if a duplicate among the gaps then // search reassemblyQ?
//    if (false)
//    {
//      /* Case 3) Duplicate Among gaps */
//
//      //Discard PDU and increment counter of dropped duplicates PDU
//      delete pdu;
//      //TODO A1 increment counter of dropped duplicates PDU
//      state.incDropDup();
//
//      //TODO A! send an Ack/Flow Control PDU with current window values
//      return;
//    }
//    else
//    {
//      /* Case 3) This goes in a gap */
//      /* Put at least the User-Data of the PDU with its Sequence Number on PDUReassemblyQueue in Sequence Number order */
//      reassemblyPDUQ.push_back(pdu);
//      if (state.isDtcpPresent())
//      {
//        svUpdate(state.getMaxSeqNumRcvd()); /* Update left edge, etc */
//      }
//      else
//      {
//        state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
//        /* No A-Timer necessary, already running */
//      }
//      //TODO A1
//      delimitFromRMT(pdu, pdu->getUserDataArraySize());
//      return;
//    }
//  }
//  /* Case 4) */
//  if (pdu->getSeqNum() == state.getMaxSeqNumRcvd() + 1)
//  {
//    state.incMaxSeqNumRcvd();
//    if (state.isDtcpPresent())
//    {
//      svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
//    }
//    else
//    {
//      state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
//      //TODO A! start A-Timer (for this PDU)
//    }
//    delimitFromRMT(pdu, pdu->getUserDataArraySize()); /* Create as many whole SDUs as possible */
//
//  }
//  else{
//
//    /* Case 5) it is out of order */
//    if (pdu->getSeqNum() > state.getMaxSeqNumRcvd() + 1)
//    {
//      if (state.isDtcpPresent())
//      {
//        svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
//      }
//      else
//      {
//        //LeftWindowEdge = MaxSeqNumRcvd;
//        //TODO A! start A-timer
//      }
//      delimitFromRMT(pdu, pdu->getUserDataArraySize());
//    }
//    schedule(rcvrInactivityTimer); //TODO Find out why there is sequenceNumber -> Start RcvrInactivityTimer(PDU.SequenceNumber) /* Backstop timer */
//  }
//  //TODO A1 DIF.integrity
//  /* If we are encrypting, we can't let PDU sequence numbers roll over */
//
//  //If DIF.Integrity and PDU.SeqNum > SequenceNumberRollOverThreshhold Then
//  ///* Security requires a new flow */
//  //RequestFAICreateNewConnection( PDU.FlowID )
//  //Fi
//
//}

///*
// * Iterate over postablePDUs and give them to RMT
// */
//void DTP::sendPostablePDUsToRMT(){
//
//  if(state.isRxPresent()){
//    std::vector<PDU*>::iterator it;
//      for (it = postablePDUs.begin(); it != postablePDUs.end(); it = postablePDUs.begin()){
//        /* Put a copy of each PDU in the RetransmissionQueue */
//        //TODO A1 start retransmission timer
//      }
//
//  }else if(state.isFCPresent()){
//    std::vector<PDU*>::iterator it;
//    /* Post all postable PDU */
//    for (it = postablePDUs.begin(); it != postablePDUs.end(); it = postablePDUs.begin()){
//
//    }
//  }
//}


//void DTP::sendPDUToRMT(PDU* pdu){
//
//  send(pdu, southO);
//}

/**
 * This method calls specified function to perform SDU protection.
 * SDU size will probably change because of the added CRC or whatnot.
 * @param sdu is the SDU being protected eg added CRC or otherwise
 */
void DTP::sduProtection(SDU *sdu)
{
  //TODO A1

}
/**
 * This method
 * @para
 */

void DTP::getSDUFromQ(SDU *sdu)
{
  if (sdu == NULL)
  {
    sdu = sduQ.front();
    return;
  }
  else
  {
    if (sdu->getRestSize() > 0)
    {
      return;
    }
    else
    {
      sdu = sduQ.front();
    }
  }
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
        it != pduQ->end() || (*it)->getSeqNum() <= dtcp->getSndRtWinEdge();)
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

void DTP::runFlowControlOverrunPolicy()
{
  /* Default */
  closedWindowQ.push_back(generatedPDUs.front());
  generatedPDUs.erase(generatedPDUs.begin());

  //TODO A1 How to block further Write API calls on this port-id
}

void DTP::runNoRateSlowDownPolicy()
{
  //TODO A1 Do I need to propagate the pduQ (gneratedPDUs vs closedWindowQ
  /* Default */
  postablePDUs.push_back(generatedPDUs.front());
  generatedPDUs.erase(generatedPDUs.begin());
  dtcp->flowControl->pdusSentInTimeUnit++;
}

void DTP::runNoOverrideDefaultPeakPolicy()
{
  /*Default */
  state.setRateFullfilled(true);
  if (state.getClosedWinQueLen() < state.getMaxClosedWinQueLen() - 1)
  {
    closedWindowQ.push_back(generatedPDUs.front());
    generatedPDUs.erase(generatedPDUs.begin());
  }
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

void DTP::runRcvrFlowControlPolicy()
{
  /* This policy has to be the one to impose the condition to set WindowClosed to True */
  /* Default */
  if (dtcp->flowControl->rcvBuffersPercentFree > dtcp->flowControl->rcvBufferPercentThreshold)
  {
    dtcp->flowControl->rcvRightWindowEdge++;
  }
  else
  {
    /* Buffers are getting low */
    //Leave RightWindowEdge unchanged.
  }
  /* End default */
}

void DTP::runRateReductionPolicy()
{
  /* Default */
  if (dtcp->flowControl->rcvBuffersPercentFree <= dtcp->flowControl->rcvBufferPercentThreshold)
  {
    dtcp->flowControl->rcvrRate *= 0.9; //Reduce Rate 10%
  }
  else
  {
    if (dtcp->flowControl->rcvrRate < dtcp->flowControl->configRcvrRate
        && dtcp->flowControl->rcvBuffersPercentFree > dtcp->flowControl->rcvBufferPercentThreshold)
    {
      //set rate back to config rate
      dtcp->flowControl->rcvrRate = dtcp->flowControl->configRcvrRate;
    }
  }
  /* End Default */
}

/* TODO A! either add argument to this policy (PDU* pdu) or variable currentPDU to DTP class */
void DTP::runRcvrAckPolicy(unsigned int seqNum)
{

  /* Default */
  if (dtcp->dtcpState->isImmediate())
  {
    //TODO A2 How to remove allowed gaps?
    //Update LeftWindowEdge removing allowed gaps;



    //send an Ack/FlowControlPDU
    AckOnlyPDU* ackPDU = new AckOnlyPDU();
    setPDUHeader(ackPDU);
    ackPDU->setSeqNum(dtcp->getNextSndCtrlSeqNum());
    ackPDU->setAckNackSeqNum(seqNum);
    EV << getFullPath() <<": Sending Ack for PDU number: " << seqNum << endl;

//    send(ackPDU, southO);
    sendToRMT(ackPDU);

    //TODO A1 Add handling for A-timer != 0
    //stop any A-Timers asscociated with this PDU and earlier ones.

  }
  else
  {
    //set A-timer for this PDU
  }
}

void DTP::runReceivingFlowControlPolicy()
{
  if (state.isWinBased())
  {
    //TODO A!
    //Send FlowControl PDU /* Already updated the window and not sending Ack */
  }
}

void DTP::runRxTimerExpiryPolicy(RxExpiryTimer* timer)
{

  DataTransferPDU* pdu = timer->getPdu();

  if (timer->getExpiryCount() == dtcp->rxControl->dataReXmitMax + 1)
  {
    //TODO A! Indicate an error "Unable to maintain the QoS for this connection"
    std::vector<RxExpiryTimer*>::iterator it;
    for (it = rxQ.begin(); it != rxQ.end();)
    {
      if (timer == *it)
      {
        delete (*it)->getPdu();
        cancelEvent((*it));
        delete (*it);
        rxQ.erase(it);
        return;
      }
    }
  }
  else
  {

    DataTransferPDU* dup = pdu->dup();
    dup->setDisplayString("b=15,15,oval,#0099FF,#0099FF,0");
    std::ostringstream out;
    out  << "Sending PDU number " << pdu->getSeqNum() << " from RX Queue";

    bubble(out.str().c_str());
    EV << this->getFullPath() << ": " << out.str().c_str() << " in time " << simTime() << endl;
    sendToRMT(dup);

    timer->setExpiryCount(timer->getExpiryCount() + 1);
  }
  schedule(timer);

}

void DTP::sendControlAckPDU()
{
  //TODO A!
  return;

  //TODO A! Send Control Ack PDU
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
  uint seqNum = state.getNextSeqNumToSend();
  dataPdu->setSeqNum(seqNum);

  if(setDRFInPDU(false)){
    dataPdu->setFlags(dataPdu->getFlags() | ECN_FLAG);
  }
  UserDataField* userData = new UserDataField();
  dataPdu->setUserDataField(userData);

  RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
  rxExpTimer->setPdu(dataPdu->dup());
  rxQ.push_back(rxExpTimer);
  schedule(rxExpTimer);

  sendToRMT(dataPdu);
}

void DTP::runRcvrInactivityTimerPolicy()
{

  /* Default */
  state.setSetDrfFlag(true);
  if (runInitialSequenceNumberPolicy())
  {
    state.setNextSeqNumToSend(DEFAULT_INIT_SEQUENCE_NUMBER); //TODO A2 It SHOULD return random value;
  }

  //Discard any PDUs on the PDUretransmissionQueue
  clearRxQ();

  //Discard any PDUs on the ClosedWindowQueue
  clearClosedWindowQ();

  //TODO A! Send Control Ack PDU
  sendControlAckPDU();
 //TODO RcvRates

  //TODO A! Send Transfer PDU With Zero length
  sendEmptyDTPDU();

  //TODO A! Notify User Flow there has been no activity for awhile.

}

void DTP::runSenderInactivityTimerPolicy()
{
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
  clearClosedWindowQ();

  //TODO A! Send Control Ack PDU
  sendControlAckPDU();

  //TODO A! Send Transfer PDU With Zero length
  sendEmptyDTPDU();

  //TODO A! Notify User Flow there has been no activity for awhile.

}

bool DTP::runSendingAckPolicy(ATimer* timer)
{
  /* Default */
  //TODO A!
  unsigned int gap = getAllowableGap();
  unsigned int seqNum = timer->getPdu()->getSeqNum();
  unsigned int leftWindowEdge = state.getRcvLeftWinEdge();


//  if (leftWindowEdge + 1 == leftWindowEdge < seqNum && leftWindowEdge + gap > seqNum)
//  {
//    //this PDU is
//
//  }

  //Update LeftWindowEdge

  return false;
}

void DTP::sendToRMT(PDU* pdu)
{

//  rmt->fromDTPToRMT(new APNamingInfo(), connId.getQoSId(), pdu);
  if(pdu->getType() == DATA_TRANSFER_PDU){
    state.setLastSeqNumSent(pdu->getSeqNum());
    EV << getFullPath() <<": PDU number: " << pdu->getSeqNum() <<" sent in time: " << simTime() << endl;
    if(pdu->getSeqNum() == 20){
      int i = 4;
    }
  }else{
    //This should be controlPDU so do not have to increment LastSeqNumSent
    EV << getFullPath() <<": Control PDU number: " << pdu->getSeqNum() <<" sent in time: " << simTime() << endl;
  }

  send(pdu,southO);

}

double DTP::getRxTime()
{
  //TODO A! 2MPL + A + epsilon
  //This might be job for a policy, presumably RTT estimator policy?
  /* 2MPL == RTT
   * A == ?
   * epsilon ?
   */
  return state.getRtt() - 3.5;
}

unsigned int DTP::getAllowableGap()
{
  //TODO A! This is placeholder for calling QoSCube::getAllowableGapSize
  /*This method is used as a middle-man so when location of QoSCube changes,
   * I will have to change it only in one place.
   */

  //TODO A! find QoSCube
//  return connId.getQosCube()->getMaxAllowGap();
  return 4;
}

void DTP::svUpdate(unsigned int seqNum)
{

//  //TODO A! Find out how svUpdate should treat leftWindowEdge (guessing the rcvLeftWinEdge)
//  state.setRcvLeftWinEdge(seqNum);
//  uint ackSeqNum = state.getRcvLeftWinEdge();
  /* XXX Don't know where else to put */
  if(state.getRcvLeftWinEdge()  == seqNum){
    state.incRcvLeftWindowEdge();
    std::vector<RxExpiryTimer*>::iterator it;
    for (it = rxQ.begin(); it != rxQ.end(); ++it)
    {
      if((*it)->getPdu()->getSeqNum() == state.getRcvLeftWinEdge()){
        state.incRcvLeftWindowEdge();
      }else{
        break;
      }
    }
//    ackSeqNum = seqNum;
  }


  if (state.isFCPresent())
  {
    if (state.isWinBased())
    {
      runRcvrFlowControlPolicy();
    }

    if (state.isRateBased())
    {
      runRateReductionPolicy();
    }
  }

  if (state.isRxPresent())
  {
    runRcvrAckPolicy(state.getRcvLeftWinEdge() - 1);
  }

  if (state.isFCPresent() && !state.isRxPresent())
  {
    runReceivingFlowControlPolicy();
  }

}

void DTP::flushReassemblyPDUQ()
{
  std::vector<DataTransferPDU*>::iterator it;
  for (it = reassemblyPDUQ.begin(); it != reassemblyPDUQ.end();)
  {
    delete (*it);
    it = reassemblyPDUQ.erase(it);
  }
}



void DTP::clearRxQ()
{
  std::vector<RxExpiryTimer*>::iterator it;
  for (it = rxQ.begin(); it != rxQ.end();)
  {
    delete (*it)->getPdu();
    cancelEvent((*it));
    delete (*it);
    it = rxQ.erase(it);
  }
}

void DTP::clearClosedWindowQ()
{
  std::vector<DataTransferPDU*>::iterator it;
  for (it = closedWindowQ.begin(); it != closedWindowQ.end();)
  {
    delete (*it);
    it = closedWindowQ.erase(it);
  }
}

void DTP::schedule(DTPTimers *timer, double time)
{

  switch (timer->getType())
  {
    case (DTP_RX_EXPIRY_TIMER): {
      //TODO A! Expiry Timer time interval
      scheduleAt(simTime() + getRxTime(), timer); //TODO A! simTime() + something. Find the SOMETHING!
      break;
    }
    case (DTP_SENDER_INACTIVITY_TIMER): {
      //TODO A! 3(MPL+R+A)
      scheduleAt(simTime() + state.getRtt() + 3, timer);
//      scheduleAt(simTime() + 10, timer);
      break;
    }
    case (DTP_RCVR_INACTIVITY_TIMER): {
      //TODO A!
      scheduleAt(simTime() + state.getRtt() + 2, timer);
      break;
    }
    case (DTP_SENDING_RATE_TIMER): {

      scheduleAt(simTime() + (dtcp->flowControl->timeUnit * 1000), timer);
      break;
    }
  }

}

void DTP::setFlow(Flow* flow)
{
  this->flow = flow;
}

void DTP::setDTCP(DTCP* dtcp){
  this->dtcp = dtcp;
}



//
//void DTP::setCepId(int cepId){
//  this->cepId = cepId;
//}
