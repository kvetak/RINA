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

#ifndef QUEUEALLOCBASE_H_
#define QUEUEALLOCBASE_H_

#include <omnetpp.h>
#include "RABase.h"
#include "QosCube.h"
#include "RMTQueueManager.h"
#include "RMTPort.h"

/*
 *
 */
class QueueAllocBase : public cSimpleModule
{
  public:
    QueueAllocBase();
    virtual ~QueueAllocBase();
    virtual void createQueues(RMTPort* port, RMTQueues& result);

  protected:
    void initialize();
    void handleMessage(cMessage *msg);

    RMTQueueManager* rmtQM;
    QosCubeSet qosCubes;
};

#endif /* QUEUEALLOCBASE_H_ */
