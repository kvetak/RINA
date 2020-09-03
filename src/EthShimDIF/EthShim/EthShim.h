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

#include "inet/common/InitStages.h"
#include "inet/common/Protocol.h"

// INET forward declarations (should be less overhead than including everything every time)
namespace inet {
    class Packet;
    class MacAddress;
    class InterfaceEntry;
};

class RINArp;
class RINArpPacket;
class ShimFA;
class SDUData;

/**
 * Implements the main element of the RINA Ethernet shim DIF
 */
class EthShim : public cSimpleModule, public cListener
{
  public:
    /// enum used for returning status of a create request
    enum class CreateResult { error, pending, completed };

    /// enum used for recording the state of a connection
    enum class ConnectionState {
        null,
        initiatorAllocatePending,
        recipientAllocatePending,
        allocated
    };

    /// Information required for connection with a remote system
    struct ConnectionEntry {
        ConnectionState state = ConnectionState::null;
        cGate *inGate = nullptr;
        cGate *outGate = nullptr;
        cPacketQueue outQueue = cPacketQueue("Queue for outgoing packets");
        cPacketQueue inQueue = cPacketQueue("Queue for incoming packets");
    };

    static const inet::Protocol rinaEthShim;
    static const int rinaEthShimProtocolId;

  private:
    /// map containing connection states with remote systems
    std::map<APN, ConnectionEntry> connections;

    /// State variable for whether an application is connected
    bool hasRegisteredApplication = false;

    /// VLAN ID to use for outgoing messages
    int vlanId;

    /// Pointers to important modules
    cModule *ipcProcess = nullptr;
    RINArp *arp = nullptr;
    ShimFA *shimFA = nullptr;
    inet::InterfaceEntry *eth = nullptr;

    /// Statistics
    long numSentToNetwork = 0;
    long numReceivedFromNetwork = 0;

  public:
    /** @brief Empty constructor for the time being */
    EthShim() = default;

    /**
     * @brief Registers name of the application using this shim IPCP in static ARP entry
     * @param  apn Name of registered application
     */
    void registerApplication(const APN &apn);

    /**
     * @brief Finalises a connection entry
     * @param  dstApn Name of application to be reached
     * @param  portId Port ID used as handle for registered application, used in gate names
     * @return true if the bindings were successfully created, false otherwise
     */
    [[nodiscard]] bool finalizeConnection(const APN &dstApn, int portId);

    /**
     * @brief Creates a connection state entry, and starts ARP resolution
     * @param  dstApn Name of application to be reached
     * @return CreateResult::completed if ARP returned an address immediately, ::pending if ARP
     *         resolution was initiated, and ::failed if a connection entry already exists
     */
    [[nodiscard]] CreateResult createEntry(const APN &dstApn);

    /**
     * @brief Deletes a connection entry
     * @param  dstApn Name of "connected" application
     */
    void deleteEntry(const APN &dstApn);

  private:
    /// cSimpleModule overrides

    /** @brief Initialises module pointers and subscribes to ARP signals */
    void initialize(int stage) override;
    int numInitStages() const override { return inet::NUM_INIT_STAGES; }

    /** @brief Passes packets to correct helper function based on input */
    void handleMessage(cMessage *msg) override;


    /// Initialisation

    /**
     * @brief Extracts VLAN ID from DIF name
     * @param  difName Name of DIF, to use as VLAN ID
     * @return VLAN ID as an integer, parsed from string
     */
    int extractVlanId(const std::string &difName);


    /// Packet handling

    /**
     * @brief Handles SDUs from upper layer, resolving gate to destination address
     * @param  sdu  SDU from upper layer
     * @param  gate Input gate that received sdu
     */
    void handleOutgoingSDU(SDUData *sdu, const cGate *gate);

    /**
     * @brief Handles SDU from network, resolving connection entry from source MAC Address
     * @param  sdu  SDU from ethernet interface
     */
    void handleIncomingSDU(inet::Packet *packet);

    /**
     * @brief Wraps an SDU in a `cPacketChunk` before sending it on to the Ethernet interface
     * @param  sdu    SDU to encapsulate and send
     * @param  dstMac MAC address of destination host
     */
    void sendSDUToNIC(SDUData *sdu, const inet::MacAddress &dstMac);

    /**
     * @brief Sends waiting SDUs in queue,
     * @param  srcApn The name of the application that the SDUs originated from
     */
    void sendWaitingIncomingSDUs(const APN &srcApn);


    /// Entry management

    /**
     * @brief Creates gates and bindings for an entry, and populates its gate pointers
     * @param  entry  Entry to create gates for
     * @param  portId Used as gate ID
     * @return true if gates were successfully created, false otherwise
     */
    [[nodiscard]] bool createBindingsForEntry(ConnectionEntry &entry, const int portId);

    /**
     * @brief Removes gates and bindings for an entry
     * @param  entry Entry to remove gates from
     */
    void removeBindingsForEntry(ConnectionEntry &entry);


    /// cListener overrides and ARP signal handlers

    /**
     * @brief Retrieves `ArpNotification` objects, passing them to correct helper function
     * @param  source  Source module of signal (unused)
     * @param  id      Id of signal, either completedRINArpResolution or failedRINArpResolution
     * @param  obj     ArpNotification object to be passed on
     * @param  details Unused
     */
    void receiveSignal(cComponent *source, simsignal_t id, cObject *obj, cObject *details) override;

    /**
     * @brief Sends waiting outgoing packets or finishes flow allocation, based on entry state
     * @param  entry Relevant connection entry
     * @param  apn   Destination application name associated with the connection entry
     * @param  mac   Destination MAC address of interface to reach
     */
    void arpResolutionCompleted(ConnectionEntry &entry,
                                const APN &apn,
                                const inet::MacAddress &mac);

    /**
     * @brief Handles a failed ARP resolve, removing connection entry and notifying Flow Allocator
     * @param  apn Destination application name associated with a connection entry to be removed
     */
    void arpResolutionFailed(const APN &apn);
};

std::ostream &operator<<(std::ostream &os, const EthShim::ConnectionState &connectionState);
std::ostream &operator<<(std::ostream &os, const EthShim::ConnectionEntry &connectionEntry);
