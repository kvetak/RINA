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

/*
 * @file DTCPState.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#include <DTCPState.h>

Define_Module(DTCPState);

void DTCPState::initFC()
{
  rcvRtWinEdge = rcvCredit;
  sndRtWinEdge = sndCredit;
  sendingRateFullfilled = false;
  closedWindow = false;
  dupAcks = 0;
  dupFC = 0;
  rcvBuffersPercentFree = 100;
  rcvrRate = configRcvrRate;
  sendingRate = 0;
  rcvrRate = 0;

}


DTCPState::DTCPState()
{
  rcvRtWinEdgeSent = 0;
  lastControlSeqNumRcv = 0;
  senderLeftWinEdge = 0;

  //TODO B1 remove immediate and use aTimer eg if(ATime == 0){//imediate}
  immediate = true;

  rxSent = 0;
}

void DTCPState::incRxSent()
{
  rxSent++;
}


bool DTCPState::isImmediate() const
{
  return immediate;
}

void DTCPState::setImmediate(bool immediate)
{
  this->immediate = immediate;
}

unsigned int DTCPState::getRcvrRightWinEdgeSent() const
{
  return rcvRtWinEdgeSent;
}

void DTCPState::setRcvRtWinEdgeSent(unsigned int rcvRightWinEdgeSent)
{
  this->rcvRtWinEdgeSent = rcvRightWinEdgeSent;
}

unsigned int DTCPState::getSenderLeftWinEdge() const {
    return senderLeftWinEdge;
}

void DTCPState::setSenderLeftWinEdge(unsigned int senderLeftWinEdge) {
    this->senderLeftWinEdge = senderLeftWinEdge;
}

unsigned int DTCPState::getSenderRightWinEdge() const
{
  return sndRtWinEdge;
}

void DTCPState::setSenderRightWinEdge(unsigned int senderRightWinEdge)
{
  this->sndRtWinEdge = senderRightWinEdge;
}

DTCPState::~DTCPState()
{
  clearClosedWindowQ();
  clearRxQ();
}

unsigned int DTCPState::getRcvCredit() const
{
  return rcvCredit;
}

void DTCPState::setRcvCredit(unsigned int rcvCredit)
{
  this->rcvCredit = rcvCredit;
}

unsigned int DTCPState::getSndCredit() const
{
  return sndCredit;
}

void DTCPState::setSndCredit(unsigned int sndCredit)
{
  this->sndCredit = sndCredit;
}

unsigned int DTCPState::getRcvRtWinEdge() const
{
  return rcvRtWinEdge;
}

void DTCPState::setRcvRtWinEdge(unsigned int rcvRtWinEdge)
{
  this->rcvRtWinEdge = rcvRtWinEdge;
}

void DTCPState::incRcvRtWinEdge()
{
  rcvRtWinEdge++;
}

void DTCPState::updateRcvRtWinEdge(unsigned int rcvLtWinEdge)
{
  setRcvRtWinEdge(rcvLtWinEdge + getRcvCredit());
}

unsigned int DTCPState::getNextSndCtrlSeqNum()
{
  return nextSenderControlSeqNum++;
}

unsigned int DTCPState::getNextSndCtrlSeqNumNoInc()
{
  return nextSenderControlSeqNum;
}

unsigned int DTCPState::getLastCtrlSeqNumRcv(){
  return lastControlSeqNumRcv;
}

void DTCPState::setLastCtrlSeqNumRcv(unsigned int ctrlSeqNum){
  lastControlSeqNumRcv = ctrlSeqNum;
}

unsigned int DTCPState::getRcvBufferPercentThreshold() const
{
  return rcvBufferPercentThreshold;
}

void DTCPState::setRcvBufferPercentThreshold(unsigned int rcvBufferPercentThreshold)
{
  this->rcvBufferPercentThreshold = rcvBufferPercentThreshold;
}

unsigned int DTCPState::getRcvBuffersPercentFree() const
{
  return rcvBuffersPercentFree;
}

void DTCPState::setRcvBuffersPercentFree(unsigned int rcvBuffersPercentFree)
{
  this->rcvBuffersPercentFree = rcvBuffersPercentFree;
}

void DTCPState::deleteRxTimer(unsigned int seqNum)
{
  std::vector<DTCPRxExpiryTimer*>::iterator it;
  for (it = rxQ.begin(); it != rxQ.end();)
  {
    if (seqNum == (*it)->getPdu()->getSeqNum())
    {
      delete (*it)->getPdu();
      cancelEvent((*it));
      delete (*it);
      rxQ.erase(it);
      return;
    }
    ++it;
  }
}

unsigned int DTCPState::getDataReXmitMax() const
{
  return dataReXmitMax;
}

void DTCPState::setDataReXmitMax(unsigned int dataReXmitMax)
{
  this->dataReXmitMax = dataReXmitMax;
}

std::vector<DTCPRxExpiryTimer*>* DTCPState::getRxQ()
{
  return &rxQ;
}

void DTCPState::pushBackToRxQ(DTCPRxExpiryTimer* timer)
{
  rxQ.push_back(timer);
}

void DTCPState::clearPDUQ(PDUQ_t* pduQ)
{
  PDUQ_t::iterator it;
  for (it = pduQ->begin(); it != pduQ->end();)
  {
    delete (*it);
    it = pduQ->erase(it);
  }
}

void DTCPState::clearRxQ()
{

  std::vector<DTCPRxExpiryTimer*>::iterator it;
    for (it = rxQ.begin(); it != rxQ.end();)
    {
      if((*it)->getPdu() != NULL){
        take((*it)->getPdu());
        delete (*it)->getPdu();
      }
      cancelAndDelete((*it));
      it = rxQ.erase(it);
    }
}

void DTCPState::clearClosedWindowQ()
{
  clearPDUQ(&closedWindowQ);
}

void DTCPState::pushBackToClosedWinQ(DataTransferPDU* pdu) {
//TODO A3 Check if this PDU is already on the queue (I believe the FSM is broken and it might try to add one PDU twice)

  take(pdu);
    closedWindowQ.push_back(pdu);
}

std::vector<DataTransferPDU*>* DTCPState::getClosedWindowQ()
{
  return &closedWindowQ;
}

bool DTCPState::isClosedWinQClosed() const
{
  if (closedWindowQ.size() >= maxClosedWinQueLen)
  {
        return true;
  }else
  {
    return false;
  }
}

bool DTCPState::isClosedWindow() const {

    return closedWindow;
}

void DTCPState::setClosedWindow(bool closedWindowQue) {
    this->closedWindow = closedWindowQue;
}

unsigned int DTCPState::getClosedWinQueLen() const {
    return closedWindowQ.size();
}

unsigned int DTCPState::getMaxClosedWinQueLen() const {
    return maxClosedWinQueLen;
}

void DTCPState::setMaxClosedWinQueLen(unsigned int maxClosedWinQueLen) {
    this->maxClosedWinQueLen = maxClosedWinQueLen;
}


bool DTCPState::isSendingRateFullfilled() const {
    return sendingRateFullfilled;
}

void DTCPState::setSendingRateFullfilled(bool sendingRateFullfilled) {
    this->sendingRateFullfilled = sendingRateFullfilled;
}

unsigned int DTCPState::getPdusSentInTimeUnit() const
{
  return pdusSentInTimeUnit;
}

void DTCPState::setPdusSentInTimeUnit(unsigned int pdusSentInTimeUnit)
{
  this->pdusSentInTimeUnit = pdusSentInTimeUnit;
}

unsigned int DTCPState::getSendingRate() const
{
  return sendingRate;
}

unsigned int DTCPState::getRcvrRate() const
{
  return rcvrRate;
}

unsigned int DTCPState::getConfigRcvrRate() const
{
  return configRcvrRate;
}

void DTCPState::setConfigRcvrRate(unsigned int configRcvrRate)
{
  this->configRcvrRate = configRcvrRate;
}

void DTCPState::setRcvrRate(unsigned int rcvrRate)
{
  this->rcvrRate = rcvrRate;
}

void DTCPState::setSendingRate(unsigned int sendingRate)
{
  this->sendingRate = sendingRate;
}

unsigned int DTCPState::getDupAcks() const
{
  return dupAcks;
}

void DTCPState::incDupAcks()
{
  dupAcks++;
}

void DTCPState::incDupFC()
{
  dupFC++;
}

unsigned long DTCPState::getTimeUnit() const
{
  return timeUnit;
}

unsigned int DTCPState::getDupFC() const
{
  return dupFC;
}

unsigned long DTCPState::getSendingTimeUnit() const
{
  return sendingTimeUnit;
}

void DTCPState::setSendingTimeUnit(unsigned long sendingTimeUnit)
{
  this->sendingTimeUnit = sendingTimeUnit;
}

void DTCPState::updateSndLWE(unsigned int seqNum)
{
  if(!getRxQ()->empty()){
      setSenderLeftWinEdge(getRxQ()->front()->getPdu()->getSeqNum());
    }else{
      setSenderLeftWinEdge(seqNum);
    }
}

void DTCPState::handleMessage(cMessage* msg)
{
}

void DTCPState::initialize(int step)
{
  if(step == 1){
    if(par("aTime").doubleValue() != 0){
      immediate = false;
    }

    rcvCredit = par("rcvCredit");
    if(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->hasPar("rcvCredit")){
      rcvCredit = getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par("rcvCredit");
    }
    sndCredit = par("initialSenderCredit");
    if(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->hasPar("initialSenderCredit")){
      sndCredit = getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par("initialSenderCredit");
    }
    nextSenderControlSeqNum = par("nextSenderControlSeqNum");
    dataReXmitMax = par("dataReXmitMax");


    maxClosedWinQueLen = par("maxClosedWinQueLen");
    if(getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->hasPar("maxClosedWinQueLen")){
      maxClosedWinQueLen = getModuleByPath((std::string(".^.^.") + std::string(MOD_EFCP)).c_str())->par("maxClosedWinQueLen");

    }
    timeUnit = par("timeUnit");
    sendingTimeUnit = par("sendingTimeUnit");
    rcvBufferPercentThreshold = par("rcvBufferPercentThreshold");
    initFC();
  }
}

unsigned int DTCPState::getRxSent() const
{
  return rxSent;
}

void DTCPState::initFromQoS(const QoSCube* qosCube)
{

}
