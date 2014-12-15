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

/* Author: Kewin Rausch (kewin.rausch@create-net.org) */

#ifndef __RINA_DISTANCEVECTORPOLICY_H
#define __RINA_DISTANCEVECTORPOLICY_H

#include <omnetpp.h>

#include "PDUFTGPolicy.h"

/* This implements a basic distance-vector routing policy.
 * The metric used is in term of hops.
 */
class DistanceVectorPolicy :
        public PDUFTGPolicy
{
private:

    /* Just prepare an update fo a destination host. */
    FSUpdateInfo * prepareFSUpdate(Address destination);

protected:

    void handleMessage(cMessage *msg);
    void initialize();

public:
    DistanceVectorPolicy();
    DistanceVectorPolicy(PDUFwdTabGenerator * generator);
    ~DistanceVectorPolicy();

    /* Computes the initial state of the forwarding table.
     */
    void computeForwardingTable();

    /* Gets a filtered network state that will be used to inform neighbors.
     * There will be one info per neighbor.
     */
    virtual std::list<FSUpdateInfo *> * getNetworkState();

    /* Insert a new flow which has been open locally to this IPC Process.
     */
    void insertNewFlow(Address addr, short unsigned int qos, RMTPort * port);

    /* Merge an incoming information with the existing ones.
     */
    void mergeForwardingInfo(FSUpdateInfo * info);

    /* Removes a local opened flow.
     */
    virtual void removeFlow(Address addr, short unsigned int qos);
};

#endif /* __RINA_DISTANCEVECTORPOLICY_H */
