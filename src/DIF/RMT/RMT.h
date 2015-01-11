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

#include "RMTBase.h"
#include "RMTListeners.h"

#include "RMTQueueManager.h"
#include "RMTQueue.h"

#include "RMTSchedulingBase.h"
#include "RMTQMonitorBase.h"
#include "RMTMaxQBase.h"

#include "QueueAllocBase.h"

#include "RINASignals.h"
#include "Address.h"
#include "ExternConsts.h"
#include "PDU_m.h"
#include "CDAPMessage_m.h"
#include "PDUForwardingTable.h"

typedef std::map<int, cGate*> EfcpiMapping;

class RMT : public RMTBase
{
  friend class RA;
  friend class FAI;

  public:
    RMT();
    virtual ~RMT();

    bool getRelayStatus() { return relayOn; };
    bool isOnWire() { return onWire; };

    void invokeQueueArrivalPolicies(cObject* obj);
    void invokeQueueDeparturePolicies(cObject* obj);

  protected:
    void initialize();
    void handleMessage(cMessage *msg);

  private:
    PDUForwardingTable* fwTable;
    RMTQueueManager* rmtQM;

    Address thisIpcAddr;
    bool relayOn;
    bool onWire;

    EfcpiMapping efcpiOut;
    EfcpiMapping efcpiIn;

    RMTQMonitorBase* qMonPolicy;
    RMTMaxQBase* maxQPolicy;
    RMTSchedulingBase* schedPolicy;

    QueueAllocBase* qAllocPolicy;
    QueueIDGenBase* queueIdGenerator;

    void processMessage(cMessage* msg);
    void efcpiToPort(PDU_Base* msg);
    void efcpiToEfcpi(PDU_Base* msg);
    void portToEfcpi(PDU_Base* msg);
    void RIBToPort(CDAPMessage* msg);
    void portToRIB(CDAPMessage* msg);
    void portToPort(cMessage* msg);

    RMTPort* fwTableLookup(Address& destAddr, short pduQosId, bool useQoS = true);

    simsignal_t sigRMTNoConnID;
    LisRMTPDURcvd* lisRMTMsgRcvd;
    LisRMTPDUSent* lisRMTMsgSent;

    // management methods for Resource Allocator
    void setOnWire(bool status) { onWire = status; };
    void enableRelay() { relayOn = true; };
    void disableRelay() { relayOn = false; };

    // management methods for FAIs
    void createEfcpiGate(unsigned int efcpiId);
    void deleteEfcpiGate(unsigned int efcpiId);
};

#endif /* RMT_H_ */
