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

#ifndef RALISTENERS_H_
#define RALISTENERS_H_


#include <omnetpp.h>
#include "RABase.h"

class RAListeners : public cListener
{
  public:
    RAListeners(RABase* nra);
    virtual ~RAListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
            EV << "Signal to RA initiated by " << src->getFullPath() << endl;
        }
  protected:
    RABase* ra;
};

class LisRACreFlow : public RAListeners
{
  public:
    LisRACreFlow(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRAAllocResPos : public RAListeners
{
  public:
    LisRAAllocResPos(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};


class LisRACreAllocResPos : public RAListeners
{
  public:
    LisRACreAllocResPos(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRACreResPosi : public RAListeners
{
  public:
    LisRACreResPosi(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisEFCPStopSending : public RAListeners
{
  public:
    LisEFCPStopSending(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisEFCPStartSending : public RAListeners
{
  public:
    LisEFCPStartSending(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRMTSlowdownRequest : public RAListeners
{
  public:
    LisRMTSlowdownRequest(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBCongNotif : public RAListeners
{
  public:
    LisRIBCongNotif(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};


#endif /* RALISTENERS_H_ */
