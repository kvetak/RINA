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

#pragma once

#include <omnetpp.h>

#include "Common/QoSCube.h"
#include "DIF/FA/FABase.h"

#include "inet/common/InitStages.h"

class ShimFAI;
class EthShim;
class RINArp;

/**
 * Shim specific Flow Allocator.
 *
 * Flow Allocator Instances are still allocated, but only source port information is kept.
 */
class ShimFA : public FABase
{
  private:
    /// Pointers to important modules
    cModule *shimIpcProcess = nullptr;
    cModule *connectedApplication = nullptr;
    RINArp *arp = nullptr;
    EthShim *shim = nullptr;

    APN registeredApplication;  ///< apName of "registered" application

    QoSCube qos;  ///< Unreliable QoS cube declaration

  public:
    ShimFA();
    ~ShimFA() override;

    /**
     * @brief Attempts to initialise a new flow
     * @param  flow A flow object pre-populated with destination and source APNIs and QoSReq
     * @return true if FA instance created and connection entry was either created or pending,
     *         false if creation of instance or connection entry fails
     */
    bool receiveAllocateRequest(Flow *flow) override;

    /**
     * @brief Attempts to deallocate a new flow
     * @param  flow The flow object corresponding with a Flow Allocator Instance
     * @return true if flow was successfully deallocated, false otherwise
     */
    bool receiveDeallocateRequest(Flow *flow) override;

    /**
     * @brief Finalises a pending connection and sends a positive allocation response to N+1 IPCP
     * @param  apn Application name associated with destination application of a flow table entry
     */
    void completedAddressResolution(const APN &apn);

    /**
     * @brief Cancels a pending flow or deallocates an allocated flow
     * @param  apn Application name associated with destination application of a flow table entry
     */
    void failedAddressResolution(const APN &apn);

    /**
     * @brief Deallocates a FAI and removes the corresponding flow and connection entry
     * @param  flow Flow corresponding to the FAI and connection entry (in shim module)
     */
    void deinstantiateFai(Flow *flow) override;

    /**
     * @brief Attempts to allocate a flow from NM1 IPCP
     *
     * Called when a frame from an unknown host arrives at the shim module.
     *
     * @param  apn Application name of the connection source
     * @return true if a flow allocator instance is successfully created, false otherwise
     */
    bool createUpperFlow(const APN &apn);

    /// Provided for compatibility ?
    bool invokeNewFlowRequestPolicy(Flow *flow) override;

    /// These are all unused in shim layer, but still implemented as required by FABase
    bool receiveMgmtAllocateRequest(Flow *mgmtflow) override;
    bool receiveMgmtAllocateRequest(APNamingInfo src, APNamingInfo dst) override;
    bool receiveMgmtAllocateFinish(APNIPair *apnip) override;
    void receiveNM1FlowCreated(Flow *flow) override;
    bool receiveCreateFlowRequestFromRibd(Flow *flow) override;
    bool setOriginalAddresses(Flow *flow) override;
    bool setNeighborAddresses(Flow *flow) override;

  private:
    ShimFAI *createFAI(Flow *flow);

    /// SimpleModule overrides
    void initialize(int stage) override;
    int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    void handleMessage(cMessage *msg) override;
};
