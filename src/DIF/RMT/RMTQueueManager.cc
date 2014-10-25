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
}

RMTQueueManager::~RMTQueueManager()
{

}


void RMTQueueManager::addQueue(RMTQueue* queue)
{
    queues.push_back(queue);
}

void RMTQueueManager::removeQueue(RMTQueue* queue)
{

}

RMTQueue* RMTQueueManager::getFirst(RMTQueue::queueType type)
{
    for(std::vector<RMTQueue*>::iterator it = queues.begin(); it != queues.end(); ++it )
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
    for(std::vector<RMTQueue*>::iterator it = queues.begin(); it != queues.end(); ++it )
    {
        RMTQueue* a = *it;
        if ((a->getName() == queueName) && (a->getType() == type))
        {
            return a;
        }
    }
    return NULL;
}

RMTQueueManager::iterator RMTQueueManager::begin(){
    return this->queues.begin();
}

RMTQueueManager::iterator RMTQueueManager::end(){
    return this->queues.end();
}
