/*
 * ECNMarker.cpp
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#include <ECNMarker.h>

Define_Module(ECNMarker);

void ECNMarker::run(RMTQueue* queue)
{
    if (queue->getLength() > queue->getMaxLength())
    {
        EV << "ECNMarker: dropping message for queue " << queue->getName() << "!" << endl;
        queue->dropLast();
    }
    else
    {
        EV << "ECNMarker: marking the last message in queue " << queue->getName() << "!" << endl;
        queue->markCongestionOnLast();
    }
}

