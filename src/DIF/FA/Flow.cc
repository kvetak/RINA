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

#include <Flow.h>

Flow::Flow() {

}

Flow::Flow(APN* src, APN* dst) {
    this->srcApn = src;
    this->dstApn = dst;
}

Flow::~Flow() {

}

const ConnectionId* Flow::getConId() const {
    return conId;
}

void Flow::setConId(ConnectionId* conId) {
    this->conId = conId;
}

uint32_t Flow::getCreateFlowRetries() const {
    return createFlowRetries;
}

void Flow::setCreateFlowRetries(uint32_t createFlowRetries) {
    this->createFlowRetries = createFlowRetries;
}

uint64_t Flow::getDstAddr() const {
    return dstAddr;
}

void Flow::setDstAddr(uint64_t dstAddr) {
    this->dstAddr = dstAddr;
}

const APN* Flow::getDstApn() const {
    return dstApn;
}

void Flow::setDstApn(APN* dstApn) {
    this->dstApn = dstApn;
}

uint64_t Flow::getDstPort() const {
    return dstPort;
}

void Flow::setDstPort(uint64_t dstPort) {
    this->dstPort = dstPort;
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

uint64_t Flow::getSrcAddr() const {
    return srcAddr;
}

void Flow::setSrcAddr(uint64_t srcAddr) {
    this->srcAddr = srcAddr;
}

const APN* Flow::getSrcApn() const {
    return srcApn;
}

void Flow::setSrcApn(APN* srcApn) {
    this->srcApn = srcApn;
}

uint64_t Flow::getSrcPort() const {
    return srcPort;
}

void Flow::setSrcPort(uint64_t srcPort) {
    this->srcPort = srcPort;
}



