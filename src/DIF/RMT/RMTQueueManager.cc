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
    WATCH_PTRVECTOR(queues);
    qypos = 120;
    qxpos = 45;
}

RMTQueueManager::~RMTQueueManager()
{

}

void RMTQueueManager::initialize()
{
    qMonPolicy = ModuleAccess<RMTQMonitorBase>("queueMonitorPolicy").get();
}


RMTQueue* RMTQueueManager::addQueue(RMTQueue::queueType type)
{
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.DIF.RMT.RMTQueue");

    // instantiate a new object
    std::ostringstream queueName;

    // generate a name
    const char* strType = (type == RMTQueue::INPUT ? "in" : "out");

    for (int i = 0; ; i++)
    {
        queueName << strType << i;
        if (lookup(queueName.str().c_str(), type) != NULL)
        {
            queueName.str(std::string());
            queueName.clear();
            continue;
        }
        else
        {
            break;
        }
    }

    cModule *module_f = moduleType->createScheduleInit(queueName.str().c_str(), this->getParentModule());
    RMTQueue* module = dynamic_cast<RMTQueue*>(module_f);

    // modify the position a little
    std::ostringstream istr;
    istr << "p=" << qxpos << "," << qypos << ";i=block/queue;is=vs";

    cDisplayString& dispStr = module->getDisplayString();
    dispStr.parse(istr.str().c_str());
    qxpos = qxpos + 45;

    // connect to RMT submodule
    cModule* rmt = getParentModule()->getModuleByPath(".rmt");
    if (type == RMTQueue::OUTPUT)
    {
        cGate* rmtOut = rmt->addGate(queueName.str().c_str(), cGate::OUTPUT, false);
        rmtOut->connectTo(module->getInputGate());
        module->setRmtAccessGate(rmtOut);
    }
    else if (type == RMTQueue::INPUT)
    {
        cGate* rmtIn = rmt->addGate(queueName.str().c_str(), cGate::INPUT, false);
        module->getOutputGate()->connectTo(rmtIn);
    }

    module->redrawGUI();

    qMonPolicy->postQueueCreation(module);

    module->setType(type);
    queues.push_back(module);
    return module;
}



void RMTQueueManager::removeQueue(RMTQueue* queue)
{
    cModule* rmt = getParentModule()->getModuleByPath(".rmt");

    if (queue->getType() == RMTQueue::OUTPUT)
    {
        queue->getRmtAccessGate()->disconnect();
    }
    else
    {
        queue->getOutputGate()->disconnect();
    }

    rmt->deleteGate(queue->getName());

    // remove item from table
    RMTQueuesIter i = queues.begin();
    while (i != queues.end())
    {
        if (*i == queue)
        {
            i = queues.erase(i);
        }
        else
        {
            ++i;
        }
    }

    qMonPolicy->preQueueRemoval(queue);

    queue->deleteModule();
}

RMTQueue* RMTQueueManager::getFirst(RMTQueue::queueType type)
{
    for(RMTQueues::iterator it = queues.begin(); it != queues.end(); ++it )
    {
        RMTQueue* a = *it;
        if (a->getType() == type)
        {
            return a;
        }
    }
    return NULL;
}

RMTQueue* RMTQueueManager::lookup(const char* queueName, RMTQueue::queueType type)
{
    for(RMTQueues::iterator it = queues.begin(); it != queues.end(); ++it )
    {
        RMTQueue* a = *it;
        if (!opp_strcmp(a->getName(), queueName) && (a->getType() == type))
        {
            return a;
        }
    }
    return NULL;
}

RMTQueue* RMTQueueManager::getLongest(RMTQueue::queueType type)
{
    int longest = 0;
    RMTQueue* result = NULL;

    for(RMTQueues::iterator it = queues.begin(); it != queues.end(); ++it)
    {
        RMTQueue* a = *it;
        if (a->getLength() > longest)
        {
            longest = a->getLength();
            result = a;
        }
    }

    return result;
}

RMTQueueManager::iterator RMTQueueManager::begin()
{
    return this->queues.begin();
}

RMTQueueManager::iterator RMTQueueManager::end()
{
    return this->queues.end();
}
