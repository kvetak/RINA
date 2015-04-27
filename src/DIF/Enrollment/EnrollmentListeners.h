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

#ifndef ENROLLMENTLISTENERS_H_
#define ENROLLMENTLISTENERS_H_

#include "Enrollment.h"

class Enrollment;
class EnrollmentListeners : public cListener {
public:
    EnrollmentListeners(Enrollment* nenrollment);
    virtual ~EnrollmentListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj) {
               EV << "Signal to Enrollment initiated by " << src->getFullPath() << endl;
        }
protected:
    Enrollment* enrollment;
};


class LisEnrollmentAllResPosi : public EnrollmentListeners {
public:
    LisEnrollmentAllResPosi(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};


class LisEnrollmentGetFlowFromFaiCreResPosi : public EnrollmentListeners {
public:
    LisEnrollmentGetFlowFromFaiCreResPosi(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};


class LisEnrollmentStartEnrollReq : public EnrollmentListeners {
public:
    LisEnrollmentStartEnrollReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentStartEnrollRes : public EnrollmentListeners {
public:
    LisEnrollmentStartEnrollRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentStopEnrollReq : public EnrollmentListeners {
public:
    LisEnrollmentStopEnrollReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentStopEnrollRes : public EnrollmentListeners {
public:
    LisEnrollmentStopEnrollRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentStopOperationReq : public EnrollmentListeners {
public:
    LisEnrollmentStopOperationReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentStartOperationRes : public EnrollmentListeners {
public:
    LisEnrollmentStartOperationRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentConResPosi : public EnrollmentListeners {
public:
    LisEnrollmentConResPosi(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentConResNega : public EnrollmentListeners {
public:
    LisEnrollmentConResNega(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

class LisEnrollmentConReq : public EnrollmentListeners {
public:
    LisEnrollmentConReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};


#endif /* ENROLLMENTLISTENERS_H_ */
