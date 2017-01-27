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
 * Mux : Cherish/Urgency
 *      Cherish Drop : AbsTH || TH + DropProb
 *          -> Drop First
 */

#include "DIF/RMT/Monitor/QTAMux/Mux.h"
#include <vector>
#include <map>
#include <queue>

namespace QTAMux {
using namespace std;

class Mux2 : public Mux {
public:
    Mux2 (QTAMonitor * _parent, cXMLElement* config);
    Mux2 (QTAMonitor * _parent, int _maxU, int _maxC,
            vector<int> & _CATh, vector<int> & _CTh, vector<double> & _CDprob,
            int _defaultEcnTh, map<string, int> _baseEcnQTh);
    virtual Mux * clone(RMTPort * _port);

    virtual void add(RMTQueue * q, char urgency, char cherish);
    virtual RMTQueue * getNext();

    virtual void addedQueue(RMTQueue * q);
protected:
    int maxU, maxC;
    vector<int> CATh, CTh;
    vector<double> CDprob;
    vector<queue<RMTQueue *> > UQ;

    int defaultEcnTh;
    map<string, int> baseEcnQTh;
    map<RMTQueue *, int> ecnQTh;
    map<RMTQueue *, queue<unsigned short> > queueAddedAt;
    long long currentSeq;
};

}
