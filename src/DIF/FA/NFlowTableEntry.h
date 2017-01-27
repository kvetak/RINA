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

#ifndef FAITABLEENTRY_H_
#define FAITABLEENTRY_H_

//Standard libraries
#include <omnetpp.h>
#include <string>
//RINASim libraries
#include "DIF/FA/FAIBase.h"

class NFlowTableEntry {
  public:
    enum EAllocateStatus {UNKNOWN,
        ALLOC_PEND, ALLOC_NEGA, ALLOC_ERR,
        TRANSFER,
        FORWARDING, FORWARDED,
        DEALLOC_PEND, DEALLOCATED,
        DEINST_PEND, DEINSTANTIATED};

    NFlowTableEntry();
    NFlowTableEntry(Flow* nflow);
    virtual ~NFlowTableEntry();

    bool operator== (const NFlowTableEntry& other) const;

    std::string info() const;

    std::string getAllocateStatusString() const;
    FAIBase* getFai() const;
    const simtime_t& getTimeCreated() const;
    const simtime_t& getTimeDeleted() const;
    void setTimeDeleted(const simtime_t& timDel);
    void setAllocateStatus(NFlowTableEntry::EAllocateStatus allocateStatus);
    NFlowTableEntry::EAllocateStatus getAllocateStatus() const;
    void setFai(FAIBase* nfai);
    const Flow* getCFlow() const;
    Flow* getFlow();

  private:
    FAIBase* fai;
    Flow* flow;
    EAllocateStatus allocStatus;
    simtime_t timeCreated;
    simtime_t timeDeleted;
};

//Free function
std::ostream& operator<< (std::ostream& os, const NFlowTableEntry& fte);

#endif /* FLOWTABLEENTRY_H_ */
