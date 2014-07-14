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

FAITableEntry::FAITableEntry() : fai(NULL), allocStatus(this->UKNOWN), timeCreated(0), timeLastActive(0) {

}

FAITableEntry::FAITableEntry(FAI* nfai): allocStatus(this->PENDING) {
    this->fai = nfai;
    this->timeCreated = simTime();
    this->timeLastActive= simTime();
}

FAITableEntry::~FAITableEntry() {
    this->fai = NULL;
    allocStatus = this->UKNOWN;
    timeCreated = 0;
    timeLastActive = 0;
}

std::string FAITableEntry::info() const {
    std::stringstream os;
    os << *(this->getFai()) << "\n" <<
          "status: " << this->getAllocateStatusString() <<
          "\tcreated: " << this->getTimeCreated() << "\tlastActive: " << this->getTimeLastActive() << "\n" <<
          *(this->getFai()->getFlow());
    return os.str();
}

std::ostream& operator <<(std::ostream& os, const FAITableEntry& fte) {
    return os << fte.info();
}

const FAI* FAITableEntry::getFai() const {
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
        case PENDING: return "pending";
        case ALLOC_POSI: return "allocation positive";
        case ALLOC_NEGA: return "allocation negative";
        default: return "UNKNOWN";

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
