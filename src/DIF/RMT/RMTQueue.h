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

#ifndef __RINA_RMTQUEUE_H_
#define __RINA_RMTQUEUE_H_

#include <omnetpp.h>
#include <queue>

#include "PDU_m.h"
#include "QoSCube.h"
#include "RINASignals.h"


class RMTQueue : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    RMTQueue();
    virtual ~RMTQueue();

    enum queueType { INPUT = 'I', OUTPUT = 'O'};

    queueType getType();
    void setType(queueType type);

    int getMaxLength();
    void setMaxLength(int value);
    int getThreshLength();
    void setThreshLength(int value);
    const char* getQueueId() const;
    void setQueueId(const char* queueId);
    int getLength() const;
    simtime_t getQTime() const;

    cGate* getOutputGate();
    cGate* getInputGate();
    cGate* getRmtAccessGate();
    void setRmtAccessGate(cGate* gate);

    void releasePDU();
    void dropLast();
    void markCongestionOnLast();

    bool isBounded();
    std::string info() const;

    void startTransmitting();

  private:
    std::deque<cMessage*> queue;
    queueType type;

    const char* queueId;

    int maxQLength;
    int thresholdQLength;

    double queuingTime;
    simtime_t qTime;

    cGate* rmtAccessGate;
    cGate* outputGate;
    cGate* inputGate;

    simsignal_t sigRMTPDURcvd;
    simsignal_t sigRMTPDUSent;

    void enqueuePDU(cMessage* pdu);
    void redrawGUI();

};

typedef RMTQueue::queueType RMTQueueType;

typedef std::vector<RMTQueue*>  RMTQueues;
typedef RMTQueues::iterator  RMTQueuesIter;

std::ostream& operator<< (std::ostream& os, const RMTQueue& cte);

#endif
