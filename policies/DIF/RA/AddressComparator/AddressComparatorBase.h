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

#ifndef ADDRESSCOMPARATORBASE_H_
#define ADDRESSCOMPARATORBASE_H_

#include <omnetpp.h>
#include "ExternConsts.h"
#include "Address.h"

/**
 * Noop base class for the RA address comparator policy
 * The policy decides whether this IPC accepts given address.
 */
class AddressComparatorBase : public cSimpleModule
{
  public:
    virtual bool matchesThisIPC(const Address& addr);

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
