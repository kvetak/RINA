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

#ifndef FALISTENERS_H_
#define FALISTENERS_H_

#include <omnetpp.h>
#include "FABase.h"

class FAListeners : public cListener {
  protected:
    FABase* fa;
  public:
    FAListeners(FABase* sfa){
        fa = sfa;
    };
    virtual ~FAListeners(){};

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
        EV << "Signal to FA initiated by " << src->getFullPath() << endl;
    }

};

class LisFAAllocReq : public FAListeners
{
  public:
    LisFAAllocReq(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};


class LisFACreFloPosi : public FAListeners
{
  public:
    LisFACreFloPosi(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFADeallocReq : public FAListeners
{
  public:
    LisFADeallocReq(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFACreReq : public FAListeners
{
  public:
    LisFACreReq(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
/*
class LisFACreRes : public FAListeners
{
  public:
    LisFACreRes(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
*/
class LisFADelRes : public FAListeners
{
  public:
    LisFADelRes(FABase* sfa) : FAListeners(sfa){};
};

#endif /* FALISTENERS_H_ */
