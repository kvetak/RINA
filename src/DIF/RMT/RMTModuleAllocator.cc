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

#include "DIF/RMT/RMTModuleAllocator.h"

Define_Module(RMTModuleAllocator);

void RMTModuleAllocator::initialize()
{
    qMonPolicy = getRINAModule<RMTQMonitorBase*>(this, 1, {MOD_POL_RMT_QMONITOR});

    portCount = 0;
    interfacePort = nullptr;

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
    if (queue != nullptr)
    {
        EV << "addQueue(): Queue with this ID already exists!";
        return queue;
    }

    // instantiate a new module
    cModuleType *moduleType = cModuleType::get(MOD_RMT_QUEUE);
    cModule *newModule = moduleType->createScheduleInit(queueName.str().c_str(), portWrapper);
    queue = dynamic_cast<RMTQueue*>(newModule);

    // create bindings to other modules
    cModule* rmt = getRINAModule<cModule*>(this, 1, {MOD_RMT});
    std::ostringstream combinedQueueName;
    combinedQueueName << portWrapper->getFullName() << queueName.str();
    if (type == RMTQueue::OUTPUT)
    {
        // connect to RMT submodule
        cGate* rmtOut = rmt->addGate(combinedQueueName.str().c_str(), cGate::OUTPUT, false);
        cGate* portBorder = portWrapper->addGate(queueName.str().c_str(), cGate::INPUT, false);
        rmtOut->connectTo(portBorder);
        portBorder->connectTo(queue->getInputGate());

        queue->setRMTAccessGate(rmtOut);

        // connect to port
        cGate* fromOutputQueue = port->addGate(queue->getFullName(), cGate::INPUT, false);
        queue->getOutputGate()->connectTo(fromOutputQueue);

        port->registerOutputQueue(queue);
    }
    else if (type == RMTQueue::INPUT)
    {
        // connect to RMT submodule
        cGate* rmtIn = rmt->addGate(combinedQueueName.str().c_str(), cGate::INPUT, false);
        cGate* portBorder = portWrapper->addGate(queueName.str().c_str(), cGate::OUTPUT, false);

        queue->getOutputGate()->connectTo(portBorder);
        portBorder->connectTo(rmtIn);

        queue->setRMTAccessGate(rmtIn);

        // connect to port
        cGate* toInputQueue = port->addGate(queue->getFullName(), cGate::OUTPUT, false);
        toInputQueue->connectTo(queue->getInputGate());

        port->registerInputQueue(queue);
    }

    queue->setType(type);
    queueToPort[queue] = port;
    qMonPolicy->postQueueCreation(queue);

    return queue;
}

RMTPort* RMTModuleAllocator::addPort(Flow* flow)
{
    std::ostringstream portName;
    portName << "p" << portCount;
    portCount++;

    // initialize a wrapper with port inside it
    cModuleType* moduleType = cModuleType::get(MOD_RMT_PORTWRAPPER);
    cModule* portWrapper = moduleType->createScheduleInit(portName.str().c_str(), getParentModule());
    RMTPort* port = check_and_cast<RMTPort*>(portWrapper->getSubmodule(MOD_RMTPORT));

    port->setFlow(flow);

    // modify the position a little
    cDisplayString& portDisp = portWrapper->getDisplayString();
    portDisp.setTagArg("p", 0, portXCoord);
    portDisp.setTagArg("p", 1, portYCoord);
    portXCoord += 120;

    if (flow == nullptr)
    {
        interfacePort = port;
    }
    else if (flow->isManagementFlow())
    {
        portDisp.setTagArg("i2", 0, "status/execute");
    }

    // initialize SDU protection
    std::ostringstream sdupInstanceName, sdupPolicyType;
    const char* sdupParam = getParentModule()->par("sdupPolicyName");
    sdupPolicyType << "rina.policies.DIF.SDUProtection." << sdupParam << "." << sdupParam;
    sdupInstanceName << "sdup" << portCount;
    moduleType = cModuleType::get(sdupPolicyType.str().c_str());
    cModule* sdup = check_and_cast<IntSDUProtection*>(
            moduleType->createScheduleInit(sdupInstanceName.str().c_str(), portWrapper));

    // modify the position a little
    cDisplayString& sdupDisp = sdup->getDisplayString();
    sdupDisp.setTagArg("p", 0, 150);
    sdupDisp.setTagArg("p", 1, 228);
    sdupDisp.setTagArg("i", 0, "block/encrypt");
    sdupDisp.setTagArg("is", 0, "s");

    interconnectModules(port, sdup, std::string("protect"), std::string("protect"));
    interconnectModules(port, sdup, std::string("unprotect"), std::string("unprotect"));

    return port;
}

void RMTModuleAllocator::removeQueue(RMTQueue* queue)
{
    cModule* rmt = getRINAModule<cModule*>(this, 1, {MOD_RMT});
    RMTPort* port = queueToPort[queue];
    cGate* rmtGate = queue->getRMTAccessGate();
    cGate* qOutputGate = queue->getOutputGate();
    cGate* qInputGate = queue->getInputGate();

    if (queue->getType() == RMTQueue::OUTPUT)
    {
        rmtGate->getNextGate()->disconnect();
        rmtGate->disconnect();
        qOutputGate->disconnect();
        port->unregisterOutputQueue(queue);
    }
    else
    {
        qOutputGate->getNextGate()->disconnect();
        qOutputGate->disconnect();
        qInputGate->getPreviousGate()->disconnect();
        port->unregisterInputQueue(queue);
    }

    rmt->deleteGate(rmtGate->getFullName());
    port->deleteGate(queue->getFullName());
    port->getParentModule()->deleteGate(queue->getFullName());

    qMonPolicy->preQueueRemoval(queue);
    queue->callFinish();
    queue->deleteModule();
}

void RMTModuleAllocator::removeQueues(RMTQueues& queues)
{
    while (!queues.empty())
    {
        removeQueue(queues.back());
        queues.pop_back();
    }
}

RMTQueue* RMTModuleAllocator::lookup(RMTPort* port, RMTQueueType type, const char* queueName)
{
    RMTQueues queues = (type == RMTQueue::OUTPUT ? port->getOutputQueues() : port->getInputQueues());

    for(auto const q : queues)
    {
        if (!opp_strcmp(q->getName(), queueName))
        {
            return q;
        }
    }
    return nullptr;
}

void RMTModuleAllocator::removePort(RMTPort* port)
{
    removeQueues(port->getOutputQueues());
    removeQueues(port->getInputQueues());

    port->callFinish();
    port->getParentModule()->deleteModule();
}

RMTPort* RMTModuleAllocator::getQueueToPortMapping(RMTQueue* queue)
{
    return queueToPort[queue];
}

RMTPort* RMTModuleAllocator::getInterfacePort()
{
    return interfacePort;
}

RMTPort* RMTModuleAllocator::getPort(const char* name)
{
    cModule* portWrapper = getParentModule()->getSubmodule(name);
    if (portWrapper)
    {
        return dynamic_cast<RMTPort*>(portWrapper->getSubmodule(MOD_RMTPORT));
    }

    return nullptr;
}
