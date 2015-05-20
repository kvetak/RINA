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
 * @file ReconcileFCPolicyBase.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief
 * @detail
 */

#ifndef RECONCILEFCPOLICYBASE_H_
#define RECONCILEFCPOLICYBASE_H_

#include <omnetpp.h>

#include "EFCPPolicy.h"

/*
 *
 */
class ReconcileFCPolicyBase : public EFCPPolicy
{
  public:
    ReconcileFCPolicyBase();
    virtual ~ReconcileFCPolicyBase();
    //    virtual bool run(DTPState* dtpState, DTCPState* dtcpState) = 0;
        void defaultAction(DTPState* dtpState, DTCPState* dtcpState);

  protected:
    virtual void initialize(){};
    virtual void handleMessage(cMessage* msg){};

};

#endif /* PRECONCILEFCPOLICYBASE_H_ */
