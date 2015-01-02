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

#ifndef RMTQMONITORBASE_H_
#define RMTQMONITORBASE_H_

#include <omnetpp.h>

#include "RMTQueue.h"

class RMTQMonitorBase : public cSimpleModule
{
  public:
    RMTQMonitorBase();
    virtual ~RMTQMonitorBase();

    virtual void run(RMTQueue* queue);

    // optional event hooks
    virtual void onPolicyInit();
    virtual void postQueueCreation(RMTQueue* queue);
    virtual void preQueueRemoval(RMTQueue* queue);

  protected:
    void initialize();
    void handleMessage(cMessage *msg);
};

#endif /* RMTQMONITORBASE_H_ */
