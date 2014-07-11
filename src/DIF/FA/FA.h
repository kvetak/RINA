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
/**
 * @file FlowAllocator.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Apr 29, 2014
 * @brief
 * @detail
 */

#ifndef FA_H_
#define FA_H_

//Standard libraries
#include <omnetpp.h>
#include <string>
#include "FlowTable.h"
#include "ModuleAccess.h"

#define RANDOM_NUMBER_GENERATOR 0
#define MAX_PORTID 65535
#define MAX_CEPID  65535

class FA : public cSimpleModule
{
  public:
    FA();
    virtual ~FA();

    void receiveAllocateRequest(Flow* fl);
    void processCreateFlowRequest();
    void processDeallocateRequest();
    bool invokeNewFlowRequestPolicy();

  protected:
    //SimpleModule overloads
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    FlowTable* FlowTab;
    bool createFAI();
};

#endif /* FLOWALLOCATOR_H_ */
