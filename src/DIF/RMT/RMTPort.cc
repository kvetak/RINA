//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "RMTPort.h"

Define_Module(RMTPort);

void RMTPort::initialize()
{
    southInputGate = gateHalf("southIo", cGate::INPUT);
    southOutputGate = gateHalf("southIo", cGate::OUTPUT);
}

void RMTPort::handleMessage(cMessage *msg)
{
    if (msg->getArrivalGate() == southInputGate)
    {
        send(msg, northOutputGate);
    }
    else if (northInputGates.count(msg->getArrivalGate()))
    {
        send(msg, southOutputGate);
    }
}

RMTQueue* RMTPort::getInputQueue() const
{
    return inputQueue;
}

void RMTPort::setInputQueue(RMTQueue* queue, cGate* portGate)
{
    inputQueue = queue;
    northOutputGate = portGate;
}

const RMTQueues& RMTPort::getOutputQueues() const
{
    return outputQueues;
}

void RMTPort::addOutputQueue(RMTQueue* queue, cGate* portGate)
{
    northInputGates.insert(portGate);
    outputQueues.push_back(queue);
}

cGate* RMTPort::getSouthInputGate() const
{
    return southInputGate;
}

cGate* RMTPort::getSouthOutputGate() const
{
    return southOutputGate;
}
