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
#include "FAI.h"

class FAITableEntry {
  public:
    enum AllocateStatus {UNKNOWN, ALLOC_PEND, ALLOC_POSI, ALLOC_NEGA, ALLOC_ERR, DEALLOC_PEND, DEALLOCATED, FORWARDED};

    FAITableEntry();
    FAITableEntry(Flow* nflow);
    FAITableEntry(FAI* nfai);
    virtual ~FAITableEntry();

    std::string info() const;
    std::string getAllocateStatusString() const;
    FAI* getFai() const;
    const simtime_t& getTimeCreated() const;
    const simtime_t& getTimeLastActive() const;
    void setTimeLastActive(const simtime_t& timeLastActive);
    AllocateStatus getAllocateStatus() const;
    void setAllocateStatus(AllocateStatus allocateStatus);
    void setFai(FAI* nfai);
    const Flow* getFlow() const;

  private:
    FAI* fai;
    Flow* flow;
    AllocateStatus allocStatus;
    simtime_t timeCreated;
    simtime_t timeLastActive;
};

//Free function
std::ostream& operator<< (std::ostream& os, const FAITableEntry& fte);

#endif /* FLOWTABLEENTRY_H_ */
