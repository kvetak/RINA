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

#ifndef __RINA_RMTFLOW_H_
#define __RINA_RMTFLOW_H_

#include <omnetpp.h>

#include "RMTQueue.h"

class RMTFlow
{
  public:
    RMTFlow();
    virtual ~RMTFlow();

    // connection with a EFCP instance
    void setEfcpiGateId(int val);
    int getEfcpiGateId();

    // connection with (N-1) ports
    void setSouthGateId(int val);
    int getSouthGateId();

    // output queue write supression
    bool outboundState();
    void suspendOutbound();
    void resumeOutbound();

    int getIncomingLength();
    int getOutgoingLength();

    void addIncomingPDU(DataTransferPDU* pdu);
    void addOutgoingPDU(DataTransferPDU* pdu);

    DataTransferPDU* popIncomingPDU();
    DataTransferPDU* popOutgoingPDU();

  private:
    RMTQueue inQ;
    RMTQueue outQ;

    int outGateId;
    int efcpId;

    bool outboundActive;
};

#endif
