/*
 * RED.cpp
 *
 *  Created on: 17. 11. 2014
 *      Author: cloq
 */

#include <RED.h>

Define_Module(RED);

void RED::run(RMTQueue* queue)
{
    maxQPolicy = ModuleAccess<RMTMaxQBase>("maxQueuePolicy").get();

    int length = queue->getLength();
    int minThresh = queue->getThreshLength();
    int maxThresh = queue->getMaxLength();
    double avr = queue->getAverageLength();
    double wq = queue->getWeight();
    double maxP = getParentModule()->par("dropProbability").doubleValue();
    int count = queue->getAqmCounter();
    simtime_t qTime = queue->getQTime();

    if (length > 0)
    {
        avr = (1 - wq) * avr + wq * length;
    }
    else
    {
        const double m = SIMTIME_DBL(simTime() - qTime);
        avr = pow(1 - wq, m) * avr;
    }

    if (minThresh <= avr && avr < maxThresh)
    {
        queue->setAqmCounter(++count);
        const double pb = maxP * (avr - minThresh) / (maxThresh - minThresh);
        const double pa = pb / (1 - count * pb);
        if (dblrand() < pa)
        {
            maxQPolicy->run(queue);
            queue->setAqmCounter(0);
        }
    }
    else if (length > maxThresh || avr > maxThresh)
    {
        maxQPolicy->run(queue);
        queue->setAqmCounter(0);
    }
    else
    {
        queue->setAqmCounter(-1);
    }
}

