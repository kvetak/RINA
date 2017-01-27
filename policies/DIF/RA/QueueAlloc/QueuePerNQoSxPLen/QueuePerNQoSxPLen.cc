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

#include "DIF/RA/QueueAlloc/QueuePerNQoSxPLen/QueuePerNQoSxPLen.h"

Define_Module(QueuePerNQoSxPLen);

using namespace std;

void QueuePerNQoSxPLen::onNM1PortInit(RMTPort* port) {

    rmtAllocator->addQueue(RMTQueue::OUTPUT, port, "M");
    rmtAllocator->addQueue(RMTQueue::INPUT, port, "M");
    rmtAllocator->addQueue(RMTQueue::INPUT, port, "Q");

    // get this IPCP's QoS cubes
    const QoSCubeSet& cubes = ra->getQoSCubes();

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        if (it->getQosId() == VAL_MGMTQOSID) continue;

        for(int i = 1; i <= maxHCount; i++) {
            string q = it->getQosId() + "_" + to_string(i);
            rmtAllocator->addQueue(RMTQueue::OUTPUT, port, q.c_str());
        }
    }
}


void QueuePerNQoSxPLen::onPolicyInit() {
    maxHCount = par("maxHCount").longValue();
    if(maxHCount <= 0) { maxHCount = 1; }
}
