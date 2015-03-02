//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef RMTMAXQBASE_H_
#define RMTMAXQBASE_H_

#include <omnetpp.h>

#include "RINASignals.h"
#include "RMTQueue.h"
#include "RMTQMonitorBase.h"
#include "AddressComparatorBase.h"
#include "RMTModuleAllocator.h"


/**
 * Noop base class for the RMT max queue policy.
 * This policy decides what to do when a queue is overflowing its threshold.
 */
class RMTMaxQBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked when a queue length is greater or equal to its threshold.
     * Makes a decision about whether to drop the arrived PDU.
     *
     * @param queue pointer to the queue
     * @return true if the PDU should be dropped, false otherwise
     */
    virtual bool run(RMTQueue* queue);

  protected:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     */
    virtual void handleMessage(cMessage* msg);

    /**
     * Send CDAP congestion notification to the PDU sender via RIBd.
     */
    void notifySenderOfCongestion(const cPacket* pdu);

    /**
     * Pointer to the monitoring policy module.
     */
    RMTQMonitorBase* qMonPolicy;

    /**
     * Pointer to an address comparator module.
     */
    AddressComparatorBase* addrComparator;

    /**
     * Pointer to the RMT allocator module (also providing queue<->port mappings).
     */
    RMTModuleAllocator* rmtAllocator;

  private:

    /**
     *  Module initialization routine setting up parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    void initialize();

    /**
     * Congestion notifier.
     */
    simsignal_t sigRMTSDReq;
};

#endif /* RMTMAXQBASE_H_ */
