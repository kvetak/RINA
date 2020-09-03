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

#include "EthShimDIF/RINArp/RINArp.h"

#include "Common/Utils.h"
#include "EthShimDIF/RINArp/RINArpPacket_m.h"

#include "inet/common/packet/Packet.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/VlanTag_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"


Define_Module(RINArp);
Register_Abstract_Class(RINArp::ArpNotification);

// Static signal entries
const simsignal_t RINArp::initiatedRINArpResolutionSignal =
    registerSignal("initiatedRINArpResolution");
const simsignal_t RINArp::completedRINArpResolutionSignal =
    registerSignal("completedRINArpResolution");
const simsignal_t RINArp::failedRINArpResolutionSignal = registerSignal("failedRINArpResolution");
const simsignal_t RINArp::sentRINArpReqSignal = registerSignal("sentRINArpReq");
const simsignal_t RINArp::sentRINArpReplySignal = registerSignal("sentRINArpReply");

RINArp::~RINArp()
{
    for (auto &elem : arpCache) {
        auto *entry = elem.second;
        cancelAndDelete(entry->timer);
        delete entry;
    }

    if (thisHost.second != nullptr)
        delete thisHost.second;
}

void RINArp::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == inet::INITSTAGE_LOCAL) {
        eth = getRINAModule<inet::InterfaceEntry *>(this, 1, {"eth"});

        retryTimeout = par("retryTimeout");
        retryCount = par("retryCount");
        cacheTimeout = par("cacheTimeout");

        WATCH(numResolutions);
        WATCH(numFailedResolutions);
        WATCH(numRequestsSent);
        WATCH(numRepliesSent);
    } else if (stage == inet::INITSTAGE_NETWORK_LAYER) {
        inet::registerService(inet::Protocol::arp, nullptr, gate("ifIn"));
        inet::registerProtocol(inet::Protocol::arp, gate("ifOut"), nullptr);
    }
}

bool RINArp::addStaticEntry(const inet::MacAddress &mac, const APN &apn)
{
    Enter_Method("addStaticEntry(%s, %s)", mac.str().c_str(), apn.c_str());

    ASSERT(!mac.isUnspecified());
    ASSERT(!apn.isUnspecified());

    // Is already in use
    if (!thisHost.first.isUnspecified())
        return false;

    auto *entry = new ArpCacheEntry();
    entry->macAddress = mac;
    entry->timer = nullptr;
    entry->lastUpdate = simTime();
    thisHost = std::make_pair(apn, entry);
    return true;
}

void RINArp::deleteStaticEntry()
{
    Enter_Method("deleteStaticEntry()");
    if (!thisHost.first.isUnspecified())
        thisHost.first.setName("");

    if (thisHost.second != nullptr) {
        auto *entry = thisHost.second;
        cancelAndDelete(entry->timer);
        entry->timer = nullptr;
        delete entry;
    }
}

void RINArp::setVlanId(int vlanId)
{
    this->vlanId = vlanId;
}

bool RINArp::addressRecognized(const APN &destApn)
{
    if (destApn == thisHost.first)
        return true;
    else
        return false;
}

void RINArp::flush()
{
    while (!arpCache.empty()) {
        auto i = arpCache.begin();
        auto *entry = i->second;
        cancelAndDelete(entry->timer);
        entry->timer = nullptr;
        delete entry;
        arpCache.erase(i);
    }
}

void RINArp::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
        requestTimeout(msg);
    else {
        auto *packet = check_and_cast<inet::Packet *>(msg);
        processArpPacket(packet);
    }
}

void RINArp::updateArpCache(ArpCacheEntry *entry, const inet::MacAddress &macAddress)
{
    if (entry->pending) {
        entry->pending = false;
        cancelAndDelete(entry->timer);
        entry->timer = nullptr;
        entry->numRetries = 0;
    }
    entry->macAddress = macAddress;
    entry->lastUpdate = simTime();
    ArpNotification signal(entry->myIter->first, macAddress);
    emit(completedRINArpResolutionSignal, &signal);
}

