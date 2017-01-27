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

#ifndef QUEUEALLOCBASE_H_
#define QUEUEALLOCBASE_H_

#include <omnetpp.h>
#include "Common/Flow.h"
#include "DIF/RMT/RMTModuleAllocator.h"
#include "DIF/RMT/RMTPort.h"
#include "DIF/RA/RABase.h"
#include "DIF/RA/QueueIDGen/QueueIDGenBase.h"

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
