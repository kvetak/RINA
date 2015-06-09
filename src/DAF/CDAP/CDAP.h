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

#ifndef __RINA_CDAP_H_
#define __RINA_CDAP_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "CDAPListeners.h"
#include "RINASignals.h"
#include "CDAPMessage_m.h"
#include "ExternConsts.h"


class LisCDAPSendData;
class CDAP : public cSimpleModule
{
  public:
    enum ConnectionState {NIL, CONNECTED, AWAITCLOSE, AWAITCON};

    void sendData(CDAPMessage* cmsg);

  protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initSignalsAndListeners();

    //Signals
    simsignal_t sigCDAPReceiveData;

    //Listeners
    LisCDAPSendData* lisCDAPSendData;

    //Signaling
    void signalizeReceiveData(CDAPMessage* cmsg);

};

#endif
