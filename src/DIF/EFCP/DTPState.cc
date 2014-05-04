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
    // TODO Auto-generated constructor stub

}

DTPState::~DTPState() {
    // TODO Auto-generated destructor stub
}

bool DTPState::isClosedWindow() const {
    return closedWindow;
}

void DTPState::setClosedWindow(bool closedWindowQue) {
    this->closedWindow = closedWindowQue;
}

unsigned int DTPState::getClosedWinQueLen() const {
    return closedWinQueLen;
}

void DTPState::setClosedWinQueLen(unsigned int closedWinQueLen) {
    this->closedWinQueLen = closedWinQueLen;
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

int DTPState::getMaxSeqNumRcvd() const {
    return maxSeqNumRcvd;
}

void DTPState::setMaxSeqNumRcvd(int maxSeqNumRcvd) {
    this->maxSeqNumRcvd = maxSeqNumRcvd;
}

/*
 * Return value of nextSeqNumToSend and increments it
 * @return nextSeqNumToSend value before incrementing
 */
unsigned int DTPState::getNextSeqNumToSend() {

    return nextSeqNumToSend++;
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

bool DTPState::isRateFullfilled() const {
    return rateFullfilled;
}

void DTPState::setRateFullfilled(bool rateFullfilled) {
    this->rateFullfilled = rateFullfilled;
}

int DTPState::getRcvLeftWinEdge() const {
    return rcvLeftWinEdge;
}

void DTPState::setRcvLeftWinEdge(int rcvLeftWinEdge) {
    this->rcvLeftWinEdge = rcvLeftWinEdge;
}

bool DTPState::isRxPresent() const {
    return rxPresent;
}

void DTPState::setRxPresent(bool rexmsnPresent) {
    this->rxPresent = rexmsnPresent;
}

int DTPState::getSenderLeftWinEdge() const {
    return senderLeftWinEdge;
}

void DTPState::setSenderLeftWinEdge(int senderLeftWinEdge) {
    this->senderLeftWinEdge = senderLeftWinEdge;
}

int DTPState::getSeqNumRollOverThresh() const {
    return seqNumRollOverThresh;
}

void DTPState::setSeqNumRollOverThresh(int seqNumRollOverThresh) {
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
