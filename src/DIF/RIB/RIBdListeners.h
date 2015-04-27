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

#ifndef RIBDLISTENERS_H_
#define RIBDLISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "RIBdBase.h"

class RIBdListeners : public cListener {
  public:
    RIBdListeners(RIBdBase* nribd);
    virtual ~RIBdListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
        EV << "Signal to RIBd initiated by " << src->getFullPath() << endl;
    }
  protected:
    RIBdBase* ribd;
};

class LisRIBDCreReq : public RIBdListeners {
  public:
    LisRIBDCreReq(RIBdBase* nribd) : RIBdListeners(nribd){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDDelReq : public RIBdListeners {
  public:
    LisRIBDDelReq(RIBdBase* nribd) : RIBdListeners(nribd){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDDelRes : public RIBdListeners {
  public:
    LisRIBDDelRes(RIBdBase* nribd) : RIBdListeners(nribd){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDRcvData : public RIBdListeners {
  public:
    LisRIBDRcvData(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDAllReqFromFai : public RIBdListeners {
  public:
    LisRIBDAllReqFromFai(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDCreResNega: public RIBdListeners {
  public:
    LisRIBDCreResNega(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDCreResPosi: public RIBdListeners {
  public:
    LisRIBDCreResPosi(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDCreFloNega: public RIBdListeners {
  public:
    LisRIBDCreFloNega(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDCreFloPosi: public RIBdListeners {
  public:
    LisRIBDCreFloPosi(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

/* Listen for Forwarding info updates from PDUFTG and handle them. */
class LisRIBDRoutingUpdate: public RIBdListeners
{
  public:
    LisRIBDRoutingUpdate(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDCongesNotif: public RIBdListeners {
  public:
    LisRIBDCongesNotif(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};



class LisRIBDRcvCACE: public RIBdListeners {
  public:
    LisRIBDRcvCACE(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDRcvEnrollCACE: public RIBdListeners {
  public:
    LisRIBDRcvEnrollCACE(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStaEnrolReq: public RIBdListeners {
  public:
    LisRIBDStaEnrolReq(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStaEnrolRes: public RIBdListeners {
  public:
    LisRIBDStaEnrolRes(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStoEnrolReq: public RIBdListeners {
  public:
    LisRIBDStoEnrolReq(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStoEnrolRes: public RIBdListeners {
  public:
    LisRIBDStoEnrolRes(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStaOperReq: public RIBdListeners {
  public:
    LisRIBDStaOperReq(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisRIBDStaOperRes: public RIBdListeners {
  public:
    LisRIBDStaOperRes(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

#endif /* RIBDLISTENERS_H_ */
