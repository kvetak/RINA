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

#ifndef AELISTENERS_H_
#define AELISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AE.h"

class AE;
class AEListeners : public cListener {
  public:
    AEListeners(AE* nae);
    virtual ~AEListeners();

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b) {
        EV << "Signal to AE initiated by " << src->getFullPath() << endl;
    }
  protected:
    AE* ae;
};

class LisAEReceiveData : public AEListeners {
  public:
    LisAEReceiveData(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllReqFromFai : public AEListeners {
  public:
    LisAEAllReqFromFai(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllResPosi : public AEListeners {
  public:
    LisAEAllResPosi(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEAllResNega : public AEListeners {
  public:
    LisAEAllResNega(AE* nae) : AEListeners(nae){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

#endif /* AELISTENERS_H_ */
