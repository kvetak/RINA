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
 * @file RMT.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 4, 2014
 * @brief
 * @detail
 */

#ifndef RMT_H_
#define RMT_H_

#include <omnetpp.h>
#include "APNamingInfo.h"
#include "PDU.h"
#include "PDUForwardingTable.h"
#include "ModuleAccess.h"
#include "DataTransferPDU_m.h"

class RMT : public cSimpleModule
{
  private:
    PDUForwardingTable *FwTable;


  public:
    RMT();
    virtual ~RMT();

    /* Just a placeholder -- TO BE DELETED */
    void fromDTPToRMT(APNamingInfo* destAddr, unsigned int qosId, PDU *pdu);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

#endif /* RMT_H_ */
