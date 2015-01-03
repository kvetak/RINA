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

#ifndef __RINA_RMTQUEUEMANAGER_H_
#define __RINA_RMTQUEUEMANAGER_H_

#include <omnetpp.h>

#include "RMTQueue.h"
#include "RMTPort.h"
#include "RMTQMonitorBase.h"

class RMTQueueManager : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg) {};

  public:
    RMTQueueManager();
    virtual ~RMTQueueManager();

    RMTPort* addPort(Flow* flow);
    RMTQueue* addQueue(RMTQueueType type, RMTPort* port, const char* queueId = "0");
    void addMgmtQueues(RMTPort* port);
    void removePort(RMTPort* port);
    void removeQueue(RMTQueue* queue);
    void removeQueues(const RMTQueues& queues);

    RMTQueue* lookup(RMTPort* port, RMTQueueType type, const char* queueName);
    RMTPort* getQueueToPortMapping(RMTQueue* queue);
    RMTPort* getInterfacePort();

  private:
    RMTQMonitorBase* qMonPolicy;
    RMTPort* interfacePort;
    std::map<RMTQueue*, RMTPort*> queueToPort;

    // TODO: purge this crap and think of a smarter way of positioning modules
    unsigned int portCount;
    std::map<RMTPort*, unsigned int> portQueueCount;
    unsigned int portXCoord, portYCoord;
};

#endif
