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
 * @file DTCPSendingAckPolicyBase.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#ifndef DTCPSENDINGACKPOLICYBASE_H_
#define DTCPSENDINGACKPOLICYBASE_H_

#include <omnetpp.h>

#include "DTPState.h"
#include "DTCPState.h"
#include "DTPTimers_m.h"

/*
 *
 */
class DTCPSendingAckPolicyBase : public cSimpleModule
{
  public:
    DTCPSendingAckPolicyBase();
    virtual ~DTCPSendingAckPolicyBase();
    virtual bool run(DTPState* dtpState, DTCPState* dtcpState, ATimer* timer) = 0;

      protected:
        virtual void initialize(){};
        virtual void handleMessage(cMessage* msg){};
};

#endif /* DTCPSENDINGACKPOLICYBASE_H_ */
