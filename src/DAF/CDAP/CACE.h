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

#ifndef __RINA_CACE_H_
#define __RINA_CACE_H_

#include <omnetpp.h>
#include "RINASignals.h"
#include "CDAPMessage_m.h"
#include "CACEListeners.h"
#include "ExternConsts.h"
#include "AE.h"

class LisCACESendData;
class LisCACEConReq;
class LisCACERelReq;
class LisCACEAuthRes;
class CACE : public cSimpleModule
{
public:
    void processMRelease(CDAPMessage *cmsg);
    void processMConnect(CDAPMessage *cmsg);
    void processMConnectResPosi(CDAPMessage *cmsg);
    void processMConnectResNega(CDAPMessage *cmsg);
    void treatAuthRes(CDAPMessage *cmsg);

    void sendData(CDAPMessage *cmsg);
  protected:

    int potentialConTimer;
    int currentConRetries;
    int maxConRetries;
    AE* ae;

    simsignal_t sigCACEAuthReq;
    simsignal_t sigCACEConResPosi;
    simsignal_t sigCACEConResNega;
    simsignal_t sigCACERelRes;

    simsignal_t sigCACEReceiveData;

    LisCACEConReq* lisCACEConReq;
    LisCACERelReq* lisCACERelReq;
    LisCACEAuthRes* lisCACEAuthRes;

    LisCACESendData* lisCACESendData;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void changeConnectionState(CDAPConnectionState connectionState);
    void initPointers();
    void initSignalsAndListeners();
    void CACEStateMachine(CDAPMessage *cmsg);
    void processMRelease();
    void processMReleaseR(CDAPMessage *cmsg);
    void sendMessage(CDAPMessage *cmsg);
    void signalizeDataReceive(CDAPMessage* cmsg);
    void signalizeAuthenticationRequest(CDAPMessage* cmsg);
    void signalizeConnResponseNegative(CDAPMessage* cmsg);
    void signalizeConnResponsePositive(CDAPMessage* cmsg);
    void signalizeReleaseResponse(CDAPMessage* cmsg);

};

#endif
