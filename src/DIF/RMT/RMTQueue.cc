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

Define_Module(RMTQueue);


RMTQueue::RMTQueue()
{
}


RMTQueue::~RMTQueue()
{

}

void RMTQueue::initialize()
{
    outputGate = gate("outputGate");
    inputGate = gate("inputGate");
    sigRMTPDURcvd = registerSignal(SIG_RMT_MessageReceived);

    maxQLength = getParentModule()->par("queueMaxThresh");
    thresholdQLength = getParentModule()->par("queueMinThresh");
    averageLength = 0.0;
    weight = 0;
    aqmCounter = -1;
}

std::string RMTQueue::info() const
{
    std::ostringstream os;

    os << "name: " << this->getFullName()
       << "; type: " << this->type
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
        disp.setTagArg("i", 1, getParentModule()->par("queueColorBusy").stringValue());
    }
    else if (len < maxQLength)
    {
        disp.setTagArg("i", 1, getParentModule()->par("queueColorWarn").stringValue());
    }
    else
    {
        disp.setTagArg("i", 1, getParentModule()->par("queueColorFull").stringValue());
    }

    // print current saturation in numbers
    std::ostringstream desc;
    desc << " " << len << "/" << maxQLength;
    disp.setTagArg("t", 1, "r");
    disp.setTagArg("t", 0, desc.str().c_str());
}

void RMTQueue::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // wtf?
    }
    else
    {
        enqueuePDU(msg);
        emit(sigRMTPDURcvd, this);
    }
}

void RMTQueue::enqueuePDU(cMessage* pdu)
{
    queue.push_back(pdu);
    redrawGUI();
}

void RMTQueue::releasePDU(void)
{
    if (this->getLength() > 0)
    {
        cMessage* pdu = queue.front();
        queue.pop_front();
        send(pdu, outputGate);

        if (getLength() == 0)
        {
            qTime = simTime();
        }
    }
    redrawGUI();
}

void RMTQueue::dropLast()
{
    queue.pop_back();
}


int RMTQueue::getLength() const
{
    return queue.size();
}

int RMTQueue::getMaxLength()
{
    return maxQLength;
}


void RMTQueue::setMaxLength(int val)
{
    this->maxQLength = val;
}

int RMTQueue::getThreshLength()
{
    return thresholdQLength;
}

void RMTQueue::setThreshLength(int val)
{
    this->thresholdQLength = val;
}

double RMTQueue::getAverageLength() const
{
    return averageLength;
}

void RMTQueue::setAverageLength(double avr)
{
    averageLength = avr;
}

double RMTQueue::getWeight() const
{
    return weight;
}

simtime_t RMTQueue::getQTime() const
{
    return qTime;
}

int RMTQueue::getAqmCounter() const
{
    return aqmCounter;
}

void RMTQueue::setAqmCounter(int val)
{
    aqmCounter = val;
}


RMTQueue::queueType RMTQueue::getType()
{
    return type;
}

void RMTQueue::setType(RMTQueue::queueType type)
{
    this->type = type;
}

cGate* RMTQueue::getRmtAccessGate()
{
    return rmtAccessGate;
}

void RMTQueue::setRmtAccessGate(cGate* gate)
{
    rmtAccessGate = gate;
}

cGate* RMTQueue::getOutputGate()
{
    return outputGate;
}

cGate* RMTQueue::getInputGate()
{
    return inputGate;
}

