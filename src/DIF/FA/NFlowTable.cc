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

#include "DIF/FA/NFlowTable.h"

#include "Common/APN.h"
#include "Common/Flow.h"
#include "Common/Utils.h"

// Statistic collextion
const char *SIG_STAT_FT_SIZE = "FT_FlowTableSize";

Define_Module(NFlowTable);

NFlowTable::~NFlowTable() {
    for (auto &elem : NFlowTab)
        delete elem.getFlow();
}

void NFlowTable::initialize()
{
    // Inits
    initSignalsAndListeners();
    // Watchers
    WATCH_LIST(NFlowTab);
}

std::string NFlowTable::str() const
{
    std::ostringstream os;
    os << "id=" << this->getId() << endl;
    return os.str();
}

NFlowTableEntry *NFlowTable::findEntryByDstAddressAndFwd(const APN &apname)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstAddr().getApn() == apname &&
            tft.getAllocateStatus() == NFlowTableEntry::FORWARDED) {
            return &tft;
        }
    }
    return nullptr;
}

NFlowTableEntry *NFlowTable::findEntryBySrcAddressAndFwd(const APN &apname)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getSrcAddr().getIpcAddress() == apname &&
            tft.getAllocateStatus() == NFlowTableEntry::FORWARDED)
            return &tft;
    }
    return nullptr;
}

NFlowTableEntry *NFlowTable::findEntryByApns(const APN &srcApn, const APN &dstApn)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getSrcApni().getApn() == srcApn &&
            tft.getCFlow()->getDstApni().getApn() == dstApn &&
            tft.getAllocateStatus() == NFlowTableEntry::FORWARDED)
            return &tft;
    }
    return nullptr;
}

TFAIPtrs NFlowTable::findEntriesByDstNeighborAndFwd(const APN &apname)
{
    TFAIPtrs list;
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstNeighbor().getApn() == apname &&
            tft.getAllocateStatus() == NFlowTableEntry::FORWARDING) {
            list.push_back(&tft);
        }
    }
    return list;
}

NFlowTableEntry *NFlowTable::findEntryByInvokeId(long invId)
{
    if (!invId)
        return nullptr;
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getAllocInvokeId() == invId) {
            return &tft;
        }
    }
    return nullptr;
}

// XXX: Vesely - This search does not yield exact intended match!
NFlowTableEntry *NFlowTable::findMgmtEntryByDstNeighbor(const Address &addr)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstNeighbor() == addr &&
            tft.getCFlow()->isManagementFlowLocalToIPCP()) {
            return &tft;
        }
    }
    return nullptr;
}

void NFlowTable::handleMessage(cMessage *msg)
{
    delete msg;
    throw cRuntimeError("This module is not supposed to handle messages");
}

void NFlowTable::insertNew(Flow *flow)
{
    this->insert(NFlowTableEntry(flow));
    updateDisplayString();
    // EV << "FT emits signal " << (long)FaiTable.size() << endl;
    emit(sigStatFTSize, (long)NFlowTab.size());
}

void NFlowTable::insert(const NFlowTableEntry &entry)
{
    Enter_Method("insertFlow()");
    NFlowTab.push_back(entry);
}

void NFlowTable::removeByFlow(Flow *flow)
{
    Enter_Method("removeFlow()");
    NFlowTableEntry *entry = findEntryByFlow(flow);
    if (entry)
        NFlowTab.remove(*entry);
}

NFlowTableEntry *NFlowTable::findEntryByFlow(const Flow *flow)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow() == flow)
            return &tft;
    }
    return nullptr;
}

NFlowTableEntry *NFlowTable::findEntryByFai(FAIBase *fai)
{
    for (auto &tft : NFlowTab) {
        if (tft.getFai() == fai)
            return &tft;
    }
    return nullptr;
}

NFlowTableEntry *NFlowTable::findEntryByApnisAndQosId(const APN &srcApn,
                                                      const APN &dstApn,
                                                      const std::string &qosId)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getSrcApni().getApn() == srcApn &&
            tft.getCFlow()->getDstApni().getApn() == dstApn &&
            tft.getCFlow()->getConId().getQoSId() == qosId) {
            return &tft;
        }
    }
    return nullptr;
}

void NFlowTable::changeAllocStatus(Flow *flow, NFlowTableEntry::EAllocateStatus status)
{
    NFlowTableEntry *fte = findEntryByFlow(flow);
    if (fte) {
        fte->setAllocateStatus(status);
    } else {
        EV << "findByFlow() returned NULL" << endl;
    }
}

void NFlowTable::changeAllocStatus(FAIBase *fai, NFlowTableEntry::EAllocateStatus status)
{
    // TODO please return false on failure
    NFlowTableEntry *fte = findEntryByFai(fai);
    if (fte)
        fte->setAllocateStatus(status);
    else
        EV << "findByFai() returned NULL" << endl;
}

void NFlowTable::setFaiToFlow(FAIBase *fai, Flow *flow)
{
    NFlowTableEntry *fte = findEntryByFlow(flow);
    fte->setFai(fai);
}

void NFlowTable::updateDisplayString()
{
    // display number of flows
    std::ostringstream os;
    os << "records: " << getSize();
    setPolicyDisplayString(this, os.str().c_str());
}

void NFlowTable::initSignalsAndListeners()
{
    sigStatFTSize = registerSignal(SIG_STAT_FT_SIZE);
}

NFlowTableEntry *NFlowTable::findMgmtEntryByDstAddr(const Address &addr)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstAddr() == addr && tft.getCFlow()->isManagementFlowLocalToIPCP())
            return &tft;
    }
    return nullptr;
}

NFlowTableEntry *NFlowTable::findMgmtEntryByDstApni(const APN &dstApn)
{
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstApni().getApn() == dstApn &&
            tft.getCFlow()->isManagementFlowLocalToIPCP()) {
            return &tft;
        }
    }
    return nullptr;
}

unsigned int NFlowTable::getSize() const
{
    return NFlowTab.size();
}

TFAIPtrs NFlowTable::findEntriesAffectedByMgmt(const APNIPair *apnip)
{
    TFAIPtrs list;
    for (auto &tft : NFlowTab) {
        if (tft.getCFlow()->getDstNeighbor().getApn() == apnip->second.getApn()) {
            if (tft.getAllocateStatus() == NFlowTableEntry::ALLOC_PEND ||
                tft.getAllocateStatus() == NFlowTableEntry::FORWARDING) {
                list.push_back(&tft);
            }
        }
    }
    return list;
}
