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
 * @file EFCPTableEntry.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#ifndef EFCPTABLEENTRY_H_
#define EFCPTABLEENTRY_H_

#include <omnetpp.h>
#include <vector>
#include <string>

//#include "FAI.h"
#include "Flow.h"
#include "EFCPInstance.h"
#include "Delimiting.h"

//class EFCPInstance;


typedef std::vector<EFCPInstance*> TEFCPITab; //type EFCP instance

class EFCPTableEntry
{
  private:
    Flow* flow;
    Delimiting* delimit;
    TEFCPITab efcpiTab;

  public:
    EFCPTableEntry();
    virtual ~EFCPTableEntry();

    std::string info() const;
    const Delimiting* getDelimit() const;
    const TEFCPITab* getEfcpiTab();
    const Flow* getFlow() const;
    void setDelimit(Delimiting* delimit);
    void setFlow(Flow* flow);
    void addEFCPI(EFCPInstance* efcpi);
};

#endif /* EFCPTABLEENTRY_H_ */
