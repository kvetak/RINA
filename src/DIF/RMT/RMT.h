//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

/**
 * @file RMT.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Relaying and Multiplexing Task
 * @detail
 */

#ifndef RMT_H_
#define RMT_H_

#include <omnetpp.h>

#include "APNamingInfo.h"
#include "PDUForwardingTable.h"
#include "ModuleAccess.h"
#include "PDU_m.h"
#include "CDAPMessage_m.h"
#include "Flow.h"
#include "Address.h"
#include "ExternConsts.h"

#include "RMTQueueManager.h"
#include "RMTQueue.h"

typedef std::map<int, cGate*> EfcpiMapping;
typedef std::map<cGate*, RMTQueue*> EfcpiToQueue;

class RMT : public cSimpleModule
{
  private:
    PDUForwardingTable* fwTable;

    Address thisIpcAddr;
    bool relayOn;

    void sendDown(PDU_Base* pdu);
    void sendUp(PDU_Base* pdu);

    RMTQueueManager* queues;

    int qxpos, qypos;

    cGate* fwTableLookup(Address& destAddr, short pduQosId);

  public:
    RMT();
    virtual ~RMT();

    void createEfcpiGate(unsigned int efcpiId);
    void deleteEfcpiGate(unsigned int efcpiId);

    void createSouthGate(std::string portId);
    void deleteSouthGate(std::string portId);
    RMTQueue* addQueue(const char* queueName, RMTQueue::queueType type);
    void addQueueSet(const char* queueName);

    // TODO: purge this mess as soon as queues are back
    EfcpiMapping efcpiOut;
    EfcpiMapping efcpiIn;
    EfcpiToQueue efcpiToQueue;
    bool onWire;

    void enableRelay() { relayOn = true; };
    void disableRelay() { relayOn = false; };
    bool getRelayStatus() { return relayOn; };

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

#endif /* RMT_H_ */