const inet::MacAddress &RINArp::resolveAddress(const APN &apn)
{
    Enter_Method("resolveAddress(%s)", apn.c_str());

    EV << "Asked to resolve destination address " << apn << endl;

    auto it = arpCache.find(apn);
    if (it == arpCache.end()) {
        // No ARP cache entry found, need to send ARP request
        auto *entry = new ArpCacheEntry();
        auto where = arpCache.insert(arpCache.begin(), std::make_pair(apn, entry));
        entry->myIter = where;
        initiateArpResolution(entry);
        return inet::MacAddress::UNSPECIFIED_ADDRESS;
    } else if (it->second->pending) {
        return inet::MacAddress::UNSPECIFIED_ADDRESS;
    } else if (it->second->lastUpdate + cacheTimeout >= simTime()) {
        return it->second->macAddress;
    }

    // If entry exists but has been timed out
    auto *entry = it->second;
    initiateArpResolution(entry);
    return inet::MacAddress::UNSPECIFIED_ADDRESS;
}

const APN &RINArp::getAddressFor(const inet::MacAddress &mac) const
{
    Enter_Method_Silent();

    if (mac.isUnspecified())
        return APN::UNSPECIFIED_APN;

    simtime_t now = simTime();
    for (const auto &elem : arpCache)
        if (elem.second->macAddress == mac && elem.second->lastUpdate + cacheTimeout >= now)
            return elem.first;

    return APN::UNSPECIFIED_APN;
}

void RINArp::initiateArpResolution(ArpCacheEntry *entry)
{
    const APN &apn = entry->myIter->first;
    entry->pending = true;
    entry->numRetries = 0;
    entry->lastUpdate = SIMTIME_ZERO;
    entry->macAddress = inet::MacAddress::UNSPECIFIED_ADDRESS;
    sendArpRequest(apn);

    cMessage *msg = entry->timer = new cMessage("ARP timeout");
    msg->setContextPointer(entry);
    scheduleAt(simTime() + retryTimeout, msg);

    numResolutions++;
    ArpNotification signal(apn, inet::MacAddress::UNSPECIFIED_ADDRESS);
    emit(initiatedRINArpResolutionSignal, &signal);
}

void RINArp::sendArpRequest(const APN &dstApn)
{
    const APN &srcApn = thisHost.first;  // Registered application
    const inet::MacAddress &srcMac = thisHost.second->macAddress;

    ASSERT(!srcMac.isUnspecified());
    ASSERT(!srcApn.isUnspecified());

    const int apnLen = std::max(srcApn.length(), dstApn.length());

    const auto &arp = inet::makeShared<RINArpPacket>();
    arp->setChunkLength(inet::B(ARP_BASE_LEN + apnLen * 2));
    arp->setApnLength(apnLen);

    arp->setOpcode(ARP_REQUEST);
    arp->setSrcMacAddress(srcMac);
    arp->setSrcApName(srcApn);
    arp->setDstApName(dstApn);

    inet::Packet *packet = new inet::Packet("arpREQ");
    packet->insertAtFront(arp);
    packet->addTag<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    packet->addTag<inet::InterfaceReq>()->setInterfaceId(eth->getInterfaceId());
    packet->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::arp);
    packet->addTag<inet::VlanReq>()->setVlanId(vlanId);

    EV_INFO << "Sending " << packet << " to network." << endl;
    send(packet, "ifOut");

    numRequestsSent++;
    emit(sentRINArpReqSignal, 1L);
}

