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

#ifndef ROUTINGNOTIFIERBASE_H_
#define ROUTINGNOTIFIERBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Common/CDAPProcessingBase.h"
#include "Common/ExternConsts.h"
#include "Common/RINASignals.h"
#include "DIF/Routing/IntRoutingUpdate.h"

class RoutingNotifierBase : public cSimpleModule, public CDAPProcessingBase {
  public:
    virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * update) = 0;

    virtual bool isMessageProcessable(CDAPMessage* msg);
    virtual void receiveMessage(CDAPMessage* msg);
    virtual void signalizeMessage(CDAPMessage* msg) = 0;
};

#endif /* ROUTINGNOTIFIERBASE_H_ */
