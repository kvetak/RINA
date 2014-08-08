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

#include "Flow.h"

const int UNDEFINED_PORTADDR = -1;
const int MAX_HOPCOUNT = 16;
const int MAX_CREATERETRIES = 3;

Register_Class(Flow);

Flow::Flow() :
        srcPortId(UNDEFINED_PORTADDR), dstPortId(UNDEFINED_PORTADDR),
        srcAddr(UNDEFINED_PORTADDR), dstAddr(UNDEFINED_PORTADDR),
        createFlowRetries(0), maxCreateFlowRetries(MAX_CREATERETRIES), hopCount(MAX_HOPCOUNT) {
}

Flow::Flow(APNamingInfo src, APNamingInfo dst) :
        srcPortId(UNDEFINED_PORTADDR), dstPortId(UNDEFINED_PORTADDR),
        srcAddr(UNDEFINED_PORTADDR), dstAddr(UNDEFINED_PORTADDR),
        createFlowRetries(0), maxCreateFlowRetries(MAX_CREATERETRIES), hopCount(MAX_HOPCOUNT) {
    this->srcApni = src;
    this->dstApni = dst;
}

Flow::~Flow() {
    this->srcPortId = UNDEFINED_PORTADDR;
    this->dstPortId = UNDEFINED_PORTADDR;
    this->srcAddr = UNDEFINED_PORTADDR;
    this->dstAddr = UNDEFINED_PORTADDR;
    this->createFlowRetries = 0;
    this->maxCreateFlowRetries = 0;
    this->hopCount = 0;
}

std::string Flow::info() const {
    std::stringstream os;
    os << "SRC>\t" << srcApni <<  "\tport: " << srcPortId << "\taddr: " << srcAddr << "\n" <<
          "DST>\t" << dstApni <<  "\tport: " << dstPortId << "\taddr: " << dstAddr << "\n" <<
          "Hop Count: " << hopCount << "\n" <<
          "Retries: " << createFlowRetries << "/" << maxCreateFlowRetries;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const Flow& fl) {
    return os << fl.info();
}

bool Flow::operator ==(const Flow& other) {
    return (srcApni == other.srcApni && dstApni == other.dstApni &&
            srcPortId == other.srcPortId && dstPortId == other.dstPortId &&
            srcAddr == other.srcAddr && dstAddr && other.dstAddr);
}

const ConnectionId& Flow::getConId() const {
    return conId;
}

void Flow::setConId(const ConnectionId& conId) {
    this->conId = conId;
}

uint32_t Flow::getCreateFlowRetries() const {
    return createFlowRetries;
}

void Flow::setCreateFlowRetries(uint32_t createFlowRetries) {
    this->createFlowRetries = createFlowRetries;
}

int Flow::getDstAddr() const {
    return dstAddr;
}

void Flow::setDstAddr(int dstAddr) {
    this->dstAddr = dstAddr;
}

const APNamingInfo& Flow::getDstApni() const {
    return dstApni;
}

void Flow::setDstApni(const APNamingInfo& dstApni) {
    this->dstApni = dstApni;
}

int Flow::getDstPortId() const {
    return dstPortId;
}

void Flow::setDstPortId(int dstPortId) {
    this->dstPortId = dstPortId;
}

uint32_t Flow::getHopCount() const {
    return hopCount;
}

void Flow::setHopCount(uint32_t hopCount) {
    this->hopCount = hopCount;
}

uint32_t Flow::getMaxCreateFlowRetries() const {
    return maxCreateFlowRetries;
}

void Flow::setMaxCreateFlowRetries(uint32_t maxCreateFlowRetries) {
    this->maxCreateFlowRetries = maxCreateFlowRetries;
}

int Flow::getSrcAddr() const {
    return srcAddr;
}

void Flow::setSrcAddr(int srcAddr) {
    this->srcAddr = srcAddr;
}

const APNamingInfo& Flow::getSrcApni() const {
    return srcApni;
}

void Flow::setSrcApni(const APNamingInfo& srcApni) {
    this->srcApni = srcApni;
}

int Flow::getSrcPortId() const {
    return srcPortId;
}

void Flow::setSrcPortId(int srcPortId) {
    this->srcPortId = srcPortId;
}
