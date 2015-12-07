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

#ifndef __RINA_RMTPORT_H_
#define __RINA_RMTPORT_H_

#include <omnetpp.h>
#include <algorithm>

#include "RINASignals.h"
#include "Flow.h"
#include "CDAPMessage_m.h"
#include "RMTQueue.h"
#include "QueueIDGenBase.h"

class RMTPort : public cSimpleModule
{
    /* tight coupling for management purposes */
    friend class RA;
    friend class RMT;
    friend class RMTModuleAllocator;

  public:

    /**
     * Returns the port state (ready to send out data/busy).
     *
     * @return port state
     */
    bool isOutputReady();

    /**
     * Returns the port state (ready to receive data/busy).
     *
     * @return port state
     */
    bool isInputReady();

    /**
     * Marks the port as blocked for sending (e.g. when (N-1)-EFCPI isn't keeping up).
     */
    void blockOutput();

    /**
     * Unmarks the port as blocked for sending (e.g. when (N-1)-EFCPI is keeping up again).
     */
    void unblockOutput();

    /**
     * Marks the port as blocked for reading (e.g. when other (N-1)-ports aren't keeping up).
     */
    void blockInput();

    /**
     * Unmarks the port as blocked for reading (e.g. when other (N-1)-ports are keeping up again).
     */
    void unblockInput();

    /**
     * Returns input block status.
     */
    bool hasBlockedInput() { return blockedInput; };

    /*
     * Returns the input drain speed of this port.
     */
    long getInputRate();

    /*
     * Sets the input drain speed of this port.
     */
    void setInputRate(long pdusPerSecond);

    /**
     * Returns the (N-1)-flow this port is assigned to.
     *
     * @return (N-1)-flow object
     */
    const Flow* getFlow() const;

    /**
     * Returns the port's management queue.
     * Note: this will go away soon when we start dedicating entire (N-1)-flows
     *       for management purposes
     *
     * @param type direction of data
     * @return management queue
     */
    RMTQueue* getManagementQueue(RMTQueueType type) const;

    /**
     * Returns the first queue available on this port.
     * Note: this excludes the temporary management queues
     *
     * @param type direction of data
     * @return queue
     */
    RMTQueue* getFirstQueue(RMTQueueType type) const;

    /**
     * Returns the longest queue attached to this port.
     *
     * @param type direction of data
     * @return queue
     */
    RMTQueue* getLongestQueue(RMTQueueType type) const;

    /**
     * Returns the queue that matches given ID.
     *
     * @param type direction of data
     * @param queueId queue ID
     * @return queue
     */
    RMTQueue* getQueueById(RMTQueueType type, const char* queueId) const;

    /**
     * Returns a list of available input queues.
     *
     * @return set of queues
     */
    const RMTQueues& getInputQueues() const;

    /**
     * Returns a list of available output queues.
     *
     * @return set of queues
     */
    const RMTQueues& getOutputQueues() const;

    /**
     * Returns number of PDUs waiting to be read.
     *
     * @param direction of transfer (read/serve)
     * @return PDUs count accross queues
     */
    unsigned long getWaiting(RMTQueueType direction);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage* msg);

    /**
     * Increments number of waiting PDUs.
     *
     * @param direction of transfer (read/serve)
     */
    void addWaiting(RMTQueueType direction);

    /**
     * Decrements number of waiting PDUs.
     *
     * @param direction of transfer (read/serve)
     * @return PDUs count accross queues
     */
    void substractWaiting(RMTQueueType direction);

  private:
    bool inputReady;
    bool outputReady;
    bool blockedInput;
    bool blockedOutput;
    unsigned long waitingOnInput;
    unsigned long waitingOnOutput;
    long inputReadRate;
    double postReadDelay;
    std::string dstAppAddr;

    Flow* flow;
    QueueIDGenBase* queueIdGen;

    std::set<cGate*> northInputGates;
    cGate* southInputGate;
    cGate* southOutputGate;
    cChannel* outputChannel;

    RMTQueues outputQueues;
    RMTQueues inputQueues;

    /**
     * Marks the port as ready to receive data.
     */
    void setOutputReady();

    /**
     * Marks the port as busy (e.g. when sending data through it).
     */
    void setOutputBusy();

    /**
     * Marks the port as ready to receive data.
     */
    void setInputReady();

    /**
     * Marks the port as busy (e.g. when sending data through it).
     */
    void setInputBusy();

    void postInitialize();
    void setFlow(Flow* flow);
    void registerInputQueue(RMTQueue* queue);
    void registerOutputQueue(RMTQueue* queue);
    void unregisterInputQueue(RMTQueue* queue);
    void unregisterOutputQueue(RMTQueue* queue);
    cGate* getSouthInputGate() const;
    cGate* getSouthOutputGate() const;

    void scheduleNextRead();
    void scheduleNextWrite();
    void redrawGUI(bool redrawParent = false);

    simsignal_t sigRMTPortReadyForRead;
    simsignal_t sigRMTPortReadyToWrite;
    simsignal_t sigStatRMTPortUp;
    simsignal_t sigStatRMTPortDown;
};

typedef std::vector<RMTPort*> RMTPorts;

#endif
