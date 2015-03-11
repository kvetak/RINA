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

#include "RMTQueue.h"

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
        EV << "This queue still contains " << pduCount << " unprocessed PDUs!" << endl;

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
    sigRMTPDURcvd = registerSignal(SIG_RMT_QueuePDURcvd);
    // message departure signal handler
    sigRMTPDUSent = registerSignal(SIG_RMT_QueuePDUSent);
    // length for vector stats
    sigStatRMTQueueLength = registerSignal(SIG_STAT_RMTQUEUE_LENGTH);

    maxQLength = getParentModule()->getParentModule()->par("defaultMaxQLength");
    thresholdQLength = getParentModule()->getParentModule()->par("defaultThreshQLength");
    qTime = simTime();
    redrawGUI();

    WATCH(thresholdQLength);
    WATCH(maxQLength);
    WATCH(qTime);
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
    if (!ev.isGUI())
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
        disp.setTagArg("i", 1, getParentModule()->getParentModule()->par("queueColorBusy").stringValue());
    }
    else if (len < maxQLength)
    {
        disp.setTagArg("i", 1, getParentModule()->getParentModule()->par("queueColorWarn").stringValue());
    }
    else
    {
        disp.setTagArg("i", 1, getParentModule()->getParentModule()->par("queueColorFull").stringValue());
    }

    // print current saturation in numbers
    std::ostringstream desc;
    desc << " " << len << "/" << maxQLength;
    disp.setTagArg("t", 1, "l");
    disp.setTagArg("t", 0, desc.str().c_str());
}

void RMTQueue::handleMessage(cMessage* msg)
{
    if (dynamic_cast<cPacket*>(msg) != NULL)
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
    queue.push_back(pdu);
    emit(sigRMTPDURcvd, this);
    emit(sigStatRMTQueueLength, getLength());
    redrawGUI();
}

void RMTQueue::releasePDU(void)
{
    Enter_Method("releasePDU()");

    if (this->getLength() > 0)
    {
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

void RMTQueue::markCongestionOnLast()
{
    cPacket* msg = queue.back();

    if (dynamic_cast<PDU*>(msg) != NULL)
    {
        PDU* pdu = (PDU*) msg;
        pdu->setFlags(pdu->getFlags() | 0x01);
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
