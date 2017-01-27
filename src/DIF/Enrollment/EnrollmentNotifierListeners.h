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

#ifndef ENROLLMENTNOTIFIERLISTENERES_H_
#define ENROLLMENTNOTIFIERLISTENERES_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DIF/Enrollment/EnrollmentNotifierBase.h"

class EnrollmentNotifierListeners : public cListener {
  public:
    EnrollmentNotifierListeners(EnrollmentNotifierBase* nenb);
    virtual ~EnrollmentNotifierListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail) {
               EV << "Signal to EnrollmentNotifierBase initiated by " << src->getFullPath() << endl;
    }
  protected:
    EnrollmentNotifierBase* enb;
};

class LisRIBDRcvCACE: public EnrollmentNotifierListeners {
  public:
    LisRIBDRcvCACE(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDRcvEnrollCACE: public EnrollmentNotifierListeners {
  public:
    LisRIBDRcvEnrollCACE(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStaEnrolReq: public EnrollmentNotifierListeners {
  public:
    LisRIBDStaEnrolReq(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStaEnrolRes: public EnrollmentNotifierListeners {
  public:
    LisRIBDStaEnrolRes(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStoEnrolReq: public EnrollmentNotifierListeners {
  public:
    LisRIBDStoEnrolReq(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStoEnrolRes: public EnrollmentNotifierListeners {
  public:
    LisRIBDStoEnrolRes(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStaOperReq: public EnrollmentNotifierListeners {
  public:
    LisRIBDStaOperReq(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBDStaOperRes: public EnrollmentNotifierListeners {
  public:
    LisRIBDStaOperRes(EnrollmentNotifierBase* nenb) : EnrollmentNotifierListeners(nenb) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};


#endif /* ENROLLMENTNOTIFIERLISTENERES_H_ */
