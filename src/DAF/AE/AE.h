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

class AE : public AEBase
{
  public:
    AE();
    virtual ~AE();

  protected:
    IRM* Irm;
    ConnectionTable* ConTab;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void initPointers();
    void initSignalsAndListeners();

    void insert(Flow& flow);
    void createBinding(Flow& flow);

    //Signals
    simsignal_t sigAEAllocReq;
    simsignal_t sigAEDeallocReq;

    //Listeners

    //Signaling
    void signalizeAllocateRequest(Flow* flow);
    void signalizeDeallocateRequest(Flow* flow);

};

#endif
