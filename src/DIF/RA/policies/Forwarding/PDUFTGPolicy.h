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

#ifndef __RINA_PDUFTGPOLICY_H
#define __RINA_PDUFTGPOLICY_H

#include <omnetpp.h>

#include "Flow.h"
#include "RMTPort.h"
#include "FSUpdateInfo.h"

/* Forwarding declaration. */
class PDUFwdTabGenerator;

/* Provides a base class for every policy used in the PDUFTG module.
 */
class PDUFTGPolicy :
        public cSimpleModule
{
private:

protected:
    /* msec between updates. */
    unsigned int updateT = 0;

    PDUFwdTabGenerator * fwdtg;

    void handleMessage(cMessage *msg);
    void initialize();

public:
    PDUFTGPolicy();
    PDUFTGPolicy(PDUFwdTabGenerator * generator);
    ~PDUFTGPolicy();

    /* Computes the initial state of the forwarding table.
     */
    virtual void computeForwardingTable();

    /* Gets a filtered network state that will be used to inform neighbors.
     * There will be one info per neighbor.
     */
    virtual std::list<FSUpdateInfo *> * getNetworkState();

    /* Gets the update timeout.
     */
    unsigned int getUpdateTimeout();

    /* Insert a new flow which has been open locally to this IPC Process.
     */
    virtual void insertNewFlow(Address addr, short unsigned int qos, RMTPort * port);

    /* Merge an incoming information with the existing ones.
     */
    virtual void mergeForwardingInfo(FSUpdateInfo * info);

    /* Removes a local opened flow.
     */
    virtual void removeFlow(Address addr, short unsigned int qos);

    /* Set a new timeout between an update message and another.
     */
    void setUpdateTimeout(unsigned int time);
};

#endif /* __PDUFTGPOLICY_H */
