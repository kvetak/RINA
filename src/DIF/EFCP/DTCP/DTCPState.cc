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

/*
 * @file DTCPState.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#include "DIF/EFCP/DTCP/DTCPState.h"

Define_Module(DTCPState);

void DTCPState::resetRcvVars()
{
  rcvRightWinEdge = UINT_MAX;
//  rcvRate = ??
  rcvBuffersPercentFree = 100;
  rcvrRate = configRcvrRate;
  sndRightWinEdge = sndCredit;
  sendingRateFullfilled = false;

  lastControlSeqNumRcv = 0;


}

void DTCPState::resetSndVars()
{
  //  timeUnit = 1000;
  //  sendingTimeUnit = 1000;

  //  sendingRate = 2;

  sendingRate = 0;
  sndLeftWinEdge = 0;
  rcvRightWinEdgeSent = 0;
}

void DTCPState::initFC()
{
//  rcvRightWinEdge = rcvCredit;
  resetRcvVars();


  closedWindow = false;
//  maxClosedWinQueLen = MAX_CLOSED_WIN_Q_LEN;
  dupAcks = 0;
  dupFC = 0;


//  timeUnit = 1000;
//  sendingTimeUnit = 1000;

//  rcvBufferPercentThreshold = 75;
//  sendingRate = 2;

//  configRcvrRate = 50;


  resetSndVars();
//  rcvrRate = 0;
  rendezSeqNum = 0;

}


DTCPState::DTCPState()
{

  winBased = false;
  rateBased = false;


  lastControlSeqNumRcv = 0;


  rxSent = 0;

  sndRendez = false;
  rcvRendez = false;

  rendezvousTimer = nullptr;
  reliableCPDUTimer = nullptr;
}

void DTCPState::incRxSent()
{
  rxSent++;
}


//bool DTCPState::isImmediate() const
//{
//  return immediate;
//}

//void DTCPState::setImmediate(bool immediate)
//{
//  this->immediate = immediate;
//}

unsigned int DTCPState::getRcvrRightWinEdgeSent() const
{
  return rcvRightWinEdgeSent;
}

void DTCPState::setRcvRightWinEdgeSent(unsigned int rcvRightWinEdgeSent)
{
  this->rcvRightWinEdgeSent = rcvRightWinEdgeSent;
}

unsigned int DTCPState::getSndLeftWinEdge() const {
    return sndLeftWinEdge;
}

void DTCPState::setSenderLeftWinEdge(unsigned int senderLeftWinEdge) {
    this->sndLeftWinEdge = senderLeftWinEdge;
}

unsigned int DTCPState::getSndRightWinEdge() const
{
  return sndRightWinEdge;
}

void DTCPState::setSenderRightWinEdge(unsigned int senderRightWinEdge)
{
  this->sndRightWinEdge = senderRightWinEdge;
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

unsigned int DTCPState::getRcvRightWinEdge() const
{
  return rcvRightWinEdge;
}

void DTCPState::setRcvRtWinEdge(unsigned int rcvRtWinEdge)
{
  this->rcvRightWinEdge = rcvRtWinEdge;
}

void DTCPState::incRcvRtWinEdge()
{
  rcvRightWinEdge++;
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

//void DTCPState::deleteRxTimer(unsigned int seqNum)
//{
//  std::vector<DTCPRxExpiryTimer*>::iterator it;
//  for (it = rxQ.begin(); it != rxQ.end();)
//  {
//    if (seqNum == (*it)->getPdu()->getSeqNum())
//    {
//      delete (*it)->getPdu();
////      take((*it));
//      cancelEvent((*it));
//      delete (*it);
//      rxQ.erase(it);
//      return;
//    }
//    ++it;
//  }
//}

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
//      drop((*it));
//      if((*it)->isScheduled()){
//        take((*it));
//        cancelAndDelete((*it));
//      }
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

      rxPresent = qoSCube->isRxOn();
          winBased = qoSCube->isWindowFcOn();
          rateBased = qoSCube->isRateFcOn();

    if(par("aTime").doubleValue() != 0){
//      immediate = false;
    }

    rcvCredit = par("rcvCredit");
    if(getRINAModule<cModule*>(this, 2, {MOD_EFCP})->hasPar("rcvCredit")){
          rcvCredit = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("rcvCredit");
    }
    sndCredit = par("initialSenderCredit");
    if(getRINAModule<cModule*>(this, 2, {MOD_EFCP})->hasPar("initialSenderCredit")){
          sndCredit = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("initialSenderCredit");
    }
    nextSenderControlSeqNum = par("nextSenderControlSeqNum");
    dataReXmitMax = par("dataReXmitMax");


    maxClosedWinQueLen = par("maxClosedWinQueLen");
    if(getRINAModule<cModule*>(this, 2, {MOD_EFCP})->hasPar("maxClosedWinQueLen")){
          maxClosedWinQueLen = getRINAModule<cModule*>(this, 2, {MOD_EFCP})->par("maxClosedWinQueLen");

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

const QoSCube* DTCPState::getQoSCube() const {
    return qoSCube;
}

void DTCPState::setQoSCube(const QoSCube*& qoSCube) {
    this->qoSCube = qoSCube;
}

DTCPReliableControlPDUTimer* DTCPState::getReliableCpduTimer()
{
  return reliableCPDUTimer;
}

void DTCPState::setReliableCpduTimer(DTCPReliableControlPDUTimer* reliableCpduTimer)
{
  reliableCPDUTimer = reliableCpduTimer;
}

void DTCPState::initFromQoS(const QoSCube* qosCube)
{

}

unsigned int DTCPState::getRxQLen()
{
  return rxQ.size();
}

bool DTCPState::isRateBased() const {
    return rateBased;
}

void DTCPState::setRateBased(bool rateBased) {
    this->rateBased = rateBased;
}

bool DTCPState::isRxPresent() const {
    return rxPresent;
}

void DTCPState::setRxPresent(bool rxPresent) {
    this->rxPresent = rxPresent;
}

bool DTCPState::isWinBased() const {
    return winBased;
}

void DTCPState::setWinBased(bool winBased) {
    this->winBased = winBased;
}

unsigned int DTCPState::getPdusRcvdInTimeUnit() const
{
  return pdusRcvdinTimeUnit;
}

void DTCPState::setPdusRcvdinTimeUnit(unsigned int pdusRcvdinTimeUnit)
{
  this->pdusRcvdinTimeUnit = pdusRcvdinTimeUnit;
}

unsigned int DTCPState::getLastControlSeqNumSent() const
{
  return lastControlSeqNumSent;
}

void DTCPState::setLastControlSeqNumSent(unsigned int lastControlSeqNumSent)
{
  this->lastControlSeqNumSent = lastControlSeqNumSent;
}

bool DTCPState::isRcvRendez() const
{
  return rcvRendez;
}

void DTCPState::setRcvRendez(bool rcvRendez)
{
  this->rcvRendez = rcvRendez;
}

bool DTCPState::isSndRendez() const
{
  return sndRendez;
}

void DTCPState::setSndRendez(bool sndRendez)
{
  this->sndRendez = sndRendez;
}

DTCPRendezvousTimer* DTCPState::getRendezvousTimer()
{
  return rendezvousTimer;
}

void DTCPState::setRendezvousTimer(DTCPRendezvousTimer* rendezvousTimer)
{
  this->rendezvousTimer = rendezvousTimer;
}

unsigned int DTCPState::getRendezSeqNum() const
{
  return rendezSeqNum;
}

void DTCPState::setRendezSeqNum(unsigned int rendezSeqNum)
{
  this->rendezSeqNum = rendezSeqNum;
}
