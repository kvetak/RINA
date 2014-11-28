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

#include "RINASignals.h"
#include "ModuleAccess.h"
#include "Address.h"
#include "ExternConsts.h"
#include "PDU_m.h"
#include "CDAPMessage_m.h"
#include "PDUForwardingTable.h"

typedef std::map<int, cGate*> EfcpiMapping;
typedef std::map<cGate*, RMTQueue*> EfcpiToQueue;

class RMT : public RMTBase
{
  private:
    PDUForwardingTable* fwTable;
    RMTQueueManager* queues;

    Address thisIpcAddr;
    bool relayOn;
    bool onWire;

    EfcpiMapping efcpiOut;
    EfcpiMapping efcpiIn;
    EfcpiToQueue efcpiToQueue;

    RMTQMonitorBase* qMonPolicy;
    RMTMaxQBase* maxQPolicy;
    RMTSchedulingBase* schedPolicy;
    unsigned int waitingMsgs;

    void processMessage(cMessage* msg);
    void efcpiToPort(PDU_Base* msg);
    void efcpiToEfcpi(PDU_Base* msg);
    void portToEfcpi(PDU_Base* msg);
    void RIBToPort(CDAPMessage* msg);
    void portToRIB(CDAPMessage* msg);
    void portToPort(cMessage* msg);

    void scheduleServiceEnd();

    cGate* fwTableLookup(Address& destAddr, short pduQosId);

    simsignal_t sigRMTNoConnID;
    LisRMTPDURcvd* lisRMTMsgRcvd;

  public:
    RMT();
    virtual ~RMT();

    void createEfcpiGate(unsigned int efcpiId);
    void deleteEfcpiGate(unsigned int efcpiId);
    void addEfcpiToQueueMapping(unsigned cepId, RMTQueue* outQueue);
    void deleteEfcpiToQueueMapping(unsigned cepId);

    void setOnWire(bool status) { onWire = status; };
    bool isOnWire() { return onWire; };

    void enableRelay() { relayOn = true; };
    void disableRelay() { relayOn = false; };
    bool getRelayStatus() { return relayOn; };

    void invokeSchedulingPolicy(cObject* obj);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

#endif /* RMT_H_ */
