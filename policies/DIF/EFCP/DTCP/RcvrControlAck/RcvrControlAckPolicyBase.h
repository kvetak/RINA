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
 * @file RcvrControlAckPolicyBase.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 5, 2015
 * @brief
 * @detail
 */

#ifndef RCVRCONTROLACKPOLICYBASE_H_
#define RCVRCONTROLACKPOLICYBASE_H_

#include <omnetpp.h>

#include "EFCPPolicy.h"
/*
 *
 */
class RcvrControlAckPolicyBase : public EFCPPolicy
{
  public:
    RcvrControlAckPolicyBase();
    virtual ~RcvrControlAckPolicyBase();
    //    virtual bool run(DTPState* dtpState, DTCPState* dtcpState) = 0;
        void defaultAction(DTPState* dtpState, DTCPState* dtcpState);

  protected:
    virtual void initialize(){};
    virtual void handleMessage(cMessage* msg){};

};

#endif /* RCVRCONTROLACKPOLICYBASE_H_ */
