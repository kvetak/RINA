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

#ifndef FAIBASE_H_
#define FAIBASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Flow.h"

class FAIBase : public cSimpleModule {
  public:
    FAIBase();
    virtual ~FAIBase();

    virtual bool receiveAllocateRequest() = 0;
    virtual bool processDegenerateDataTransfer() = 0;
    virtual bool receiveAllocateResponsePositive() = 0;
    virtual void receiveAllocateResponseNegative() = 0;
    virtual bool receiveCreateRequest() = 0;
    virtual bool receiveCreateResponsePositive(Flow* flow) = 0;
    virtual bool receiveCreateResponseNegative(Flow* flow) = 0;
    virtual void receiveDeallocateRequest() = 0;
    virtual void receiveDeleteRequest() = 0;
    virtual void receiveDeleteResponse() = 0;

    virtual void receiveCreateFlowResponsePositiveFromNminusOne() = 0;
    virtual void receiveCreateFlowResponseNegativeFromNminusOne() = 0;


    Flow* getFlow()  {
        return FlowObject;
    }

  protected:
    Flow* FlowObject;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;


};

#endif /* FAIBASE_H_ */
