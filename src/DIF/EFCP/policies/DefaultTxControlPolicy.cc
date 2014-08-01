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
 * @file DefaultTxContrlPolicy.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2014
 * @brief
 * @detail
 */

#include <DefaultTxControlPolicy.h>

DefaultTxControlPolicy::DefaultTxControlPolicy()
{
  // TODO Auto-generated constructor stub

}

DefaultTxControlPolicy::~DefaultTxControlPolicy()
{
  // TODO Auto-generated destructor stub
}

void DefaultTxControlPolicy::run(cObject *dtpT)
{
  /* Default */

    DTP *dtp = static_cast<DTP *>( dtpT);
    /* Add as many PDU to PostablePDUs as Window Allows, closing it if necessary
     And Set the ClosedWindow flag appropriately. */
    std::vector<PDU*>::iterator it;
    for (it = dtp->generatedPDUs.begin();
        it != dtp->generatedPDUs.end() || (*it)->getSeqNum() <= dtp->dtcp->getFlowControlRightWinEdge();)
    {
      dtp->postablePDUs.push_back((*it));
      dtp->generatedPDUs.erase(it);

    }

    if (!dtp->generatedPDUs.empty())
    {
      dtp->state.setClosedWindow(true);
    }


}
