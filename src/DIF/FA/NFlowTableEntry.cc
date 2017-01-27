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

#include "DIF/FA/NFlowTableEntry.h"

NFlowTableEntry::NFlowTableEntry() :
    fai(NULL), flow(NULL),
    allocStatus(this->UNKNOWN),
    timeCreated(0), timeDeleted(0)
{
}

NFlowTableEntry::NFlowTableEntry(Flow* nflow): fai(NULL), allocStatus(this->UNKNOWN) {
    this->flow           = nflow;
    this->timeCreated    = simTime();
    this->timeDeleted    = 0;
}

NFlowTableEntry::~NFlowTableEntry() {
    this->fai       = NULL;
    this->flow      = NULL;
    allocStatus     = this->UNKNOWN;
    timeCreated     = 0;
    timeDeleted     = 0;
}

std::string NFlowTableEntry::info() const {
    std::ostringstream os;
    os << "STATUS: " << this->getAllocateStatusString() << endl;
    if ( this->getFai() )
        os << "FAI> " << *(this->getFai()) << endl;
    if ( this->getCFlow() ) {
        os << this->getCFlow()->infoSource() << endl;
        os << this->getCFlow()->infoDestination() << endl;
        os << this->getCFlow()->infoOther() << endl;
        os << this->getCFlow()->infoQoS() << endl;
    }
    os << "Created at: " << this->getTimeCreated() << ", invId: " << this->getCFlow()->getAllocInvokeId() << endl
       << "Deleted at: " << this->getTimeDeleted() << ", invId: " << this->getCFlow()->getDeallocInvokeId() << endl;
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const NFlowTableEntry& fte) {
    return os << fte.info();
}

FAIBase* NFlowTableEntry::getFai() const {
    return fai;
}

const simtime_t& NFlowTableEntry::getTimeCreated() const {
return timeCreated;
}

const simtime_t& NFlowTableEntry::getTimeDeleted() const {
return timeDeleted;
}

std::string NFlowTableEntry::getAllocateStatusString() const {
    switch(this->allocStatus)
    {
        case ALLOC_PEND:        return "allocation pending";
        case TRANSFER:          return "allocation positive, transfer";
        case ALLOC_NEGA:        return "allocation negative";
        case ALLOC_ERR:         return "allocation error";
        case DEALLOC_PEND:      return "deallocation pending";
        case DEALLOCATED:       return "deallocated";
        case DEINST_PEND:       return "deinstantiation pending";
        case DEINSTANTIATED:    return "deinstantiated";
        case FORWARDING:        return "allocation forwarded";
        case FORWARDED:         return "allocation forwarded";
        default:                return "UNKNOWN";
    }
//    static std::string AllocateStatusStrings[] = {"Pending", "Allocation Positive", "Allocation Negative"};
//    return AllocateStatusStrings[];
}

void NFlowTableEntry::setAllocateStatus(EAllocateStatus allocateStatus) {
    this->allocStatus = allocateStatus;
}

void NFlowTableEntry::setTimeDeleted(const simtime_t& timDel) {
    this->timeDeleted = timDel;
}

void NFlowTableEntry::setFai(FAIBase* nfai) {
    this->fai = nfai;
}

const Flow* NFlowTableEntry::getCFlow() const {
    return flow;
}

bool NFlowTableEntry::operator ==(const NFlowTableEntry& other) const {
    return this->fai == other.fai
            && this->flow == other.flow
            && this->allocStatus == other.allocStatus
            && this->timeCreated == other.timeCreated;
}

NFlowTableEntry::EAllocateStatus NFlowTableEntry::getAllocateStatus() const {
    return allocStatus;
}

Flow* NFlowTableEntry::getFlow() {
    return flow;
}
