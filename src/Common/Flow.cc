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

const int VAL_UNDEF_PORTADDR = -1;
const int VAL_MAXHOPCOUNT = 16;
const int VAL_MAXCREATERETRIES = 3;

Register_Class(Flow);

Flow::Flow() :
        srcPortId(VAL_UNDEF_PORTADDR), dstPortId(VAL_UNDEF_PORTADDR),
        srcAddr(Address()), dstAddr(Address()),
        createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT) {
}

Flow::Flow(APNamingInfo src, APNamingInfo dst) :
        srcPortId(VAL_UNDEF_PORTADDR), dstPortId(VAL_UNDEF_PORTADDR),
        srcAddr(Address()), dstAddr(Address()),
        createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT) {
    this->srcApni = src;
    this->dstApni = dst;
}

Flow::~Flow() {
    this->srcPortId = VAL_UNDEF_PORTADDR;
    this->dstPortId = VAL_UNDEF_PORTADDR;
    this->srcAddr = Address();
    this->dstAddr = Address();
    this->createFlowRetries = 0;
    this->maxCreateFlowRetries = 0;
    this->hopCount = 0;
}

//Free function
bool Flow::operator ==(const Flow& other) {
    return (srcApni == other.srcApni && dstApni == other.dstApni &&
            srcPortId == other.srcPortId && dstPortId == other.dstPortId &&
            srcAddr == other.srcAddr && dstAddr == other.dstAddr);
}

ConnectionId& Flow::getConId() {
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

const Address& Flow::getDstAddr() const {
    return dstAddr;
}

void Flow::setDstAddr(const Address& dstAddr) {
    this->dstAddr = dstAddr;
}

const Address& Flow::getSrcAddr() const {
    return srcAddr;
}

void Flow::setSrcAddr(const Address& srcAddr) {
    this->srcAddr = srcAddr;
}

const QosCube& Flow::getQosParameters() const {
    return qosParameters;
}

Flow* Flow::dup() const {
    Flow* flow = new Flow();
    flow->setQosParameters(this->getQosParameters());
    flow->setSrcApni(this->getSrcApni());
    flow->setDstApni(this->getDstApni());
    return flow;
}

void Flow::setQosParameters(const QosCube& qosParameters) {
    this->qosParameters = qosParameters;
}

std::string Flow::info() const {
    std::stringstream os;
    os << "SRC>\t" << srcApni <<  "\tport: " << srcPortId << "\taddr: " << srcAddr << "\tcep:" << conId.getSrcCepId() << endl
       << "DST>\t" << dstApni <<  "\tport: " << dstPortId << "\taddr: " << dstAddr << "\tcep:" << conId.getDstCepId() << endl
       << "Hop Count: " << hopCount << endl
       << "Retries: " << createFlowRetries << "/" << maxCreateFlowRetries << endl
       <<  qosParameters;
    return os.str();
}

std::ostream& operator<< (std::ostream& os, const Flow& fl) {
    return os << fl.info();
}

