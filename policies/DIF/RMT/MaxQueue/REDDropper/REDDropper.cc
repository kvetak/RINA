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

#include "DIF/RMT/MaxQueue/REDDropper/REDDropper.h"

Define_Module(REDDropper);

void REDDropper::onPolicyInit()
{
    monitor = dynamic_cast<REDMonitor*>(qMonPolicy);
    if (monitor == NULL)
    {
        EV << "!!! REDDropper has to be used in conjecture with REDMonitor!" << endl;
    }
}

/**
 * Either drops or marks the last PDU in given queue (depending on the NED setting).
 *
 * @param queue target queue
 * @return true for PDU drop, false for PDU mark
 */
bool REDDropper::dropOrMark(RMTQueue* queue)
{
    if (par("marking").boolValue() == true)
    {
        EV << "REDDropper: Marking the last message in " << queue->getFullName()
           << " with an ECN bit." << endl;
        queue->markCongestionOnLast();
        return false;
    }
    else
    {
        EV << "REDDropper: executing tail drop in " << queue->getFullName() << endl;
        return true;
    }
}

/**
 * Decides whether to mark/drop last incoming packet in a queue.
 *
 * @param queue target queue
 * @return true for PDU drop, false for PDU mark
 */
bool REDDropper::run(RMTQueue* queue)
{
    if (monitor == NULL)
    {
        return false;
    }

    // gather some variables from the queue, the monitoring policy and the NED module
    const char* qname = queue->getFullName();
    int length = queue->getLength();
    int minThresh = queue->getThreshLength();
    int maxThresh = queue->getMaxLength();
    double avr = monitor->qAvgLengths[queue];
    int count = monitor->qCounters[queue];
    double maxP = par("dropProbability").doubleValue();

    bool dropped = false;

    if (minThresh <= avr && avr < maxThresh)
    {
        monitor->qCounters[queue] += 1;
        const double pb = maxP * (avr - minThresh) / (maxThresh - minThresh);
        double pa;
        if ((count * pb) < 1)
        {
            pa = pb / (1 - (count * pb));
        }
        else
        {
            pa = 1.0;
        }

        const double rand = dblrand();

        if (rand < pa)
        {
            EV << "REDDropper: rand < pa (" << rand << " < " << pa << ")" << endl;
            monitor->qCounters[queue] = 0;
            dropped = dropOrMark(queue);
        }
    }
    else if (avr >= maxThresh)
    {
        EV << "REDDropper: Average queue length in " << qname << " exceeds the maximum threshold." << endl;
        monitor->qCounters[queue] = 0;
        dropped = dropOrMark(queue);
    }
    else if (length >= maxThresh)
    {
        EV << "REDDropper: Queue length in " << qname << " exceeds the maximum threshold." << endl;
        monitor->qCounters[queue] = 0;
        dropped = dropOrMark(queue);
    }
    else
    {
        monitor->qCounters[queue] = -1;
    }

    return dropped;
}
