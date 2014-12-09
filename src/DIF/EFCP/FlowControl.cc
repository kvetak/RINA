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
 * @file FlowControl.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#include <FlowControl.h>


FlowControl::FlowControl()
{

  sendingRateTimer = new FCSendingRateTimer();

  schedule(sendingRateTimer);

  dupFC = 0;
  rcvRightWindowEdge = 0;

}

unsigned int FlowControl::getSendRightWindowEdge() const
{
  return sendRightWindowEdge;
}

void FlowControl::setSendRightWindowEdge(unsigned int sendRightWindowEdge)
{
  this->sendRightWindowEdge = sendRightWindowEdge;
}

FlowControl::~FlowControl()
{
  // TODO Auto-generated destructor stub
}

void FlowControl::incDupFC()
{
  dupFC++;
}

void FlowControl::setSendingRate(unsigned int sendingRate)
{
  this->sendingRate = sendingRate;
}

unsigned int FlowControl::getSendingRate()
{
  return sendingRate;
}

void FlowControl::setRcvrRate(unsigned int rcvrRate)
{
  this->rcvrRate = rcvrRate;
}

unsigned int FlowControl::getRcvrRate()
{
  return rcvrRate;
}

unsigned long FlowControl::getSendingTimeUnit() const
{
  return sendingTimeUnit;
}

void FlowControl::setSendingTimeUnit(unsigned long sendingTimeUnit)
{
  this->sendingTimeUnit = sendingTimeUnit;
}

unsigned int FlowControl::getRcvRightWindowEdge() const
{
  return rcvRightWindowEdge;
}

void FlowControl::setRcvRightWindowEdge(unsigned int rcvRightWindowEdge)
{
  this->rcvRightWindowEdge = rcvRightWindowEdge;
}


void FlowControl::schedule(FCTimers* timer, double time)
{
  switch (timer->getType())
  {
    case (FC_SENDING_RATE_TIMER): {
      time = 0;
      scheduleAt(simTime() + timeUnit / 1000, timer);
      break;
    }
  }
}

bool FlowControl::isSendingRateFullfilled() const
{
  return sendingRateFullfilled;
}

void FlowControl::setSendingRateFullfilled(bool rateFullfilled)
{
  this->sendingRateFullfilled = rateFullfilled;
}

void FlowControl::handleSendingRateTimer(FCSendingRateTimer* fcTimer)
{
  pdusSentInTimeUnit = 0;
  setSendingRateFullfilled(false);
  schedule(fcTimer);
}

void FlowControl::handleMessage(cMessage *msg){
  if(msg->isSelfMessage()){
    FCTimers* fcTimer = static_cast<FCTimers*>(msg);
    switch(fcTimer->getType()){
      case(FC_SENDING_RATE_TIMER):{
        handleSendingRateTimer((FCSendingRateTimer*)fcTimer);
        break;
      }



    }

  }else{

    //PANIC!
  }
}
