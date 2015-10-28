// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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

class LisRIBDRcvData : public RIBdListeners {
  public:
    LisRIBDRcvData(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
/*
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
*/
/* Listen for Forwarding info updates from PDUFTG and handle them. */
//class LisRIBDRoutingUpdate: public RIBdListeners
//{
//  public:
//    LisRIBDRoutingUpdate(RIBdBase* nribd) : RIBdListeners(nribd) {};
//    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
//};

class LisRIBDCongesNotif: public RIBdListeners {
  public:
    LisRIBDCongesNotif(RIBdBase* nribd) : RIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
/*
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
*/
#endif /* RIBDLISTENERS_H_ */
