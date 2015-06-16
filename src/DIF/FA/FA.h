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
 * @brief Class representing Flow allocator component
 * @authors Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Last refactorized and documented on 2015-03-10
 */

#ifndef FA_H_
#define FA_H_

//Standard libraries
#include <omnetpp.h>
#include <string>
//RINASim libraries
#include "FABase.h"
#include "FAListeners.h"
#include "FAI.h"
#include "Flow.h"
#include "FAITable.h"
#include "RINASignals.h"
#include "ModuleAccess.h"
#include "EFCP.h"
#include "ExternConsts.h"
#include "DA.h"
#include "NewFlowRequestBase.h"

//Constants

extern const int RANDOM_NUMBER_GENERATOR;
extern const int MAX_PORTID;
extern const int MAX_CEPID;
extern const char* MOD_NEFFLOWREQPOLICY;

class FA : public FABase
{
  public:
    FA();
    virtual ~FA();

    virtual bool receiveAllocateRequest(Flow* flow);
    virtual bool receiveLocalMgmtAllocateRequest(Flow* flow);
    virtual bool receiveMgmtAllocateFinish();
    virtual void receiveNM1FlowCreated(Flow* flow);
    virtual bool receiveDeallocateRequest(Flow* flow);
    virtual bool receiveCreateFlowRequestFromRibd(Flow* flow);

    virtual void deinstantiateFai(Flow* flow);

    virtual bool setOriginalAddresses(Flow* flow);
    virtual bool setNeighborAddresses(Flow* flow);

    bool invokeNewFlowRequestPolicy(Flow* flow);

    //Signals
    simsignal_t sigFACreReqFwd;
    simsignal_t sigFACreResNega;
    simsignal_t sigFACreResPosiFwd;

    //Listeners
    LisFAAllocReq*      lisAllocReq;
    LisFAAllocFinMgmt*  lisAllocFinMgmt;
    LisFACreFloPosi*    lisCreFloPosi;
    LisFADeallocReq*    lisDeallocReq;
    LisFACreReq*        lisCreReq;

  protected:
    //SimpleModule overloads
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initPointers();

  private:
    EFCP* Efcp;
    DA* DifAllocator;
    NewFlowRequestBase* NFloReqPolicy;

    bool isMalformedFlow(Flow* flow);
    FAI* createMgmtFAI(Flow* flow);
    FAI* createFAI(Flow* flow);

    void initSignalsAndListeners();

    void signalizeCreateFlowRequestForward(Flow* flow);
    void signalizeCreateFlowResponseNegative(Flow* flow);

    const Address getAddressFromDa(const APN& apn, bool useNeighbor, bool isMgmtFlow);

    bool changeDstAddresses(Flow* flow, bool useNeighbor);
    bool changeSrcAddress(Flow* flow, bool useNeighbor);

};

#endif /* FLOWALLOCATOR_H_ */
