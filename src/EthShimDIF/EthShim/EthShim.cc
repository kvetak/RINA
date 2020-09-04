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

#include "EthShimDIF/EthShim/EthShim.h"

#include <algorithm>

#include "Common/SDUData_m.h"
#include "Common/Utils.h"
#include "EthShimDIF/RINArp/RINArp.h"
#include "EthShimDIF/RINArp/RINArpPacket_m.h"
#include "EthShimDIF/ShimFA/ShimFA.h"

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/cPacketChunk.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/VlanTag_m.h"
#include "inet/networklayer/common/InterfaceEntry.h"


const inet::Protocol EthShim::rinaEthShim =
    inet::Protocol("rinaEthShim", "Ethernet shim layer for RINA");
const int EthShim::rinaEthShimProtocolId = 0xD1F0; // Ethernet shim DIF ethertype

Define_Module(EthShim);

void EthShim::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == inet::INITSTAGE_LOCAL) {
        ipcProcess = getParentModule();
        shimFA = getRINAModule<ShimFA *>(this, 1, {MOD_FLOWALLOC, MOD_FA});
        // TODO karlhto: maybe change, kind of a dirty way of doing this (use parameters instead?)
        arp = getRINAModule<RINArp *>(this, 1, {"arp"});
        eth = getRINAModule<inet::InterfaceEntry *>(this, 1, {"eth"});

        // For tidiness, this would normally be -1 which could lead to confusion.
        // TODO karlhto: consider setting to IPC address so that's used for something
        eth->setInterfaceId(0);

        arp->subscribe(RINArp::completedRINArpResolutionSignal, this);
        arp->subscribe(RINArp::failedRINArpResolutionSignal, this);

        vlanId = extractVlanId(ipcProcess->par("difName").stringValue());
        arp->setVlanId(vlanId);

        WATCH(numSentToNetwork);
        WATCH(numReceivedFromNetwork);
        WATCH_MAP(connections);
    } else if (stage == inet::INITSTAGE_NETWORK_LAYER) {
        // Register the RINA Ethernet shim DIF ethertype, necessary for the Ethernet Interface
        if (inet::ProtocolGroup::ethertype.findProtocol(rinaEthShimProtocolId) == nullptr)
            inet::ProtocolGroup::ethertype.addProtocol(rinaEthShimProtocolId, &rinaEthShim);

        // Configure the message dispatcher for lower layers
        inet::registerService(rinaEthShim, nullptr, gate("ifIn"));
        inet::registerProtocol(rinaEthShim, gate("ifOut"), nullptr);
    }
}

int EthShim::extractVlanId(const std::string &difName)
{
    int extractedVlanId = -1;

    try {
        std::string::size_type rest;
        int tmpId = std::stoi(difName, &rest, 10);
        if (rest < difName.length())
            throw std::invalid_argument("");

        // VLAN IDs 0 and 4095 (where 4095 is max, 2^12) are reserved
        if (tmpId < 1 || tmpId >= 4095)
            throw std::invalid_argument("");

        extractedVlanId = tmpId;
    } catch (std::invalid_argument) {
        throw cRuntimeError("DIF name for shim IPCP must be a valid VLAN ID, not: %s",
                            difName.c_str());
    }

    return extractedVlanId;
}

void EthShim::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("ifIn")) {
        EV_INFO << "Received " << msg << " from network." << endl;
        numReceivedFromNetwork++;
        auto *packet = check_and_cast<inet::Packet *>(msg);
        handleIncomingSDU(packet);
        delete packet;
    } else {
        EV_INFO << "Received PDU from upper layer" << endl;
        auto *sdu = check_and_cast<SDUData *>(msg);
        handleOutgoingSDU(sdu, sdu->getArrivalGate());
    }
}

void EthShim::handleOutgoingSDU(SDUData *sdu, const cGate *gate)
{
    EV_INFO << "Sending packet over ethernet" << endl;
    ASSERT(gate != nullptr);
    ASSERT(hasRegisteredApplication);

    auto iter = std::find_if(connections.begin(), connections.end(),
                             [gate](const auto &iter) { return iter.second.inGate == gate; });
    ASSERT(iter != connections.end());

    const APN &dstApn = iter->first;
    const inet::MacAddress &mac = arp->resolveAddress(dstApn);
    if (mac.isUnspecified()) {
        // This means that resolution has started
        ConnectionEntry &entry = iter->second;
        ASSERT(entry.state != ConnectionState::null);
        entry.outQueue.insert(sdu);
        return;
    }

    sendSDUToNIC(sdu, mac);
}

