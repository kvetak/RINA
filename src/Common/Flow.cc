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

#include "Common/Flow.h"

const int VAL_UNDEF_PORTID = -1;
const int VAL_MGMT_PORTID = 0;
const int VAL_MAXHOPCOUNT = 16;
const int VAL_MAXCREATERETRIES = 3;

Register_Class(Flow);

Flow::Flow() :
    srcApni(APNamingInfo()), dstApni(APNamingInfo()),
    srcPortId(VAL_UNDEF_PORTID), dstPortId(VAL_UNDEF_PORTID),
    srcAddr(Address()), dstAddr(Address()),
    srcNeighbor(Address()), dstNeighbor(Address()),
    conId(ConnectionId()),
    createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT),
    allocInvokeId(0), deallocInvokeId(0),
    ddtFlag(false)
{
}

Flow::Flow(APNamingInfo src, APNamingInfo dst) :
        srcApni(src), dstApni(dst),
        srcPortId(VAL_UNDEF_PORTID), dstPortId(VAL_UNDEF_PORTID),
        srcAddr(Address()), dstAddr(Address()),
        srcNeighbor(Address()), dstNeighbor(Address()),
        conId(ConnectionId()),
        createFlowRetries(0), maxCreateFlowRetries(VAL_MAXCREATERETRIES), hopCount(VAL_MAXHOPCOUNT),
        allocInvokeId(0), deallocInvokeId(0),
        ddtFlag(false)
{
}

Flow::~Flow() {
    this->srcApni = APNamingInfo();
    this->dstApni = APNamingInfo();
    this->srcPortId = 0;
    this->dstPortId = 0;
    this->srcAddr = Address();
    this->dstAddr = Address();
    this->createFlowRetries = 0;
    this->maxCreateFlowRetries = 0;
    this->hopCount = 0;
    srcNeighbor = Address();
    dstNeighbor = Address();
    allocInvokeId = 0;
    deallocInvokeId = 0;
    ddtFlag = false;
}

bool Flow::operator ==(const Flow& other) const {
    return (srcApni == other.srcApni && dstApni == other.dstApni
            && srcPortId == other.srcPortId && dstPortId == other.dstPortId
            && srcAddr == other.srcAddr && dstAddr == other.dstAddr
            && conId == other.conId
            && createFlowRetries == other.createFlowRetries && maxCreateFlowRetries == other.maxCreateFlowRetries
            && hopCount == other.hopCount
            && srcNeighbor == other.srcNeighbor && dstNeighbor == other.dstNeighbor
            //&& allocInvokeId == other.allocInvokeId && deallocInvokeId == other.deallocInvokeId
            && ddtFlag == other.ddtFlag
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


void Flow::setQosCube(const QoSCube& qosCube) {
    this->qosCube = qosCube;
}

const QoSCube& Flow::getQosCube() const {
    return qosCube;
}


const QoSReq& Flow::getQosRequirements() const {
    return qosReqs;
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
    flow->setQosCube(this->getQosCube());
    flow->setQosRequirements(this->getQosRequirements());
    flow->setSrcNeighbor(this->getSrcNeighbor());
    flow->setDstNeighbor(this->getDstNeighbor());
    flow->setAllocInvokeId(this->getAllocInvokeId());
    flow->setDeallocInvokeId(this->getDeallocInvokeId());
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
    os << "SRC> " << (isManagementFlowLocalToIPCP() ? "RIBd of ": "") << srcApni
       << "\n   address:  " << srcAddr
       << ", neighbor: " << srcNeighbor
       << "\n   port: " << srcPortId
       << "\n   cep: " << conId.getSrcCepId();
    return os.str();
}

std::string Flow::infoDestination() const {
    std::stringstream os;
    os << "DST> " << (isManagementFlowLocalToIPCP() ? "RIBd of ": "") << dstApni
       << "\n   address:  " << dstAddr
       << ", neighbor: " << dstNeighbor
       << "\n   port: " << dstPortId
       << "\n   cep: " << conId.getDstCepId();
    return os.str();
}

std::string Flow::infoOther() const {
    std::stringstream os;
    os << "Hop Count: " << hopCount << endl
       << "Retries: " << createFlowRetries << "/" << maxCreateFlowRetries << endl
       << "DDT: " << (ddtFlag ? "yes" : "no");
       //endl << "InvokeIds: allocate(" << allocInvokeId << ") deallocate(" << deallocInvokeId << ")";
    return os.str();
}

std::string Flow::infoQoS() const {
    std::stringstream os;
    os << "Chosen RA's QoS cube: " << conId.getQoSId();
    if (this->isManagementFlow() && !this->isManagementFlowLocalToIPCP())
    {
        os << " (aggregated)";
    }
    os << endl << qosReqs.info();
    return os.str();
}

bool Flow::compare(const Flow& other) const {
    return (srcApni == other.srcApni && dstApni == other.dstApni
            && srcPortId == other.srcPortId && dstPortId == other.dstPortId
            && srcAddr == other.srcAddr && dstAddr == other.dstAddr
            && conId == other.conId
            );
}

long Flow::getAllocInvokeId() const{
    return allocInvokeId;
}

void Flow::setAllocInvokeId(long allocInvokeId) {
    this->allocInvokeId = allocInvokeId;
}

long Flow::getDeallocInvokeId() const {
    return deallocInvokeId;
}

void Flow::setDeallocInvokeId(long deallocInvokeId) {
    this->deallocInvokeId = deallocInvokeId;
}

bool Flow::isDdtFlag() const {
    return ddtFlag;
}

void Flow::setDdtFlag(bool ddtFlag) {
    this->ddtFlag = ddtFlag;
}

QoSReq& Flow::getQosReqs() {
    return qosReqs;
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

void Flow::setQosRequirements(const QoSReq& qosParameters) {
    this->qosReqs = qosParameters;
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

Flow* Flow::dupToMgmt() const {
    Flow* mgmtflow = this->dup();
    mgmtflow->setQosRequirements(QoSReq::MANAGEMENT);
    mgmtflow->setSrcApni(getSrcAddr().getApn());
    mgmtflow->setDstApni(getDstNeighbor().getApn());
    mgmtflow->setDstAddr(getDstNeighbor().getApn());
    //EV << mgmtflow->info() << endl;
    return mgmtflow;
}

bool Flow::isManagementFlow() const {
    return getQosRequirements().compare(QoSReq::MANAGEMENT);
}

bool Flow::isManagementFlowLocalToIPCP() const {
    return isManagementFlow()
            && this->getSrcApni().getApn() == getSrcAddr().getApn()
            && this->getDstApni().getApn() == getDstAddr().getApn();
}
