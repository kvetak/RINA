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

const int VAL_UNDEFINED = -1;
const int VAL_MAXHOPCOUNT = 16;
const int VAL_MAXCREATERETRIES = 3;

Register_Class(Flow);

Flow::Flow() :
    srcApni(APNamingInfo()), dstApni(APNamingInfo()),
    srcPortId(VAL_UNDEFINED), dstPortId(VAL_UNDEFINED),
    srcAddr(Address()), dstAddr(Address()),
    srcNeighbor(Address()), dstNeighbor(Address()),
    conId(ConnectionId()),
    createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT) {
}

Flow::Flow(APNamingInfo src, APNamingInfo dst) :
        srcApni(src), dstApni(dst),
        srcPortId(VAL_UNDEFINED), dstPortId(VAL_UNDEFINED),
        srcAddr(Address()), dstAddr(Address()),
        srcNeighbor(Address()), dstNeighbor(Address()),
        conId(ConnectionId()),
        createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT)
{
}

Flow::~Flow() {
    this->srcApni = APNamingInfo();
    this->dstApni = APNamingInfo();
    this->srcPortId = VAL_UNDEFINED;
    this->dstPortId = VAL_UNDEFINED;
    this->srcAddr = Address();
    this->dstAddr = Address();
    this->createFlowRetries = VAL_UNDEFINED;
    this->maxCreateFlowRetries = VAL_UNDEFINED;
    this->hopCount = VAL_UNDEFINED;
    srcNeighbor = Address();
    dstNeighbor = Address();
}

bool Flow::operator ==(const Flow& other) const {
    return (srcApni == other.srcApni && dstApni == other.dstApni
            && srcPortId == other.srcPortId && dstPortId == other.dstPortId
            && srcAddr == other.srcAddr && dstAddr == other.dstAddr
            && conId == other.conId
            && createFlowRetries == other.createFlowRetries && maxCreateFlowRetries == other.maxCreateFlowRetries
            && hopCount == other.hopCount
            && srcNeighbor == other.srcNeighbor && dstNeighbor == other.dstNeighbor
            );
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

const QoSCube& Flow::getQosParameters() const {
    return qosParameters;
}

Flow* Flow::dup() const {
    Flow* flow = new Flow();
    flow->setSrcApni(this->getSrcApni());
    flow->setDstApni(this->getDstApni());
    flow->setSrcAddr(this->getSrcAddr());
    flow->setDstAddr(this->getDstAddr());
    flow->setSrcPortId(this->getSrcPortId());
    flow->setDstPortId(this->getDstPortId());
    flow->setConId(this->getConId());
    flow->setMaxCreateFlowRetries(this->getMaxCreateFlowRetries());
    flow->setHopCount(this->getHopCount());
    flow->setCreateFlowRetries(this->getCreateFlowRetries());
    flow->setQosParameters(this->getQosParameters());
    flow->setSrcNeighbor(this->getSrcNeighbor());
    flow->setDstNeighbor(this->getDstNeighbor());
    return flow;
}

std::string Flow::getFlowName() const {
    std::stringstream os;
    os << srcApni << "<=>" << dstApni;
    return os.str();
}

ConnectionId& Flow::getConnectionId() {
    return conId;
}

void Flow::swapPortIds() {
    int tmp = srcPortId;
    srcPortId = dstPortId;
    dstPortId = tmp;
}

void Flow::swapAddresses() {
    Address tmpa = srcAddr;
    srcAddr = dstAddr;
    dstAddr = tmpa;
}

void Flow::swapCepIds() {
    conId = conId.swapCepIds();
}

std::string Flow::infoSource() const {
    std::stringstream os;
    os << "SRC> " << srcApni
       << "\n   address:  " << srcAddr
       << "\n   neighbor: " << srcNeighbor
       << "\n   port: " << srcPortId
       << "\n   cep: " << conId.getSrcCepId();
    return os.str();
}

std::string Flow::infoDestination() const {
    std::stringstream os;
    os << "DST> " << dstApni
       << "\n   address:  " << dstAddr
       << "\n   neighbor: " << dstNeighbor
       << "\n   port: " << dstPortId
       << "\n   cep: " << conId.getDstCepId();
    return os.str();
}

std::string Flow::infoOther() const {
    std::stringstream os;
    os << "Hop Count: " << hopCount << endl
       << "Retries: " << createFlowRetries << "/" << maxCreateFlowRetries;
    return os.str();
}

std::string Flow::infoQoS() const {
    std::stringstream os;
    os << "Chosen RA's QoS cube>" << conId.getQoSId();
    //os << qosParameters.info();
    return os.str();
}

bool Flow::compare(const Flow& other) const {
    return (srcApni == other.srcApni && dstApni == other.dstApni
            && srcPortId == other.srcPortId && dstPortId == other.dstPortId
            && srcAddr == other.srcAddr && dstAddr == other.dstAddr
            && conId == other.conId
            );
}

void Flow::swapApni() {
    APNamingInfo tmpapni = srcApni;
    srcApni = dstApni;
    dstApni = tmpapni;
}

Flow& Flow::swapFlow() {
    swapApni();

    swapAddresses();

    swapPortIds();

    swapCepIds();

    return *this;
}

void Flow::setQosParameters(const QoSCube& qosParameters) {
    this->qosParameters = qosParameters;
}

std::string Flow::info() const {
    std::stringstream os;
    os << infoSource() << endl;
    os << infoDestination() << endl;
    os << infoOther() << endl;
    os << infoQoS() << endl;
    return os.str();
}

std::ostream& operator<< (std::ostream& os, const Flow& fl) {
    return os << fl.info();
}

const Address& Flow::getDstNeighbor() const {
    return dstNeighbor;
}

void Flow::setDstNeighbor(const Address& dstNeighbor) {
    this->dstNeighbor = dstNeighbor;
}

const Address& Flow::getSrcNeighbor() const {
    return srcNeighbor;
}

void Flow::setSrcNeighbor(const Address& srcNeighbor) {
    this->srcNeighbor = srcNeighbor;
}
