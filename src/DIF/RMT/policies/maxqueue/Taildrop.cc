/*
 * SimpleMonitor.cpp
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#include <Taildrop.h>

Define_Module(Taildrop);

void Taildrop::run(RMTQueue* queue)
{
    EV << "queue " << queue->getName() << "is overflowing! dropping the last packet." << endl;
    queue->dropLast();
}

