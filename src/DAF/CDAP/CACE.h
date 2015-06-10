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

class LisCACESendData;
class CACE : public cSimpleModule
{
public:
    void sendData(CDAPMessage *cmsg);
  protected:

    simsignal_t sigCACEReceiveData;

    LisCACESendData* lisCACESendData;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initPointers();
    void initSignalsAndListeners();
    void signalizeDataReceive(CDAPMessage* cmsg);

};

#endif
