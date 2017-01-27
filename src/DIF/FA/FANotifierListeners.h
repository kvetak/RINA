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

#ifndef FANOTIFIERLISTENERS_H_
#define FANOTIFIERLISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/FA/FANotifierBase.h"

class FANotifierListeners : public cListener {
  public:
    FANotifierListeners(FANotifierBase* nfanb);
    virtual ~FANotifierListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail) {
            EV << "Signal to FANotifierBase initiated by " << src->getFullPath() << endl;
    }
  protected:
    FANotifierBase* fanb;
};


class LisRIBDCreReq : public FANotifierListeners {
  public:
    LisRIBDCreReq(FANotifierBase* nfanb) : FANotifierListeners(nfanb){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDDelReq : public FANotifierListeners {
  public:
    LisRIBDDelReq(FANotifierBase* nfanb) : FANotifierListeners(nfanb){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDDelRes : public FANotifierListeners {
  public:
    LisRIBDDelRes(FANotifierBase* nfanb) : FANotifierListeners(nfanb){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDAllReqFromFai : public FANotifierListeners {
  public:
    LisRIBDAllReqFromFai(FANotifierBase* nfanb) : FANotifierListeners(nfanb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDCreResNega: public FANotifierListeners {
  public:
    LisRIBDCreResNega(FANotifierBase* nfanb) : FANotifierListeners(nfanb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDCreResPosi: public FANotifierListeners {
  public:
    LisRIBDCreResPosi(FANotifierBase* nfanb) : FANotifierListeners(nfanb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDCreFloNega: public FANotifierListeners {
  public:
    LisRIBDCreFloNega(FANotifierBase* nfanb) : FANotifierListeners(nfanb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDCreFloPosi: public FANotifierListeners {
  public:
    LisRIBDCreFloPosi(FANotifierBase* nfanb) : FANotifierListeners(nfanb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};



#endif /* FANOTIFIERLISTENERS_H_ */
