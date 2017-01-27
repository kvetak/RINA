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

#ifndef __RINA_RMTQUEUE_H_
#define __RINA_RMTQUEUE_H_

#include <omnetpp.h>
#include <queue>

#include "Common/RINASignals.h"
#include "Common/PDU.h"

#include "Common/Flow.h"

class RMTQueue : public cSimpleModule
{
  /* tight coupling for management purposes */
  friend class RMT;
  friend class RMTPort;
  friend class RMTModuleAllocator;

  public:

    virtual ~RMTQueue();

    /**
     * Queue type (i.e. its direction).
     */
    enum queueType { INPUT = 'I', OUTPUT = 'O'};

    /**
     * Returns the queue's type (i.e. its direction).
     *
     * @return queue type enum value
     */
    queueType getType() const;

    /**
     * Returns the current length of the message queue.
     *
     * @return length
     */
    int getLength() const;

    /**
     * Returns the timestamp of the simulation time from which the queue has been empty.
     * Usable only if the queue is currently empty.
     *
     * @return start of queue idle time
     */
    simtime_t getQTime() const;

    /**
     * Returns the maximum length of the queue.
     *
     * @return maximum length
     */
    int getMaxLength() const;

    /**
     * Sets the maximum length of the queue.
     *
     * @param value new maximum
     */
    void setMaxLength(int value);

    /**
     * Returns the threshold length of the queue.
     *
     * @return threshold length
     */
    int getThreshLength() const;

    /**
     * Sets the threshold length of the queue.
     *
     * @param value new threshold
     */
    void setThreshLength(int value);

    /**
     * Returns a pointer to the first PDU in the queue.
     *
     * @return PDU
     */
    const cPacket* getFirstPDU() const;

    /**
     * Returns a pointer to the last PDU in the queue.
     *
     * @return PDU
     */
    const cPacket* getLastPDU() const;

    /**
     * Iterators.
     */
    typedef std::deque<cPacket*>::iterator iterator;
    typedef std::deque<cPacket*>::const_iterator const_iterator;
    iterator begin() { return queue.begin(); }
    iterator end() { return queue.end(); }

    /**
     * Sends out the first PDU in the queue.
     */
    void releasePDU();

    /**
     * Marks the last PDU in a queue with a congestion bit.
     */
    void markCongestionOnLast();

    /**
     * Marks the first PDU in a queue with a congestion bit.
     */
    void markCongestionOnFirst();

    /**
     * Spews out some information about queue state.
     */
    std::string info() const;

    void setFlow(Flow *);
    const Flow* getFlow() const;


    cPacket* dropLast();
    cPacket* dropFirst();

  protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage* msg);

  private:
    std::deque<cPacket*> queue;
    queueType type;

    int maxQLength;
    int thresholdQLength;

    simtime_t qTime;

    cGate* rmtAccessGate;
    cGate* outputGate;
    cGate* inputGate;

    Flow  * flow;

    void setType(queueType type);

    void enqueuePDU(cPacket* pdu);

    cGate* getOutputGate() const;
    cGate* getInputGate() const;
    cGate* getRMTAccessGate() const;
    void setRMTAccessGate(cGate* gate);

    void redrawGUI();

    simsignal_t sigRMTPDUPreRcvd;
    simsignal_t sigRMTPDUPostRcvd;
    simsignal_t sigRMTPDUPreSend;
    simsignal_t sigRMTPDUSent;
    simsignal_t sigStatRMTQueueLength;
};

typedef RMTQueue::queueType RMTQueueType;
typedef std::vector<RMTQueue*>  RMTQueues;

std::ostream& operator<< (std::ostream& os, const RMTQueue& cte);

#endif
