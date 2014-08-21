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

const int MAXLENGTH = 50;
const int THRESHLENGTH = 30;

RMTQueue::RMTQueue()
{
    //EV << "creating a RMTqueue" << endl;
    this->maxQLength = MAXLENGTH;
    this->thresholdQLength = THRESHLENGTH;
}

RMTQueue::RMTQueue(int MaxQLength, int threshQLength)
{
    //EV << "creating a specified RMTqueue" << endl;
    this->maxQLength = MaxQLength;
    this->thresholdQLength = threshQLength;
}


RMTQueue::~RMTQueue()
{
    //EV << "destroying a RMTqueue" << endl;
}

void RMTQueue::insertPDU(DataTransferPDU* pdu)
{
    queue.push(pdu);
}

DataTransferPDU* RMTQueue::popPDU(void)
{
    //EV << "popping a PDU" << endl;
    if (this->getLength() > 0)
    {
        DataTransferPDU* ret = queue.front();
        queue.pop();
        return ret;
    }
    else
    {
        return NULL;
    }

}


int RMTQueue::getMaxLength()
{
    return maxQLength;
}

int RMTQueue::getThreshLength()
{
    return thresholdQLength;
}

int RMTQueue::getLength()
{
    return queue.size();
}

void RMTQueue::setMaxLength(int val)
{
    this->maxQLength = val;
}

void RMTQueue::setThreshLength(int val)
{
    this->thresholdQLength = val;
}

