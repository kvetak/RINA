/*
 * SmartMonitor.h
 *
 *  Created on: Apr 21, 2015
 *      Author: gaixas1
 */

#ifndef SMARTMONITOR_H_
#define SMARTMONITOR_H_

#include "RMTQMonitorBase.h"

struct queueStat {
    int ocupation;
    int threshold;
    double dropProb;
    int absThreshold;

    queueStat() :
        ocupation(1), threshold(0), dropProb(1), absThreshold(0) {}

    queueStat(int o, int t, double pD, int aT) :
        ocupation(o), threshold(t), dropProb(pD), absThreshold(aT) {}
};

class SmartMonitor : public RMTQMonitorBase {
public:
    virtual int getInCount(RMTPort* port) = 0;
    virtual RMTQueue* getNextInput(RMTPort* port) = 0;

    virtual int getOutCount(RMTPort* port) = 0;
    virtual RMTQueue* getNextOutput(RMTPort* port) = 0;

    virtual int getInThreshold(RMTQueue * queue) = 0;
    virtual int getOutThreshold(RMTQueue * queue) = 0;

    virtual queueStat getInStat(RMTQueue * queue) = 0;
    virtual queueStat getOutStat(RMTQueue * queue) = 0;
};




#endif /* SMARTMONITOR_H_ */
