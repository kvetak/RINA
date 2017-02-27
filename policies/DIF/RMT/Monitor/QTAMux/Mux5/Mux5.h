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

/*
 * Mux : WFQ per Urgency
 *      Drop : TH per Urgency
 *          -> Drop Last
 *      Mark ECN per flow : drop N of flow X, mark next N arriving at flow X
 */

#include "DIF/RMT/Monitor/QTAMux/Mux.h"
#include <vector>
#include <map>
#include <queue>

namespace QTAMux {
using namespace std;

struct M5QinfoStat {
    bool enoughTk;
    int priority;
    M5QinfoStat() {
        enoughTk = false;
        priority = 1000;
    }
    M5QinfoStat(bool _enoughTk, int _priority) {
        enoughTk = _enoughTk; //Vesely: added _enoughTh
        priority = _priority;
    }
    bool compare(const M5QinfoStat & o) const;
};

struct M5Qinfo {
    int w;
    int th;
    int tk;

    int rTkBit;
    int sTkBit;
    int maxTk;
    int priority;

    M5Qinfo() {
        w = 0;
        th = 0;
        tk = 0;

        rTkBit = 0;
        sTkBit = 0;
        maxTk = 0;
        priority = 999;
    }

    void removeTk(int);
    void addTk(int);
    M5QinfoStat getInfo(const int & s);

};

class Mux5 : public Mux {
public:
    Mux5 (QTAMonitor * _parent, cXMLElement* config);
    Mux5 (QTAMonitor * _parent, int _defaultTh, int _maxE, map<string, M5Qinfo> _baseQInfo);
    virtual Mux * clone(RMTPort * _port);

    virtual void add(RMTQueue * q, char urgency, char cherish);
    virtual RMTQueue * getNext();

    virtual void addedQueue(RMTQueue * q);
protected:

    int defaultTh;
    int maxE;

    map<string, M5Qinfo> baseQInfo;
    map<RMTQueue *, M5Qinfo> QInfo;

    map<ConnectionId, int> FlowECN;
};

}
