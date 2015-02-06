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
    ready = false; // port should get activated by RA
    blocked = false;
    southInputGate = gateHalf(GATE_SOUTHIO, cGate::INPUT);
    southOutputGate = gateHalf(GATE_SOUTHIO, cGate::OUTPUT);
    postServeDelay = par("postServeDelay").doubleValue() / 1000;


    queueIdGen = check_and_cast<QueueIDGenBase*>
            (getModuleByPath("^.^.resourceAllocator.queueIdGenerator"));

    sigRMTPortPDURcvd = registerSignal(SIG_RMT_PortPDURcvd);
    sigRMTPortPDUSent = registerSignal(SIG_RMT_PortPDUSent);
    sigRMTPortReady = registerSignal(SIG_RMT_PortReadyToServe);
}

void RMTPort::postInitialize()
{
    // this will be NULL if this IPC doesn't use a channel
    outputChannel = southOutputGate->findTransmissionChannel();
}

void RMTPort::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage())
    {
        if (!opp_strcmp(msg->getFullName(), "portTransmitEnd"))
        { // a PDU transmit procedure has just been finished
            //emit(sigRMTPortPDUSent, this);
            setReadyDelayed();
            delete msg;
        }
        else if (!opp_strcmp(msg->getFullName(), "readyToServe"))
        {
            setReady();
            emit(sigRMTPortReady, this);
        }
    }
    else if (msg->getArrivalGate() == southInputGate) // incoming message
    {
        if (dynamic_cast<CDAPMessage*>(msg) != NULL)
        { // this will go away when we figure out management flow pre-allocation
            send(msg, getManagementQueue(RMTQueue::INPUT)->getInputGate()->getPreviousGate());
        }
        else if (dynamic_cast<PDU*>(msg) != NULL)
        {
            // get a proper queue for this message
            RMTQueue* inQueue = getQueueById(RMTQueue::INPUT,
                                             queueIdGen->generateID((PDU*)msg).c_str());

            if (inQueue != NULL)
            {
                send(msg, inQueue->getInputGate()->getPreviousGate());
            }
            else
            {
                EV << "no input queue with such ID is available!";
            }
        }
        else
        {
            EV << "this type of message isn't supported!" << endl;
        }

        emit(sigRMTPortPDURcvd, this);
    }
    else if (northInputGates.count(msg->getArrivalGate())) // outgoing message
    {
        cPacket* packet = NULL;
        if ((packet = dynamic_cast<cPacket*>(msg)) != NULL)
        {
            // start the transmission
            send(packet, southOutputGate);

            // determine when should the port be ready to serve again
            if (outputChannel != NULL)
            { // we're using a channel, likely with some sort of data rate/delay
                simtime_t transmitEnd = outputChannel->getTransmissionFinishTime();
//                EV << "!!!!!!!!! transmit start: " << simTime()
//                   << "; transmit end: " << transmitEnd << endl;
                if (transmitEnd > simTime())
                { // transmit requires some simulation time
                    scheduleAt(transmitEnd, new cMessage("portTransmitEnd"));
                }
                else
                {
                    setReadyDelayed();
                    emit(sigRMTPortPDUSent, this);
                }
            }
            else
            { // there isn't any delay or rate control in place
                setReadyDelayed();
                //emit(sigRMTPortPDUSent, this);
                emit(sigRMTPortReady, this);
            }
        }
        else
        {
            EV << "this type of message isn't supported!" << endl;
        }
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

RMTQueue* RMTPort::getManagementQueue(RMTQueueType type) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    return queueVect.front();
}

RMTQueue* RMTPort::getFirstQueue(RMTQueueType type) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    return queueVect.at(1);
}

RMTQueue* RMTPort::getLongestQueue(RMTQueueType type) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    int longest = 0;
    RMTQueue* result = NULL;

    for(RMTQueuesConstIter it = queueVect.begin(); it != queueVect.end(); ++it)
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

RMTQueue* RMTPort::getQueueById(RMTQueueType type, const char* queueId) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    std::ostringstream fullId;
    fullId << getFullName() << (type == RMTQueue::INPUT ? 'i' : 'o') << queueId;

    for(RMTQueuesConstIter it = queueVect.begin(); it != queueVect.end(); ++it)
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
    if (blocked == false)
    {
        ready = true;
        emit(sigRMTPortReady, this);
        redrawGUI();
    }
}

void RMTPort::setReadyDelayed()
{
    scheduleAt(simTime() + postServeDelay, new cMessage("readyToServe"));
}

void RMTPort::setBusy()
{
    ready = false;
    redrawGUI();
}

void RMTPort::redrawGUI()
{
    if (!ev.isGUI())
    {
        return;
    }

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

void RMTPort::blockOutput()
{
    EV << getFullPath() << ": blocking the port output." << endl;
    blocked = true;
    if (ready)
    {
        setBusy();
    }
}

void RMTPort::unblockOutput()
{
    EV << getFullPath() << ": unblocking the port output." << endl;
    blocked = false;
    setReady();
}
