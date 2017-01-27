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

#ifndef RMTSCHEDULINGBASE_H_
#define RMTSCHEDULINGBASE_H_

#include <omnetpp.h>

#include "DIF/RMT/RMTPort.h"
#include "DIF/RMT/RMTQueue.h"
#include "DIF/RMT/RMTModuleAllocator.h"

/* FIXME: circular dependencies */
class RMTModuleAllocator;

/**
 * Noop base class for the RMT scheduling policy.
 * This policy is invoked each time some queue has data to send and uses some
 * algorithm to make a decision about which queues should be handled first.
 */
class RMTSchedulingBase : public cSimpleModule
{

  friend class RMTQMonitorBase; /* For access to scheduling policy variables. */

  public:

    /**
     * A hook method invoked on multiple occasions.
     * 1) A PDU arrives into a queue.
     * 2) An (N-1)-port becomes ready to serve.
     * 3) By self-postponed scheduler invocation.
     *
     * @param port the (N-1)-port
     * @param direction the direction of data flow (in/out)
     */
    virtual void processQueues(RMTPort* port, RMTQueueType direction);

  protected:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Method used for creating postponed Scheduler calls (e.g. for PDU spacing).
     *
     * @param simtime_t target simulation time
     * @param port (N-1)-port
     * @param direction direction that is to be processed
     */
    void scheduleReinvocation(simtime_t time, RMTPort* port, RMTQueueType direction);

    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     */
    void handleMessage(cMessage *msg);

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
};

#endif /* RMTSCHEDULINGBASE_H_ */