void EthShim::handleIncomingSDU(inet::Packet *packet)
{
    EV_INFO << "Passing SDU to correct gate" << endl;

    if (!hasRegisteredApplication) {
        EV_WARN << "Received an SDU, but no application is registered with this shim IPC Process."
                << " Discarding SDU." << endl;
        return;
    }

    const inet::MacAddress &srcMac = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    const APN &srcApn = arp->getAddressFor(srcMac);
    if (srcApn.isUnspecified()) {
        EV_WARN << "ARP does not have a valid entry for source MAC " << srcMac
                << ". Discarding SDU." << endl;
        return;
    }

    const auto &sduWrapper = packet->peekAtFront<inet::cPacketChunk>();

    // Duplication is required since a cPacketChunk is intended to be immutable. cPacketChunk will
    // handle deletion of the original cPacket.
    SDUData *sdu = check_and_cast<SDUData *>(sduWrapper->getPacket()->dup());

    EV_INFO << "SDU is from application with name " << srcApn << endl;

    auto &entry = connections[srcApn];
    if (entry.state == ConnectionState::null) {
        EV_INFO << "No connection entry with destination application name " << srcApn
                << ". Creating a new one and passing request to Flow Allocator." << endl;
        entry.state = ConnectionState::recipientAllocatePending;
        entry.inQueue.insert(sdu);
        shimFA->createUpperFlow(srcApn);
        return;
    }

    if (entry.state != ConnectionState::allocated) {
        EV_INFO << "Connection with application " << srcApn
                << " is still pending, SDU inserted into queue." << endl;
        entry.inQueue.insert(sdu);
        return;
    }

    EV_INFO << "Sending SDU to upper layer" << endl;
    send(sdu, entry.outGate);
}

void EthShim::sendSDUToNIC(SDUData *sdu, const inet::MacAddress &dstMac)
{
    EV_INFO << "Sending " << sdu << " to ethernet interface." << endl;

    // cPacketChunk for compatibility with the "old" OMNeT++ cPacket API, which RINA uses
    auto sduWrapper = inet::makeShared<inet::cPacketChunk>(sdu);
    inet::Packet *packet = new inet::Packet("SDUData");
    packet->insertAtFront(sduWrapper);
    packet->addTag<inet::MacAddressReq>()->setDestAddress(dstMac);
    packet->addTag<inet::InterfaceReq>()->setInterfaceId(eth->getInterfaceId());
    packet->addTag<inet::PacketProtocolTag>()->setProtocol(&rinaEthShim);
    packet->addTag<inet::VlanReq>()->setVlanId(vlanId);
    numSentToNetwork++;
    send(packet, "ifOut");
}

void EthShim::sendWaitingIncomingSDUs(const APN &srcApn)
{
    auto &entry = connections[srcApn];
    ASSERT(entry.state == ConnectionState::allocated);
    ASSERT(entry.outGate != nullptr);

    auto &queue = entry.inQueue;
    while (!queue.isEmpty()) {
        cPacket *sdu = queue.pop();
        send(sdu, entry.outGate);
    }
}

bool EthShim::createBindingsForEntry(ConnectionEntry &entry, const int portId)
{
    ASSERT(portId >= 0 && portId < ShimFA::MAX_PORTID);
    ASSERT(entry.state == ConnectionState::initiatorAllocatePending ||
           entry.state == ConnectionState::recipientAllocatePending);

    std::ostringstream gateName;
    gateName << GATE_NORTHIO_ << portId;
    const std::string &tmp = gateName.str();
    const char *gateStr = tmp.c_str();

    ASSERT(!hasGate(gateStr));

    addGate(gateStr, cGate::INOUT, false);
    cGate *shimIn = gateHalf(gateStr, cGate::INPUT);
    cGate *shimOut = gateHalf(gateStr, cGate::OUTPUT);

    // This gate should already be created
    if (!ipcProcess->hasGate(gateStr))
        ipcProcess->addGate(gateStr, cGate::INOUT, false);
    cGate *ipcDownIn = ipcProcess->gateHalf(gateStr, cGate::INPUT);
    cGate *ipcDownOut = ipcProcess->gateHalf(gateStr, cGate::OUTPUT);

    shimOut->connectTo(ipcDownOut);
    ipcDownIn->connectTo(shimIn);
    if (!shimOut->isConnected() || !shimIn->isConnected())
        return false;

    entry.inGate = shimIn;
    entry.outGate = shimOut;

    return true;
}

void EthShim::removeBindingsForEntry(ConnectionEntry &entry)
{
    if (entry.inGate == nullptr)
        return;

    const char *gate = entry.inGate->getBaseName();
    if (ipcProcess->hasGate(gate)) {
        cGate *ipcDownIn = ipcProcess->gateHalf(gate, cGate::INPUT);
        ipcDownIn->disconnect();
        entry.outGate->disconnect();
        ipcProcess->deleteGate(gate);
    }

    deleteGate(gate);
    entry.inGate = nullptr;
    entry.outGate = nullptr;
}

