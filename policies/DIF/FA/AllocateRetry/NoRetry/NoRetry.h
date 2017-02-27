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

#ifndef __RINA_NORETRY_H_
#define __RINA_NORETRY_H_

#include <omnetpp.h>
#include "DIF/FA/AllocateRetry/AllocateRetryBase.h"

using namespace omnetpp;

class NoRetry : public AllocateRetryBase
{
  public:
    virtual bool run(Flow& flow);
  protected:
    virtual void initialize() {setPolicyDisplayString(this);};
    virtual void handleMessage(cMessage *msg) {return;};
};

#endif
