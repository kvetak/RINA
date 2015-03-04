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

#include "RMTModuleAllocator.h"

Define_Module(RMTModuleAllocator);

void RMTModuleAllocator::initialize()
{
    qMonPolicy = check_and_cast<RMTQMonitorBase*>
        (getModuleByPath("^.queueMonitorPolicy"));

    portCount = 0;
    interfacePort = NULL;

    // TODO: purge this crap and think of something smarter
    // port module coordinates
    portXCoord = 55;
    portYCoord = 180;

    WATCH(portCount);
}


RMTQueue* RMTModuleAllocator::addQueue(RMTQueueType type, RMTPort* port, const char* queueId)
{
    cModule* portWrapper = port->getParentModule();

    // generate a name
    std::ostringstream queueName;
    const char* strType = (type == RMTQueue::INPUT ? "inQ_" : "outQ_");
    queueName << strType << queueId;

    RMTQueue* queue = lookup(port, type, queueName.str().c_str());
    if (queue)
    {
        EV << "addQueue(): Queue with this ID already exists!";
        return queue;
    }

    // instantiate a new module
    cModuleType *moduleType = cModuleType::get("rina.DIF.RMT.RMTQueue");
    cModule *newModule = moduleType->createScheduleInit(queueName.str().c_str(), portWrapper);
    queue = dynamic_cast<RMTQueue*>(newModule);

    // modify the position a little
//    cDisplayString& disp = queue->getDisplayString();
//    disp.setTagArg("p", 0, atoi(port->getDisplayString().getTagArg("p", 0)) - 40);
//    disp.setTagArg("p", 1, 130 + (portQueueCount[port] * 40));
//    portQueueCount[port] += 1;

    // create bindings to other modules
    cModule* rmt = getModuleByPath("^.rmt");
    std::ostringstream combinedQueueName;
    combinedQueueName << portWrapper->getFullName() << queueName.str();
    if (type == RMTQueue::OUTPUT)
    {
        // connect to RMT submodule
        cGate* rmtOut = rmt->addGate(combinedQueueName.str().c_str(), cGate::OUTPUT, false);
        cGate* portBorder = portWrapper->addGate(queueName.str().c_str(), cGate::INPUT, false);
        rmtOut->connectTo(portBorder);
        portBorder->connectTo(queue->getInputGate());

        queue->setRmtAccessGate(rmtOut);

        // connect to port
        cGate* fromOutputQueue = port->addGate(queue->getFullName(), cGate::INPUT, false);
        queue->getOutputGate()->connectTo(fromOutputQueue);
        port->addOutputQueue(queue, fromOutputQueue);
    }
    else if (type == RMTQueue::INPUT)
    {
        // connect to RMT submodule
        cGate* rmtIn = rmt->addGate(combinedQueueName.str().c_str(), cGate::INPUT, false);
        cGate* portBorder = portWrapper->addGate(queueName.str().c_str(), cGate::OUTPUT, false);

        queue->getOutputGate()->connectTo(portBorder);
        portBorder->connectTo(rmtIn);

        // connect to port
        cGate* toInputQueue = port->addGate(queue->getFullName(), cGate::OUTPUT, false);
        toInputQueue->connectTo(queue->getInputGate());
        port->addInputQueue(queue, toInputQueue);
    }

    queue->setType(type);
    qMonPolicy->postQueueCreation(queue);
    queueToPort[queue] = port;

    return queue;
}

void RMTModuleAllocator::addMgmtQueues(RMTPort* port)
{
    cModule* inQ = addQueue(RMTQueue::INPUT, port, "M");
    cModule* outQ = addQueue(RMTQueue::OUTPUT, port, "M");

    cDisplayString& dispIn = inQ->getDisplayString();
    cDisplayString& dispOut = outQ->getDisplayString();

    dispIn.setTagArg("i2", 0, "status/execute");
    dispOut.setTagArg("i2", 0, "status/execute");
}

RMTPort* RMTModuleAllocator::addPort(Flow* flow)
{
    std::ostringstream portName;
    portName << "p" << portCount;
    portCount++;

    // initialize a wrapper with port inside it
    cModuleType* moduleType = cModuleType::get("rina.DIF.RMT.RMTPortWrapper");
    cModule* portWrapper = moduleType->createScheduleInit(portName.str().c_str(), getParentModule());
    RMTPort* port = check_and_cast<RMTPort*>(portWrapper->getSubmodule("port"));

    port->setFlow(flow);

    // modify the position a little
    cDisplayString& portDisp = portWrapper->getDisplayString();
    portDisp.setTagArg("p", 0, portXCoord);
    portDisp.setTagArg("p", 1, portYCoord);
    portXCoord += 60;

    if (flow == NULL)
    {
        interfacePort = port;
    }

    return port;
}

void RMTModuleAllocator::removeQueue(RMTQueue* queue)
{
    if (queue->getType() == RMTQueue::OUTPUT)
    {
        queue->getRmtAccessGate()->disconnect();
    }
    queue->getOutputGate()->disconnect();

    cModule* rmt = getParentModule()->getModuleByPath(".rmt");
    rmt->deleteGate(queue->getName());

    qMonPolicy->preQueueRemoval(queue);
    queue->deleteModule();
}

void RMTModuleAllocator::removeQueues(const RMTQueues& queues)
{
    for(RMTQueues::const_iterator it = queues.begin(); it != queues.end(); ++it )
    {
        removeQueue((RMTQueue*)*it);
    }
}

RMTQueue* RMTModuleAllocator::lookup(RMTPort* port, RMTQueueType type, const char* queueName)
{
    RMTQueues queues = (type == RMTQueue::OUTPUT ? port->getOutputQueues() : port->getInputQueues());
    for(RMTQueuesIter it = queues.begin(); it != queues.end(); ++it )
    {
        RMTQueue* a = *it;
        if (!opp_strcmp(a->getName(), queueName))
        {
            return a;
        }
    }
    return NULL;
}

void RMTModuleAllocator::removePort(RMTPort* port)
{
    removeQueues(port->getOutputQueues());
    removeQueues(port->getInputQueues());

    port->deleteModule();
}

RMTPort* RMTModuleAllocator::getQueueToPortMapping(RMTQueue* queue)
{
    return queueToPort[queue];
}

RMTPort* RMTModuleAllocator::getInterfacePort()
{
    return interfacePort;
}
