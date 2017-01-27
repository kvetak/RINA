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

#include "DIF/RMT/Monitor/QTAMux/PS1/PS1.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;

PS1::PS1 (string _name, QTAMonitor * _parent, cXMLElement* config) :
        PS(_name, _parent), running(false), waiting(0), Bl(0) {

    urgency = 10; cherish = 10; header = 8;
    if(config != nullptr) {
        urgency = atoi(config->getAttribute("urgency"));
        cherish = atoi(config->getAttribute("cherish"));
        header = atoi(config->getAttribute("header"));
        if(urgency < 0 || urgency > 10) { urgency = 10; }
        if(cherish < 0 || cherish > 10) { cherish = 10; }
        if(header < 0) { header = 0; }
    }
}

PS * PS1::clone(RMTPort * _port, RMTQueue * _queue, Mux * _mux) {
    PS1 * c = new PS1(name, parent, nullptr);
    c->set(_port, _queue, _mux);
    c->setCU(urgency, cherish);
    c->setHeader(header);

    long portRate = _port->getInputRate();
    c->setBtXbit(1.0/portRate);
    return c;
}

void PS1::setCU(char _urgency, char _cherish) {
    urgency = _urgency;
    cherish = _cherish;
}

void PS1::setHeader(int _header) {
    header = _header;
}

void PS1::setBtXbit(double r) {
    wtXbit = r;
}

void PS1::run() {
    running = true;
    if (waiting <= 0) {
        running = false;
        return;
    }

    mux->add(q, urgency, cherish);

    if(W.empty()) { running = false; }
    else {
        double w = W.front();
        W.pop_front();
        Bl -= w;
        parent->schedulePS(this, w);
    }
}

void PS1::inserted() {
    double w = (q->getLastPDU()->getBitLength() + header) * wtXbit;
    if(q->getLength() >= maxQSize || w + Bl > maxBacklog) {
        parent->recDelete(q->dropLast());
        return;
    }
    W.push_back(w);
    Bl += w;
    waiting++;
    if(!running) { run(); }
}

}
