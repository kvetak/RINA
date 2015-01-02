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

#include "RMTQueueManager.h"

Define_Module(RMTQueueManager);

RMTQueueManager::RMTQueueManager()
{
}

RMTQueueManager::~RMTQueueManager()
{

}

void RMTQueueManager::initialize()
{
    qMonPolicy = check_and_cast<RMTQMonitorBase*>
        (getModuleByPath("^.queueMonitorPolicy"));
    WATCH_PTRMAP(queueToPort);

    portCount = 0;

    // TODO: purge this crap and think of something smarter
    // port module coordinates
    portXCoord = 100;
    portYCoord = 220;
}


RMTQueue* RMTQueueManager::addQueue(RMTQueueType type, RMTPort* port, const char* queueId)
{
    // generate a name
    std::ostringstream queueName;
    const char* strType = (type == RMTQueue::INPUT ? "i" : "o");
    queueName << port->getFullName() << strType << queueId;

    RMTQueue* queue = lookup(port, type, queueName.str().c_str());
    if (queue)
    {
        EV << "addQueue(): Queue with this ID already exists!";
        return queue;
    }

    // instantiate a new module
    cModuleType *moduleType = cModuleType::get("rina.DIF.RMT.RMTQueue");
    cModule *newModule = moduleType->createScheduleInit(queueName.str().c_str(), this->getParentModule());
    queue = dynamic_cast<RMTQueue*>(newModule);

    // modify the position a little
    cDisplayString& disp = queue->getDisplayString();
    disp.setTagArg("p", 0, atoi(port->getDisplayString().getTagArg("p", 0)) - 40);
    disp.setTagArg("p", 1, 130 + (portQueueCount[port] * 40));
    portQueueCount[port] += 1;

    // create bindings to other modules
    cModule* rmt = getModuleByPath("^.rmt");
    if (type == RMTQueue::OUTPUT)
    {
        // connect to RMT submodule
        cGate* rmtOut = rmt->addGate(queueName.str().c_str(), cGate::OUTPUT, false);
        rmtOut->connectTo(queue->getInputGate());
        queue->setRmtAccessGate(rmtOut);

        // connect to port
        cGate* fromOutputQueue = port->addGate(queue->getFullName(), cGate::INPUT, false);
        queue->getOutputGate()->connectTo(fromOutputQueue);
        port->addOutputQueue(queue, fromOutputQueue);
    }
    else if (type == RMTQueue::INPUT)
    {
        // connect to RMT submodule
        cGate* rmtIn = rmt->addGate(queueName.str().c_str(), cGate::INPUT, false);
        queue->getOutputGate()->connectTo(rmtIn);

        // connect to port
        cGate* toInputQueue = port->addGate(queue->getFullName(), cGate::OUTPUT, false);
        toInputQueue->connectTo(queue->getInputGate());
        port->addInputQueue(queue, toInputQueue);
    }

    queue->setType(type);
    queue->setQueueId(queueId);
    qMonPolicy->postQueueCreation(queue);
    queueToPort[queue] = port;

    return queue;
}

void RMTQueueManager::addMgmtQueues(RMTPort* port)
{
    cModule* inQ = addQueue(RMTQueue::INPUT, port, "M");
    cModule* outQ = addQueue(RMTQueue::OUTPUT, port, "M");

    cDisplayString& dispIn = inQ->getDisplayString();
    cDisplayString& dispOut = outQ->getDisplayString();

    dispIn.setTagArg("i2", 0, "status/execute");
    dispOut.setTagArg("i2", 0, "status/execute");
}

RMTPort* RMTQueueManager::addPort(Flow* flow)
{
    std::ostringstream portName;
    portName << "p" << portCount;
    portCount++;

    cModuleType* moduleType = cModuleType::get("rina.DIF.RMT.RMTPort");
    RMTPort* port = (RMTPort*)moduleType->
                    createScheduleInit(portName.str().c_str(), getParentModule());

    port->setFlow(flow);

    // modify the position a little
    cDisplayString& portDisp = port->getDisplayString();
    portDisp.setTagArg("p", 0, portXCoord);
    portDisp.setTagArg("p", 1, portYCoord);
    portXCoord += 90;

    return port;
}

void RMTQueueManager::removeQueue(RMTQueue* queue)
{
//    cModule* rmt = getParentModule()->getModuleByPath(".rmt");
//
//    if (queue->getType() == RMTQueue::OUTPUT)
//    {
//        queue->getRmtAccessGate()->disconnect();
//    }
//    else
//    {
//        queue->getOutputGate()->disconnect();
//    }
//
//    rmt->deleteGate(queue->getName());
//
//    // remove item from table
//    RMTQueuesIter i = queues.begin();
//    while (i != queues.end())
//    {
//        if (*i == queue)
//        {
//            i = queues.erase(i);
//        }
//        else
//        {
//            ++i;
//        }
//    }
//
//    qMonPolicy->preQueueRemoval(queue);
//
//    queue->deleteModule();
}

RMTQueue* RMTQueueManager::lookup(RMTPort* port, RMTQueueType type, const char* queueName)
{
    RMTQueues queues = port->getOutputQueues();
    for(std::vector<RMTQueue*>::iterator it = queues.begin(); it != queues.end(); ++it )
    {
        RMTQueue* a = *it;
        if (!opp_strcmp(a->getName(), queueName) && (a->getType() == type))
        {
            return a;
        }
    }
    return NULL;
}

