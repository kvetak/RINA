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

#ifndef __RINA_RMTPORT_H_
#define __RINA_RMTPORT_H_

#include <omnetpp.h>

#include "RMTQueue.h"

// representation of a (N-1)-port & its corresponding queues
class RMTPort
{
  public:
    RMTPort();
    virtual ~RMTPort();

    // connection with a EFCP instance
    void setEfcpiGate(cGate* val);
    cGate* getEfcpiGate();

    // output queue write supression
    bool outboundState();
    void suspendOutbound();
    void resumeOutbound();

    int getIncomingLength();
    int getOutgoingLength();

    void addIncomingPDU(PDU_Base* pdu);
    void addOutgoingPDU(PDU_Base* pdu);

    PDU_Base* popIncomingPDU();
    PDU_Base* popOutgoingPDU();

  private:
    RMTQueue inQ;
    RMTQueue outQ;

    cGate* efcpiGate;

    bool outboundActive;
};

#endif
