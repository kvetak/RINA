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

#ifndef ADDRESSCOMPARATORBASE_H_
#define ADDRESSCOMPARATORBASE_H_

#include <omnetpp.h>
#include "Common/Utils.h"
#include "Common/ExternConsts.h"
#include "Common/Address.h"
#include "Common/PDU.h"

/**
 * Noop base class for the RA address comparator policy
 * The policy decides whether this IPC accepts given address.
 */
class AddressComparatorBase : public cSimpleModule
{
  public:
    virtual bool matchesThisIPC(const Address& addr, PDU * pdu);

  protected:
    /**
     * A hook method invoked after the initial setup of policy module.
     */
    virtual void onPolicyInit();

    /**
     * This IPC address.
     */
    Address thisIPCAddr;

  private:
    /**
     *  Module initialization routine setting up some parameters for GUI.
     *  Inherited policies should be using onPolicyInit() instead.
     */
    void initialize();
};

#endif /* ADDRESSCOMPARATORBASE_H_ */
