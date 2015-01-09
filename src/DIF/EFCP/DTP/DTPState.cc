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

#include "DTPState.h"

DTPState::DTPState() {


  initDefaults();
}

void DTPState::initDefaults(){

  currentPDU = NULL;

  closedWindow = false;

  dropDup = 0;

  setDRFFlag = true;

  //TODO A1 load it from flow->qosparameters
  dtcpPresent = true;
  winBased = false;
  rateBased = false;
  incompDeliv = false;
  maxClosedWinQueLen = MAX_CLOSED_WIN_Q_LEN;
  maxFlowPDUSize = MAX_PDU_SIZE;

  //TODO A1
  rcvLeftWinEdge = 0;
  maxSeqNumRcvd = 0;
  nextSeqNumToSend = 1;
  senderLeftWinEdge = 0;


  //TODO B! Fix
  rtt = 0.5;

}

void DTPState::clearPDUQ(std::vector<DataTransferPDU*>* pduQ)
{
  std::vector<DataTransferPDU*>::iterator itP;
  for (itP = pduQ->begin(); itP != pduQ->end();)
  {
    delete (*itP);
    //    delete (*it);
    itP = pduQ->erase(itP);
  }
}

void DTPState::clearClosedWindowQ()
{
  clearPDUQ(&closedWindowQ);

}

void DTPState::clearReassemblyPDUQ()
{
  clearPDUQ(&reassemblyPDUQ);
}

DTPState::~DTPState() {

  clearReassemblyPDUQ();
  clearClosedWindowQ();
}

bool DTPState::isClosedWindow() const {
    return closedWindow;
}

void DTPState::setClosedWindow(bool closedWindowQue) {
    this->closedWindow = closedWindowQue;
}

unsigned int DTPState::getClosedWinQueLen() const {
    return closedWindowQ.size();
}

bool DTPState::isDtcpPresent() const {
    return dtcpPresent;
}

void DTPState::setDtcpPresent(bool dtcpPresent) {
    this->dtcpPresent = dtcpPresent;
}

bool DTPState::isIncompDeliv() const {
    return incompDeliv;
}

void DTPState::setIncompDeliv(bool incompDeliv) {
    this->incompDeliv = incompDeliv;
}

unsigned int DTPState::getMaxClosedWinQueLen() const {
    return maxClosedWinQueLen;
}

void DTPState::setMaxClosedWinQueLen(unsigned int maxClosedWinQueLen) {
    this->maxClosedWinQueLen = maxClosedWinQueLen;
}

unsigned int DTPState::getMaxFlowPduSize() const {
    return maxFlowPDUSize;
}

void DTPState::setMaxFlowPduSize(unsigned int maxFlowPduSize) {
    maxFlowPDUSize = maxFlowPduSize;
}

unsigned int DTPState::getMaxFlowSduSize() const {
    return maxFlowSDUSize;
}

void DTPState::setMaxFlowSduSize(unsigned int maxFlowSduSize) {
    maxFlowSDUSize = maxFlowSduSize;
}

unsigned int DTPState::getMaxSeqNumRcvd() const {
    return maxSeqNumRcvd;
}

void DTPState::setMaxSeqNumRcvd(unsigned int maxSeqNumRcvd) {

    this->maxSeqNumRcvd = (this->maxSeqNumRcvd > maxSeqNumRcvd) ? this->maxSeqNumRcvd : maxSeqNumRcvd;
}

void DTPState::incMaxSeqNumRcvd() {
  maxSeqNumRcvd++;
}

void DTPState::incRcvLeftWindowEdge() {
  rcvLeftWinEdge++;
}

/*
 * Returns value of nextSeqNumToSend and increments it
 * @return nextSeqNumToSend
 */
unsigned int DTPState::getNextSeqNumToSend() {

    return nextSeqNumToSend++;
}

unsigned int DTPState::getNextSeqNumToSendWithoutIncrement() {

    return nextSeqNumToSend;
}

void DTPState::setNextSeqNumToSend(unsigned int nextSeqNumToSend) {
    this->nextSeqNumToSend = nextSeqNumToSend;
}

void DTPState::incNextSeqNumToSend(){
  //TODO A1 what about threshold?
  this->nextSeqNumToSend++;
}

bool DTPState::isPartDeliv() const {
    return partDeliv;
}

void DTPState::setPartDeliv(bool partDeliv) {
    this->partDeliv = partDeliv;
}

bool DTPState::isRateBased() const {
    return rateBased;
}

void DTPState::setRateBased(bool rateBased) {
    this->rateBased = rateBased;
}

