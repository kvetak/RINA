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

#ifndef FAITABLEENTRY_H_
#define FAITABLEENTRY_H_

//Standard libraries
#include <omnetpp.h>
#include <string>
//RINASim libraries
#include "FAIBase.h"

class FAITableEntry {
  public:
    enum AllocateStatus {UNKNOWN,
        ALLOC_PEND, ALLOC_POSI, ALLOC_NEGA, ALLOC_ERR,
        FORWARDED,
        DEALLOC_PEND, DEALLOCATED,
        DEINST_PEND, DEINSTANTIATED};

    FAITableEntry();
    FAITableEntry(Flow* nflow);
    FAITableEntry(FAIBase* nfai);
    virtual ~FAITableEntry();

    bool operator== (const FAITableEntry& other) const;

    std::string info() const;

    std::string getAllocateStatusString() const;
    FAIBase* getFai() const;
    const simtime_t& getTimeCreated() const;
    const simtime_t& getTimeLastActive() const;
    void setTimeLastActive(const simtime_t& timeLastActive);
    void setAllocateStatus(FAITableEntry::AllocateStatus allocateStatus);
    FAITableEntry::AllocateStatus getAllocateStatus() const;
    void setFai(FAIBase* nfai);
    const Flow* getCFlow() const;
    Flow* getFlow();

  private:
    FAIBase* fai;
    Flow* flow;
    AllocateStatus allocStatus;
    simtime_t timeCreated;
    simtime_t timeLastActive;
};

//Free function
std::ostream& operator<< (std::ostream& os, const FAITableEntry& fte);

#endif /* FLOWTABLEENTRY_H_ */
