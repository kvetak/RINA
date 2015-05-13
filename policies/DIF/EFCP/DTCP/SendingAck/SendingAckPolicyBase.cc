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
/**
 * @file SendingAckPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "SendingAckPolicyBase.h"
#include "DTP.h"

SendingAckPolicyBase::SendingAckPolicyBase()
{


}

SendingAckPolicyBase::~SendingAckPolicyBase()
{

}

void SendingAckPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  /* Oh my, oh my, oh my */
  /* You wish your wife was this dirty, don't you? */
  /* Default */
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());

  //Update RcvLetWindowEdge
  dtpState->updateRcvLWE(dtpState->getTmpAtimer()->getSeqNum());

  //Invoke Delimiting
  dtp->delimitFromRMT(NULL);

  //resetSenderInactivity
  dtp->resetSenderInactivTimer();

  /* End default */

}
