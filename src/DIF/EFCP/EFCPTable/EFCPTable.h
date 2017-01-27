// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
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

#include "DIF/EFCP/EFCPTable/EFCPTableEntry.h"



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
