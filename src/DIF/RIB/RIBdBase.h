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

#ifndef RIBDBASE_H_
#define RIBDBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "ExternConsts.h"
#include "Flow.h"
#include "CDAPMessage_m.h"
#include "PDUFTGUpdate.h"
#include "CongestionDescriptor.h"
#include "PDU.h"
#include "IntRoutingUpdate.h"


class RIBdBase : public cSimpleModule {
  public:
    RIBdBase();
    virtual ~RIBdBase();

    virtual void sendCreateRequestFlow(Flow* flow) = 0;
    virtual void sendCreateResponseNegative(Flow* flow) = 0;
    virtual void sendCreateResponsePostive(Flow* flow) = 0;
    virtual void sendDeleteRequestFlow(Flow* flow) = 0;
    virtual void sendDeleteResponseFlow(Flow* flow) = 0;
    virtual void receiveData(CDAPMessage* flow) = 0;
    virtual void receiveAllocationRequestFromFai(Flow* flow) = 0;
    virtual void receiveCreateFlowPositiveFromRa(Flow* flow) = 0;
    virtual void receiveCreateFlowNegativeFromRa(Flow* flow) = 0;
    /* Handles information coming from PDUFTG module. */
    virtual void receiveRoutingUpdateFromRouting(IntRoutingUpdate * flow) = 0;

    virtual void sendCongestionNotification(PDU* pdu) = 0;

    const Address& getMyAddress() const;

  protected:
    Address MyAddress;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();
    long getNewInvokeId();

};

#endif /* RIBDBASE_H_ */
