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

#ifndef RMTBASE_H_
#define RMTBASE_H_

#include <omnetpp.h>

#include "RMTSchedulingBase.h"
#include "RMTQueue.h"

class RMTBase : public cSimpleModule
{
  public:
    RMTBase();
    virtual ~RMTBase();

    virtual void createEfcpiGate(unsigned int efcpiId) = 0;
    virtual void deleteEfcpiGate(unsigned int efcpiId) = 0;
    virtual void addEfcpiToQueueMapping(unsigned cepId, RMTQueue* outQueue) = 0;
    virtual void setOnWire(bool status) = 0;
    virtual bool isOnWire() = 0;
    virtual void enableRelay() = 0;
    virtual void disableRelay() = 0;
    virtual bool getRelayStatus() = 0;
    virtual void invokeSchedulingPolicy(cObject* obj) = 0;

  protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;

};

#endif /* RMTBASE_H_ */
