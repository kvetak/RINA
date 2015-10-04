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

#ifndef AEMGMTLISTENERS_H_
#define AEMGMTLISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "AEMgmtBase.h"

class AEMgmtListeners : public cListener {
  public:
    AEMgmtListeners(AEMgmtBase* nmgmt);
    virtual ~AEMgmtListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
        EV << "Signal to AEMgmt initiated by " << src->getFullPath() << endl;
    }
  protected:
    AEMgmtBase* aemgmt;
};

class LisAEMgmtCreReq : public AEMgmtListeners {
  public:
    LisAEMgmtCreReq(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtDelReq : public AEMgmtListeners {
  public:
    LisAEMgmtDelReq(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtDelRes : public AEMgmtListeners {
  public:
    LisAEMgmtDelRes(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtRcvData : public AEMgmtListeners {
  public:
    LisAEMgmtRcvData(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtAllReqFromFai : public AEMgmtListeners {
  public:
    LisAEMgmtAllReqFromFai(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtCreResNega: public AEMgmtListeners {
  public:
    LisAEMgmtCreResNega(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtCreResPosi: public AEMgmtListeners {
  public:
    LisAEMgmtCreResPosi(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtCreFloNega: public AEMgmtListeners {
  public:
    LisAEMgmtCreFloNega(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtCreFloPosi: public AEMgmtListeners {
  public:
    LisAEMgmtCreFloPosi(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

/* Listen for Forwarding info updates from PDUFTG and handle them. */
class LisAEMgmtRoutingUpdate: public AEMgmtListeners
{
  public:
    LisAEMgmtRoutingUpdate(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtCongesNotif: public AEMgmtListeners {
  public:
    LisAEMgmtCongesNotif(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};



class LisAEMgmtRcvCACE: public AEMgmtListeners {
  public:
    LisAEMgmtRcvCACE(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtRcvEnrollCACE: public AEMgmtListeners {
  public:
    LisAEMgmtRcvEnrollCACE(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStaEnrolReq: public AEMgmtListeners {
  public:
    LisAEMgmtStaEnrolReq(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStaEnrolRes: public AEMgmtListeners {
  public:
    LisAEMgmtStaEnrolRes(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStoEnrolReq: public AEMgmtListeners {
  public:
    LisAEMgmtStoEnrolReq(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStoEnrolRes: public AEMgmtListeners {
  public:
    LisAEMgmtStoEnrolRes(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStaOperReq: public AEMgmtListeners {
  public:
    LisAEMgmtStaOperReq(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisAEMgmtStaOperRes: public AEMgmtListeners {
  public:
    LisAEMgmtStaOperRes(AEMgmtBase* naemgmt) : AEMgmtListeners(naemgmt) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

#endif /* AEMgmtLISTENERS_H_ */
