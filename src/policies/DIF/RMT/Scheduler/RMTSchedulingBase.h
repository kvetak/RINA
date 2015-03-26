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

#ifndef RMTSCHEDULINGBASE_H_
#define RMTSCHEDULINGBASE_H_

#include <omnetpp.h>

#include "RMTPort.h"
#include "RMTQueue.h"

/**
 * Noop base class for the RMT scheduling policy.
 * This policy is invoked each time some queue has data to send and uses some
 * algorithm to make a decision about which queues should be handled first.
 */
class RMTSchedulingBase : public cSimpleModule
{

  friend class RMTQMonitorBase; /* For access to scheduling policy variables. */

  public:

    /**
     * A hook method invoked on multiple occasions.
     * 1) A PDU arrives into a queue.
     * 2) An (N-1)-port becomes ready to serve.
     * 3) By self-postponed scheduler invocation.
     *
     * @param port the (N-1)-port
     * @param direction the direction of data flow (in/out)
     */
    virtual void processQueues(RMTPort* port, RMTQueueType direction);

  protected:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Method used for creating postponed Scheduler calls (e.g. for PDU spacing).
     */
    void scheduleReinvocation(simtime_t time, RMTPort* port, RMTQueueType direction);

    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     */
    void handleMessage(cMessage *msg);

  private:

    /**
     *  Module initialization routine setting up parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    void initialize();
};

#endif /* RMTSCHEDULINGBASE_H_ */
