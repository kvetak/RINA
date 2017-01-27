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

#include "DIF/RMT/RMTQueue.h"

const char* SIG_STAT_RMTQUEUE_LENGTH = "RMTQueue_Length";
const char* SIG_STAT_RMTQUEUE_DROP = "RMTQueue_Drop";

Define_Module(RMTQueue);

RMTQueue::~RMTQueue()
{
    while (!queue.empty())
    {
        delete queue.front();
        queue.pop_front();
    }
}

void RMTQueue::finish()
{
    size_t pduCount = queue.size();
    if (pduCount)
    {
        EV << "Queue " << getFullPath() << " still contains " << pduCount
           << " unprocessed PDUs!" << endl;

        for (iterator it = begin(); it != end(); ++it)
        {
            cPacket* p = *it;
            EV << p->getClassName() << " received at " << p->getArrivalTime() << endl;
        }
    }
}


void RMTQueue::initialize()
{
    outputGate = gate("outputGate");
    inputGate = gate("inputGate");
    // message retrieval signal handler
    sigRMTPDUPreRcvd = registerSignal(SIG_RMT_QueuePDUPreRcvd);
    // message retrieval signal handler
    sigRMTPDUPostRcvd = registerSignal(SIG_RMT_QueuePDUPostRcvd);
    // message pre-departure signal handler
    sigRMTPDUPreSend = registerSignal(SIG_RMT_QueuePDUPreSend);
    // message departure signal handler
    sigRMTPDUSent = registerSignal(SIG_RMT_QueuePDUSent);
    // length for vector stats
    sigStatRMTQueueLength = registerSignal(SIG_STAT_RMTQUEUE_LENGTH);

    maxQLength = getModuleByPath("^.^")->par("defaultMaxQLength");
    thresholdQLength = getModuleByPath("^.^")->par("defaultThreshQLength");
    qTime = simTime();
    redrawGUI();

    WATCH(thresholdQLength);
    WATCH(maxQLength);
    WATCH(qTime);
}

void RMTQueue::setFlow(Flow * f){
    flow = f;
}
const Flow* RMTQueue::getFlow() const{
    return flow;
}


std::string RMTQueue::info() const
{
    std::ostringstream os;

    os << "name: " << this->getFullName()
       << "; type: " << ((this->type == INPUT) ? "input" : "output")
       << "; saturation: " << getLength() << "/" << this->maxQLength;

    return os.str();
}

std::ostream& operator <<(std::ostream& os, const RMTQueue& cte)
{
    return os << cte.info();
}


void RMTQueue::redrawGUI()
{
    if (!getEnvir()->isGUI())
    {
        return;
    }

    int len = getLength();
    cDisplayString& disp = getDisplayString();

    // change color to reflect queue saturation
    if (len == 0)
    {
        disp.setTagArg("i", 1, "");
    }
    else if (len < thresholdQLength)
    {
        disp.setTagArg("i", 1, "#80FF80");
    }
    else if (len < maxQLength)
    {
        disp.setTagArg("i", 1, "#FF8000");
    }
    else
    {
        disp.setTagArg("i", 1, "#800000");
    }

    // print current saturation in numbers
    std::ostringstream desc;
    desc << " " << len << "/" << maxQLength;
    disp.setTagArg("t", 1, "l");
    disp.setTagArg("t", 0, desc.str().c_str());
}

void RMTQueue::handleMessage(cMessage* msg)
{
    if (dynamic_cast<cPacket*>(msg) != nullptr)
    {
        enqueuePDU((cPacket*)msg);
    }
    else
    {
        EV << "handleMessage(): unsupported message type!" << endl;
    }
}

void RMTQueue::enqueuePDU(cPacket* pdu)
{
    emit(sigRMTPDUPreRcvd, this);
    queue.push_back(pdu);
    emit(sigRMTPDUPostRcvd, this);
    emit(sigStatRMTQueueLength, getLength());
    redrawGUI();
}

void RMTQueue::releasePDU(void)
{
    Enter_Method("releasePDU()");

    if (this->getLength() > 0)
    {
        emit(sigRMTPDUPreSend, this);
        cPacket* pdu = queue.front();
        queue.pop_front();
        send(pdu, outputGate);

        if (getLength() == 0)
        {
            qTime = simTime();
        }

        emit(sigRMTPDUSent, this);
        emit(sigStatRMTQueueLength, getLength());
        bubble("Releasing a PDU...");
        redrawGUI();
    }
}

cPacket* RMTQueue::dropLast()
{
    cPacket* dropped = queue.back();
    bubble("Dropping a PDU...");
    queue.pop_back();
    redrawGUI();
    return dropped;
}

cPacket* RMTQueue::dropFirst()
{
    cPacket* dropped = queue.front();
    bubble("Dropping a PDU...");
    queue.pop_front();
    redrawGUI();
    return dropped;
}

void RMTQueue::markCongestionOnLast()
{
    cPacket* msg = queue.back();

    if (dynamic_cast<PDU*>(msg) != nullptr)
    {
        PDU* pdu = (PDU*) msg;
        pdu->setFlags(pdu->getFlags() | ECN_FLAG);
    }
    else
    {
        EV << "The message isn't a PDU, cannot apply marking!" << endl;
    }
}

void RMTQueue::markCongestionOnFirst()
{
    cPacket* msg = queue.front();

    if (dynamic_cast<PDU*>(msg) != nullptr)
    {
        PDU* pdu = (PDU*) msg;
        pdu->setFlags(pdu->getFlags() | ECN_FLAG);
    }
    else
    {
        EV << "The message isn't a PDU, cannot apply marking!" << endl;
    }
}


int RMTQueue::getLength() const
{
    return queue.size();
}

int RMTQueue::getMaxLength() const
{
    return maxQLength;
}


void RMTQueue::setMaxLength(int val)
{
    this->maxQLength = val;
}

int RMTQueue::getThreshLength() const
{
    return thresholdQLength;
}

void RMTQueue::setThreshLength(int val)
{
    this->thresholdQLength = val;
}

simtime_t RMTQueue::getQTime() const
{
    return qTime;
}

RMTQueueType RMTQueue::getType() const
{
    return type;
}

void RMTQueue::setType(queueType type)
{
    this->type = type;
}

cGate* RMTQueue::getRMTAccessGate() const
{
    return rmtAccessGate;
}

void RMTQueue::setRMTAccessGate(cGate* gate)
{
    rmtAccessGate = gate;
}

cGate* RMTQueue::getOutputGate() const
{
    return outputGate;
}

cGate* RMTQueue::getInputGate() const
{
    return inputGate;
}

const cPacket* RMTQueue::getFirstPDU() const
{
    return queue.front();
}

const cPacket* RMTQueue::getLastPDU() const
{
    return queue.back();
}
