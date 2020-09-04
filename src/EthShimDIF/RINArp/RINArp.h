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

#pragma once

#include <omnetpp.h>

#include "Common/APN.h"

#include "inet/linklayer/common/MacAddress.h"

namespace inet {
    class Packet;
    class InterfaceEntry;
};

class RINArpPacket;

/**
 * RINArp
 *
 * This module is more or less a RINA-specific version of the ARP
 * implementation done in INET.
 */
class RINArp : public cSimpleModule
{
  public:
    struct ArpCacheEntry;
    using ArpCache = std::map<APN, ArpCacheEntry *>;

    /**
     * Used for resolving path for APNs
     */
    struct ArpCacheEntry
    {
        inet::MacAddress macAddress;
        bool pending = false;
        simtime_t lastUpdate;
        int numRetries = 0;
        cMessage *timer = nullptr;
        ArpCache::iterator myIter;
    };

    /**
     * Notifications for changes in ARP, like a completed ARP resolution
     */
    class ArpNotification : public cObject
    {
      private:
        const APN apName;
        const inet::MacAddress macAddress;

      public:
        ArpNotification(const APN &apName, const inet::MacAddress &macAddress)
            : apName(apName), macAddress(macAddress)
        {
        }

        [[nodiscard]] const APN &getApName() const { return apName; }
        [[nodiscard]] const inet::MacAddress &getMacAddress() const { return macAddress; }
    };

    /** @brief Signals for publishing ARP state changes */
    static const simsignal_t initiatedRINArpResolutionSignal;
    static const simsignal_t completedRINArpResolutionSignal;
    static const simsignal_t failedRINArpResolutionSignal;
    static const simsignal_t sentRINArpReqSignal;
    static const simsignal_t sentRINArpReplySignal;

  private:
    /// Retry settings for ARP cache entries
    simtime_t retryTimeout;
    int retryCount = 0;

    /// ID of VLAN to use for ougtoing packets
    int vlanId;

    /// Some watchable numbers
    long numResolutions = 0;
    long numFailedResolutions = 0;
    long numRequestsSent = 0;
    long numRepliesSent = 0;

    /// How long an ARP entry should stay in cache
    simtime_t cacheTimeout;

    /// ARP cache entries
    ArpCache arpCache;
    std::pair<APN, ArpCacheEntry *> thisHost;  ///< Naming information for this host

    /// Bound Ethernet interface
    inet::InterfaceEntry *eth;

  public:
    RINArp() = default;
    ~RINArp() override;

    /** @brief Attempts to resolve an application name, may send ARP_REQ packet */
    const inet::MacAddress &resolveAddress(const APN &apn);

    /** @brief Finds the APN name of an entry by its MAC address */
    const APN &getAddressFor(const inet::MacAddress &mac) const;

    /** @brief Adds this host's information, necessary for N+1 registration */
    bool addStaticEntry(const inet::MacAddress &mac, const APN &apn);

    /** @brief Removes static entry for connected host */
    void deleteStaticEntry();

    /** @brief Sets VLAN ID for outgoing messages */
    void setVlanId(int vlanId);

  protected:
    /** @brief Processes ARP packets, adds entry if destination is same as apname */
    void processArpPacket(inet::Packet *packet);

    /** @brief Handles timeout selfmessages */
    void requestTimeout(cMessage *msg);

    /** @brief Removes all entries of ARP cache */
    void flush();

    /** @brief Readies pending entry, sends ARP_REQ, and starts timeout timer */
    void initiateArpResolution(ArpCacheEntry *entry);

    /** @brief Updates an ARP cache entry with an address */
    void updateArpCache(ArpCacheEntry *entry, const inet::MacAddress &mac);

    /** @brief Checks if specified APN is same as in static entry */
    bool addressRecognized(const APN &apn);

    /** @brief Sends an ARP request addressed to specified APN */
    void sendArpRequest(const APN &apn);


    /// cSimpleModule overrides

    /** @brief Initialises parameters and out gate */
    void initialize(int stage) override;
    int numInitStages() const override { return inet::NUM_INIT_STAGES; }

    /** @brief Handles selfmessages and messages from ethernet shim module */
    void handleMessage(cMessage *msg) override;
};
