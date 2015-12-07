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
 * @file EFCPInstance.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#ifndef EFCPINSTANCE_H_
#define EFCPINSTANCE_H_

#include "DTP.h"
#include "DTCP.h"

//class DTP;
//class DTCP;

class EFCPInstance
{
  private:
    DTP* dtp;
    DTCP* dtcp;

  public:
    EFCPInstance();
    virtual ~EFCPInstance();
    DTCP* getDtcp();
    void setDtcp(DTCP* dtcp);
    DTP* getDtp();
    void setDtp(DTP* dtp);
};

#endif /* EFCPINSTANCE_H_ */
