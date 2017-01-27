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

#ifndef RMTMAXQBASE_H_
#define RMTMAXQBASE_H_

#include <omnetpp.h>

#include "Common/RINASignals.h"
#include "DIF/RMT/RMTQueue.h"
#include "DIF/RMT/Monitor/RMTQMonitorBase.h"
#include "DIF/RA/AddressComparator/AddressComparatorBase.h"
#include "DIF/RMT/RMTModuleAllocator.h"


/**
 * Noop base class for the RMT max queue policy.
 * This policy decides what to do when a queue is overflowing its threshold.
 */
class RMTMaxQBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked when a queue length is greater or equal to its threshold.
     * Makes a decision about whether to drop the arrived PDU.
     *
     * @param queue pointer to the queue
     * @return true if the PDU should be dropped, false otherwise
     */
    virtual bool run(RMTQueue* queue);

    /**
     * A hook method invoked when a queue length drops back under its threshold.
     * @param queue pointer to the queue
     */
    virtual void onQueueLengthDrop(RMTQueue* queue);

  protected:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     */
    virtual void handleMessage(cMessage* msg);

    /**
     * Send CDAP congestion notification to the PDU sender via RIBd.
     *
     * @param pdu pointer to PDU
     */
    void notifySenderOfCongestion(const cPacket* pdu);

    /**
     * Pointer to the monitoring policy module.
     */
    RMTQMonitorBase* qMonPolicy;

    /**
     * Pointer to an address comparator module.
     */
    AddressComparatorBase* addrComparator;

    /**
     * Pointer to the RMT allocator module (also providing queue<->port mappings).
     */
    RMTModuleAllocator* rmtAllocator;

  private:

    /**
     *  Module initialization routine setting up parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    void initialize();

    /**
     * Congestion notifier.
     */
    simsignal_t sigRMTSDReq;

    /**
     * Signal used for disabling an incoming PDU's arrival port.
     */
    //FIXME: Vesely: Unused variable commented
    //simsignal_t sigRMTPortDrainDisable;

    /**
     * Signal used for enabling an incoming PDU's arrival port.
     */
    //FIXME: Vesely: Unused variable commented
    //simsignal_t sigRMTPortDrainEnable;

    /**
     * Signal used for speeding up an incoming PDU's arrival port drain rate.
     */
    //FIXME: Vesely: Unused variable commented
    //simsignal_t sigRMTPortDrainSpeedUp;

    /**
     * Signal used for slowing down an incoming PDU's arrival port drain rate.
     */
    //FIXME: Vesely: Unused variable commented
    //simsignal_t sigRMTPortDrainSlowDown;
};

#endif /* RMTMAXQBASE_H_ */
