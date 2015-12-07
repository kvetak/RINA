//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
#include <fstream>
#include <bitset>

#include "RINASignals.h"
#include "ExternConsts.h"
#include "Address.h"
#include "PDU.h"
#include "CDAPMessage_m.h"

#include "IntPDUForwarding.h"
#include "QueueAllocBase.h"
#include "AddressComparatorBase.h"

#include "RMTBase.h"
#include "RMTListeners.h"
#include "RMTModuleAllocator.h"
#include "RMTSchedulingBase.h"
#include "RMTQMonitorBase.h"
#include "RMTMaxQBase.h"

// mapping of cepIDs to output gates
typedef std::map<int, cGate*> EfcpiMapping;

// shared access to trace logger
extern std::ofstream rmtTraceFile;

class RMT : public RMTBase
{
  friend class RA;
  friend class FAI;

  public:

    virtual ~RMT();

    virtual bool getRelayStatus() { return relayOn; };
    virtual bool isOnWire() { return onWire; };

    virtual void onQueueArrival(cObject* obj);
    virtual void preQueueDeparture(cObject* obj);
    virtual void postQueueDeparture(cObject* obj);
    virtual void writeToPort(cObject* obj);
    virtual void readFromPort(cObject* obj);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    IntPDUForwarding* fwd;
    RMTModuleAllocator* rmtAllocator;

    bool relayOn;
    bool onWire;

    EfcpiMapping efcpiOut;
    EfcpiMapping efcpiIn;

    RMTQMonitorBase* qMonPolicy;
    RMTMaxQBase* maxQPolicy;
    RMTSchedulingBase* schedPolicy;

    QueueAllocBase* qAllocPolicy;
    QueueIDGenBase* queueIdGenerator;
    AddressComparatorBase* addrComparator;

    enum TraceEventType
    {
        MSG_SEND = 's', MSG_RECEIVE = 'r', MSG_ENQUEUE = '+', MSG_DEQUEUE = '-',
        MSG_DROP = 'd'
    };
    bool tracing;

    void processMessage(cMessage* msg);
    void efcpiToPort(PDU* msg);
    void portToEfcpi(PDU* msg);
    void efcpiToEfcpi(PDU* msg);
    void ribToPort(CDAPMessage* msg);
    void portToRIB(CDAPMessage* msg);
    void ribToRIB(CDAPMessage* msg);
    void portToPort(cMessage* msg);

    RMTPort* fwTableLookup(const Address& destAddr, const unsigned short &pduQosId);
    RMTPort* fwTableLookup(const PDU * pdu);
    std::deque<cMessage*> invalidPDUs;

    void tracePDUEvent(const cPacket* pkt, TraceEventType eventType);

    simsignal_t sigRMTNoConnID;
    simsignal_t sigRMTPacketError;
    LisRMTQueuePDURcvd* lisRMTQueuePDURcvd;
    LisRMTQueuePDUPreSend* lisRMTQueuePDUPreSend;
    LisRMTQueuePDUSent* lisRMTQueuePDUSent;
    LisRMTPortReadyToServe* lisRMTPortReadyToServe;
    LisRMTPortReadyForRead* lisRMTPortReadyForRead;

    // management methods for Resource Allocator
    void setOnWire(bool status) { onWire = status; };
    void enableRelay() { relayOn = true; };
    void disableRelay() { relayOn = false; };

    // management methods for FAIs
    void createEfcpiGate(unsigned int efcpiId);
    void deleteEfcpiGate(unsigned int efcpiId);
};

#endif /* RMT_H_ */
