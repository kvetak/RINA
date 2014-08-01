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
 * @file EFCPTable.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#ifndef EFCPTABLE_H_
#define EFCPTABLE_H_

#include <omnetpp.h>
#include <csimplemodule.h>

#include "EFCPTableEntry.h"
<<<<<<< HEAD
//#include "Delimiting.h"
//#include "EFCPInstance.h"
//class EFCPTableEntry;
//class EFCPInstance;
=======
#include "Delimiting.h"
>>>>>>> branch 'master' of https://github.com/kvetak/RINA.git

typedef std::vector<EFCPTableEntry*> TEFCPTable;

class EFCPTable : public cSimpleModule
{
  private:
    TEFCPTable efcpTable;



  public:
    EFCPTable();
    virtual ~EFCPTable();
    EFCPTableEntry* getEntryByFlow(Flow* flow);
    EFCPTableEntry* getEntryByEFCPI(EFCPInstance* efcpi);
    EFCPTableEntry* getEntryByDelimit(Delimiting* delimit);

};

#endif /* EFCPTABLE_H_ */
