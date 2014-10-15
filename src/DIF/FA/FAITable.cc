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

#include "FAITable.h"

Define_Module(FAITable);

void FAITable::initialize()
{
    WATCH_LIST(FaiTable);
}

std::string FAITable::info() const {
    std::ostringstream os;
    os << "id=" << this->getId() << endl;
    /*
    for(TFTConstIter it = FaiTable.begin(); it != FaiTable.end(); ++it )
    {
        FAITableEntry tft = *it;
        os << tft << endl;
    }
    */
    return os.str();
}

void FAITable::handleMessage(cMessage *msg)
{

}

void FAITable::insertNew(Flow* flow) {
    this->insert(FAITableEntry(flow));
}

void FAITable::insert(const FAITableEntry& entry) {
    Enter_Method("insertFlow()");
    FaiTable.push_back(entry);
}

void FAITable::remove() {
}

FAITableEntry* FAITable::findEntryByFlow(Flow* flow) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getFlow() == flow)
            return &(*it);
    }
    return NULL;
}

FAITableEntry* FAITable::findEntryByFai(FAIBase* fai) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getFai() == fai)
            return &(*it);
    }
    return NULL;
}

void FAITable::changeAllocStatus(Flow* flow, FAITableEntry::AllocateStatus status) {
    FAITableEntry* fte = findEntryByFlow(flow);
    if (fte)
        fte->setAllocateStatus(status);
    else
        EV << "findByFlow() returned NULL" << endl;
}

void FAITable::changeAllocStatus(FAIBase* fai, FAITableEntry::AllocateStatus status) {
    FAITableEntry* fte = findEntryByFai(fai);
    if (fte)
        fte->setAllocateStatus(status);
    else
        EV << "findByFai() returned NULL" << endl;
}

void FAITable::bindFaiToFlow(FAIBase* fai, Flow* flow) {
    FAITableEntry* fte = findEntryByFlow(flow);
    fte->setFai(fai);
}

