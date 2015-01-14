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

/**
 * @file PDUFwdTabGenerator.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz) and Kewin Rausch(kewin.rausch@create-net.org)
 * @brief PDU forwarding (routing) table generator.
 * @detail Responds to various events happening inside the IPC process
 *         by adding, removing and editing entries in the forwarding table.
 */

#ifndef __RINA_PDUFWDTABGENERATOR_H_
#define __RINA_PDUFWDTABGENERATOR_H_

// Comment this directive to disable private debugging.
// With private debugging all the output will be redirected to a text file.
//#define PDUFTG_PRIVATE_DEBUG

#ifdef PDUFTG_PRIVATE_DEBUG

#include <iostream>
#include <fstream>

extern std::ofstream pduftg_debug_file;

// Log a string as a debug information.
#define pduftg_debug(x)         pduftg_debug_file << x;

#else

// Log a string as a debug information.
#define pduftg_debug(x)         EV << x;

#endif

#include <omnetpp.h>

#include "ModuleAccess.h"
#include "ConnectionId.h"
#include "RMT.h"
#include "RINASignals.h"
#include "NM1FlowTable.h"
#include "PDUForwardingTable.h"
#include "PDUFTGListeners.h"
#include "PDUFTGPolicy.h"
#include "FSUpdateInfo.h"

typedef std::list<FSInfo *> NetworkState;
typedef NetworkState::iterator NIter;

// This is mapped as string --> port because Address do not have <, > operators overloads.
typedef std::list<PDUForwardingTableEntry *> NeighborState;
typedef NeighborState::iterator EIter;

// Generator of the forwarding informations.
//
class PDUFwdTabGenerator : public cSimpleModule
{
  private:

    // Signal to notify forwarding info update occurs.
    //
    simsignal_t sigPDUFTGFwdInfoUpdate;

    // Listener for forwarding information.
    //
    LisPDUFTGFwdInfoRecv * lisInfoRecv;

    // The actual active forwarding policy to use.
    //
    PDUFTGPolicy * fwdPolicy;

    // Contains the actual status of the network we're aware of.
    //
    NetworkState netState;

    // Contains the list of N-DIF neighbors of this IPC Address.
    //
    NeighborState neiState;

    // PDU Forwarding table module pointer(filled during initialization).
    //
    PDUForwardingTable* fwTable;

    // This table will allow us to get the right queue starting from the flow information.
    //
    NM1FlowTable * flTable;

    // The IP Address. We will use this to filter flow informations and collect
    // only those of the same DIF.
    //
    Address ipcAddr;

    // Will the network state be visible at upper levels?
    //
    bool showNetState;

    // The module where the report will be posted on.
    //
    cModule * nstm;

    // Gets a user friendly formatted network state report.
    //
    std::string prepareFriendlyNetState();

  protected:
    virtual void finish();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    // Initializes the necessary input/output mechanisms.
    void initializeSignalsAndListeners();

  public:

    //
    // Getters:
    //

    // Gets the managed instance of Forwarding table.
    PDUForwardingTable * getForwardingTable();

    // Gets the address associated with this IPC.
    Address getIpcAddress();

    // Gets the map of the current mapped neighbors.
    NeighborState * getNeighborhoodState();

    // Gets the actual network state known by us.
    NetworkState * getNetworkState();

    // Find the next known neighbor to reach the destination.
    PDUForwardingTableEntry * getNextNeighbor(Address destination, unsigned short qos);

    // Gets the managed instance of the N-1 flow table.
    NM1FlowTable * getNM1FlowTable();

    //
    // Network state actions:
    //

    // Insert a network state information.
    void insertNetInfo(Address dest, unsigned short qos, RMTPort * port, unsigned int metric);

    // Check if the info is already present into the owned one.
    FSInfo * netInfoExists(Address dest, unsigned short qos);

    // Returns the actual string formatted network info we have.
    std::string netInfo();

    // Removes a network state information.
    void removeNetInfo(FSInfo * info);

    //
    // Neighbors state actions:
    //

    // Insert a new neighbor.
    void insertNeighbor(Address addr, unsigned short qos, RMTPort * p);

    // Check if the neighbor desired exists.
    PDUForwardingTableEntry * neighborExists(Address src);

    // Returns the actual string formatted neighbor state.
    std::string neiInfo();

    // Removes a neighbor.
    void removeNeiInfo(Address addr);

    //
    // Policy plugin architecture:
    //

    // Publish a policy replacing the one actually in use.
    void publishPolicy(PDUFTGPolicy * p);

    // Removes the actual policy in use.
    void unpublishPolicy();

    //
    // Flow up/down operations:
    //

    // Inserts a new flow through which a neighbor can be reached.
    void insertFlowInfo(Address addr, unsigned short qos, RMTPort * port);

    // Removes an existing flow from the existing ones.
    void removeFlowInfo(RMTPort * port);

    //
    // Module signal emission:
    //

    // Signal to whoever listen for SIG_PDUFTG_FwdInfoUpdate event that an update
    // information must be handled.
    //
    void signalForwardingInfoUpdate(FSUpdateInfo * info);

    // Handle an incoming update message.
    void handleUpdateMessage(FSUpdateInfo * info);

    //
    // Debug only
    //

    // Bubble out a message on the selected network state report module.
    void reportBubbleInfo(const char * message);
};

#endif /* __RINA_PDUFWDTABGENERATOR_H_ */
