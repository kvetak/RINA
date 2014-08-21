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

#ifndef __RINA_RMTFLOWMANAGER_H_
#define __RINA_RMTFLOWMANAGER_H_

#include <omnetpp.h>

#include "RMTFlow.h"

typedef std::map<int, RMTFlow*>  RMTFlows;

class RMTFlowManager : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    RMTFlowManager();
    virtual ~RMTFlowManager();

    typedef RMTFlows::iterator iterator;
    iterator begin();
    iterator end();

    RMTFlow* getRibFlow();

    // identifiers shared with corresponding EFCP instances
    RMTFlow* getFlow(int portId);
    void addFlow(int portId);
    void removeFlow(int portId);

  private:
    RMTFlows flows;
    // dedicated management flow
    RMTFlow* ribFlow;
};

#endif
