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
  // TODO Auto-generated constructor stub

}
DTP::~DTP()
{
  // TODO Auto-generated destructor stub
}

void DTP::initGates()
{
  northI = this->gateHalf(GATE_DTP_NORTHIO, cGate::INPUT);
  northO = this->gateHalf(GATE_DTP_NORTHIO, cGate::OUTPUT);
  southI = this->gateHalf(GATE_DTP_SOUTHIO, cGate::INPUT);
  southO = this->gateHalf(GATE_DTP_SOUTHIO, cGate::OUTPUT);
}

void DTP::initialize(int step)
{

  initGates();

  senderInactivityTimer = new SenderInactivityTimer();


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
        schedule(timer);

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
      handleMsgFromDelimiting((Data*) msg);

    }
    else if (msg->arrivedOn(southI->getId()))
    {
      handleMsgFromRmt((PDU*) msg);
    }
  }

}

/**
 * This method fills header fields in given @param pdu
 * @param pdu
 */
void DTP::setPDUHeader(DataTransferPDU* pdu)
{
  pdu->setConnId(this->flow->getConId());
  pdu->setSrcAddr(this->flow->getSrcAddr());
  pdu->setDstAddr(this->flow->getDstAddr());
  pdu->setSrcApn(this->flow->getDstApni().getApn());
  pdu->setDstApn(this->flow->getSrcApni().getApn());
}

void DTP::handleMsgFromDelimiting(Data* msg)
{

  cancelEvent(senderInactivityTimer);

  DataTransferPDU* pdu = new DataTransferPDU();
  pdu->setMUserData(msg);
  setPDUHeader(pdu);
  pdu->setSeqNum(this->state.getNextSeqNumToSend());

  send(pdu, southO);

}

void DTP::handleMsgFromRmt(PDU* msg)
{

  if (dynamic_cast<DataTransferPDU*>(msg))
  {
    DataTransferPDU* pdu = (DataTransferPDU*) msg;
    cMessage* sdu = pdu->getMUserData();
    take(check_and_cast<cOwnedObject*>(sdu) );
    send(pdu->getMUserData(), northO);
  }
}

void DTP::handleSDUs(CDAPMessage* cdap)
{

  cancelEvent(senderInactivityTimer);

//    this->delimit(buffer, len);
//  delimit(cdap);

  /* Now tae data from buffer are copied to SDUs so we can free the memory */
//    free(buffer);
  this->generatePDUs();

  /* Iterate over generated PDUs and decide if we can send them */
  this->trySendGenPDUs();

  //  /* iterate over postablePDUs */
  //  this->sendPostablePDUsToRMT();

  schedule(senderInactivityTimer);

}
/**
 *
 * @param timer
 */
