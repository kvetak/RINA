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

#ifndef FABASE_H_
#define FABASE_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "FAITable.h"

class FABase : public cSimpleModule {
  public:

    FABase();
    virtual ~FABase();

    virtual bool receiveAllocateRequest(Flow* flow) = 0;
    virtual void receiveCreateFlowPositive(Flow* flow) = 0;
    //virtual void receiveCreateResponseFlowPositiveFromRibd(Flow* flow) = 0;
    virtual bool receiveCreateFlowRequestFromRibd(Flow* flow) = 0;
    virtual bool receiveDeallocateRequest(Flow* flow) = 0;
    virtual void deinstantiateFai(Flow* flow) = 0;
    virtual bool invokeNewFlowRequestPolicy(Flow* flow) = 0;

    virtual bool setOriginalAddresses(Flow* flow) = 0;
    virtual bool setNeighborAddresses(Flow* flow) = 0;

    FAITable* getFaiTable() const;
    const Address& getMyAddress() const;

  protected:
    FAITable* FaiTable;
    Address MyAddress;

    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

    void initMyAddress();

};


#endif /* FABASE_H_ */
