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
 * @file NoRateSlowDownPolicyBase.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief
 * @detail
 */

#include "NoRateSlowDownPolicyBase.h"

NoRateSlowDownPolicyBase::NoRateSlowDownPolicyBase()
{


}

NoRateSlowDownPolicyBase::~NoRateSlowDownPolicyBase()
{

}

void NoRateSlowDownPolicyBase::defaultAction(DTPState* dtpState, DTCPState* dtcpState)
{

  /* Default */
  //TODO A1 Do I need to propagate the pduQ (gneratedPDUs vs closedWindowQ
  /* Default */

  dtpState->pushBackToPostablePDUQ(dtpState->getGeneratedPDUQ()->front());
  dtpState->getGeneratedPDUQ()->erase(dtpState->getGeneratedPDUQ()->begin());
//  dtcpState->incincPdusSentInTimeUnit();
  dtcpState->setPdusSentInTimeUnit(dtcpState->getPdusSentInTimeUnit() + 1);
  /* End default */
}
