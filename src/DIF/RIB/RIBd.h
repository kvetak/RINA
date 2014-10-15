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
 * @file RIBd.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief Kind of a Notification Board for DIF
 * @detail
 */

#ifndef RIBDAEMON_H_
#define RIBDAEMON_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "RIBdBase.h"
#include "ExternConsts.h"
#include "RIBdListeners.h"
#include "RINASignals.h"

//Constants
extern const char* MSG_CREREQFLO;
extern const char* CLS_FLOW;

class RIBd : public RIBdBase {
  public:
    virtual void sendCreateRequestFlow(Flow* flow);
    virtual void receiveData(CDAPMessage* cimsg);
    virtual void receiveAllocationRequestFromFAI(Flow* flow);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initCdapBindings();
    void initSignalsAndListeners();

    //Signals
    simsignal_t sigRIBDSendData;
    simsignal_t sigRIBDCreReqFlo;
    simsignal_t sigRIBDAllocResPosi;
    simsignal_t sigRIBDCreFlow;

    //Listeners
    LisRIBDRcvData*             lisRIBDRcvData;
    LisRIBDCreReq*              lisRIBDCreReq;
    LisRIBDAllReqFromFai*       lisRIBDAllReqFromFai;

    void signalizeSendData(CDAPMessage* msg);
    void signalizeCreateRequestFlow(Flow* flow);
    void signalizeAllocateResponsePositive(Flow* flow);
    void signalizeCreateFlow(Flow* flow);

};

#endif /* RIBDAEMON_H_ */