void DTP::handleDTPRxExpiryTimer(RxExpiryTimer* timer)
{
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
bool DTP::write(int portId, unsigned char* buffer, int len)
{

  cancelEvent(senderInactivityTimer);

  this->delimit(buffer, len);
  /* Now the data from buffer are copied to SDUs so we can free the memory */
  free(buffer);

  this->generatePDUs();

  /* Iterate over generated PDUs and decide if we can send them */
  this->trySendGenPDUs();

//  /* iterate over postablePDUs */
//  this->sendPostablePDUsToRMT();

  schedule(senderInactivityTimer);
  return true;
}

unsigned int DTP::delimit(SDU* sdu)
{

  //TODO B2 Does PDU header counts to MaxFlowPDUSize?
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



/**
 * This method takes all SDUs from sduQ and generates PDUs by filling appropriate header fields
 */
void DTP::generatePDUs()
{

  DataTransferPDU* dataPDU = new DataTransferPDU();

  dataPDU->setConnId((const ConnectionId) (*connId.dup()));
  //setDestAddr... APN
  //setSrcAddr ... APN

  //invoke SDU protection so we don't have to bother with it afterwards
  for (std::vector<SDU*>::iterator it = sduQ.begin(); it != sduQ.end(); ++it)
  {
    sduProtection(*it);
  }

  SDU *sdu = NULL;
  DataTransferPDU* genPDU = dataPDU->dup();
  bool fragment = false;
  int delimitFlags = 0;
  do
  {
    //This method fetches next SDU if current one has been put to some PDU(s) (offset = size)
    this->getSDUFromQ(sdu);

    unsigned int copySize = 0;
    /* TODO We should take into account also SDUDelimiterFlags etc */
    unsigned int pduAvailSize = state.getMaxFlowPduSize() - genPDU->getPduLen();
    /* if the rest of the SDU is bigger than empty space in PDU then fill-up PDU */
    copySize = (sdu->getRestSize() >= pduAvailSize) ? pduAvailSize : sdu->getRestSize();

    if (genPDU->getPduLen() == PDU_HEADER_LEN)
    {
      //PDU is empty
      //set noLength flag
      delimitFlags |= 0x04;
      if (sdu->getRestSize() > pduAvailSize)
      {
        //(rest of) SDU is bigger than PDU
        //set noLength flag
        delimitFlags |= 0x04;
        if (sdu->getSize() > sdu->getRestSize())
        {
          //not first segment, something has been read from SDU
          //and since it won't fit cannot be last
          //this is middle segment
          delimitFlags |= 0x00;
        }
        else
        {
          //this is first segment of next SDU
          delimitFlags |= 0x01;
        }
      }
      else
      {
        //(rest of) SDU is smaller than available space in PDU
        if (sdu->getSize() > sdu->getRestSize())
        {
          //last fragment of previous SDU
          delimitFlags |= 0x02;
        }
        else
        {
          //this is complete SDU
          delimitFlags |= 0x03;
        }
      }

    }
    else
    {
      //clear noLength flag
      delimitFlags &= 0xFB;

      if (sdu->getRestSize() > pduAvailSize)
      {
        //(rest of) SDU won't fit into rest of PDU
        if (sdu->getSize() > sdu->getRestSize())
        {
          //this is not first segment
          if (copySize == sdu->getRestSize())
          {
            //this is last segment
            delimitFlags |= 0x02;
          }
          else
          {
            //this is middle segment
            //not permitted
            throw cRuntimeError("This type of PDU delimiting is not permitted!");
          }
        }
        else
        {
          //adding first segment
          delimitFlags |= 0x01;
        }
      }
      else
      {
        //(rest of) SDU will fit into rest of PDU
        //complete sdu
        if ((delimitFlags & 0x03) == 3)
        {
          //since i'm adding complete SDU, this flag is possible only when adding complete SDU to one (or more)complete SDU
          delimitFlags &= 0xFC;
        }
      }
    }

    //add whole SDU or fragment to PDU
    genPDU->addUserData(sdu->getUserData(copySize), copySize, &fragment);
//    fragment = true;

    if (sdu->getRestSize() == 0)
    {
      delete sduQ.front();
      sduQ.erase(sduQ.begin());
    }

    //if genPDU is full or SDU queue is empty, 'close' PDU and put it to generated PDUs and create new PDU
    if (genPDU->getPduLen() >= this->state.getMaxFlowPduSize() || sduQ.empty())
    {
      //TODO A2 what else to do before sending?
      //what about formating SDUDelimitersFlags in userData?
      genPDU->putDelimitFlags(delimitFlags, fragment);

      //put genPDU to generatedPDUs
      generatedPDUs.push_back(genPDU);

      if (!sduQ.empty())
      {
        genPDU = dataPDU->dup();
        fragment = false;
        //set DRF(false) -> not needed (false is default)
        genPDU->setSeqNum(this->state.getNextSeqNumToSend());
      }
    }

  } while (!sduQ.empty());
}

void DTP::generatePDUsnew(){

  DataTransferPDU* dataPDU = new DataTransferPDU();

  setPDUHeader(dataPDU);

}




/**
 *
 */
void DTP::trySendGenPDUs()
{

  if (state.isDtcpPresent())
  {
    //postablePDUs = empty;

    //if flowControl present
    if (state.isWinBased() || state.isRateBased())
    {
      std::vector<PDU*>::iterator it;
      for (it = generatedPDUs.begin(); it != generatedPDUs.end(); it = generatedPDUs.begin())
      {
        if (state.isWinBased())
        {
          if ((*it)->getSeqNum() <= dtcp->getFlowControlRightWinEdge())
          {
            /* The Window is Open. */
            runTxControlPolicy();
            /* Watchout because the current 'it' could be freed */
          }
          else
          {
            /* The Window is Closed */
            state.setClosedWindow(true);
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

        if (state.isClosedWindow() ^ state.isRateFullfilled())
        {
          runReconcileFlowControlPolicy();
        }
      }//end of for
    }else{
      //TODO A1 This should probably put ALL generatedPDUs to postablePDUs
      std::vector<PDU*>::iterator it;
      for (it = generatedPDUs.begin(); it != generatedPDUs.end();)
      {
        postablePDUs.push_back((*it));
        it = generatedPDUs.erase(it);
      }
    }

    /* Iterate over postablePDUs and give them to the RMT */
    if (state.isRxPresent())
    {
      std::vector<PDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();)
      {
        /* Put a copy of each PDU in the RetransmissionQueue */
        //new rxTimerMessage
        RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
        rxExpTimer->setPdu((*it)->dup());

        rxQ.push_back(rxExpTimer);
        scheduleAt(simTime() + getRxTime(), rxExpTimer); //TODO A! simTime() + something. Find the SOMETHING!
        //TODO A! Where do I get destAddr? Probably from FlowAllocator
        sendToRMT((*it));
//        rmt->fromDTPToRMT(new APN(), connId.getQoSId(), (*it));

        it = postablePDUs.erase(it);
      }
    }
    else
    {
      /*No Retransmission Control is present, but FlowControl */
      /* Post all postablePDUs to RMT */
      std::vector<PDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();)
      {
        //TODO A! Where do I get destAddr? Probably from FlowAllocator
        //TODO A! change to send using omnet messages
//        rmt->fromDTPToRMT(new APNamingInfo(), connId.getQoSId(), (*it));
        it = postablePDUs.erase(it);
      }

    }
  }
  else
  {
    /* DTCP is not present */
    /* Post all generatedPDUs to RMT */
    std::vector<PDU*>::iterator it;
    for (it = postablePDUs.begin(); it != postablePDUs.end();)
    {
      //TODO A! Where do I get destAddr? Probably from FlowAllocator
      APNamingInfo* apn = new APNamingInfo();
      //TODO A! change to send using omnet messages
//      rmt->fromDTPToRMT(new APNamingInfo(), connId.getQoSId(), (*it));
//      rmt->fromDTPToRMT(apn, 1, (*it));
      it = postablePDUs.erase(it);
    }
  }

}

void DTP::fromRMT(PDU* pdu)
{

  if (state.isFlowControlPresent())
  {
    dtcp->resetWindowTimer();

  }
  // if PDU.DRF == true
  if ((pdu->getFlags() & 0x80) == 0x80)
  {
    /* Case 1) DRF is set - either first PDU or new run */
    //TODO A! Invoke delimiting delimitFromRMT()
    delimitFromRMT(pdu, pdu->getUserDataArraySize());

    //Flush the PDUReassemblyQueue
    flushReassemblyPDUQ();

    state.setMaxSeqNumRcvd(pdu->getSeqNum());
    /* Initialize the other direction */
    dtcp->dtcpState->setSetDrfFlag(true);

    runInitialSequenceNumberPolicy();

    if (state.isDtcpPresent())
    {
      /* Update RxControl */
      svUpdate(pdu->getSeqNum());
    }

  }
  else
  {
    /* Not the start of a run */
    if (pdu->getSeqNum() < state.getRcvLeftWinEdge())
    {
      /* Case 2) A Real Duplicate */
      //Discard PDU and increment counter of dropped duplicates PDU
      delete pdu;
      //TODO A1 increment counter of dropped duplicates PDU
      state.incDropDup();

      //TODO A! send an Ack/Flow Control PDU with current window values

      return;
    }

    if (state.getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() <= state.getMaxSeqNumRcvd())
    {
      /* Not a true duplicate. (Might be a duplicate amongst the gaps) */
      //TODO A!
      //if a duplicate among the gaps then // search reassemblyQ?
      if (false)
      {
        /* Case 3) Duplicate Among gaps */

        //Discard PDU and increment counter of dropped duplicates PDU
        delete pdu;
        //TODO A1 increment counter of dropped duplicates PDU
        state.incDropDup();

        //TODO A! send an Ack/Flow Control PDU with current window values
        return;
      }
      else
      {
        /* Case 3) This goes in a gap */
        /* Put at least the User-Data of the PDU with its Sequence Number on PDUReassemblyQueue in Sequence Number order */
        reassemblyPDUQ.push_back(pdu);
        if (state.isDtcpPresent())
        {
          svUpdate(state.getMaxSeqNumRcvd()); /* Update left edge, etc */
        }
        else
        {
          state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
          /* No A-Timer necessary, already running */
        }
        //TODO A1
        delimitFromRMT(pdu, pdu->getUserDataArraySize());
        return;
      }
    }

    if (pdu->getSeqNum() == state.getMaxSeqNumRcvd() + 1)
    {
      state.incMaxSeqNumRcvd();
      if (state.isDtcpPresent())
      {
        svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
      }
      else
      {
        state.setRcvLeftWinEdge(state.getMaxSeqNumRcvd());
        //TODO A! start A-Timer (for this PDU)
      }
      delimitFromRMT(pdu, pdu->getUserDataArraySize()); /* Create as many whole SDUs as possible */

    }
    else
    {
      /* Case 5) it is out of order */
      if (pdu->getSeqNum() > state.getMaxSeqNumRcvd() + 1)
      {
        if (state.isDtcpPresent())
        {
          svUpdate(state.getMaxSeqNumRcvd()); /* Update Left Edge, etc. */
        }
        else
        {
          //TODO A! start A-timer
        }
        delimitFromRMT(pdu, pdu->getUserDataArraySize());
      }
      schedule(rcvrInactivityTimer); //TODO Find out why there is sequenceNumber -> Start RcvrInactivityTimer(PDU.SequenceNumber) /* Backstop timer */

      //TODO A1 DIF.integrity
      /* If we are encrypting, we can't let PDU sequence numbers roll over */

      //If DIF.Integrity and PDU.SeqNum > SequenceNumberRollOverThreshhold Then
      ///* Security requires a new flow */
      //RequestFAICreateNewConnection( PDU.FlowID )
      //Fi
    }

  }
}

///*
// * Iterate over postablePDUs and give them to RMT
// */
//void DTP::sendPostablePDUsToRMT(){
//
//  if(state.isRxPresent()){
//    std::vector<PDU*>::iterator it;
//      for (it = generatedPDUs.begin(); it != generatedPDUs.end(); it = generatedPDUs.begin()){
//        /* Put a copy of each PDU in the RetransmissionQueue */
//      }
//
//  }
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

unsigned int DTP::getFlowControlRightWinEdge()
{

  return dtcp->getFlowControlRightWinEdge();
}

/*
 * We assume that this policy is used only under flowControl, it doesn't check presence
 * of flowControl object - it might be NULL
 */
void DTP::runTxControlPolicy()
{
  /* Default */
  if (this->txControlPolicy == NULL)
  {
    /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
     And Set the ClosedWindow flag appropriately. */
    std::vector<PDU*>::iterator it;
    for (it = generatedPDUs.begin();
        it != generatedPDUs.end() || (*it)->getSeqNum() <= dtcp->getFlowControlRightWinEdge();)
    {
      postablePDUs.push_back((*it));
      it = generatedPDUs.erase(it);

    }

    if (!generatedPDUs.empty())
    {
      state.setClosedWindow(true);
    }
  }
  else
  {
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
  state.setNextSeqNumToSend(4);
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
void DTP::runRcvrAckPolicy()
{
  /* Default */
  if (dtcp->dtcpState->isImmediate())
  {
    //TODO A!
    //Update LeftWindowEdge removing allowed gaps;
    //send an Ack/FlowControlPDU
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

  PDU* pdu = timer->getPdu();
  /*  unsigned int seqNum = pdu->getSeqNum();
   std::vector<RxExpiryTimer*>::iterator it;
   Retransmitt all PDUs that have SeqNum less or equal to the one that just expired?
   for(it = rxQ.begin(); it != rxQ.end(); ++it){
   if((*it)->getPdu()->getSeqNum() <= seqNum){
   sendToRMT((*it)->getPdu());
   (*it)->setExpiryCount((*it)->getExpiryCount() + 1);
   }
   }*/

  if (timer->getExpiryCount() == dtcp->rxControl->dataReXmitMax + 1)
  {
    //TODO A! Indicate an error "Unable to maintain the QoS for this connection"
  }
  else
  {
    sendToRMT(pdu);
    timer->setExpiryCount(timer->getExpiryCount() + 1);
  }

}

void DTP::runRcvrInactivityTimerPolicy()
{

  /* Default */
  dtcp->dtcpState->setSetDrfFlag(true);
  if (runInitialSequenceNumberPolicy())
  {
    state.setNextSeqNumToSend(4); //TODO A2 It SHOULD return random value;
  }

  //Discard any PDUs on the PDUretransmissionQueue
  clearRxQ();

  //Discard any PDUs on the ClosedWindowQueue
  clearClosedWindowQ();

  //TODO A! Send Control Ack PDU

  //TODO A! Send Transfer PDU With Zero length

  //TODO A! Notify User Flow there has been no activity for awhile.

}

void DTP::runSenderInactivityTimerPolicy()
{

  /* Default */
  dtcp->dtcpState->setSetDrfFlag(true);
  if (runInitialSequenceNumberPolicy())
  {
    state.setNextSeqNumToSend(4); //TODO A2 It SHOULD return random value;
  }

  //Discard any PDUs on the PDUretransmissionQueue
  clearRxQ();

  //Discard any PDUs on the ClosedWindowQueue
  clearClosedWindowQ();

  //TODO A! Send Control Ack PDU

  //TODO A! Send Transfer PDU With Zero length

  //TODO A! Notify User Flow there has been no activity for awhile.

}

bool DTP::runSendingAckPolicy(ATimer* timer)
{
  /* Default */
  //TODO A!
  unsigned int gap = getAllowableGap();
  unsigned int seqNum = timer->getPdu()->getSeqNum();
  unsigned int leftWindowEdge = state.getRcvLeftWinEdge();

  //TODO Co to je za hovnokod?
  if (leftWindowEdge + 1 == leftWindowEdge < seqNum && leftWindowEdge + gap > seqNum)
  {
    //this PDU is

  }

  //Update LeftWindowEdge

  return false;
}

void DTP::sendToRMT(PDU* pdu)
{
  //TODO A! change to send using omnet messages
//  rmt->fromDTPToRMT(new APNamingInfo(), connId.getQoSId(), pdu);
}

unsigned int DTP::getRxTime()
{
  //TODO A! 2MPL + A + epsilon
  //This might be job for a policy, presumably RTT estimator policy?
  /* 2MPL == RTT
   * A == ?
   * epsilon ?
   */
  return dtcp->dtcpState->getRtt();
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

  if (state.isFlowControlPresent())
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
    runRcvrAckPolicy();
  }

  if (state.isFlowControlPresent() && !state.isRxPresent())
  {
    runReceivingFlowControlPolicy();
  }

}

void DTP::flushReassemblyPDUQ()
{
  std::vector<PDU*>::iterator it;
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
    delete (*it);
    it = rxQ.erase(it);
  }
}

void DTP::clearClosedWindowQ()
{
  std::vector<PDU*>::iterator it;
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
      break;
    }
    case (DTP_SENDER_INACTIVITY_TIMER): {
      //TODO A! 3(MPL+R+A)
      scheduleAt(simTime() + dtcp->dtcpState->getRtt(), timer);
      break;
    }
    case (DTP_RCVR_INACTIVITY_TIMER): {
      //TODO A!
      scheduleAt(simTime() + dtcp->dtcpState->getRtt(), timer);
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



//
//void DTP::setCepId(int cepId){
//  this->cepId = cepId;
//}
