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
 * @file RA.h
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Monitoring and adjustment of IPC process operations
 * @detail
 */

#ifndef __RINA_RA_H_
#define __RINA_RA_H_

#include <omnetpp.h>
#include "RINASignals.h"
#include "DA.h"
#include "FABase.h"
#include "RMT.h"
#include "RMTPort.h"

#include "RABase.h"
#include "RAListeners.h"
#include "NM1FlowTable.h"
#include "QueueAllocBase.h"
#include "CongestionDescriptor.h"

/* Forwarding and routing stuff... */
#include "IntPDUFG.h"

//Consts
extern const char* PAR_QOSDATA;
extern const char* ELEM_QOSCUBE;
extern const char* PAR_QOSREQ;
extern const char* ELEM_QOSREQ;
extern const char* ATTR_ID;
extern const char* ELEM_AVGBW;
extern const char* ELEM_AVGSDUBW;
extern const char* ELEM_PEAKBWDUR;
extern const char* ELEM_PEAKSDUBWDUR;
extern const char* ELEM_BURSTPERIOD;
extern const char* ELEM_BURSTDURATION;
extern const char* ELEM_UNDETECTBITERR;
extern const char* ELEM_PDUDROPPROBAB;
extern const char* ELEM_MAXSDUSIZE;
extern const char* ELEM_PARTIALDELIVER;
extern const char* ELEM_INCOMPLETEDELIVER;
extern const char* ELEM_FORCEORDER;
extern const char* ELEM_MAXALLOWGAP;
extern const char* ELEM_DELAY;
extern const char* ELEM_JITTER;
extern const char* ELEM_COSTTIME;
extern const char* ELEM_COSTBITS;
extern const char* ELEM_ATIME;
extern const char* ELEM_RXON;
extern const char* ELEM_WINON;
extern const char* ELEM_RATEON;
extern const char* ELEM_EFCPPOL;


class RA : public RABase
{
  public:
    virtual void createNM1Flow(Flow* flow);
    virtual void createNM1FlowWithoutAllocate(Flow* flow);
    virtual void removeNM1Flow(Flow* flow);
    virtual bool bindNFlowToNM1Flow(Flow* flow);
    virtual void blockNM1PortOutput(NM1FlowTableItem* ftItem);
    virtual void unblockNM1PortOutput(NM1FlowTableItem* ftItem);
    virtual NM1FlowTable* getFlowTable();

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
    NM1FlowTable* flowTable;
    QueueAllocBase* qAllocPolicy;

    // Forwarding and routing stuff...
    IntPDUFG * fwdtg;

    std::string processName;
    std::map<simtime_t, std::list<Flow*>*> preparedFlows;
    std::map<std::string, std::list<Flow*>*> pendingFlows;
    QoSReq mgmtReqs;

    void initQoSCubes();
    QoSReq* initQoSReqById(unsigned short id);
    void initSignalsAndListeners();
    void initFlowAlloc();
    void setRMTMode();
    void bindMediumToRMT();
    RMTPort* bindNM1FlowToRMT(cModule* ipc, FABase* fab, Flow* flow);
    void interconnectModules(cModule* m1, cModule* m2, std::string n1, std::string n2);
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
    LisEFCPStopSending* lisEFCPStopSending;
    LisEFCPStartSending* lisEFCPStartSending;

    LisRMTSlowdownRequest* lisRMTSDReq;
    LisRIBCongNotif* lisRIBCongNotif;

    void signalizeCreateFlowPositiveToRIBd(Flow* flow);
    void signalizeCreateFlowNegativeToRIBd(Flow* flow);
    void signalizeSlowdownRequestToRIBd(cPacket* pdu);
    void signalizeSlowdownRequestToEFCP(cObject* obj);
    void signalizeMgmtAllocToEnrollment(Flow* flow);
    void signalizeMgmtDeallocToEnrollment(Flow* flow);

};
    

#endif
