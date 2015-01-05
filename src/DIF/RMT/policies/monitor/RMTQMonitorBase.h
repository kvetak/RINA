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

/**
 * Noop base class for the RMT monitoring policy.
 * This policy responds to various events happening inside RMT, usually by
 * modifying values used by the scheduling policy.
 */
class RMTQMonitorBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked after a PDU arrives into a queue.
     *
     * @param queue pointer to the queue
     */
    virtual void onMessageArrival(RMTQueue* queue);

    /**
     * A hook method invoked after a PDU gets dropped from a queue.
     *
     * @param queue pointer to the queue
     */
    virtual void onMessageDrop(RMTQueue* queue);

    /**
     * A hook method invoked after a queue is created.
     *
     * @param queue pointer to the queue
     */
    virtual void postQueueCreation(RMTQueue* queue);

    /**
     * A hook method invoked before a queue is removed.
     *
     * @param queue pointer to the queue
     */
    virtual void preQueueRemoval(RMTQueue* queue);

  protected:
    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Handler for OMNeT++ module messages (probably not of much use here).
     */
    virtual void handleMessage(cMessage* msg);

  private:
    /**
     *  Module initialization routine setting up parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    virtual void initialize();
};

#endif /* RMTQMONITORBASE_H_ */
