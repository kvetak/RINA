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

#ifndef FAILISTENERS_H_
#define FAILISTENERS_H_

#include "FAI.h"

class FAI;
class FAIListeners : public cListener {
 public:
    FAIListeners(FAI* nfai);
    virtual ~FAIListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
        EV << "Signal to FAI initiated by " << src->getFullPath() << endl;
    }
 protected:
   FAI* fai;
};

class LisFAIAllocResPosi : public FAIListeners
{
  public:
    LisFAIAllocResPosi(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAIAllocResNega : public FAIListeners
{
  public:
    LisFAIAllocResNega(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAIAllocReq : public FAIListeners
{
  public:
    LisFAIAllocReq(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAICreResPosi : public FAIListeners
{
  public:
    LisFAICreResPosi(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAICreReq : public FAIListeners
{
  public:
    LisFAICreReq(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAICreResNega : public FAIListeners
{
  public:
    LisFAICreResNega(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAIDelRes : public FAIListeners
{
  public:
    LisFAIDelRes(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisFAIDelReq : public FAIListeners
{
  public:
    LisFAIDelReq(FAI* nfai) : FAIListeners(nfai){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
#endif /* FAILISTENERS_H_ */
