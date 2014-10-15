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
#include "FAITableEntry.h"

typedef std::list<FAITableEntry> TFAITable;
typedef TFAITable::iterator TFTIter;
typedef TFAITable::const_iterator TFTConstIter;

class FAITable : public cSimpleModule
{
  public:
    std::string info() const;
    void insertNew(Flow* flow);
    void insert(const FAITableEntry& entry);
    void remove();
    FAITableEntry* findEntryByFlow(Flow* flow);
    FAITableEntry* findEntryByFai(FAIBase* fai);
    void bindFaiToFlow(FAIBase* fai, Flow* flow);
    void changeAllocStatus(Flow* flow, FAITableEntry::AllocateStatus status);
    void changeAllocStatus(FAIBase* fai, FAITableEntry::AllocateStatus status);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

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
