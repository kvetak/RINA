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
 * @file RXControl.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#include <RXControl.h>

RXControl::RXControl()
{
//  nextSenderControlSeqNum = 1;
  dupAcks = 0;
//  lastControlSeqNumRcv = 0;
//  dataReXmitMax = 3;

}

RXControl::~RXControl()
{
  // TODO Auto-generated destructor stub
}

unsigned int RXControl::getRightWinEdge(){

  return rightWinEdge;
}

//unsigned int RXControl::getNextSndCtrlSeqNum()
//{
//  return nextSenderControlSeqNum++;
//}

//unsigned int RXControl::getLastCtrlSeqNumRcv(){
//  return lastControlSeqNumRcv;
//}

//void RXControl::setLastCtrlSeqNumRcv(unsigned int ctrlSeqNum){
//  lastControlSeqNumRcv = ctrlSeqNum;
//}
void RXControl::incDupAcks()
{
  dupAcks++;
}
