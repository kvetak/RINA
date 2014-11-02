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

#include "FAITableEntry.h"

FAITableEntry::FAITableEntry() : fai(NULL), flow(NULL), allocStatus(this->UNKNOWN), timeCreated(0), timeLastActive(0) {

}

FAITableEntry::FAITableEntry(Flow* nflow): fai(NULL), allocStatus(this->UNKNOWN) {
    this->flow           = nflow;
    this->timeCreated    = simTime();
    this->timeLastActive = simTime();
}

FAITableEntry::FAITableEntry(FAIBase* nfai): flow(NULL), allocStatus(this->UNKNOWN) {
    this->fai            = nfai;
    this->timeCreated    = simTime();
    this->timeLastActive = simTime();
}

FAITableEntry::~FAITableEntry() {
    this->fai       = NULL;
    this->flow      = NULL;
    allocStatus     = this->UNKNOWN;
    timeCreated     = 0;
    timeLastActive  = 0;
}

std::string FAITableEntry::info() const {
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
    os << "Created at: " << this->getTimeCreated()
       << "\tLast active at: " << this->getTimeLastActive() << endl;
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const FAITableEntry& fte) {
    return os << fte.info();
}

FAIBase* FAITableEntry::getFai() const {
    return fai;
}

const simtime_t& FAITableEntry::getTimeCreated() const {
return timeCreated;
}

const simtime_t& FAITableEntry::getTimeLastActive() const {
return timeLastActive;
}

std::string FAITableEntry::getAllocateStatusString() const {
    switch(this->allocStatus)
    {
        case ALLOC_PEND:    return "allocation pending";
        case ALLOC_POSI:    return "allocation positive";
        case ALLOC_NEGA:    return "allocation negative";
        case ALLOC_ERR:     return "allocation error";
        case DEALLOC_PEND:  return "deallocation pending";
        case DEALLOCATED:   return "deallocated";
        case DEINST_PEND:   return "deinstantiation pending";
        case DEINSTANTIATED:return "deinstantiated";
        case FORWARDED:     return "allocation forwarded";
        default:            return "UNKNOWN";
    }
//    static std::string AllocateStatusStrings[] = {"Pending", "Allocation Positive", "Allocation Negative"};
//    return AllocateStatusStrings[];
}

void FAITableEntry::setAllocateStatus(AllocateStatus allocateStatus) {
    this->allocStatus = allocateStatus;
}

void FAITableEntry::setTimeLastActive(const simtime_t& timeLastActive) {
    this->timeLastActive = timeLastActive;
}

void FAITableEntry::setFai(FAIBase* nfai) {
    this->fai = nfai;
}

const Flow* FAITableEntry::getCFlow() const {
    return flow;
}

bool FAITableEntry::operator ==(const FAITableEntry& other) const {
    return this->fai == other.fai
            && this->flow == other.flow
            && this->allocStatus == other.allocStatus
            && this->timeCreated == other.timeCreated;
}

FAITableEntry::AllocateStatus FAITableEntry::getAllocateStatus() const {
    return allocStatus;
}

Flow* FAITableEntry::getFlow() {
    return flow;
}
