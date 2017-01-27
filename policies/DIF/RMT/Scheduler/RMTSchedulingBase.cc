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

#include "DIF/RMT/Scheduler/RMTSchedulingBase.h"

Define_Module(RMTSchedulingBase);

void RMTSchedulingBase::initialize()
{
    rmtAllocator = getRINAModule<RMTModuleAllocator*>(this, 1, {MOD_RMTALLOC});

    setPolicyDisplayString(this);
    onPolicyInit();
}

void RMTSchedulingBase::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && !opp_strcmp(msg->getFullName(), "processPort"))
    { // TODO: this is lousy, think of something better
        RMTQueueType direction = (RMTQueueType)msg->par("direction").longValue();
        const char* portName = msg->par("portName").stringValue();
        RMTPort* port = rmtAllocator->getPort(portName);
        if (port != NULL)
        {
            processQueues(port, direction);
        }
        else
        {
            EV << "RMT Scheduler reinvocation: Port " << portName
               << " ceased to exist!" << endl;
        }
    }

    delete msg;
}

void RMTSchedulingBase::onPolicyInit()
{
}

void RMTSchedulingBase::scheduleReinvocation(simtime_t time, RMTPort* port, RMTQueueType direction)
{
    // TODO: this is lousy, think of something better
    cMessage* msg = new cMessage("processPort");
    msg->addPar("portName");
    msg->par("portName").setStringValue(port->getParentModule()->getFullName());

    msg->addPar("direction");
    msg->par("direction").setLongValue(direction);

    scheduleAt(time, msg);
}

void RMTSchedulingBase::processQueues(RMTPort* port, RMTQueueType direction)
{
}
