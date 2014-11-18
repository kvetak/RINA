/*
 * SimpleMonitor.cpp
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#include <TailDrop.h>

Define_Module(TailDrop);

void TailDrop::run(RMTQueue* queue)
{
    EV << "TailDrop: dropping packet for queue " << queue->getName() << "!" << endl;
    queue->dropLast();
}

