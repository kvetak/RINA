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
#include "AEListeners.h"
#include "Flow.h"
#include "RINASignals.h"

class AE : public cSimpleModule
{
  public:
    AE();
    virtual ~AE();

  protected:
    Flow* flow;

    std::string srcApName;
    std::string srcApInstance;
    std::string srcAeName;
    std::string srcAeInstance;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initSignalsAndListeners();
    void initNamingInfo();

    //Signals
    simsignal_t sigAEAllocReq;
    simsignal_t sigAEDeallocReq;

    //Listeners

    //Signaling
    void signalizeAllocateRequest();
    void signalizeDeallocateRequest();

};

#endif
