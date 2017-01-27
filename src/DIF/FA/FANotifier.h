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

#ifndef FANOTIFIER_H_
#define FANOTIFIER_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/FA/FANotifierBase.h"
#include "DIF/FA/FANotifierListeners.h"
#include "DIF/RIB/RIBdBase.h"

class FANotifier : public FANotifierBase {
  public:

    virtual void sendCreateRequestFlow(Flow* flow);
    virtual void sendCreateResponseNegative(Flow* flow);
    virtual void sendCreateResponsePostive(Flow* flow);
    virtual void sendDeleteRequestFlow(Flow* flow);
    virtual void sendDeleteResponseFlow(Flow* flow);
    virtual void receiveAllocationRequestFromFai(Flow* flow);
    virtual void receiveCreateFlowPositiveFromRa(Flow* flow);
    virtual void receiveCreateFlowNegativeFromRa(Flow* flow);

  protected:
    //Signals
    simsignal_t sigRIBDCreReqFlo;
    simsignal_t sigRIBDDelReqFlo;
    simsignal_t sigRIBDDelResFlo;
    simsignal_t sigRIBDCreResFloPosi;
    simsignal_t sigRIBDCreResFloNega;
    simsignal_t sigRIBDAllocResPosi;
    simsignal_t sigRIBDAllocResNega;
    simsignal_t sigRIBDCreFlow;

    //Listeners
    LisRIBDCreReq*              lisRIBDCreReq;
    LisRIBDCreReq*              lisRIBDCreReqByForward;
    LisRIBDAllReqFromFai*       lisRIBDAllReqFromFai;
    LisRIBDCreResNega*          lisRIBDCreResNega;
    LisRIBDCreResNega*          lisRIBDCreResNegaFromFa;
    LisRIBDCreResPosi*          lisRIBDCreResPosi;
    LisRIBDCreResPosi*          lisRIBDCreResPosiForward;
    LisRIBDDelReq*              lisRIBDDelReq;
    LisRIBDDelRes*              lisRIBDDelRes;
    LisRIBDCreFloPosi*          lisRIBDCreFloPosi;
    LisRIBDCreFloNega*          lisRIBDCreFloNega;

    void signalizeCreateRequestFlow(Flow* flow);
    void signalizeDeleteRequestFlow(Flow* flow);
    void signalizeDeleteResponseFlow(Flow* flow);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeAllocateResponseNegative(Flow* flow);
    void signalizeCreateFlow(Flow* flow);
    void signalizeCreateResponseFlowPositive(Flow* flow);
    void signalizeCreateResponseFlowNegative( Flow* flow);

    void initPointers();
    void initSignalsAndListeners();

    //SimpleModule overloads
    virtual void initialize();
    virtual void handleMessage(cMessage *msg){};

    //CDAPProcessingBase overload
    virtual void signalizeMessage(CDAPMessage* msg);

    long getNewInvokeId();

    virtual void processMCreate(CDAP_M_Create* msg);
    virtual void processMCreateR(CDAP_M_Create_R* msg);
    virtual void processMDelete(CDAP_M_Delete* msg);
    virtual void processMDeleteR(CDAP_M_Delete_R* msg);

    RIBdBase* RIBd;

};

#endif /* FANOTIFIER_H_ */
