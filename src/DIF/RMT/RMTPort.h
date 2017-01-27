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

#ifndef __RINA_RMTPORT_H_
#define __RINA_RMTPORT_H_

#include <omnetpp.h>
#include <algorithm>

#include "Common/Utils.h"
#include "Common/RINASignals.h"
#include "Common/Flow.h"
#include "DIF/RMT/RMTQueue.h"
#include "DIF/RA/QueueIDGen/QueueIDGenBase.h"
#include "Common/SDUData_m.h"

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
    RMTQueues& getInputQueues();

    /**
     * Returns a list of available output queues.
     *
     * @return set of queues
     */
    RMTQueues& getOutputQueues();

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
    std::string dstAppQoS;

    Flow* flow;
    QueueIDGenBase* queueIdGen;

    std::set<cGate*> northInputGates;
    cGate* southInputGate;
    cGate* southOutputGate;
    cGate* protectIn;
    cGate* protectOut;
    cGate* unprotectIn;
    cGate* unprotectOut;
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
