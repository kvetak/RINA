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

#ifndef __RINA_PDUForwardingTable_H_
#define __RINA_PDUForwardingTable_H_

#include <omnetpp.h>
#include "Address.h"
#include "RMTPort.h"

class PDUForwardingTable : public cSimpleModule
{
  public:
    virtual void clean() = 0;
    virtual RMTPort* lookup(Address& destAddr, unsigned short QoSid) = 0;
    virtual RMTPort* lookup(Address& destAddr) = 0;
    virtual void printAll() = 0;

  protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
};

#endif
