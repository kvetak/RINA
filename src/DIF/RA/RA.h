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
 * @file RA.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Monitoring and adjustment of IPC process operations
 * @detail
 */

#ifndef __RINA_RA_H_
#define __RINA_RA_H_

#include <omnetpp.h>
#include "Common/Utils.h"
#include "Common/ExternConsts.h"
#include "Common/RINASignals.h"
#include "DAF/DA/DA.h"
#include "DIF/FA/FABase.h"
#include "DIF/RMT/RMT.h"
#include "DIF/RMT/RMTPort.h"

#include "DIF/RA/RABase.h"
#include "DIF/RA/RAListeners.h"
#include "DIF/RA/NM1FlowTable.h"
#include "DIF/RA/QueueAlloc/QueueAllocBase.h"
#include "Common/CongestionDescriptor.h"

/* Forwarding and routing stuff... */
#include "DIF/RA/PDUFG/IntPDUFG.h"



//Consts
extern const char* PAR_QOSDATA;
extern const char* ELEM_QOSCUBE;
extern const char* PAR_QOSREQ;
extern const char* ELEM_QOSREQ;
extern const char* ATTR_ID;


class RA : public RABase
{
  public:
    virtual void createNM1Flow(Flow* flow);
    virtual void createNM1FlowWithoutAllocate(Flow* flow);
    virtual void removeNM1Flow(Flow* flow);
    virtual void removeNM1FlowBindings(NM1FlowTableItem* ftItem);
    virtual void createNFlow(Flow *flow);
    virtual bool bindNFlowToNM1Flow(Flow* flow);
    virtual void blockNM1PortOutput(NM1FlowTableItem* ftItem);
    virtual void unblockNM1PortOutput(NM1FlowTableItem* ftItem);
    virtual NM1FlowTable* getFlowTable();
    virtual bool hasFlow(std::string addr, std::string qosId);

    virtual bool sleepFlow(Flow * flow, simtime_t wakeUp);

    // event hook handlers
    virtual void postNFlowAllocation(Flow* flow);
    virtual void postNM1FlowAllocation(NM1FlowTableItem* ftItem);

  protected:
    virtual void initialize(int stage);
    int numInitStages() const { return 2; };
    virtual void handleMessage(cMessage *msg);

  private:
    DA* difAllocator;
    cModule* thisIPC;
    cModule* rmtModule;
    RMT* rmt;
    RMTModuleAllocator* rmtAllocator;
    FABase* fa;
    NM1FlowTable* flowTable;
    QueueAllocBase* qAllocPolicy;

    // Forwarding and routing stuff...
    IntPDUFG * fwdtg;

    std::string processName;
    std::map<simtime_t, std::list<Flow*>*> preAllocs;
    std::map<simtime_t, std::list<Flow*>*> preDeallocs;
    std::map<std::string, std::list<Flow*>*> pendingFlows;
    QoSReq mgmtReqs;

    void initQoSCubes();
    QoSReq* initQoSReqById(const char* id);
    void initSignalsAndListeners();
    void initFlowAlloc();
    void setRMTMode();
    void bindMediumToRMT();
    RMTPort* bindNM1FlowToRMT(cModule* ipc, FABase* fab, Flow* flow);
    std::string normalizePortID(std::string ipcName, int flowPortID);

    simsignal_t sigRACreFloPosi;
    simsignal_t sigRACreFloNega;
    simsignal_t sigRASDReqFromRMT;
    simsignal_t sigRASDReqFromRIB;
    simsignal_t sigRAMgmtAllocd;
    simsignal_t sigRAMgmtDeallocd;

    LisRACreFlow* lisRACreFlow;
    LisRAAllocResPos* lisRAAllocResPos;
    LisRACreAllocResPos* lisRACreAllocResPos;
    LisRACreResPosi* lisRACreResPosi;
    LisRADelFlow* lisRADelFlow;
    LisEFCPStopSending* lisEFCPStopSending;
    LisEFCPStartSending* lisEFCPStartSending;

    LisRMTSlowdownRequest* lisRMTSDReq;
    LisRIBCongNotif* lisRIBCongNotif;

    void signalizeCreateFlowPositiveToRIBd(Flow* flow);
    void signalizeCreateFlowNegativeToRIBd(Flow* flow);
    void signalizeSlowdownRequestToRIBd(cPacket* pdu);
    void signalizeSlowdownRequestToEFCP(cObject* obj);
    void signalizeMgmtAllocToEnrollment(APNIPair* apnip);
    void signalizeMgmtDeallocToEnrollment(Flow* flow);

};
    

#endif
