//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef WeightedFairQMonitor_H_
#define WeightedFairQMonitor_H_

#include <map>

#include "RMTQMonitorBase.h"
#include <WeightedFairQMonitor/FlowParams.h>


namespace FWQ {

using namespace std;

typedef map<RMTQueue*, FlowParams> queue2Fp;
typedef queue2Fp::iterator queue2FpIt;

class WeightedFairQMonitor : public RMTQMonitorBase
{
  public:
    virtual void onPolicyInit();
    virtual void onMessageArrival(RMTQueue* queue);
    virtual void onMessageDeparture(RMTQueue* queue);
    virtual void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    virtual void postQueueCreation(RMTQueue* queue);
    virtual void preQueueRemoval(RMTQueue* queue);

    virtual RMTQueue * getNextQueue();

  protected:
    queue2Fp queueTimes;
    int defBW;
    int stopQAt, startQAt;
};

} /* namespace FWQ */

#endif /* SIMPLEMONITOR_H_ */
