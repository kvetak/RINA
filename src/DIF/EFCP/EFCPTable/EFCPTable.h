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

#include "EFCPTableEntry.h"



typedef std::vector<EFCPTableEntry*> TEFCPTable;

class EFCPTable : public cSimpleModule
{
  private:
    TEFCPTable efcpTable;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


  public:
    EFCPTable();
    virtual ~EFCPTable();
    EFCPTableEntry* getEntryByFlow(const Flow* flow);
    EFCPTableEntry* getEntryByEFCPI(EFCPInstance* efcpi);
    EFCPTableEntry* getEntryByDelimit(Delimiting* delimit);
    DTP* getDTPBySrcCEP(int srcCEP);
    void insertEntry(EFCPTableEntry* entry);

    std::string info() const;

};

#endif /* EFCPTABLE_H_ */
