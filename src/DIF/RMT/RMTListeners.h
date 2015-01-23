//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#ifndef RMTLISTENERS_H_
#define RMTLISTENERS_H_

#include <omnetpp.h>
#include "RMTBase.h"

class RMTListeners : public cListener
{
  public:
    RMTListeners(RMTBase* rmt);
    virtual ~RMTListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject* obj)
    {
        EV << "Signal to RMT initiated by " << src->getFullPath() << endl;
    }
  protected:
    RMTBase* rmt;
};

class LisRMTQueuePDURcvd : public RMTListeners
{
  public:
    LisRMTQueuePDURcvd(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj);
};

class LisRMTQueuePDUSent : public RMTListeners
{
  public:
    LisRMTQueuePDUSent(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj);
};

class LisRMTPortReady : public RMTListeners
{
  public:
    LisRMTPortReady(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj);
};


#endif /* RMTLISTENERS_H_ */
