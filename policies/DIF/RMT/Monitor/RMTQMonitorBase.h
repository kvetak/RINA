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

#ifndef RMTQMONITORBASE_H_
#define RMTQMONITORBASE_H_

#include <omnetpp.h>
#include "DIF/RMT/Scheduler/RMTSchedulingBase.h"
#include "DIF/RA/AddressComparator/AddressComparatorBase.h"
#include "DIF/RMT/RMTModuleAllocator.h"
#include "DIF/RMT/RMTQueue.h"
#include "Common/PDU.h"

/* FIXME: circular dependencies */
class RMTSchedulingBase;
class RMTModuleAllocator;

/**
 * Noop base class for the RMT monitoring policy.
 * This policy responds to various events happening inside RMT, usually by
 * modifying values used by the scheduling policy.
 */
class RMTQMonitorBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked after a PDU arrives into a queue.
     *
     * @param queue pointer to the queue
     */
    virtual void prePDUInsertion(RMTQueue* queue);

    /**
     * A hook method invoked after a PDU arrives into a queue.
     *
     * @param queue pointer to the queue
     */
    virtual void postPDUInsertion(RMTQueue* queue);

    /**
     * A hook method invoked before a PDU gets released from a queue & sent.
     *
     * @param queue pointer to the queue
     */
    virtual void prePDURelease(RMTQueue* queue);

    /**
     * A hook method invoked after a PDU gets released from a queue & sent.
     *
     * @param queue pointer to the queue
     */
    virtual void postPDURelease(RMTQueue* queue);

    /**
     * A hook method invoked after a PDU gets dropped from a queue.
     * Note: the PDU object is discarded after invocation of this method.
     *
     * @param queue pointer to the queue
     * @param pdu PDU being dropped
     */
    virtual void onMessageDrop(RMTQueue* queue, const cPacket* pdu);

    /**
     * A hook method invoked after a queue is created.
     *
     * @param queue pointer to the queue
     */
    virtual void postQueueCreation(RMTQueue* queue);

    /**
     * A hook method invoked before a queue is removed.
     *
     * @param queue pointer to the queue
     */
    virtual void preQueueRemoval(RMTQueue* queue);

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
     * Pointer to the RMT allocator module (also providing queue<->port mappings).
     */
    RMTModuleAllocator* rmtAllocator;

    /**
     * Pointer to a scheduling policy module.
     */
    RMTSchedulingBase* schedPolicy;

    /**
     * Pointer to an address comparator module.
     */
    AddressComparatorBase* addrComparator;

  private:

    /**
     *  Module initialization routine setting up parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    virtual void initialize();
};

#endif /* RMTQMONITORBASE_H_ */
