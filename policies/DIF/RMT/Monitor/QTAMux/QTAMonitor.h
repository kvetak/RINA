//
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

#pragma once

#include <map>
#include "RMTQMonitorBase.h"

#include "QTAMux/PS.h"
#include "QTAMux/Mux.h"

#include "InfectionSignals.h"

class QTASch;

namespace QTAMux {
using namespace std;

class PSSched : public cMessage {
public :
    PSSched(PS * _ps);
    PS * ps;
};

class QTAMonitor: public RMTQMonitorBase {
public:
    void onPolicyInit();
    void postQueueCreation(RMTQueue* queue);
    void postPDUInsertion(RMTQueue* queue);
    void preQueueRemoval(RMTQueue* queue);
    void finish();

    cMessage * schedulePS(PS * ps, simtime_t t);
    void callMux(RMTPort * port);

    RMTQueue * getNext(RMTPort * port);
    void recDelete(cPacket * p);

    //Monitor usage
    double getPortUsage(RMTPort*);
    double getPortUsageP(RMTPort*);
    double getQueueUsage(RMTPort*, string);
    double getQueueUsageP(RMTPort*, string);

protected:
    void handleMessage(cMessage * msg);
    void recIDelete(cPacket * p);

    //Monitor usage
    int MonitoredLen;
    map<RMTPort *, list<simtime_t> > inPortTimes;
    map<RMTPort *, list<long> > inPortData;
    map<RMTPort *, long > inPortAgData;
    map<RMTPort *, map<string, list<simtime_t> > > inQueueTimes;
    map<RMTPort *, map<string, list<long> > > inQueueData;
    map<RMTPort *, map<string, long > > inQueueAgData;


private:
    QTASch * scheduler;
    map<string, PS *> baseShapers;
    map<RMTQueue *, PS *> shapers;

    Mux * baseMux;
    map<RMTPort *, Mux *> muxs;

    long currentPDU;
    map<cPacket *, long> PDUarrival;

    map<RMTPort*, map<string, long long> > received, sent;
};

}
