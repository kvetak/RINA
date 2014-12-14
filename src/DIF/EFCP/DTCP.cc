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

#include "DTCP.h"

Define_Module(DTCP);

DTCP::DTCP() {
  rxControl = NULL;
  flowControl = NULL;



}

DTCP::~DTCP()
{
  if (rxControl != NULL)
  {
    delete rxControl;
  }
  if (flowControl != NULL)
  {
    delete flowControl;
  }
}

void DTCP::setDTP(DTP* dtp)
{
  this->dtp = dtp;
}

void DTCP::initialize(int step)
{
  Enter_Method("initialize");
  dtp = (DTP*)this->getParentModule()->getModuleByPath((std::string(".") + std::string(DTP_MODULE_NAME)).c_str());

//TODO A1 Fill it with appropriate values
  dtcpState = new DTCPState();

//TODO A2 based on DTPState create appropriate components
  if (dtp->state.isRxPresent())
  {
    rxControl = new RXControl();
  }

  if (dtp->state.isFCPresent())
  {
    flowControl = new FlowControl();
    flowControl->initialize();
    if (dtp->state.isWinBased())
    {
      windowTimer = new WindowTimer();
      schedule(windowTimer);
    }
  }


}

void DTCP::schedule(DTCPTimers* timer, double time){

  switch (timer->getType())
  {
    case (DTCP_WINDOW_TIMER): {
      time = 0;
      // TODO B1 Make #define for "3"
      scheduleAt(simTime() + (1 / flowControl->getSendingRate()) + 3, timer);
      break;
    }
  }

}



void DTCP::resetWindowTimer(){
  Enter_Method_Silent();
  cancelEvent(windowTimer);
      schedule(windowTimer);
}

void DTCP::updateRcvRtWinEdge(DTPState* dtpState)
{
  dtcpState->updateRcvRtWinEdge(dtpState->getRcvLeftWinEdge());
}

void DTCP::handleMessage(cMessage *msg){
  if(msg->isSelfMessage()){
    /* Self message */
    DTCPTimers* timer = static_cast<DTCPTimers*>(msg);

    switch(timer->getType()){
      case(DTCP_WINDOW_TIMER):{
        handleWindowTimer(static_cast<WindowTimer*>(timer));
      }
    }
  }else{

    /* PANIC!! */
  }

}

void DTCP::handleWindowTimer(WindowTimer* timer){
  resetWindowTimer();
  //TODO A1 Uncomment
//  dtp->sendControlAckPDU();

}

unsigned int DTCP::getNextSndCtrlSeqNum(){
//  return rxControl->getNextSndCtrlSeqNum();
  return dtcpState->getNextSndCtrlSeqNum();
}

unsigned int DTCP::getLastCtrlSeqNumRcv(){
//  return rxControl->getLastCtrlSeqNumRcv();
  return dtcpState->getLastCtrlSeqNumRcv();
}

void DTCP::setLastCtrlSeqnumRec(unsigned int ctrlSeqNum){
//  rxControl->setLastCtrlSeqNumRcv(ctrlSeqNum);
  dtcpState->setLastCtrlSeqNumRcv(ctrlSeqNum);
}

void DTCP::setSndRtWinEdge(unsigned int sndRtWinEdge)
{
//  flowControl->setSendRightWindowEdge(sndRtWinEdge);
  dtcpState->setSenderRightWinEdge(sndRtWinEdge);
}

unsigned int DTCP::getSndRtWinEdge()
{

//  return flowControl->getSendRightWindowEdge();
  return dtcpState->getSenderRightWinEdge();

}

void DTCP::setRcvRtWinEdge(unsigned int rcvRtWinEdge)
{
  flowControl->setRcvRightWindowEdge(rcvRtWinEdge);
}

unsigned int DTCP::getRcvRtWinEdge()
{
  return flowControl->getRcvRightWindowEdge();
}

void DTCP::setSndRate(unsigned int sendingRate)
{
  flowControl->setSendingRate(sendingRate);
}
unsigned int DTCP::getSndRate(){
  return flowControl->getSendingRate();
}

void DTCP::setRcvRate(unsigned int rcvrRate)
{
  flowControl->setRcvrRate(rcvrRate);
}
unsigned int DTCP::getRcvRate(){
  return flowControl->getRcvrRate();
}

unsigned int DTCP::getRcvCredit()
{
  return dtcpState->getRcvCredit();
}


unsigned long DTCP::getSendingTimeUnit()
{
   return flowControl->getSendingTimeUnit();
}


bool DTCP::isSendingRateFullfilled() const
{
  return flowControl->isSendingRateFullfilled();
}

void DTCP::setSendingRateFullfilled(bool rateFullfilled)
{
  flowControl->setSendingRateFullfilled(rateFullfilled);
}
