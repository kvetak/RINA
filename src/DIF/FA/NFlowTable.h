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

#ifndef __RINA_FAITABLE_H_
#define __RINA_FAITABLE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim library
#include "NFlowTableEntry.h"

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
    TFAIPtrs findEntriesAffectedByMgmt(const Flow* flow);
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
    TFAITable FaiTable;
};

//Free functions
/*
std::ostream& operator<< (std::ostream& os, const FlowTable& ft);
std::ostream& operator<< (std::ostream& os, const TFlowTable& ft);
std::ostream& operator<< (std::ostream& os, const TFlowTableEntry& fte);
*/

#endif
