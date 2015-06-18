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

#include "NFlowTable.h"

//Statistic collextion
const char* SIG_STAT_FT_SIZE             = "FT_FlowTableSize";

Define_Module(NFlowTable);

void NFlowTable::initialize()
{
    //Inits
    initSignalsAndListeners();
    //Watchers
    WATCH_LIST(FaiTable);
}

std::string NFlowTable::info() const {
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

NFlowTableEntry* NFlowTable::findEntryByDstAddressAndFwd(const APN& apname) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getDstAddr().getApname() == apname
                && tft.getAllocateStatus() == NFlowTableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;
}

NFlowTableEntry* NFlowTable::findEntryBySrcAddressAndFwd(const APN& apname) {
    //EV << "Look APN> " << ipcAddr << endl;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        //EV << "XXXX " << tft.getCFlow()->getSrcAddr().getIpcAddress() << endl
        //   << "YYYY " << (tft.getAllocateStatus() == FAITableEntry::FORWARDED) << endl;
        if (tft.getCFlow()->getSrcAddr().getIpcAddress() == apname
                && tft.getAllocateStatus() == NFlowTableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;

}

NFlowTableEntry* NFlowTable::findEntryByApns(const APN& srcApn, const APN& dstApn) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getSrcApni().getApn() == srcApn
                && tft.getCFlow()->getDstApni().getApn() == dstApn
                && tft.getAllocateStatus() == NFlowTableEntry::FORWARDED)
            return &(*it);
    }
    return NULL;
}

TFAIPtrs NFlowTable::findEntriesByDstNeighborAndFwd(const APN& apname) {
    TFAIPtrs list;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getDstNeighbor().getApname() == apname
                && tft.getAllocateStatus() == NFlowTableEntry::FORWARDING)
            list.push_back(&(*it));
    }
    return list;
}

NFlowTableEntry* NFlowTable::findEntryByInvokeId(long invId) {
    if (!invId) return NULL;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getAllocInvokeId() == invId)
            return &(*it);
    }
    return NULL;
}

TFAIPtrs NFlowTable::findEntriesAffectedByMgmt(const Flow* flow) {
    TFAIPtrs list;
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getSrcAddr().getApname() == flow->getSrcApni().getApn()
            && tft.getCFlow()->getDstAddr().getApname() == flow->getDstApni().getApn()
            && tft.getAllocateStatus() == NFlowTableEntry::ALLOC_PEND)
            list.push_back(&(*it));
    }
    return list;
}

//XXX: Vesely - This search does not yield exact intended match!
NFlowTableEntry* NFlowTable::findMgmtEntryByDstNeighbor(const Address& addr) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getDstNeighbor() == addr
            && tft.getCFlow()->isManagementFlowLocalToIPCP())
            return &(*it);
    }
    return NULL;
}

void NFlowTable::handleMessage(cMessage *msg)
{
}

void NFlowTable::insertNew(Flow* flow) {
    this->insert(NFlowTableEntry(flow));
    updateDisplayString();
    //EV << "FT emits signal " << (long)FaiTable.size() << endl;
    emit(sigStatFTSize, (long)FaiTable.size());
}

void NFlowTable::insert(const NFlowTableEntry& entry) {
    Enter_Method("insertFlow()");
    FaiTable.push_back(entry);
}

void NFlowTable::removeByFlow(Flow* flow) {
    Enter_Method("removeFlow()");
    NFlowTableEntry* entry = findEntryByFlow(flow);
    if (entry)
        FaiTable.remove(*entry);
}

NFlowTableEntry* NFlowTable::findEntryByFlow(const Flow* flow) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (*(tft.getCFlow()) == *flow)
            return &(*it);
    }
    return NULL;
}

NFlowTableEntry* NFlowTable::findEntryByFai(FAIBase* fai) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getFai() == fai)
            return &(*it);
    }
    return NULL;
}

void NFlowTable::changeAllocStatus(Flow* flow, NFlowTableEntry::EAllocateStatus status) {
    NFlowTableEntry* fte = findEntryByFlow(flow);
    if (fte) {
        fte->setAllocateStatus(status);
    }
    else
        EV << "findByFlow() returned NULL" << endl;
}

void NFlowTable::changeAllocStatus(FAIBase* fai, NFlowTableEntry::EAllocateStatus status) {
    NFlowTableEntry* fte = findEntryByFai(fai);
    if (fte)
        fte->setAllocateStatus(status);
    else
        EV << "findByFai() returned NULL" << endl;
}

void NFlowTable::setFaiToFlow(FAIBase* fai, Flow* flow) {
    NFlowTableEntry* fte = findEntryByFlow(flow);
    fte->setFai(fai);
}

void NFlowTable::updateDisplayString() {
    // display number of flows
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    std::ostringstream os;
    os << "records: " << getSize();
    disp.setTagArg("t", 0, os.str().c_str());
}

void NFlowTable::initSignalsAndListeners() {
    sigStatFTSize = registerSignal(SIG_STAT_FT_SIZE);
}

NFlowTableEntry* NFlowTable::findMgmtEntry(const Flow* flow) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->isManagementFlowLocalToIPCP())
            return &(*it);
    }
    return NULL;
}

NFlowTableEntry* NFlowTable::findMgmtEntryByDstAddr(const Address& addr) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getDstAddr() == addr
            && tft.getCFlow()->isManagementFlowLocalToIPCP())
            return &(*it);
    }
    return NULL;
}

NFlowTableEntry* NFlowTable::findMgmtEntryByDstApni(const APN& dstApn) {
    for(TFTIter it = FaiTable.begin(); it != FaiTable.end(); ++it) {
        NFlowTableEntry tft = *it;
        if (tft.getCFlow()->getDstApni().getApn() == dstApn
            && tft.getCFlow()->isManagementFlowLocalToIPCP())
            return &(*it);
    }
    return NULL;
}

const unsigned int NFlowTable::getSize() const {
    return FaiTable.size();
}
