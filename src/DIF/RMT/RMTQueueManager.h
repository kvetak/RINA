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

    typedef RMTQueues::iterator iterator;
    iterator begin();
    iterator end();

    RMTPort* addPort(const char* portName);
    RMTQueue* addQueue(RMTQueueType type, RMTPort* port, int queueId = 0);
    void addMgmtQueues(RMTPort* port);
    void removeQueue(RMTQueue* queue);

    RMTQueue* lookup(const char* queueName, RMTQueueType type);
    RMTQueue* lookup(int queueId, RMTQueueType type);

    std::map<RMTQueue*, RMTPort*> queueToPort;

  private:
    RMTQueues queues;

    RMTQMonitorBase* qMonPolicy;
    std::map<RMTPort*, unsigned int> portQueueCount;

    // TODO: purge this crap and think of something smarter
    unsigned int portXCoord, portYCoord;

};

#endif
