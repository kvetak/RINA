//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

const char* SIG_STAT_RMTPORT_UP = "RMTPort_PassUp";
const char* SIG_STAT_RMTPORT_DOWN = "RMTPort_PassDown";

Define_Module(RMTPort);

void RMTPort::initialize()
{
    ready = false; // port should get activated by RA
    blockedOutput = false;
    blockedInput = false;

    waitingOnInput = 0;
    waitingOnOutput = 0;

    southInputGate = gateHalf(GATE_SOUTHIO, cGate::INPUT);
    southOutputGate = gateHalf(GATE_SOUTHIO, cGate::OUTPUT);
    postServeDelay = par("postServeDelay").doubleValue() / 1000;

    queueIdGen = check_and_cast<QueueIDGenBase*>
            (getModuleByPath("^.^.^.resourceAllocator.queueIdGenerator"));

    sigStatRMTPortUp = registerSignal(SIG_STAT_RMTPORT_UP);
    sigStatRMTPortDown = registerSignal(SIG_STAT_RMTPORT_DOWN);
    sigRMTPortReady = registerSignal(SIG_RMT_PortReadyToServe);

    WATCH(ready);
    WATCH(waitingOnInput);
    WATCH(waitingOnOutput);
    WATCH(blockedInput);
    WATCH(blockedOutput);
    WATCH(postServeDelay);
    WATCH_PTR(flow);
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
            emit(sigStatRMTPortDown, true);
            setReadyDelayed();
        }
        else if (!opp_strcmp(msg->getFullName(), "readyToServe"))
        {
            setReady();
            emit(sigRMTPortReady, this);
        }
        delete msg;
    }
    else if (msg->getArrivalGate() == southInputGate) // incoming message
    {
        if (dynamic_cast<CDAPMessage*>(msg) != NULL)
        { // this will go away when we figure out management flow pre-allocation
            send(msg, getManagementQueue(RMTQueue::INPUT)->getInputGate()->getPreviousGate());
            emit(sigStatRMTPortUp, true);
        }
        else if (dynamic_cast<PDU*>(msg) != NULL)
        {
            // get a proper queue for this message
            RMTQueue* inQueue = getQueueById(RMTQueue::INPUT,
                                             queueIdGen->generateID((PDU*)msg).c_str());

            if (inQueue != NULL)
            {
                send(msg, inQueue->getInputGate()->getPreviousGate());
                emit(sigStatRMTPortUp, true);
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
                if (transmitEnd > simTime())
                { // transmit requires some simulation time
                    scheduleAt(transmitEnd, new cMessage("portTransmitEnd"));
                }
                else
                {
                    setReadyDelayed();
                    emit(sigStatRMTPortDown, true);
                }
            }
            else
            { // there isn't any delay or rate control in place
                setReadyDelayed();
                emit(sigStatRMTPortDown, true);
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

const RMTQueues& RMTPort::getOutputQueues() const
{
    return outputQueues;
}

void RMTPort::registerInputQueue(RMTQueue* queue)
{
    inputQueues.push_back(queue);
}


void RMTPort::registerOutputQueue(RMTQueue* queue)
{
    northInputGates.insert(queue->getOutputGate()->getNextGate());
    outputQueues.push_back(queue);
}

void RMTPort::unregisterInputQueue(RMTQueue* queue)
{
    inputQueues.erase(std::remove(inputQueues.begin(), inputQueues.end(), queue),
                      inputQueues.end());
}

void RMTPort::unregisterOutputQueue(RMTQueue* queue)
{
    northInputGates.erase(queue->getOutputGate()->getNextGate());
    outputQueues.erase(std::remove(outputQueues.begin(), outputQueues.end(), queue),
                       outputQueues.end());
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
    fullId << (type == RMTQueue::INPUT ? "inQ_" : "outQ_") << queueId;

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
    if (blockedOutput == false)
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

void RMTPort::redrawGUI(bool redrawParent)
{
    if (ev.isGUI())
    {
        getDisplayString().setTagArg("i2", 0, (isReady() ? "status/green" : "status/noentry"));

        if (redrawParent)
        {
            std::ostringstream ostr;
            ostr << "dst app: " << dstAppAddr << endl;
            if (blockedInput)
            {
                ostr << "input blocked" << endl;
            }
            if (blockedOutput)
            {
                ostr << "output blocked" << endl;
            }

            cDisplayString& dStr = getParentModule()->getDisplayString();

            dStr.setTagArg("t", 0, ostr.str().c_str());
            dStr.setTagArg("t", 1, "t");
        }
    }
}

const Flow* RMTPort::getFlow() const
{
    return flow;
}

void RMTPort::setFlow(Flow* flow)
{
    this->flow = flow;

    // display address of the remote IPC on top of the module
    if (ev.isGUI())
    {
        if (flow != NULL)
        {
            // shitty temporary hack to strip the layer name off
            const std::string& dstAppFull = flow->getDstApni().getApn().getName();
            dstAppAddr = dstAppFull.substr(0, dstAppFull.find("_"));
        }
        else
        {
            dstAppAddr = "N/A (PHY)";
        }
        redrawGUI(true);
    }
}

void RMTPort::blockOutput()
{
    EV << getFullPath() << ": blocking the port output." << endl;
    blockedOutput = true;
    if (ready)
    {
        setBusy();
    }
    redrawGUI(true);
}

void RMTPort::unblockOutput()
{
    EV << getFullPath() << ": unblocking the port output." << endl;
    blockedOutput = false;
    setReady();
    redrawGUI(true);
}

void RMTPort::blockInput()
{
    EV << getFullPath() << ": blocking the port input." << endl;
    blockedInput = true;
    redrawGUI(true);
}

void RMTPort::unblockInput()
{
    EV << getFullPath() << ": unblocking the port input." << endl;
    blockedInput = false;
    redrawGUI(true);
}
