/*
 * SimpleMonitor.cpp
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#include <SimpleMonitor.h>

Define_Module(SimpleMonitor);

void SimpleMonitor::run(RMTQueue* queue)
{
    if (queue->getLength() >= queue->getMaxLength())
    {
        maxQPolicy = ModuleAccess<RMTMaxQBase>("maxQueuePolicy").get();
        maxQPolicy->run(queue);
    }
}

