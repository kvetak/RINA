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
 * @file DTCPECNPolicyDefault.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jan 9, 2015
 * @brief This is an example policy class implementing default ECN policy behavior
 * @detail
 */

#ifndef DTCPECNPOLICYDEFAULT_H_
#define DTCPECNPOLICYDEFAULT_H_

#include "DTCPECNPolicyBase.h"

class DTCPECNPolicyDefault : public DTCPECNPolicyBase
{
  public:
    DTCPECNPolicyDefault();
    virtual ~DTCPECNPolicyDefault();
    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);
};

#endif /* DTCPECNPOLICYDEFAULT_H_ */
