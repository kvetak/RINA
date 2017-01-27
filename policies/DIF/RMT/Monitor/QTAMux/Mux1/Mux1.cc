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

#include "DIF/RMT/Monitor/QTAMux/Mux1/Mux1.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;

Mux1::Mux1 (QTAMonitor * _parent, cXMLElement* config) :
        Mux(_parent) {
    maxU = 10; maxC = 10;
    if(config != nullptr) {
        maxU = atoi(config->getAttribute("maxU"));
        maxC = atoi(config->getAttribute("maxC"));
        if(maxU < 0 || maxU > 10) { maxU = 10; }
        if(maxC < 0 || maxC > 10) { maxC = 10; }
    }

    for(int i = 0; i <= maxC; i++) {
        CATh.push_back(maxC*10 + 10 - i*10);
        CTh.push_back(maxC*8 + 8 - i*8);
        CDprob.push_back(0.5);
    }
    for(int i = 0; i <= maxU; i++) {
        UQ.push_back(queue<RMTQueue *>());
    }

    if(config != nullptr) {
        cXMLElementList CThConf = config->getChildrenByTagName("CTh");
        for(auto & thConf : CThConf) {
            int C = atoi(thConf->getAttribute("C"));
            int ath = atoi(thConf->getAttribute("ath"));
            int th = atoi(thConf->getAttribute("th"));
            double p = atof(thConf->getAttribute("p"));
            if(C <0 || C > maxC) { continue; }
            if(ath < 0) { ath = 0; }
            if(th < 0) { th = 0; }
            if(th > ath) { th = ath; }
            if(p < 0.0) { p = 0.0; }
            if(p > 1.0) { p = 1.0; }
            CATh[C] = ath;
            CTh[C] = th;
            CDprob[C] = p;
        }
    }
}

Mux1::Mux1 (QTAMonitor * _parent, int _maxU, int _maxC,  vector<int> & _CATh, vector<int> & _CTh, vector<double> & _CDprob) :
    Mux(_parent), maxU(_maxU), maxC(_maxC), CATh(_CATh), CTh(_CTh), CDprob(_CDprob) {
    for(int i = 0; i <= maxU; i++) {
        UQ.push_back(queue<RMTQueue *>());
    }
}

Mux * Mux1::clone(RMTPort * _port) {
    Mux1 * c = new Mux1(parent, maxU, maxC, CATh, CTh, CDprob);
    c->set(_port);
    return c;
}

void Mux1::add(RMTQueue * q, char urgency, char cherish) {
    if(cherish > maxC) { cherish = maxU; }
    if(cherish < 0) { cherish = 0; }

    int ath = CATh[cherish];
    int th = CTh[cherish];
    double p = CDprob[cherish];


    if(ath < count || (th < count && p < uniform(omnetpp::getEnvir()->getRNG(0), 0.0,1.0)) ) {
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

RMTQueue * Mux1::getNext() {
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
