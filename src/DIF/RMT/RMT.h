// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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

#include "Common/RINASignals.h"
#include "Common/ExternConsts.h"
#include "Common/Address.h"
#include "Common/PDU.h"
#include "Common/Utils.h"

#include "DIF/RMT/PDUForwarding/IntPDUForwarding.h"
#include "DIF/RA/QueueAlloc/QueueAllocBase.h"
#include "DIF/RA/AddressComparator/AddressComparatorBase.h"

#include "DIF/RMT/RMTBase.h"
#include "DIF/RMT/RMTListeners.h"
#include "DIF/RMT/RMTModuleAllocator.h"
#include "DIF/RMT/Scheduler/RMTSchedulingBase.h"
#include "DIF/RMT/Monitor/RMTQMonitorBase.h"
#include "DIF/RMT/MaxQueue/RMTMaxQBase.h"

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

    virtual void preQueueArrival(cObject* obj);
    virtual void postQueueArrival(cObject* obj);
    virtual void preQueueDeparture(cObject* obj);
    virtual void postQueueDeparture(cObject* obj);
    virtual void writeToPort(cObject* obj);
    virtual void readFromPort(cObject* obj);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
    void recDel(cPacket * p);

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
    void relayPDUToPort(PDU* msg);
    void relayPDUToEFCPI(PDU* msg);

    std::vector<RMTPort*> fwTableLookup(const PDU * pdu);
    std::deque<cMessage*> invalidPDUs;

    void tracePDUEvent(const cPacket* pkt, TraceEventType eventType);

    simsignal_t sigRMTNoConnID;
    simsignal_t sigRMTPacketError;
    LisRMTQueuePDUPreRcvd* lisRMTQueuePDUPreRcvd;
    LisRMTQueuePDUPostRcvd* lisRMTQueuePDUPostRcvd;
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
