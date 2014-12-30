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
: id(0)
{
}

RMTQueue::~RMTQueue()
{
    while (!queue.empty())
    {
        delete queue.front();
        queue.pop_front();
    }
}

void RMTQueue::initialize()
{
    outputGate = gate("outputGate");
    inputGate = gate("inputGate");
    sigRMTPDURcvd = registerSignal(SIG_RMT_MessageReceived);
    sigRMTPDUSent = registerSignal(SIG_RMT_MessageSent);

    maxQLength = getParentModule()->par("queueSize");
    thresholdQLength = getParentModule()->par("queueThresh");
    qTime = simTime();
    redrawGUI();
}

std::string RMTQueue::info() const
{
//    std::ostringstream os;
//
//    os << "name: " << this->getFullName()
//       << "; type: " << ((this->type == INPUT) ? "input" : "output")
//       << "; saturation: " << getLength() << "/" << this->maxQLength;
//
//    return os.str();
    return this->getFullName();
}

std::ostream& operator <<(std::ostream& os, const RMTQueue& cte)
{
    return os << cte.info();
}

bool RMTQueue::isBounded()
{
    return outputGate->isConnected();
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
    disp.setTagArg("t", 1, "l");
    disp.setTagArg("t", 0, desc.str().c_str());
}

void RMTQueue::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (!opp_strcmp(msg->getFullName(), "queueTransmitEnd"))
        {
            releasePDU();
            emit(sigRMTPDUSent, this);
        }
        delete msg;
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

/**
 * Schedules an end-of-queue-service event.
 *
 */
void RMTQueue::startTransmitting()
{
    Enter_Method("startTransmitting()");

    scheduleAt(simTime() + queuingTime, new cMessage("queueTransmitEnd"));
    bubble("Releasing a PDU...");
}

void RMTQueue::dropLast()
{
    delete queue.back();
    queue.pop_back();
    redrawGUI();
}

void RMTQueue::markCongestionOnLast()
{
    cMessage* msg = queue.back();

    if (dynamic_cast<PDU_Base*>(msg) != NULL)
    {
        PDU_Base* pdu = (PDU_Base*) msg;
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

simtime_t RMTQueue::getQTime() const
{
    return qTime;
}

RMTQueueType RMTQueue::getType()
{
    return type;
}

void RMTQueue::setType(queueType type)
{
    this->type = type;
    queuingTime = getParentModule()->
            par(type == OUTPUT ? "TxQueuingTime" : "RxQueuingTime").
            doubleValue() / 1000;
}

int RMTQueue::getId() const
{
    return id;
}

void RMTQueue::setId(int queueId)
{
    this->id = queueId;
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

