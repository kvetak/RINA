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

DTP::DTP()
{
  // TODO Auto-generated constructor stub

}
DTP::~DTP()
{
  // TODO Auto-generated destructor stub
}

void DTP::setConnId(const ConnectionId& connId)
{
  this->connId = connId;
}

void DTP::handleMessage(cMessage *msg)
{

}

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


unsigned int DTP::delimitFromRMT(PDU *pdu, unsigned int len){
  unsigned int counter = 0;

//  if()

  return counter;
}

/**
 * This method takes all SDUs from sduQ and generates PDUs by adding appropriate header content
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
        if(state.isWinBased()){
          if ((*it)->getSeqNum() <= dtcp->getFlowControlRightWinEdge())
          {
            /* The Window is Open. */
            runTxControlPolicy();
            /* Watchout because the current 'it' could be freed */
          }else{
            /* The Window is Closed */
            state.setClosedWindow(true);
            if(state.getClosedWinQueLen() < state.getMaxClosedWinQueLen() -1){
              /* Put PDU on the closedWindowQueue */
              closedWindowQ.push_back((*it));
              generatedPDUs.erase(it);
            }else{
              runFlowControlOverrunPolicy();
            }
          }
        }// end of Window based

        if(state.isRateBased()){
          if(dtcp->flowControl->pdusSentInTimeUnit < dtcp->flowControl->sendingRate){
            runNoRateSlowDownPolicy();
          }else{
            /* Exceeding Sending Rate */
            runNoOverrideDefaultPeakPolicy();
          }
        }// end of RateBased

        if(state.isClosedWindow() ^ state.isRateFullfilled()){
          runReconcileFlowControlPolicy();
        }
      }//end of for
    }else{
      //TODO A1 This should probably put ALL generatedPDUs to postablePDUs
      std::vector<PDU*>::iterator it;
      for (it = generatedPDUs.begin(); it != generatedPDUs.end();){
        postablePDUs.push_back((*it));
        it = generatedPDUs.erase(it);
      }
    }

    /* Iterate over postablePDUs and give them to the RMT */
    if(state.isRxPresent()){
      std::vector<PDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();){
        /* Put a copy of each PDU in the RetransmissionQueue */
        //new rxTimerMessage
        RxExpiryTimer* rxExpTimer = new RxExpiryTimer("RxExpiryTimer");
        rxExpTimer->setPdu((*it)->dup());

        rxQ.push_back(rxExpTimer);
        scheduleAt(simTime() + getRxTime(),rxExpTimer); //TODO A! simTime() + something. Find the SOMETHING!
        //TODO A! Where do I get destAddr? Probably from FlowAllocator
        rmt->fromDTPToRMT(new APN(), connId.getQoSId(), (*it));

        it = postablePDUs.erase(it);
      }
    }else{
      /*No Retransmission Control is present, but FlowControl */
      /* Post all postablePDUs to RMT */
      std::vector<PDU*>::iterator it;
      for (it = postablePDUs.begin(); it != postablePDUs.end();){
        //TODO A! Where do I get destAddr? Probably from FlowAllocator
        rmt->fromDTPToRMT(new APN(), connId.getQoSId(), (*it));
        it = postablePDUs.erase(it);
      }

    }
  }else{
    /* DTCP is not present */
    /* Post all generatedPDUs to RMT */
    std::vector<PDU*>::iterator it;
    for (it = postablePDUs.begin(); it != postablePDUs.end();){
      //TODO A! Where do I get destAddr? Probably from FlowAllocator
      APN* apn = new APN();
      rmt->fromDTPToRMT(new APN(), connId.getQoSId(), (*it));
      rmt->fromDTPToRMT(apn, 1, (*it));
      it = postablePDUs.erase(it);
    }
  }


}


void DTP::fromRMT(PDU* pdu){

  if(state.isFlowControlPresent()){
    cancelEvent(windowTimer);
    schedule(windowTimer);
  }
  // if PDU.DRF == true
  if((pdu->getFlags() & 0x80) == 0x80){
    /* Case 1) DRF is set - either first PDU or new run */
    //TODO A! Invoke delimiting delimitFromRMT()

    //Flush the PDUReassemblyQueue
    //TODO A2 free memory of queued PDUs
    reassemblyPDUQ.clear();
    state.setMaxSeqNumRcvd(pdu->getSeqNum());
    /* Initialize the other direction */
    dtcp->dtcpState->setSetDrfFlag(true);

    runInitialSequenceNumberPolicy();

    if(state.isDtcpPresent()){
      /* Update RxControl */
      svUpdate(pdu->getSeqNum());
    }

  }else{
    /* Not the start of a run */
    if(pdu->getSeqNum() < state.getRcvLeftWinEdge()){
      /* Case 2) A Real Duplicate */
      //Discard PDU and increment counter of dropped duplicates PDU
      delete pdu;
      //TODO A1 increment counter of dropped duplicates PDU
      state.incDropDup();

      //TODO A! send an Ack/Flow Control PDU with current window values

      return;
    }

//    if(state.getRcvLeftWinEdge() < pdu->getSeqNum() && pdu->getSeqNum() <)
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
  }else{
    txControlPolicy->run((cObject *)this);
  }

}


void DTP::runFlowControlOverrunPolicy(){
  /* Default */
  closedWindowQ.push_back(generatedPDUs.front());
  generatedPDUs.erase(generatedPDUs.begin());

  //TODO A1 How to block further Write API calls on this port-id
}


void DTP::runNoRateSlowDownPolicy(){
  /* Default */
  postablePDUs.push_back(generatedPDUs.front());
  generatedPDUs.erase(generatedPDUs.begin());
  dtcp->flowControl->pdusSentInTimeUnit++;
}


void DTP::runNoOverrideDefaultPeakPolicy(){
  /*Default */
  state.setRateFullfilled(true);
  if(state.getClosedWinQueLen() < state.getMaxClosedWinQueLen() - 1){
    closedWindowQ.push_back(generatedPDUs.front());
    generatedPDUs.erase(generatedPDUs.begin());
  }
}

void DTP::runReconcileFlowControlPolicy(){
  /* Default (is empty) */
}

void DTP::runInitialSequenceNumberPolicy(){

  /*Default*/
  //TODO B1 set it to random number
  state.setNextSeqNumToSend(4);
}



unsigned int DTP::getRxTime(){
  //TODO A! 2MPL + A + epsilon
  //This might be job for a policy, presuambly RTT estimator policy?
  /* 2MPL == RTT
   * A == ?
   * epsilon ?
   */
  return dtcp->dtcpState->getRtt();
}


void DTP::svUpdate(unsigned int seqNum){

  //TODO A! Find out what svUpdate should specifically update!
  state.setRcvLeftWinEdge(seqNum);
}


void DTP::schedule(DTPTimers *timer, double time){


  switch(timer->getType()){
    case (RX_EXPIRY_TIMER):{
      break;
    }
    case (DTP_SENDER_INACTIVITY_TIMER):{
          //TODO A! 3(MPL+R+A)
            scheduleAt(simTime() + dtcp->dtcpState->getRtt(), timer);
          break;
        }
    case (DTP_RCVR_INACTIVITY_TIMER):{
          //TODO A!
            scheduleAt(simTime() + dtcp->dtcpState->getRtt(), timer);
          break;
    }
  }

}
