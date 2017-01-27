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

#include "DIF/RMT/RMTPort.h"

const char* SIG_STAT_RMTPORT_UP = "RMTPort_PassUp";
const char* SIG_STAT_RMTPORT_DOWN = "RMTPort_PassDown";

Define_Module(RMTPort);

void RMTPort::initialize()
{
    outputReady = false; // port should get activated by RA
    inputReady = false; // port should get activated by RA
    blockedOutput = false;
    blockedInput = false;

    inputReadRate = 0;
    postReadDelay = 0.0;

    waitingOnInput = 0;
    waitingOnOutput = 0;

    southInputGate = gateHalf(GATE_SOUTHIO, cGate::INPUT);
    southOutputGate = gateHalf(GATE_SOUTHIO, cGate::OUTPUT);

    queueIdGen = getRINAModule<QueueIDGenBase*>(this, 3, {MOD_RESALLOC, MOD_POL_RA_IDGENERATOR});

    sigStatRMTPortUp = registerSignal(SIG_STAT_RMTPORT_UP);
    sigStatRMTPortDown = registerSignal(SIG_STAT_RMTPORT_DOWN);
    sigRMTPortReadyToWrite = registerSignal(SIG_RMT_PortReadyToServe);
    sigRMTPortReadyForRead = registerSignal(SIG_RMT_PortReadyForRead);

    WATCH(outputReady);
    WATCH(inputReady);

    WATCH(waitingOnOutput);
    WATCH(waitingOnInput);
    WATCH(inputReadRate);

    WATCH(blockedOutput);
    WATCH(blockedInput);
    WATCH_PTR(flow);
}

void RMTPort::postInitialize()
{
    protectIn = gateHalf("protect$i", cGate::INPUT);
    protectOut = gateHalf("protect$o", cGate::OUTPUT);
    unprotectIn = gateHalf("unprotect$i", cGate::INPUT);
    unprotectOut = gateHalf("unprotect$o", cGate::OUTPUT);

    // this will be nullptr if this IPC doesn't use a channel
    outputChannel = southOutputGate->findTransmissionChannel();
}

void RMTPort::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage())
    {
        if (!opp_strcmp(msg->getFullName(), "portTransmitEnd"))
        { // a PDU transmit procedure has just been finished
            emit(sigStatRMTPortDown, true);
            scheduleNextWrite();
        }
        else if (!opp_strcmp(msg->getFullName(), "readyToServe"))
        {
            setOutputReady();
        }
        else if (!opp_strcmp(msg->getFullName(), "readyForRead"))
        {
            setInputReady();
        }

        delete msg;
    }
    else
    {
        if (msg->getArrivalGate() == southInputGate) // incoming message
        { // pass to SDU protection
            send(msg, unprotectOut);
        }
        else if (northInputGates.count(msg->getArrivalGate())) // outgoing message
        { // pass to SDU protection
            send(msg, protectOut);
        }
        else if (msg->getArrivalGate() == unprotectIn) // unprotected incoming message
        {
            SDUData* sduData = dynamic_cast<SDUData*>(msg);
            if(sduData == nullptr){
                delete msg;
                EV << "this type of message isn't supported!" << endl;
                return;
            }
            PDU* pdu = static_cast<PDU*>(sduData->decapsulate());
            delete sduData;
            // get a proper queue for this message
            std::string queueID =
                    queueIdGen->generateInputQueueID(pdu);

            RMTQueue* inQueue = getQueueById(RMTQueue::INPUT, queueID.c_str());

            if (inQueue != nullptr)
            {
                send(pdu, inQueue->getInputGate()->getPreviousGate());
                emit(sigStatRMTPortUp, true);
            }
            else
            {
                EV << getFullPath()
                                       << ": no input queue of such queue-id (" << queueID
                                       << ") available!" << endl;
                EV << pdu->getConnId().getQoSId() << endl;
            }
        }
        else if (msg->getArrivalGate() == protectIn) // protected outgoing message
        {
            PDU* pdu = dynamic_cast<PDU*>(msg);
            if (pdu == nullptr){
                delete msg;
                EV << "this type of message isn't supported!" << endl;
                return;
            }
            setOutputBusy();
            // start the transmission
            SDUData* sduData = new SDUData();
            sduData->encapsulate(pdu);
            send(sduData, southOutputGate);

            // determine when should the port be ready to serve again
            if (outputChannel != nullptr)
            { // we're using a channel, likely with some sort of data rate/delay
                simtime_t transmitEnd = outputChannel->getTransmissionFinishTime();
                if (transmitEnd > simTime())
                { // transmit requires some simulation time
                    scheduleAt(transmitEnd, new cMessage("portTransmitEnd"));
                }
                else
                {
                    scheduleNextWrite();
                    emit(sigStatRMTPortDown, true);
                }
            }
            else
            { // there isn't any delay or rate control in place, the PDU is already sent
                scheduleNextWrite();
                emit(sigStatRMTPortDown, true);
                emit(sigRMTPortReadyToWrite, this);
            }
        }
    }
}


