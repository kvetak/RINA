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

#ifndef QUEUEALLOCBASE_H_
#define QUEUEALLOCBASE_H_

#include <omnetpp.h>
#include "Flow.h"
#include "RMTModuleAllocator.h"
#include "RMTPort.h"
#include "RABase.h"
#include "QueueIDGenBase.h"

/**
 * Noop base class for the RA queue allocation policy
 * The policy manages allocation and deallocation of RMT queues via hook methods.
 */
class QueueAllocBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * A hook method invoked when a new (N-1)-port is initiated.
     *
     * @param port pointer to the port
     */
    virtual void onNM1PortInit(RMTPort* port);

    /**
     * A hook method invoked when a new (N)-flow is established.
     *
     * @param flow (N)-flow object
     * @param port pointer to a port of the (N-1)-flow used by the flow's PDUs
     */
    virtual void onNFlowAlloc(RMTPort* port, Flow* flow);

    /**
     * A hook method invoked when an (N)-flow is deallocated.
     *
     * @param flow (N)-flow object
     * @param port pointer to a port of the (N-1)-flow used by the flow's PDUs
     */
    virtual void onNFlowDealloc(RMTPort* port, Flow* flow);

  protected:
    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     *
     * @param msg message
     */
    void handleMessage(cMessage *msg);

    /**
     * Pointer to a policy module used for generating queue IDs from flow and
     * message objects.
     */
    QueueIDGenBase* idGenerator;

    /**
     * Pointer to a module providing API for (de)allocation of ports and queues.
     */
    RMTModuleAllocator* rmtAllocator;

    /**
     * Pointer to the Resource Allocator module.
     */
    RABase* ra;

  private:
    /**
     *  Module initialization routine setting up some parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    void initialize();
};

#endif /* QUEUEALLOCBASE_H_ */
