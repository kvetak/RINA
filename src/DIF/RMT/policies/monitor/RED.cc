/*
 * RED.cpp
 *
 *  Created on: 17. 11. 2014
 *      Author: cloq
 */

#include <RED.h>

Define_Module(RED);

void RED::postQueueCreation(RMTQueue* queue)
{
    // TODO: fix variable initialization, these are just for demo purposes
    qAvgLengths[queue] = 0.0;
    qWeights[queue] = 0.5;
    qProbabilities[queue] = 0.4;
    qCounters[queue] = -1;
}

void RED::preQueueRemoval(RMTQueue* queue)
{
    qAvgLengths.erase(queue);
    qWeights.erase(queue);
    qProbabilities.erase(queue);
    qCounters.erase(queue);
}


void RED::run(RMTQueue* queue)
{
    maxQPolicy = ModuleAccess<RMTMaxQBase>("maxQueuePolicy").get();

    int length = queue->getLength();
    int minThresh = queue->getThreshLength();
    int maxThresh = queue->getMaxLength();

    double avr = qAvgLengths[queue];
    double wq = qWeights[queue];
    double maxP = qProbabilities[queue];
    int count = qCounters[queue];

    simtime_t qTime = queue->getQTime();
    const char* qname = queue->getFullName();

    if (length > 0)
    {
        avr = (1 - wq) * avr + wq * length;
    }
    else
    {
        const double m = SIMTIME_DBL(simTime() - qTime);
        avr = pow(1 - wq, m) * avr;
    }

    qAvgLengths[queue] = avr;

    if (length > maxThresh)
    {
        EV << "RED: Queue " << qname << " is full! Dropping the incoming message." << endl;
        maxQPolicy->run(queue);
        qCounters[queue] = 0;
    }
    else if (minThresh <= avr && avr < maxThresh)
    {
        qCounters[queue] += 1;
        const double pb = maxP * (avr - minThresh) / (maxThresh - minThresh);
        const double pa = pb / (1 - count * pb);
        const double rand = dblrand();

        if (rand < pa)
        {
            EV << "RED: rand < pa (" << rand << " < " << pa << ")! Executing MaxQPolicy." << endl;
            maxQPolicy->run(queue);
            qCounters[queue] = 0;
        }
    }
    else
    {
        qCounters[queue] = -1;
    }
}

