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
#include <fstream>
#include "DIF/RMT/Monitor/RMTQMonitorBase.h"

#include "DIF/RMT/Monitor/QTAMux/PS.h"
#include "DIF/RMT/Monitor/QTAMux/Mux.h"

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
    string nodeName;


    void onPolicyInit();
    void postQueueCreation(RMTQueue* queue);
    void postPDUInsertion(RMTQueue* queue);
    void preQueueRemoval(RMTQueue* queue);
    void finish();

    cMessage * schedulePS(PS * ps, simtime_t t);
    void callMux(RMTPort * port);

    RMTQueue * getNext(RMTPort * port);
    void recDelete(cPacket * p);

protected:
    void handleMessage(cMessage * msg);
    void recIDelete(cPacket * p);

private:
    QTASch * scheduler;
    map<string, PS *> baseShapers;
    map<RMTQueue *, PS *> shapers;

    Mux * baseMux;
    map<RMTPort *, Mux *> muxs;

    map<string, int> baseEcnTh;
    map<RMTQueue *, int> ecnTh;

    //Stats

    bool recordStats;
    bool saveStats;
    bool pdu_IO, data_IO, pdu_IOi, data_IOi;
    bool pdu_in_IO, data_in_IO, pdu_in_IOi, data_in_IOi;

    double record_interval, last_interval;
    long long currentInterval;
    cMessage * intervalM;

    set<string> recordedQoS;
    map<RMTPort*, map<string, long long> >
        qos_pdu_IO_in, qos_pdu_IO_out, qos_pdu_IO_drop,
        qos_data_IO_in, qos_data_IO_out, qos_data_IO_drop,
        qos_pdu_IOi_in, qos_pdu_IOi_out, qos_pdu_IOi_drop,
        qos_data_IOi_in, qos_data_IOi_out, qos_data_IOi_drop,
        qos_pdu_in_IO,
        qos_data_in_IO,
        qos_pdu_in_IOi,
        qos_data_in_IOi;

    map<RMTPort*, string> PortName;
    map<RMTPort*, string> PortStream;
    map<RMTPort*, string> PortStream_in;
    map<const PDU *, RMTPort *>PDU2Port;
    map<const PDU *, simtime_t>PDU2Arrival;

    void printInterval();
    void printSummary();
    void coutSummary();
};

}
