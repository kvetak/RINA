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


#ifndef RMT_H_
#define RMT_H_

#include <omnetpp.h>

#include "APNamingInfo.h"
#include "PDUForwardingTable.h"
#include "ModuleAccess.h"
#include "PDU_m.h"
#include "CDAPMessage_m.h"
#include "ConnectionId.h"

#include "RMTPortManager.h"
#include "RMTPort.h"

typedef std::map<int, cGate*> southMapping;
typedef std::map<int, cGate*> efcpiMapping;

class RMT : public cSimpleModule
{
  private:
    PDUForwardingTable* fwTable;

    southMapping intGates;
    efcpiMapping efcpiGates;

    std::string processName;
    bool relayOn;


    void deleteEfcpiGate(int efcpiId);

//    RMTPortManager* ports;

//    void enqueueRelayPDU(PDU_Base* pdu);
//    void enqueueMuxPDU(PDU_Base* pdu);
//    void runRelay();
//    void runMux();

    void sendDown(PDU_Base* pdu);
    void sendUp(PDU_Base* pdu);

  public:

    void createEfcpiGate(unsigned int efcpiId);

    RMT();
    virtual ~RMT();

    bool relayStatus();



  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

#endif /* RMT_H_ */
