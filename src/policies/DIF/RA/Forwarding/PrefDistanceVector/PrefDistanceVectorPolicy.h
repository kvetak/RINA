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

/* Author: Sergio Leon (gaixas1@gmail.com) */

#ifndef __RINA_PrefDistanceVectorPolicy_H
#define __RINA_PrefDistanceVectorPolicy_H

#include <omnetpp.h>
#include <map>
#include <set>

#include "PDUFTGPolicy.h"
#include "PrefixPDUForwardingTable.h"
#include "rtTab.h"


#define PDUFTG_SELFMSG_FSUPDATE     0x01
#define PDUFTG_SELFMSG_FSUPDATEFORCE     0x02

typedef std::pair<unsigned short, std::string> qosAddr;

struct addrInfo{
    bool parent;
    bool son;
    bool neighbour;
    std::string addr;
    std::string commonPrefix;
    unsigned char prefSize;
    std::string storedAddr;

    addrInfo(std::string _addr);
};

// This implements a basic distance-vector routing policy.
// The metric used is in term of hops.
//
class PrefDistanceVectorPolicy :
        public PDUFTGPolicy
{
protected:

    // Will the network state be visible at upper levels?
    //
    bool showNetState;

    // The module where the report will be posted on.
    //
    cModule * nstm;


    /* msec between updates. */
    unsigned int updateT;
    unsigned int updateFT;
    bool forcedUpdateProgramed;

    PrefixPDUForwardingTable * fwt;

    void handleMessage(cMessage *msg);
    void initialize();

    void finish();
    void ForceUpdate();

    std::string thisIPCAddr;
    std::string thisIPCAddrOPref;
    std::vector<std::string> thisIPCAddrParsed;
    std::string any;
    char delimiter;


    addrInfo parseAddr(std::string addr);
    std::map<std::string, std::set<unsigned short> > address2Qos;
    std::map<qosAddr, RMTPort* > qosAddr2Port;
    rtTab table;

    simtime_t lastUpdate;

    // Just prepare an update fo a destination host.
    PDUFTGUpdate * prepareFSUpdate(Address destination);

    void replaceOrRemoveFwtEntry(std::string dst, std::string nextH, unsigned short qos);

public:
    PrefDistanceVectorPolicy();
    ~PrefDistanceVectorPolicy();

    // Computes the initial state of the forwarding table.
    //
    void computeForwardingTable();

    // Evaluated in term of policy defined flow if a flow exists.
    //
    virtual PDUFTGInfo * flowExists(Address addr, unsigned short qos);
    virtual PDUFTGInfo * flowExists(std::string addr, unsigned short qos);

    /* Get the update timer actual tick value.
     */
    unsigned int getUpdateTimeout();
    unsigned int getForcedUpdateTimeout();

    // Insert a new flow which has been open locally to this IPC Process.
    //
    void insertNewFlow(Address addr, short unsigned int qos, RMTPort * port);

    // Merge an incoming information with the existing ones.
    //
    void mergeForwardingInfo(PDUFTGUpdate * info);

    // Removes a local opened flow.
    //
    virtual void removeFlow(std::string addr, short unsigned int qos);
    virtual void removeFlow(Address addr, unsigned short qos);

    /* Set a new timeout between an update message and another, in seconds.
     */
    void setUpdateTimeout(unsigned int sec);
    void setForcedUpdateTimeout(unsigned int sec);
};

#endif // __RINA_PrefDistanceVectorPolicy_H
