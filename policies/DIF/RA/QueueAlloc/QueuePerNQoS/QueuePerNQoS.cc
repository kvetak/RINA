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


#include "DIF/RA/QueueAlloc/QueuePerNQoS/QueuePerNQoS.h"

Define_Module(QueuePerNQoS);

void QueuePerNQoS::onNM1PortInit(RMTPort* port)
{
    // get this IPCP's QoS cubes
    const QoSCubeSet& cubes = ra->getQoSCubes();

    rmtAllocator->addQueue(RMTQueue::OUTPUT, port, "M");
    rmtAllocator->addQueue(RMTQueue::INPUT, port, "M");

    // create a pair of queues for each available QoS cube (including management)
    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it)
    {
        // exclude management QoS, this is handled in a different way
        if (it->getQosId() == VAL_MGMTQOSID) continue;

        rmtAllocator->addQueue(RMTQueue::OUTPUT, port, it->getQosId().c_str());
        rmtAllocator->addQueue(RMTQueue::INPUT, port, it->getQosId().c_str());
    }
}
