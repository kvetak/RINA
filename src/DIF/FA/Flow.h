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
#include <string>
#include <sstream>
//RINASim libraries
#include "APNamingInfo.h"
#include "ConnectionId.h"

const int UNDEFINED_PORTADDR = -1;
const int MAX_HOPCOUNT = 16;
const int MAX_CREATERETRIES = 3;

class Flow : public cObject, noncopyable
{
private:
    //Properties are based on RINA-Demo-2012-001.pdf page 6
    APNamingInfo srcApni;
    APNamingInfo dstApni;
    int srcPortId;
    int dstPortId;
    int srcAddr;
    int dstAddr;
    ConnectionId conId;
    uint32_t createFlowRetries;
    uint32_t maxCreateFlowRetries;
    uint32_t hopCount;

public:
    Flow();
    Flow(APNamingInfo src, APNamingInfo dst);
    virtual ~Flow();

    //TODO: VV - Completely missing overloading of ==, < and > operators

    bool operator== (const Flow& other) {
        return (srcApni == other.srcApni && dstApni == other.dstApni &&
                srcPortId == other.srcPortId && dstPortId == other.dstPortId &&
                srcAddr == other.srcAddr && dstAddr && other.dstAddr);
    }

    std::string info() const;

    const ConnectionId getConId() const {
        return conId;
    }
    void setConId(const ConnectionId conId) {
        this->conId = conId;
    }

    uint32_t getCreateFlowRetries() const {
        return createFlowRetries;
    }
    void setCreateFlowRetries(uint32_t createFlowRetries) {
        this->createFlowRetries = createFlowRetries;
    }

    uint64_t getDstAddr() const {
        return dstAddr;
    }
    void setDstAddr(uint64_t dstAddr) {
        this->dstAddr = dstAddr;
    }

    const APNamingInfo getDstApni() const {
        return dstApni;
    }
    void setDstApni(const APNamingInfo dstApni) {
        this->dstApni = dstApni;
    }

    uint32_t getHopCount() const {
        return hopCount;
    }
    void setHopCount(uint32_t hopCount) {
        this->hopCount = hopCount;
    }

    uint32_t getMaxCreateFlowRetries() const {
        return maxCreateFlowRetries;
    }
    void setMaxCreateFlowRetries(uint32_t maxCreateFlowRetries) {
        this->maxCreateFlowRetries = maxCreateFlowRetries;
    }

    uint64_t getSrcAddr() const {
        return srcAddr;
    }
    void setSrcAddr(int srcAddr) {
        this->srcAddr = srcAddr;
    }

    const APNamingInfo getSrcApni() const {
        return srcApni;
    }
    void setSrcApni(const APNamingInfo srcApni) {
        this->srcApni = srcApni;
    }

    uint64_t getDstPortId() const {
        return dstPortId;
    }
    void setDstPortId(int dstPortId) {
        this->dstPortId = dstPortId;
    }

    uint64_t getSrcPortId() const {
        return srcPortId;
    }
    void setSrcPortId(int srcPortId) {
        this->srcPortId = srcPortId;
    }
};

//Free function
std::ostream& operator<< (std::ostream& os, const Flow& fl);

#endif /* FLOW_H_ */
