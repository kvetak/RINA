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
 * @file NoOverridePeakPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 8, 2015
 * @brief
 * @detail
 */

#include "NoOverridePeakPolicyBase.h"

NoOverridePeakPolicyBase::NoOverridePeakPolicyBase()
{


}

NoOverridePeakPolicyBase::~NoOverridePeakPolicyBase()
{

}

void NoOverridePeakPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{

  /* Default */
  dtcpState->setSendingRateFullfilled(true);
  if (dtcpState->getClosedWinQueLen() < dtcpState->getMaxClosedWinQueLen() - 1)
  {
    dtcpState->pushBackToClosedWinQ((DataTransferPDU*) dtpState->getCurrentPdu());

  }
  /* End default */
}
