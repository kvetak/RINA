// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef QUEUEIDGENBASE_H_
#define QUEUEIDGENBASE_H_

#include <omnetpp.h>
#include "Common/Utils.h"
#include "Common/Flow.h"
#include "Common/PDU.h"

/**
 * Noop base class for the RA queue ID generator.
 * This convenience class provides generation of queue IDs from given objects.
 */
class QueueIDGenBase : public cSimpleModule
{
  public:

    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * Generates input queue ID for given PDU (this is usually invoked by a port).
     *
     * @param pdu PDU
     */
    virtual std::string generateInputQueueID(PDU* pdu);

    /**
     * Generates output queue ID for given PDU (this is usually invoked by RMT).
     *
     * @param pdu PDU
     */
    virtual std::string generateOutputQueueID(PDU* pdu);

    /**
     * Generates queue ID for given flow object (this is usually invoked by QueueAlloc policy).
     *
     * @param flow flow object
     */
    virtual std::string generateIDFromFlow(Flow* flow);

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
