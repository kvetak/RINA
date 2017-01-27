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

#include "DIF/RMT/Monitor/QTAMux/PS0/PS0.h"

namespace QTAMux {
using namespace std;

PS0::PS0 (string _name, QTAMonitor * _parent, cXMLElement* config) :
        PS(_name, _parent) {

    urgency = 10; cherish = 10;
    if(config != nullptr) {
        urgency = atoi(config->getAttribute("urgency"));
        cherish = atoi(config->getAttribute("cherish"));
        if(urgency < 0 || urgency > 10) { urgency = 10; }
        if(cherish < 0 || cherish > 10) { cherish = 10; }
    }
}

PS * PS0::clone(RMTPort * _port, RMTQueue * _queue, Mux * _mux) {
    PS0 * c = new PS0(name, parent, nullptr);
    c->set(_port, _queue, _mux);
    c->setCU(urgency, cherish);
    return c;
}

void PS0::setCU(char _urgency, char _cherish) {
    urgency = _urgency;
    cherish = _cherish;
}

void PS0::run() {}

void PS0::inserted() {
    mux->add(q, urgency, cherish);
}

}
