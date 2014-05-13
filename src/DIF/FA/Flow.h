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

#ifndef FLOW_H_
#define FLOW_H_

//Standard libraries
#include <stdint.h>
//RINASim libraries
#include "APN.h"
#include "ConnectionId.h"

class Flow {
private:
    //Properties are based on RINA-Demo-2012-001.pdf page 6
    APN* srcApn;
    APN* dstApn;
    uint64_t srcPort;
    uint64_t dstPort;
    uint64_t srcAddr;
    uint64_t dstAddr;
    ConnectionId* conId;
    uint32_t maxCreateFlowRetries;
    uint32_t createFlowRetries;
    uint32_t hopCount;

public:
    Flow();
    Flow(APN* src, APN* dst);
    virtual ~Flow();

    //TODO: VV - Completely missing overloading of ==, < and > operators

    const ConnectionId* getConId() const;
    void setConId(ConnectionId* conId);
    uint32_t getCreateFlowRetries() const;
    void setCreateFlowRetries(uint32_t createFlowRetries);
    uint64_t getDstAddr() const;
    void setDstAddr(uint64_t dstAddr);
    const APN* getDstApn() const;
    void setDstApn(APN* dstApn);
    uint64_t getDstPort() const;
    void setDstPort(uint64_t dstPort);
    uint32_t getHopCount() const;
    void setHopCount(uint32_t hopCount);
    uint32_t getMaxCreateFlowRetries() const;
    void setMaxCreateFlowRetries(uint32_t maxCreateFlowRetries);
    uint64_t getSrcAddr() const;
    void setSrcAddr(uint64_t srcAddr);
    const APN* getSrcApn() const;
    void setSrcApn(APN* srcApn);
    uint64_t getSrcPort() const;
    void setSrcPort(uint64_t srcPort);
};

#endif /* FLOW_H_ */
