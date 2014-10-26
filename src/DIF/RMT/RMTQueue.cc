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

const int MAXLENGTH = 50;
const int THRESHLENGTH = 30;

RMTQueue::RMTQueue()
{
    this->maxQLength = MAXLENGTH;
    this->thresholdQLength = THRESHLENGTH;
}

RMTQueue::RMTQueue(int MaxQLength, int threshQLength)
{
    this->maxQLength = MaxQLength;
    this->thresholdQLength = threshQLength;
}


RMTQueue::~RMTQueue()
{

}

void RMTQueue::initialize()
{
    outputGate = gate("outputGate");
    inputGate = gate("inputGate");
}

std::string RMTQueue::info() const {
    std::ostringstream os;

    os << "name: " << this->getFullName()
       << "; type: " << this->type
       << "; saturation: " << getLength() << "/" << this->maxQLength;

    return os.str();
}

std::ostream& operator <<(std::ostream& os, const RMTQueue& cte) {
    return os << cte.info();
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
        releasePDU();
    }
}

void RMTQueue::enqueuePDU(cMessage* pdu)
{
    queue.push(pdu);
}

void RMTQueue::releasePDU(void)
{
    if (this->getLength() > 0)
    {
        cMessage* pdu = queue.front();
        queue.pop();
        send(pdu, outputGate);
    }
}

std::string RMTQueue::getDifName()
{
    return difName;
}

short RMTQueue::getQosId()
{
    return qosId;
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

