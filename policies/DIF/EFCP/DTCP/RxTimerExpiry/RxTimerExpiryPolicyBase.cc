//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file RxExpiryTimerPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 5, 2015
 * @brief
 * @detail
 */

#include "RxTimerExpiryPolicyBase.h"
#include "DTP.h"


RxTimerExpiryPolicyBase::RxTimerExpiryPolicyBase()
{
  // TODO Auto-generated constructor stub

}

RxTimerExpiryPolicyBase::~RxTimerExpiryPolicyBase()
{
  // TODO Auto-generated destructor stub
}

void RxTimerExpiryPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());
  DTCP* dtcp = (DTCP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTCP)).c_str());
  DTCPRxExpiryTimer* timer;

  std::vector<DTCPRxExpiryTimer*>* rxQ = dtcpState->getRxQ();
  std::vector<DTCPRxExpiryTimer*>::iterator it;

  for(it = rxQ->begin(); it != rxQ->end(); ++it){
    if(!(*it)->isScheduled()){
      timer = (*it);
      break;
    }
  }

  if(timer == NULL){
    throw cRuntimeError("Error, couldn't find RxTimerExpiry");
  }


  DataTransferPDU* pdu = timer->getPdu();



    if (timer->getExpiryCount() == dtcpState->getDataReXmitMax() + 1)
    {
      dtcpState->deleteRxTimer(timer->getPdu()->getSeqNum());
      // Notify User Flow that we were unable to maintain the QoS for this connection
      dtp->notifyAboutUnableMaintain();
  //    throw cRuntimeError("Unable to maintain the QoS for this connection");
      ASSERT2(true,"Unable to maintain the QoS for this connection. Continue at your own risk.");
    }
    else
    {

      DataTransferPDU* dup = pdu->dup();
      dup->setDisplayString("b=15,15,oval,#0099FF,#0099FF,0");
      std::ostringstream out;
      out  << "Sending PDU number " << pdu->getSeqNum() << " from RX Queue";

      bubble(out.str().c_str());
      EV << this->getFullPath() << ": " << out.str().c_str() << " in time " << simTime() << endl;
      dtp->sendToRMT(dup);

      dtcpState->incRxSent();

      timer->setExpiryCount(timer->getExpiryCount() + 1);
      dtcp->scheduleRxTimerExpiry();



    }
}
