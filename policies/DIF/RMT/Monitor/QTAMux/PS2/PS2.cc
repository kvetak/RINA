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

#include "DIF/RMT/Monitor/QTAMux/PS2/PS2.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;

PS2::PS2 (string _name, QTAMonitor * _parent, cXMLElement* config) :
        PS(_name, _parent), running(false), waiting(0), Bl(0) {

    urgency = 10; cherish = 10; header = 8; rtvar = 0.1;
    if(config != nullptr) {
        urgency = atoi(config->getAttribute("urgency"));
        cherish = atoi(config->getAttribute("cherish"));
        header = atoi(config->getAttribute("header"));
        rtvar = atof(config->getAttribute("rtvar"));
        if(urgency < 0 || urgency > 10) { urgency = 10; }
        if(cherish < 0 || cherish > 10) { cherish = 10; }
        if(header < 0) { header = 0; }
        if(rtvar < 0.0) { rtvar = -rtvar; }
        if(rtvar > 1.0) { rtvar = 1.0; }
    }
}

PS * PS2::clone(RMTPort * _port, RMTQueue * _queue, Mux * _mux) {
    PS2 * c = new PS2(name, parent, nullptr);
    c->set(_port, _queue, _mux);
    c->setCU(urgency, cherish);
    c->setHeader(header);
    c->setRateVar(rtvar);

    long portRate = _port->getInputRate();
    c->setBtXbit((1.0-rtvar)/portRate, (1.0+rtvar)/portRate);
    return c;
}

void PS2::setCU(char _urgency, char _cherish) {
    urgency = _urgency;
    cherish = _cherish;
}

void PS2::setHeader(int _header) {
    header = _header;
}

void PS2::setRateVar(int _rtvar) {
    rtvar = _rtvar;
}

void PS2::setBtXbit(double min, double max) {
    minWtXbit = min;
    maxWtXbit = max;
}

void PS2::run() {
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

void PS2::inserted() {

    double w = (q->getLastPDU()->getBitLength() + header) * uniform(omnetpp::getEnvir()->getRNG(0), minWtXbit, maxWtXbit);
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
