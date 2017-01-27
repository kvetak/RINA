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

/*
 * SmartMonitor.h
 *
 *  Created on: Apr 21, 2015
 *      Author: gaixas1
 */

#ifndef SMARTMONITOR_H_
#define SMARTMONITOR_H_

#include "DIF/RMT/Monitor/RMTQMonitorBase.h"

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
    virtual RMTQueue* getNextInput(RMTPort* port) = 0;
    virtual RMTQueue* getNextOutput(RMTPort* port) = 0;

    virtual double getInDropProb(RMTQueue * queue) = 0;
    virtual double getOutDropProb(RMTQueue * queue) = 0;
};




#endif /* SMARTMONITOR_H_ */
