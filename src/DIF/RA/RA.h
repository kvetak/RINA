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
 * @brief
 * @detail
 */

#ifndef __RINA_RA_H_
#define __RINA_RA_H_

#include <omnetpp.h>
#include "RINASignals.h"
#include "PDUForwardingTable.h"
#include "FlowTable.h"
#include "DA.h"
#include "Flow.h"
#include "FABase.h"
#include "RMT.h"

class RA : public cSimpleModule
{
  public:

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    DA* difAllocator;
    PDUForwardingTable* fwTable;
    FlowTable* flTable;
    RMT* rmt;
    std::string processName;

    void createFlow(std::string dstIpc);
    void removeFlow();

    void bindFlowToRMT(cModule* ipc, Flow *flow);
    void bindMediumToRMT();

    std::string normalizePortId(std::string ipcName, int flowPortId);

    void initSignalsAndListeners();

    // signals emitted by this module
    simsignal_t sigRAAllocReq;
    simsignal_t sigRADeallocReq;
    simsignal_t sigRAAllocResPosi;
    simsignal_t sigRAAllocResNega;
    simsignal_t sigRAFlowAllocd;
    simsignal_t sigRAFlowDeallocd;

    // emit wrapper functions
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);
    void signalizeFlowAllocated(Flow* flow);
    void signalizeFlowDeallocated(Flow* flow);

};

#endif
