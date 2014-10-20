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
#include "FABase.h"
#include "RMT.h"
#include "RABase.h"
#include "RAListeners.h"

//Consts
extern const char* PAR_QOSDATA;
extern const char* ELEM_QOSCUBE;
extern const char* ELEM_AVGBW;
extern const char* ELEM_AVGSDUBW;
extern const char* ELEM_PEAKBWDUR;
extern const char* ELEM_PEAKSDUBWDUR;
extern const char* ELEM_BURSTPERIOD;
extern const char* ELEM_BURSTDURATION;
extern const char* ELEM_UNDETECTBITERR;
extern const char* ELEM_MAXSDUSIZE;
extern const char* ELEM_PARTIALDELIVER;
extern const char* ELEM_INCOMPLETEDELIVER;
extern const char* ELEM_FORCEORDER;
extern const char* ELEM_MAXALLOWGAP;
extern const char* ELEM_DELAY;
extern const char* ELEM_JITTER;
extern const char* ELEM_COSTTIME;
extern const char* ELEM_COSTBITS;

class RA : public RABase {

  public:
    virtual bool bindToLowerFlow(Flow* flow);
    virtual void createFlow(Flow *flow);
    virtual void createFlowWithoutAllocate(Flow *flow);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    DA* difAllocator;
    PDUForwardingTable* fwTable;
    FlowTable* flTable;
    RMT* rmt;
    std::string processName;
    std::list<Flow*> preparedFlows;

    bool onWire;

    void initQoSCubes();
    void setRmtMode();

    void removeFlow();

    cGate* bindFlowToRMT(cModule* ipc, Flow *flow);
    void bindMediumToRMT();

    std::string normalizePortId(std::string ipcName, int flowPortId);

    void initSignalsAndListeners();

    LisRACreFlow* lisRACreFlow;

};
    

#endif
