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

#include "PDU.h"
#include "DataTransferPDU_m.h"

class RMTQueue
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    RMTQueue();
    RMTQueue(int MaxQLength, int threshQLength, int qLength);
    virtual ~RMTQueue();

    void insertPDU(DataTransferPDU pdu);
    void sendFirst();
    void sendLast();

    int getMaxLength();
    int getThreshLength();
    int getLength();

    void setMaxLength(int value);
    void setThreshLength(int value);
    void setLength(int value);

    // only needed for output queues, might separate this in the future
    bool qState();
    void suspendQ();
    void resumeQ();

  private:
    std::vector<PDU> queue;
    int maxQLength;
    int thresholdQLength;
    int qLength;

    // only needed for output queues as well
    bool isActive;
};

#endif
