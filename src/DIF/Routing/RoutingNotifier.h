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

#ifndef __RINA_ROUTINGNOTIFIER_H_
#define __RINA_ROUTINGNOTIFIER_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/Routing/RoutingNotifierBase.h"
#include "DIF/Routing/RoutingNotifierListeners.h"
#include "DIF/RIB/RIBdBase.h"

extern const char* MSG_ROUTINGUPDATE;

class RoutingNotifier : public RoutingNotifierBase
{
  public:
    virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * update);

  protected:
    RIBdBase* RIBd;
    simsignal_t sigRIBDRoutingUpdateRecv;

    LisRIBDRoutingUpdate* lisRIBDRoutingUpdate;

    void initPointers();
    void initSignalsAndListeners();

    //SimpleModule overloads
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    //CDAPProcessingBase overload
    virtual void signalizeMessage(CDAPMessage* msg);;

    virtual void processMWrite(CDAP_M_Write* msg);
};

#endif
