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

#ifndef __RINA_RMTQUEUE_H_
#define __RINA_RMTQUEUE_H_

#include <omnetpp.h>
#include <queue>

#include "PDU.h"
#include "DataTransferPDU_m.h"

class RMTQueue
{
  public:
    RMTQueue();
    RMTQueue(int MaxQLength, int threshQLength);
    virtual ~RMTQueue();

    void insertPDU(DataTransferPDU* pdu);
    DataTransferPDU* popPDU();

    int getMaxLength();
    int getThreshLength();
    int getLength();

    int getGateId();
    void setGate(int gate);

    void setMaxLength(int value);
    void setThreshLength(int value);

  private:
    std::queue<DataTransferPDU*> queue;

    int maxQLength;
    int thresholdQLength;

    int gateId;
};

#endif
