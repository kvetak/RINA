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

#ifndef __RINA_FAITABLE_H_
#define __RINA_FAITABLE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim library
#include "Common/Utils.h"
#include "DIF/FA/NFlowTableEntry.h"

typedef std::list<NFlowTableEntry> TFAITable;
typedef std::list<NFlowTableEntry*> TFAIPtrs;
typedef TFAITable::iterator TFTIter;
typedef TFAITable::const_iterator TFTConstIter;
typedef TFAIPtrs::iterator TFTPtrsIter;

//Statistic collextion
extern const char* SIG_STAT_FT_SIZE;

class NFlowTable : public cSimpleModule
{
  public:
    std::string info() const;
    void insertNew(Flow* flow);
    void insert(const NFlowTableEntry& entry);
    void removeByFlow(Flow* flow);
    unsigned const int getSize() const;
    NFlowTableEntry* findEntryByFlow(const Flow* flow);
    NFlowTableEntry* findEntryByApns(const APN& srcApn, const APN& dstApn);
    NFlowTableEntry* findMgmtEntry(const Flow* flow);
    NFlowTableEntry* findMgmtEntryByDstAddr(const Address& addr);
    NFlowTableEntry* findMgmtEntryByDstNeighbor(const Address& addr);
    NFlowTableEntry* findMgmtEntryByDstApni(const APN& dstApn);
    NFlowTableEntry* findEntryByDstAddressAndFwd(const APN& apname);
    TFAIPtrs findEntriesByDstNeighborAndFwd(const APN& apname);
    TFAIPtrs findEntriesAffectedByMgmt(const APNIPair* apnip);
    NFlowTableEntry* findEntryBySrcAddressAndFwd(const APN& apname);
    NFlowTableEntry* findEntryByFai(FAIBase* fai);
    NFlowTableEntry* findEntryByInvokeId(long invId);
    void setFaiToFlow(FAIBase* fai, Flow* flow);
    void changeAllocStatus(Flow* flow, NFlowTableEntry::EAllocateStatus status);
    void changeAllocStatus(FAIBase* fai, NFlowTableEntry::EAllocateStatus status);

    void updateDisplayString();

  protected:
    virtual void initialize();
    void initSignalsAndListeners();
    virtual void handleMessage(cMessage *msg);

    simsignal_t sigStatFTSize;

  private:
    TFAITable NFlowTab;
};

//Free functions
/*
std::ostream& operator<< (std::ostream& os, const FlowTable& ft);
std::ostream& operator<< (std::ostream& os, const TFlowTable& ft);
std::ostream& operator<< (std::ostream& os, const TFlowTableEntry& fte);
*/

#endif
