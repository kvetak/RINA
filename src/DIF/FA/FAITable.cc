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

//Statistic collextion
const char* SIG_STAT_FT_SIZE             = "FT_FlowTableSize";

Define_Module(FAITable);

void FAITable::initialize()
{
    //Inits
    initSignalsAndListeners();
    //Watchers
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

FAITableEntry* FAITable::findEntryByDstAddressAndFwd(const APN& apname) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getCFlow()->getDstAddr().getApname() == apname
                && tft.getAllocateStatus() == FAITableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;
}

FAITableEntry* FAITable::findEntryBySrcAddressAndFwd(const APN& apname) {
    //EV << "Look APN> " << ipcAddr << endl;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        //EV << "XXXX " << tft.getCFlow()->getSrcAddr().getIpcAddress() << endl
        //   << "YYYY " << (tft.getAllocateStatus() == FAITableEntry::FORWARDED) << endl;
        if (tft.getCFlow()->getSrcAddr().getIpcAddress() == apname
                && tft.getAllocateStatus() == FAITableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;

}

FAITableEntry* FAITable::findEntryByApns(const APN& srcApn, const APN& dstApn) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getCFlow()->getSrcApni().getApn() == srcApn
                && tft.getCFlow()->getDstApni().getApn() == dstApn
                && tft.getAllocateStatus() == FAITableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;
}

TFAIPtrs FAITable::findEntryByDstNeighborAndFwd(const APN& apname) {
    TFAIPtrs list;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getCFlow()->getDstNeighbor().getApname() == apname
                && tft.getAllocateStatus() == FAITableEntry::FORWARDING)
            list.push_back(&(*it));
    }
    return list;
}

FAITableEntry* FAITable::findEntryByInvokeId(long invId) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (tft.getCFlow()->getAllocInvokeId() == invId)
            return &(*it);
    }
    return NULL;
}

void FAITable::handleMessage(cMessage *msg)
{

}

void FAITable::insertNew(Flow* flow) {
    this->insert(FAITableEntry(flow));
    updateDisplayString();
    //EV << "FT emits signal " << (long)FaiTable.size() << endl;
    emit(sigStatFTSize, (long)FaiTable.size());
}

void FAITable::insert(const FAITableEntry& entry) {
    Enter_Method("insertFlow()");
    FaiTable.push_back(entry);
}

void FAITable::removeByFlow(Flow* flow) {
    Enter_Method("removeFlow()");
    FAITableEntry* entry = findEntryByFlow(flow);
    if (entry)
        FaiTable.remove(*entry);
}

FAITableEntry* FAITable::findEntryByFlow(const Flow* flow) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        FAITableEntry tft = *it;
        if (*(tft.getCFlow()) == *flow)
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

void FAITable::changeAllocStatus(Flow* flow, FAITableEntry::EAllocateStatus status) {
    FAITableEntry* fte = findEntryByFlow(flow);
    if (fte) {
        fte->setAllocateStatus(status);
    }
    else
        EV << "findByFlow() returned NULL" << endl;
}

void FAITable::changeAllocStatus(FAIBase* fai, FAITableEntry::EAllocateStatus status) {
    FAITableEntry* fte = findEntryByFai(fai);
    if (fte)
        fte->setAllocateStatus(status);
    else
        EV << "findByFai() returned NULL" << endl;
}

void FAITable::setFaiToFlow(FAIBase* fai, Flow* flow) {
    FAITableEntry* fte = findEntryByFlow(flow);
    fte->setFai(fai);
}

void FAITable::updateDisplayString() {
    // display number of flows
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    std::ostringstream os;
    os << "records: " << FaiTable.size();
    disp.setTagArg("t", 0, os.str().c_str());
}

void FAITable::initSignalsAndListeners() {
    sigStatFTSize = registerSignal(SIG_STAT_FT_SIZE);
}
