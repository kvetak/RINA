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

#include <omnetpp.h>

#include "ModuleAccess.h"
#include "ConnectionId.h"
#include "RMT.h"
#include "RINASignals.h"
#include "FlowTable.h"
#include "PDUForwardingTable.h"
#include "PDUFTGListeners.h"
#include "PDUFTGPolicy.h"
#include "FSUpdateInfo.h"

#define PDUFTG_SELFMSG_FSINIT       0x01
#define PDUFTG_SELFMSG_FSUPDATE     0x02

typedef std::list<FSInfo *> NetworkState;
typedef NetworkState::iterator NIter;

/* This is mapped as string --> port because Address do not have <, > operators overloads. */
typedef std::list<PDUForwardingTableEntry *> NeighborState;
typedef NeighborState::iterator EIter;

/* Generator of the forwarding informations.
 */
class PDUFwdTabGenerator : public cSimpleModule
{
  private:
    /* Signal to notify forwarding info update occurs.
     */
    simsignal_t sigPDUFTGFwdInfoUpdate;

    /* Listener for forwarding information.
     */
    LisPDUFTGFwdInfoRecv * lisInfoRecv;

    /* The actual active forwarding policy to use.
     */
    PDUFTGPolicy * fwdPolicy;

    /* Contains the actual status of the network we're aware of.
     */
    NetworkState netState;

    /* Contains the list of N-DIF neighbors of this IPC Address.
     */
    NeighborState neiState;

    /* PDU Forwarding table module pointer(filled during initialization).
     */
    PDUForwardingTable* fwTable;

    /* This table will allow us to get the right queue starting from the flow information. */
    FlowTable * flTable;

    /* The IP Address. We will use this to filter flow informations and collect
     * only those of the same DIF.
     */
    Address ipcAddr;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    /* Initializes the necessary input/output mechanisms. */
    void initializeSignalsAndListeners();

  public:

    /*
     * Getters:
     */

    /* Gets the map of the current mapped neighbors. */
    NeighborState * getNeighborhoodState();

    /* Gets the actual network state known by us. */
    NetworkState * getNetworkState();

    /* Gets the managed instance of Forwarding table. */
    PDUForwardingTable * getForwardingTable();

    /* Gets the address associated with this IPC. */
    Address * getIpcAddress();

    /*
     * Network state actions:
     */

    /* Insert a network state information. */
    void insertNetInfo(Address dest, short unsigned int qos, RMTPort * port, unsigned int metric);

    /* Check if the info is already present into the owned one. */
    FSInfo * netInfoExists(Address src, Address dest, short unsigned int qos);

    /* Prints the actual network info we have. */
    std::string netInfo();

    /* Removes a network state information. */
    void removeNetInfo(FSInfo * info);

    /*
     * Neighbors state actions:
     */

    /* Insert a new neighbor. */
    void insertNeighbor(Address addr, short unsigned qos, RMTPort * p);

    /* Check if the neighbor desired exists. */
    PDUForwardingTableEntry * neighborExists(Address src);

    /* Prints the actual neighbor state. */
    std::string neiInfo();

    /* Removes a neighbor. */
    void removeNeiInfo(Address addr);

    /*
     * Policy plugin architecture:
     */

    /* Publish a policy replacing the one actually in use. */
    void publishPolicy(PDUFTGPolicy * p);

    /* Removes the actual policy in use. */
    void unpublishPolicy();

    /*
     * Flow up/down operations:
     */

    /* Inserts a new flow through which a neighbor can be reached. */
    void insertFlowInfo(Address addr, short unsigned int qos, RMTPort * port);

    /* Removes an existing flow from the existing ones. */
    //void removeFlowInfo(RMTPort * p);

    /* Handle an incoming update message. */
    void handleUpdateMessage(FSUpdateInfo * info);

    /*
     * Module signal emission:
     */

    /* Signal to whoever listen for SIG_PDUFTG_FwdInfoUpdate event that an update
     * information must be handled.
     */
    void signalForwardingInfoUpdate(FSUpdateInfo * info);

};

#endif /* __RINA_PDUFWDTABGENERATOR_H_ */