void RINArp::processArpPacket(inet::Packet *packet)
{
    EV_INFO << "Received " << packet << " from network." << endl;
    const auto &arp = packet->peekAtFront<RINArpPacket>();

    const inet::MacAddress &srcMac = arp->getSrcMacAddress();
    const APN &srcApn = arp->getSrcApName();
    const APN &dstApn = arp->getDstApName();

    ASSERT(!srcMac.isUnspecified());
    ASSERT(!srcApn.isUnspecified());
    ASSERT(!dstApn.isUnspecified());

    EV_TRACE << arp << " has source MAC " << srcMac << " and APN " << srcApn << endl;

    bool mergeFlag = false;
    auto it = arpCache.find(srcApn);
    if (it != arpCache.end()) {
        ArpCacheEntry *entry = it->second;
        updateArpCache(entry, srcMac);
        mergeFlag = true;
    }

    if (addressRecognized(dstApn)) {
        if (!mergeFlag) {
            ArpCacheEntry *entry;
            if (it != arpCache.end()) {
                entry = it->second;
            } else {
                entry = new ArpCacheEntry();
                auto where = arpCache.insert(arpCache.begin(), std::make_pair(srcApn, entry));
                entry->myIter = where;
                entry->pending = false;
                entry->timer = nullptr;
                entry->numRetries = 0;
            }

            updateArpCache(entry, srcMac);
        }

        EV_TRACE << arp << " was for us! ";

        switch (arp->getOpcode()) {
        case ARP_REQUEST: {
            EV_TRACE << "Sending ARP reply with MAC destination: " << srcMac
                     << ", source: " << thisHost.second->macAddress << endl;

            const auto &arpReply = inet::makeShared<RINArpPacket>();
            // Protocol address length will remain the same. We need to
            // swap the addresses, however.
            arpReply->setChunkLength(arp->getChunkLength());
            arpReply->setApnLength(arp->getApnLength());
            arpReply->setDstMacAddress(srcMac);
            arpReply->setDstApName(srcApn);
            arpReply->setSrcMacAddress(thisHost.second->macAddress);
            arpReply->setSrcApName(dstApn);
            arpReply->setOpcode(ARP_REPLY);

            inet::Packet *outPacket = new inet::Packet("arpReply");
            outPacket->insertAtFront(arpReply);
            outPacket->addTag<inet::MacAddressReq>()->setDestAddress(srcMac);
            outPacket->addTag<inet::InterfaceReq>()->setInterfaceId(eth->getInterfaceId());
            outPacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::arp);
            outPacket->addTag<inet::VlanReq>()->setVlanId(vlanId);

            EV_INFO << "Sending " << outPacket << " to network protocol." << endl;
            send(outPacket, "ifOut");
            numRepliesSent++;
            emit(sentRINArpReplySignal, 1L);

            break;
        }
        case ARP_REPLY: {
            EV_DETAIL << "Discarding packet." << endl;
            break;
        }
        case ARP_RARP_REQUEST:
            throw cRuntimeError("RARP request received but not supported");
        case ARP_RARP_REPLY:
            throw cRuntimeError("RARP reply received but not supported");
        default:
            throw cRuntimeError(
                "Unsuported opcode %d from received Arp"
                " packet",
                arp->getOpcode());
        }
    } else {
        EV_INFO << "Address " << dstApn << " not recognized, "
                << "dropping packet." << endl;
    }

    delete packet;
}

void RINArp::requestTimeout(cMessage *selfmsg)
{
    auto *entry = (ArpCacheEntry *)selfmsg->getContextPointer();
    entry->numRetries++;
    if (entry->numRetries < retryCount) {
        const APN &dstApn = entry->myIter->first;
        EV_INFO << "ARP request for " << dstApn << " timed out, resending." << endl;
        sendArpRequest(dstApn);
        scheduleAt(simTime() + retryTimeout, selfmsg);
        return;
    }

    // If max retryCount hit
    delete selfmsg;

    EV << "ARP timed out with max retry count " << retryCount << " for destination address "
       << entry->myIter->first << endl;
    ArpNotification signal(entry->myIter->first, inet::MacAddress::UNSPECIFIED_ADDRESS);
    emit(failedRINArpResolutionSignal, &signal);
    arpCache.erase(entry->myIter);
    delete entry;
    numFailedResolutions++;
}
