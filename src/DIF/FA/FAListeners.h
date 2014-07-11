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
#include "FA.h"

class FAListeners : public cListener {
  protected:
    FA* fa;
  public:
    FAListeners(FA* sfa) {
        fa = sfa;
    };
    virtual ~FAListeners(){};

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
        EV << "Signal initiated by " << src->getFullPath() << endl;
    }

};

class LisFAAllocReq : public FAListeners
{
  public:
    LisFAAllocReq(FA* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFACreReq : public FAListeners
{
  public:
    LisFACreReq(FA* sfa) : FAListeners(sfa){};
};

class LisFACreRes : public FAListeners
{
  public:
    LisFACreRes(FA* sfa) : FAListeners(sfa){};
};


class LisFADelReq : public FAListeners
{
  public:
    LisFADelReq(FA* sfa) : FAListeners(sfa){};
};


class LisFADelRes : public FAListeners
{
  public:
    LisFADelRes(FA* sfa) : FAListeners(sfa){};
};

#endif /* FALISTENERS_H_ */
