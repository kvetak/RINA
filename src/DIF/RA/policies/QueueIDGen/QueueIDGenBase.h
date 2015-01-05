//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef QUEUEIDGENBASE_H_
#define QUEUEIDGENBASE_H_

#include <omnetpp.h>

#include "Flow.h"
#include "PDU_m.h"

/**
 * Noop base class for the RA queue ID generator.
 * This convenience class provides generation of queue IDs from given objects.
 */
class QueueIDGenBase : public cSimpleModule
{
  public:
    /**
     * Generates queue ID for given PDU (this is usually invoked by RMT).
     *
     * @param pdu PDU
     */
    virtual std::string generateID(PDU_Base* pdu);

    /**
     * Generates queue ID for given flow object (this is usually invoked by QueueAlloc policy).
     *
     * @param flow flow object
     */
    virtual std::string generateID(Flow* flow);

  protected:
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

#endif /* QUEUEIDGENBASE_H_ */
