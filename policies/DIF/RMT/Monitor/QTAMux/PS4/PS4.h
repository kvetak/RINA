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
 * PS : rate control,  spacing : variable rate
 *      fixed cherish/urgency
 */

#include <list>

#include "DIF/RMT/Monitor/QTAMux/PS.h"


namespace QTAMux {
using namespace std;


struct CU4 {
    double prob;
    char urgency, cherish;
    CU4 (double r, char u, char c);
};

struct CU4List{
    double rate;
    list<CU4> CUs;
    CU4List (double r);
};

class PS4 : public PS {
public:
    PS4 (string _name, QTAMonitor * _parent, cXMLElement* config);
    PS * clone(RMTPort * _port, RMTQueue * _queue, Mux * _mux);
    void setCU(list<CU4List> & _CUs);
    void setHeader(int _header);
    void setRateVar(int _rtvar);
    void setBtXbit(double min, double max);
    void setIntervalSize(int s);
    void setMaxQSize(int s);
    void setMaxBacklog(double s);

    void run();
    void inserted();

protected:

    int maxQSize;
    double maxBacklog;

    int header;
    double rtvar, minWtXbit, maxWtXbit;
    list<CU4List> CU4Lists;

    bool running;

    int waiting;
    list<double> W, C, U;
    double Bl;

    int intervalSize;
    list<simtime_t> arrivalTime;
    list<int> arrivalSize;
    long intervalData;
};

}
