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

#include "DIF/RMT/Monitor/QTAMux/Mux4/Mux4.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;

Mux4::Mux4 (QTAMonitor * _parent, cXMLElement* config) :
        Mux(_parent) {

    th = 100;
    maxE = 10;


    if(config != nullptr) {
        th = atoi(config->getAttribute("th"));
        maxE = atoi(config->getAttribute("MaxE"));

        if(th < 1) { th = 1; }
        if(maxE < 0) { maxE = 0; }
    }
}

Mux4::Mux4 (QTAMonitor * _parent, int _th, int _MaxE) :
        Mux(_parent), th(_th), maxE(_MaxE) {}

Mux * Mux4::clone(RMTPort * _port) {
    Mux4 * c = new Mux4(parent, th, maxE);
    c->set(_port);
    return c;
}

void Mux4::addedQueue(RMTQueue * q) {}

void Mux4::add(RMTQueue * q, char urgency, char cherish) {

    const cPacket *p = q->getLastPDU();
    const PDU * pdu = dynamic_cast<const PDU*>(p);
    if(pdu == nullptr) {
        cerr << "Non-PDU received"<< endl;
        return;
    }

    int & ecnM = FlowECN[pdu->getConnId()];

    if(th > (int)Q.size()) {
        Q.push(q);

        if(ecnM > 0) {
            q->markCongestionOnLast();
            ecnM--;
        }

    } else {
        parent->recDelete(q->dropLast());
        if(ecnM > maxE) { ecnM++; }

    }
}

RMTQueue * Mux4::getNext() {
    if(Q.empty()) { return nullptr; }
    RMTQueue * q = Q.front();
    Q.pop();
    return q;
}

}
