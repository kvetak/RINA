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

#include "DIF/RMT/Monitor/QTAMux/Mux0/Mux0.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;

Mux0::Mux0 (QTAMonitor * _parent, cXMLElement* config) :
        Mux(_parent) {
    maxU = 10; maxC = 10;
    if(config != nullptr) {
        maxU = atoi(config->getAttribute("maxU"));
        maxC = atoi(config->getAttribute("maxC"));
        if(maxU < 0 || maxU > 10) { maxU = 10; }
        if(maxC < 0 || maxC > 10) { maxC = 10; }
    }

    for(int i = 0; i <= maxC; i++) {
        CTh.push_back(maxC*10 + 10 - i*10);
    }
    for(int i = 0; i <= maxU; i++) {
        UQ.push_back(queue<RMTQueue *>());
    }

    if(config != nullptr) {
        cXMLElementList CThConf = config->getChildrenByTagName("CTh");
        for(auto & thConf : CThConf) {
            int C = atoi(thConf->getAttribute("C"));
            int th = atoi(thConf->getAttribute("th"));
            if(C <0 || C > maxC) { continue; }
            if(th < 0) { th = 0; }
            CTh[C] = th;
        }
    }
}

Mux0::Mux0 (QTAMonitor * _parent, int _maxU, int _maxC, vector<int> & _CTh) :
    Mux(_parent), maxU(_maxU), maxC(_maxC), CTh(_CTh) {
    for(int i = 0; i <= maxU; i++) {
        UQ.push_back(queue<RMTQueue *>());
    }
}

Mux * Mux0::clone(RMTPort * _port) {
     Mux0 * c = new Mux0(parent, maxU, maxC, CTh);
     c->set(_port);
     return c;
}

void Mux0::add(RMTQueue * q, char urgency, char cherish) {
    if(cherish > maxC) { cherish = maxU; }
    if(cherish < 0) { cherish = 0; }

    int th = CTh[cherish];
    if(th < count) {
        parent->recDelete(q->dropFirst());
        return;
    }

    if(urgency > maxU) { urgency = maxU; }
    if(urgency < 0) { urgency = 0; }

    count++;
    UQ[urgency].push(q);

    if(count == 1 && port->isOutputReady()) {
        parent->callMux(port);
    }
}

RMTQueue * Mux0::getNext() {
    if(count <= 0) { return nullptr; }
    for(int i = 0; i <= maxU; i++) {
        if(UQ[i].empty()) { continue; }
        RMTQueue * rq = UQ[i].front();
        UQ[i].pop();
        count --;
        return rq;
    }
    return nullptr;
}

}
