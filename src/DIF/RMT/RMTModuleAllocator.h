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

#ifndef __RINA_RMTMODULEALLOCATOR_H_
#define __RINA_RMTMODULEALLOCATOR_H_

#include <omnetpp.h>

#include "RMTQueue.h"
#include "RMTPort.h"
#include "RMTQMonitorBase.h"

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
     * Adds a pair of management queues.
     * Note: this will go away soon when mgmt messages get their own flows
     *
     * @param port (N-1)-port
     */
    void addMgmtQueues(RMTPort* port);

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
    void removeQueues(const RMTQueues& queues);

    /**
     * Returns (N-1)-port the given queue is assigned to.
     *
     * @param queue RMT queue
     * @return (N-1)-port
     */
    RMTPort* getQueueToPortMapping(RMTQueue* queue);

    /**
     * Returns the mock inteface (N-1)-port. Only to be used in the bottom DIFs.
     *
     * @return (N-1)-port (NULL if this isn't the bottom DIF)
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
