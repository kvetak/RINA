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


}

DTCP::~DTCP() {
    // TODO Auto-generated destructor stub
}

void DTCP::initialize(){
  // TODO Auto-generated constructor stub
dtcpState = new DTCPState();

//TODO A2 based on DTCPState create appropriate components
rxControl = new RXControl();
}

unsigned int DTCP::getFlowControlRightWinEdge(){
  return flowControl->getSendRightWindowEdge();
}


void DTCP::schedule(DTCPTimers* timer){

}

void DTCP::resetWindowTimer(){
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
  sendAckPDU();
}



void DTCP::sendAckPDU(){

}

unsigned int DTCP::getNextCtrlSeqNum(){
  return dtcpState->getNextCtrlSeqNum();
}