RMTQueues& RMTPort::getInputQueues()
{
    return inputQueues;
}

RMTQueues& RMTPort::getOutputQueues()
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

RMTQueue* RMTPort::getFirstQueue(RMTQueueType type) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    return queueVect.front();
}

RMTQueue* RMTPort::getLongestQueue(RMTQueueType type) const
{
    const RMTQueues& queueVect = (type == RMTQueue::INPUT ? inputQueues : outputQueues);

    int longest = 0;
    RMTQueue* result = nullptr;

    for(auto const q : queueVect)
    {
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

    for(auto const q : queueVect)
    {
        if (!opp_strcmp(q->getFullName(), fullId.str().c_str()))
        {
            return q;
        }
    }
    return nullptr;
}

bool RMTPort::isOutputReady()
{
    return outputReady;
}

void RMTPort::setOutputReady()
{
    if (blockedOutput == false)
    {
        outputReady = true;
        emit(sigRMTPortReadyToWrite, this);
        redrawGUI();
    }
}

void RMTPort::setOutputBusy()
{
    outputReady = false;
    redrawGUI();
}

bool RMTPort::isInputReady()
{
    return inputReady;
}

void RMTPort::setInputReady()
{
    if (blockedInput == false)
    {
        inputReady = true;
        emit(sigRMTPortReadyForRead, this);
        redrawGUI();
    }
}

void RMTPort::setInputBusy()
{
    inputReady = false;
    redrawGUI();
}

void RMTPort::scheduleNextWrite()
{
    scheduleAt(simTime(), new cMessage("readyToServe"));
}

void RMTPort::scheduleNextRead()
{
    Enter_Method_Silent("scheduleNextRead()");
    setInputBusy();
    scheduleAt(simTime() + postReadDelay, new cMessage("readyForRead"));
}

unsigned long RMTPort::getWaiting(RMTQueueType direction)
{
    return (direction == RMTQueue::INPUT ? waitingOnInput : waitingOnOutput);
}

void RMTPort::addWaiting(RMTQueueType direction)
{
    direction == RMTQueue::INPUT ? waitingOnInput++ : waitingOnOutput++;
}

void RMTPort::substractWaiting(RMTQueueType direction)
{
    direction == RMTQueue::INPUT ? waitingOnInput-- : waitingOnOutput--;
}

long RMTPort::getInputRate()
{
    return inputReadRate;
}

void RMTPort::setInputRate(long pdusPerSecond)
{
    inputReadRate = pdusPerSecond;
    postReadDelay = 60.0 / pdusPerSecond;
}

void RMTPort::redrawGUI(bool redrawParent)
{
    if (getEnvir()->isGUI())
    {
        getDisplayString().setTagArg("i2", 0, (isOutputReady() ? "status/green" : "status/noentry"));

        if (redrawParent)
        {
            std::ostringstream ostr;
            ostr << "dstApp: " << endl << dstAppAddr << endl
                 << "QoS-id: " << endl << dstAppQoS;
            if (blockedInput)
            {
                ostr << endl << "input blocked";
            }
            if (blockedOutput)
            {
                ostr << endl << "output blocked" << endl;
            }

            cDisplayString& dStr = getParentModule()->getDisplayString();

            dStr.setTagArg("t", 0, ostr.str().c_str());
            dStr.setTagArg("t", 1, "r");
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
    if (getEnvir()->isGUI())
    {
        if (flow != nullptr)
        {
            // shitty temporary (yeah, right) hack to strip the layer name off
            const std::string& dstAppFull = flow->getDstApni().getApn().getName();
            dstAppAddr = dstAppFull.substr(0, dstAppFull.find("_"));
            dstAppQoS = flow->getConId().getQoSId();
        }
        else
        {
            dstAppAddr = "N/A (PHY)";
            dstAppQoS = "N/A (medium)";
        }
        redrawGUI(true);
    }
}

void RMTPort::blockOutput()
{
    EV << getFullPath() << ": blocking the port output." << endl;
    blockedOutput = true;
    if (outputReady)
    {
        setOutputBusy();
    }
    redrawGUI(true);
}

void RMTPort::unblockOutput()
{
    EV << getFullPath() << ": unblocking the port output." << endl;
    blockedOutput = false;
    setOutputReady();
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
    setInputReady();
    redrawGUI(true);
}
