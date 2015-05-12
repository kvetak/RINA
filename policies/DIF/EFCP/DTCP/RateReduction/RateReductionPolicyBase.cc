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
 * @file RateReductionPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief
 * @detail
 */

#include "RateReductionPolicyBase.h"
#include "DTP.h"

RateReductionPolicyBase::RateReductionPolicyBase()
{


}

RateReductionPolicyBase::~RateReductionPolicyBase()
{

}

void RateReductionPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{
  DTP* dtp = (DTP*)getModuleByPath((std::string(".^.") + std::string(MOD_DTP)).c_str());
  /* Default */
  if (dtcpState->getRcvBuffersPercentFree() <= dtcpState->getRcvBufferPercentThreshold())
  {
//      flowControl->rcvrRate *= 0.9; //Reduce Rate 10%
    dtcpState->setRcvrRate(dtcpState->getRcvrRate() *0.9);

  }
  else
  {
    if (dtcpState->getRcvrRate() < dtcpState->getConfigRcvrRate()
        && dtcpState->getRcvBuffersPercentFree() > dtcpState->getRcvBufferPercentThreshold())
    {
      //set rate back to config rate
      dtcpState->setRcvrRate(dtcpState->getConfigRcvrRate());
    }
  }
  dtp->sendAckFlowPDU();
  /* End default */

}
