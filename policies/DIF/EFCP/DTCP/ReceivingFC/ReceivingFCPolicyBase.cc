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
 * @file ReceivingFCPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#include "ReceivingFCPolicyBase.h"
#include "DTP.h"

ReceivingFCPolicyBase::ReceivingFCPolicyBase()
{
}

ReceivingFCPolicyBase::~ReceivingFCPolicyBase()
{
}

void ReceivingFCPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());
  if (dtpState->isWinBased())
  {

    //Send FlowControl PDU /* Already updated the window and not sending Ack */
    dtp->sendFCOnlyPDU();

  }

  /* End default */
}
