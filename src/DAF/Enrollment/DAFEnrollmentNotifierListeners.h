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

#ifndef DAFENROLLMENTNOTIFIERLISTENERS_H_
#define DAFENROLLMENTNOTIFIERLISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAFEnrollmentNotifierBase.h"

class DAFEnrollmentNotifierListeners : public cListener {
  public:
    DAFEnrollmentNotifierListeners(DAFEnrollmentNotifierBase* nenb);
    virtual ~DAFEnrollmentNotifierListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
               EV << "Signal to DAFEnrollmentNotifierBase initiated by " << src->getFullPath() << endl;
    }
  protected:
    DAFEnrollmentNotifierBase* enb;
};

class LisDAFEnrollmentNotifierRcvCACE: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierRcvCACE(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierRcvEnrollCACE: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierRcvEnrollCACE(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStaEnrolReq: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStaEnrolReq(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStaEnrolRes: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStaEnrolRes(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStoEnrolReq: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStoEnrolReq(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStoEnrolRes: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStoEnrolRes(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStaOperReq: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStaOperReq(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

class LisDAFEnrollmentNotifierStaOperRes: public DAFEnrollmentNotifierListeners {
  public:
    LisDAFEnrollmentNotifierStaOperRes(DAFEnrollmentNotifierBase* nenb) : DAFEnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};


#endif /* DAFENROLLMENTNOTIFIERLISTENERS_H_ */
