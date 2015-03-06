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

#ifndef __RINA_AE_H_
#define __RINA_AE_H_

//Standard libraries
#include <omnetpp.h>
#include <sstream>
//RINASim libraries
#include "AEBase.h"
#include "AEListeners.h"
#include "RINASignals.h"
#include "IRM.h"
#include "ConnectionTable.h"
#include "ExternConsts.h"
#include "CDAPMessage_m.h"

class AE : public AEBase
{
  public:
    AE();
    virtual ~AE();
    void receiveData(CDAPMessage* obj);
    void sendData(Flow* flow, CDAPMessage* msg);

    void sendAllocationRequest(Flow* flow);
    void sendDeallocationRequest(Flow* flow);

    void receiveAllocationRequestFromFAI(Flow* flow);
    void receiveDeallocationRequestFromFAI(Flow* flow);

    void receiveAllocationResponseNegative(Flow* flow);
    void receiveAllocationResponsePositive(Flow* flow);

  protected:
    IRM* Irm;
    cModule* Cdap;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initPointers();
    void initSignalsAndListeners();

    void insertFlow(Flow& flow);
    bool createBindings(Flow& flow);
    bool deleteBindings(Flow& flow);

    //Signals
    simsignal_t sigAEAllocReq;
    simsignal_t sigAEDeallocReq;
    simsignal_t sigAESendData;
    simsignal_t sigAEAllocResPosi;
    simsignal_t sigAEAllocResNega;
    simsignal_t sigAEConReq;
    simsignal_t sigAERelReq;

    //Listeners
    LisAEReceiveData* lisAERcvData;
    LisAEAllReqFromFai* lisAEAllReqFromFai;
    LisAEAllResPosi* lisAEAllResPosi;
    LisAEAllResNega* lisAEAllResNega;
    LisAEDeallReqFromFai* lisAEDeallReqFromFai;
    LisAEDeallReqFromFai* lisAEDeallResFromFai;
    LisAEConResPosi* lisAEConResPosi;
    LisAEConResNega* lisAEConResNega;
    LisAERelRes* lisAERelRes;

    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);
    void signalizeSendData(cMessage* msg);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);
    void signalizeConnectionRequest(CDAPMessage* msg);
    void signalizeReleaseRequest(CDAPMessage* msg);

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);

};

#endif
