//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
#include "RMTQueue.h"
#include "Flow.h"
#include "CDAPMessage_m.h"
#include "QueueIDGenBase.h"

class RMTPort : public cSimpleModule
{
  public:
    bool isReady();
    void setReady();
    void setBusy();

    const Flow* getFlow() const;
    void setFlow(Flow* flow);

    const RMTQueues& getInputQueues() const;
    void addInputQueue(RMTQueue* queue, cGate* portGate);

    const RMTQueues& getOutputQueues() const;
    void addOutputQueue(RMTQueue* queue, cGate* portGate);

    cGate* getSouthInputGate() const;
    cGate* getSouthOutputGate() const;

    RMTQueue* getManagementQueue(RMTQueueType type);
    RMTQueue* getFirstQueue(RMTQueueType type);
    RMTQueue* getLongestQueue(RMTQueueType type);
    RMTQueue* getQueueById(RMTQueueType type, const char* queueId);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    bool ready;
    Flow* flow;

    QueueIDGenBase* queueIdGen;

    std::set<cGate*> northOutputGates;
    std::set<cGate*> northInputGates;
    cGate* southInputGate;
    cGate* southOutputGate;
    RMTQueues outputQueues;
    RMTQueues inputQueues;

    void redrawGUI();
};

typedef std::vector<RMTPort*> RMTPorts;

#endif