//bool DTPState::isRateFullfilled() const {
//    return rateFullfilled;
//}
//
//void DTPState::setRateFullfilled(bool rateFullfilled) {
//    this->rateFullfilled = rateFullfilled;
//}

unsigned int DTPState::getRcvLeftWinEdge() const {
    return rcvLeftWinEdge;
}

void DTPState::setRcvLeftWinEdge(unsigned int rcvLeftWinEdge) {
    this->rcvLeftWinEdge = rcvLeftWinEdge;
}

bool DTPState::isRxPresent() const {
    return rxPresent;
}

void DTPState::setRxPresent(bool rexmsnPresent) {
    this->rxPresent = rexmsnPresent;
}

unsigned int DTPState::getSenderLeftWinEdge() const {
    return senderLeftWinEdge;
}

void DTPState::setSenderLeftWinEdge(unsigned int senderLeftWinEdge) {
    this->senderLeftWinEdge = senderLeftWinEdge;
}

unsigned int DTPState::getSeqNumRollOverThresh() const {
    return seqNumRollOverThresh;
}

void DTPState::setSeqNumRollOverThresh(unsigned int seqNumRollOverThresh) {
    this->seqNumRollOverThresh = seqNumRollOverThresh;
}

int DTPState::getState() const {
    return state;
}

void DTPState::setState(int state) {
    this->state = state;
}

bool DTPState::isWinBased() const {
    return winBased;
}

void DTPState::setWinBased(bool winBased) {
    this->winBased = winBased;
}

bool DTPState::isSetDrfFlag() const
{
  return setDRFFlag;
}

double DTPState::getRtt() const
{
  //TODO B1 RTT estimator policy
  return rtt;
}

void DTPState::setRtt(double rtt)
{
  this->rtt = (this->rtt + rtt)/2;
//  this->rtt = rtt;
}

void DTPState::setSetDrfFlag(bool setDrfFlag)
{
  setDRFFlag = setDrfFlag;
}

unsigned int DTPState::getLastSeqNumSent() const
{
  return lastSeqNumSent;
}

void DTPState::setLastSeqNumSent(unsigned int lastSeqNumSent)
{
  this->lastSeqNumSent = lastSeqNumSent;
}

bool DTPState::isEcnSet() const
{
  return ecnSet;
}

void DTPState::setEcnSet(bool ecnSet)
{
  this->ecnSet = ecnSet;
}

const PDU* DTPState::getCurrentPdu() const
{
  return currentPDU;
}

std::vector<DataTransferPDU*>* DTPState::getClosedWindowQ()
{
  return &closedWindowQ;
}

void DTPState::setCurrentPdu(PDU* currentPdu)
{
  currentPDU = currentPdu;
}

void DTPState::pushBackToClosedWinQ(DataTransferPDU* pdu) {
//TODO check if this PDU is already on the queue (I believe the FSM is broken and it might try to add one PDU twice)

    closedWindowQ.push_back(pdu);
}

std::vector<DataTransferPDU*>* DTPState::getReassemblyPDUQ()
{
  return &reassemblyPDUQ;
}

void DTPState::pushBackToReassemblyPDUQ(DataTransferPDU* pdu)
{
//TODO check if this PDU is already on the queue (I believe the FSM is broken and it might try to add one PDU twice)

  reassemblyPDUQ.push_back(pdu);
}

void DTPState::addPDUToReassemblyQ(DataTransferPDU* pdu)
{

  if (pdu != NULL)
   {
     if (reassemblyPDUQ.empty())
     {
       reassemblyPDUQ.push_back(pdu);
     }
     else
     {
       if (reassemblyPDUQ.front()->getSeqNum() > pdu->getSeqNum())
       {
         reassemblyPDUQ.insert(reassemblyPDUQ.begin(), pdu);
       }
       else
       {
         for (std::vector<DataTransferPDU*>::iterator it = reassemblyPDUQ.begin(); it != reassemblyPDUQ.end(); ++it)
         {
           if ((*it)->getSeqNum() == pdu->getSeqNum())
           {
             //Not sure if this case could ever happen; EDIT: No, this SHOULD not ever happen.
             //TODO A1 Throw Error.
             exit(EXIT_FAILURE);
           }
           else if ((*it)->getSeqNum() > pdu->getSeqNum())
           {
             /* Put the incoming PDU before one with bigger seqNum */
             reassemblyPDUQ.insert(it, pdu);
             break;
           }
           else if (it == --reassemblyPDUQ.end())
           {
             //'it' is last element
             reassemblyPDUQ.insert(it + 1, pdu);
             break;
           }
         }
       }
     }
   }
}