bool EthShim::finalizeConnection(const APN &dstApn, const int portId)
{
    Enter_Method("finalizeConnection(%s, %d)", dstApn.c_str(), portId);
    auto &entry = connections[dstApn];
    if (entry.state != ConnectionState::initiatorAllocatePending &&
        entry.state != ConnectionState::recipientAllocatePending) {
        EV_ERROR << "Connection entry for destination application with name " << dstApn
                 << " cannot be finalized since state is not pending. Current state is: "
                 << entry.state << endl;
        return false;
    }

    const bool isConnected = createBindingsForEntry(entry, portId);
    if (!isConnected) {
        EV_ERROR << "Bindings for entry with destination address " << dstApn
                 << " could not be created" << endl;
        deleteEntry(dstApn);
        return false;
    }

    entry.state = ConnectionState::allocated;
    sendWaitingIncomingSDUs(dstApn);
    return true;
}

EthShim::CreateResult EthShim::createEntry(const APN &dstApn)
{
    Enter_Method("createEntry(%s)", dstApn.c_str());
    auto &entry = connections[dstApn];
    if (entry.state != ConnectionState::null) {
        EV_ERROR << "ConnectionEntry already exists, something has probably gone wrong" << endl;
        return CreateResult::error;
    }

    entry.state = ConnectionState::initiatorAllocatePending;

    EV_INFO << "Initiating ARP resolution for destination address " << dstApn << endl;
    const auto &mac = arp->resolveAddress(dstApn);
    if (!mac.isUnspecified()) {
        EV_INFO << "ARP entry was found!" << endl;
        return CreateResult::completed;
    }

    return CreateResult::pending;
}

void EthShim::deleteEntry(const APN &dstApn)
{
    Enter_Method("deleteEntry(%s)", dstApn.c_str());
    auto &entry = connections[dstApn];
    if (entry.state == ConnectionState::null)
        return;

    removeBindingsForEntry(entry);

    // Destructor of cPacketQueue will handle deletion of cPackets
    connections.erase(dstApn);
}

void EthShim::registerApplication(const APN &apni)
{
    Enter_Method("registerApplication(%s)", apni.c_str());
    EV_INFO << "Received request to register application name " << apni << " with Arp module."
            << endl;

    inet::MacAddress mac = eth->getMacAddress();
    arp->addStaticEntry(mac, apni);
    hasRegisteredApplication = true;
}

void EthShim::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail)
{
    RINArp::ArpNotification *notification = check_and_cast<RINArp::ArpNotification *>(obj);

    const APN &apn = notification->getApName();
    const inet::MacAddress &mac = notification->getMacAddress();
    auto &entry = connections[apn];
    if (entry.state == ConnectionState::null ||
        entry.state == ConnectionState::recipientAllocatePending)
        return;

    if (id == RINArp::completedRINArpResolutionSignal)
        arpResolutionCompleted(entry, apn, mac);
    else if (id == RINArp::failedRINArpResolutionSignal)
        arpResolutionFailed(apn);
    else
        throw cRuntimeError("Unsubscribed signalID triggered receiveSignal");

    // Unused
    (void)src;
    (void)detail;
}

void EthShim::arpResolutionCompleted(ConnectionEntry &entry,
                                     const APN &apn,
                                     const inet::MacAddress &mac)
{
    Enter_Method("arpResolutionCompleted(%s -> %s)", apn.c_str(), mac.str().c_str());

    if (entry.state == ConnectionState::initiatorAllocatePending) {
        shimFA->completedAddressResolution(apn);
        return;
    }

    auto &queue = entry.outQueue;
    while (!queue.isEmpty()) {
        SDUData *sdu = check_and_cast<SDUData *>(queue.pop());
        sendSDUToNIC(sdu, mac);
    }
}

void EthShim::arpResolutionFailed(const APN &apn)
{
    Enter_Method("arpResolutionFailed(%s -> null)", apn.c_str());

    // 1. Erase connection
    deleteEntry(apn);

    // 2. Tell ShimFA, which should tell N+1 (or maybe we should let shimFA handle entry deletion?
    shimFA->failedAddressResolution(apn);
}

std::ostream &operator<<(std::ostream &os, const EthShim::ConnectionState &connectionState)
{
    // No default case so warning will be supplied if this switch is not exhaustive
    switch (connectionState) {
    case EthShim::ConnectionState::null:
        os << "NULL";
        break;
    case EthShim::ConnectionState::initiatorAllocatePending:
        os << "INITIATOR ALLOCATE PENDING";
        break;
    case EthShim::ConnectionState::recipientAllocatePending:
        os << "RECIPIENT ALLOCATE PENDING";
        break;
    case EthShim::ConnectionState::allocated:
        os << "ALLOCATED";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const EthShim::ConnectionEntry &connectionEntry)
{
    os << "State: " << connectionEntry.state;
    os << ", Gate: ";
    if (connectionEntry.inGate != nullptr)
        os << connectionEntry.inGate->getBaseName();
    else
        os << "undefined";
    os << ", In-queue size: " << connectionEntry.inQueue.getLength();
    os << ", Out-queue size: " << connectionEntry.outQueue.getLength();
    return os;
}
