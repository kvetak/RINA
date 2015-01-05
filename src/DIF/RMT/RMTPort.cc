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
    southInputGate = gateHalf(GATE_SOUTHIO, cGate::INPUT);
    southOutputGate = gateHalf(GATE_SOUTHIO, cGate::OUTPUT);
    ready = true;

    queueIdGen = check_and_cast<QueueIDGenBase*>
            (getModuleByPath("^.^.resourceAllocator.queueIdGenerator"));
}

void RMTPort::handleMessage(cMessage *msg)
{
    if (msg->getArrivalGate() == southInputGate)
    {
        if (dynamic_cast<CDAPMessage*>(msg) != NULL)
        { // this will go away when we figure out management flow pre-allocation
            send(msg, getManagementQueue(RMTQueue::INPUT)->getInputGate()->getPreviousGate());
        }
        else if (dynamic_cast<PDU_Base*>(msg) != NULL)
        { // still unsure about whether this'll be needed
            RMTQueue* inQueue = getQueueById(RMTQueue::INPUT,
                                             queueIdGen->generateID((PDU_Base*)msg).c_str());

            if (inQueue != NULL)
            {
                send(msg, inQueue->getInputGate()->getPreviousGate());
            }
            else
            {
                EV << "no input queue with respective ID is available!";
            }
        }
        else
        {
            EV << "this type of message isn't supported!" << endl;
        }

    }
    else if (northInputGates.count(msg->getArrivalGate()))
    {
        send(msg, southOutputGate);
    }
}


const RMTQueues& RMTPort::getInputQueues() const
{
    return inputQueues;
}

void RMTPort::addInputQueue(RMTQueue* queue, cGate* portGate)
{
    northOutputGates.insert(portGate);
    inputQueues.push_back(queue);
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

RMTQueue* RMTPort::getManagementQueue(RMTQueueType type)
{
    RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    return queueVect.front();
}

RMTQueue* RMTPort::getFirstQueue(RMTQueueType type)
{
    RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    return queueVect.at(1);
}

RMTQueue* RMTPort::getLongestQueue(RMTQueueType type)
{
    RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    int longest = 0;
    RMTQueue* result = NULL;

    for(RMTQueuesIter it = queueVect.begin(); it != queueVect.end(); ++it)
    {
        RMTQueue* q = *it;
        if (q->getLength() > longest)
        {
            longest = q->getLength();
            result = q;
        }
    }
    return result;
}

RMTQueue* RMTPort::getQueueById(RMTQueueType type, const char* queueId)
{
    RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    std::ostringstream fullId;
    fullId << getFullName() << (type == RMTQueue::INPUT ? 'i' : 'o') << queueId;

    for(RMTQueuesIter it = queueVect.begin(); it != queueVect.end(); ++it)
    {
        RMTQueue* q = *it;
        if (!opp_strcmp(q->getFullName(), fullId.str().c_str()))
        {
            return q;
        }
    }
    return NULL;
}

bool RMTPort::isReady()
{
    return ready;
}

void RMTPort::setReady()
{
    ready = true;
    redrawGUI();
}

void RMTPort::setBusy()
{
    ready = false;
    redrawGUI();
}

void RMTPort::redrawGUI()
{
    getDisplayString().setTagArg("i2", 0, (isReady() ? "status/green" : "status/noentry"));
}

const Flow* RMTPort::getFlow() const
{
    return flow;
}

void RMTPort::setFlow(Flow* flow)
{
    this->flow = flow;

    // display address of the remote IPC on top of the module
    if (flow != NULL)
    {
        // shitty temporary hack to strip the layer name off
        const std::string& dstAppFull = flow->getDstApni().getApn().getName();
        const std::string& dstAppAddr = dstAppFull.substr(0, dstAppFull.find("_"));
        getDisplayString().setTagArg("t", 0, dstAppAddr.c_str());

    }
    else
    {
        getDisplayString().setTagArg("t", 0, "PHY");
    }

}
