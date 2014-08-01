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

#include <omnetpp.h>
#include <Flow.h>

class FABase : public cSimpleModule {
  public:

    FABase();
    virtual ~FABase();

    virtual void receiveAllocateRequest(cObject* fl) = 0;
    virtual void receiveAllocateResponsePositive(cObject* obj) = 0;
    virtual void receiveAllocateResponseNegative(cObject* obj) = 0;
    virtual void receiveCreateFlowRequest(cObject* fl) = 0;
    virtual void receiveDeallocateRequest(cObject* fl) = 0;
    virtual void deinstantiateFai(Flow* fl) = 0;
    virtual bool invokeNewFlowRequestPolicy(Flow* fl) = 0;

  protected:
    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;


};


#endif /* FABASE_H_ */
