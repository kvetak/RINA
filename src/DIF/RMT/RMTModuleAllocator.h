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

#ifndef __RINA_RMTMODULEALLOCATOR_H_
#define __RINA_RMTMODULEALLOCATOR_H_

#include <omnetpp.h>

#include "Common/Utils.h"
#include "Common/ExternConsts.h"
#include "DIF/RMT/RMTQueue.h"
#include "DIF/RMT/RMTPort.h"
#include "DIF/RMT/Monitor/RMTQMonitorBase.h"
#include "DIF/SDUProtection/IntSDUProtection.h"


class RMTQMonitorBase; /* FIXME: circular dependency */

/**
 * A control unit for RMTPort & RMTQueue instances that provides an API for
 * adding and deleting RMT ports and queues.
 */
class RMTModuleAllocator : public cSimpleModule
{
  public:

    /**
     * Instantiates a new RMTPort instance.
     *
     * @param flow (N-1)-flow
     * @return pointer to the new port
     */
    RMTPort* addPort(Flow* flow);

    /**
     * Instantiates a new queue and binds it to the given port.
     *
     * @param type queue type (in/out)
     * @param port (N-1)-port
     * @param queueId queue ID (determined by QueueIDGen policy)
     * @return pointer to the new queue
     */
    RMTQueue* addQueue(RMTQueueType type, RMTPort* port, const char* queueId = "0");

    /**
     * Removes the specified port.
     *
     * @param port (N-1)-port
     */
    void removePort(RMTPort* port);

    /**
     * Removes the specified queue.
     *
     * @param queue queue
     */
    void removeQueue(RMTQueue* queue);

    /**
     * Removes each queue from given vector.
     *
     * @param queues vector of queues
     */
    void removeQueues(RMTQueues& queues);

    /**
     * Returns (N-1)-port the given queue is assigned to.
     *
     * @param queue RMT queue
     * @return (N-1)-port
     */
    RMTPort* getQueueToPortMapping(RMTQueue* queue);

    /**
     * Returns (N-1)-port by its name.
     *
     * @param name port name
     * @return (N-1)-port
     */
    RMTPort* getPort(const char* name);

    /**
     * Returns the mock inteface (N-1)-port. Only to be used in the bottom DIFs.
     *
     * @return (N-1)-port (nullptr if this isn't the bottom DIF)
     */
    RMTPort* getInterfacePort();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg) {};

  private:
    RMTQMonitorBase* qMonPolicy;
    RMTPort* interfacePort;
    std::map<RMTQueue*, RMTPort*> queueToPort;

    RMTQueue* lookup(RMTPort* port, RMTQueueType type, const char* queueName);

    // TODO: purge this crap and think of a smarter way of positioning modules
    unsigned int portCount;
    std::map<RMTPort*, unsigned int> portQueueCount;
    unsigned int portXCoord, portYCoord;
};

#endif
