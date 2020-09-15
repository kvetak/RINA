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

/**
 * @file EnrollmentListeners.h
 * @author Kamil Jerabek (xjerab18@stud.fit.vutbr.cz)
 * @date Apr 1, 2015
 * @brief Enrollment and CACE listeners
 * @detail
 */



#ifndef ENROLLMENTLISTENERS_H_
#define ENROLLMENTLISTENERS_H_

#include <omnetpp.h>

class Enrollment;
class CDAPMessage;
class EnrollmentListeners : public cListener {
  public:
    EnrollmentListeners(Enrollment* enrollment) : enrollment(enrollment) {}

  protected:
    Enrollment* enrollment;
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail) override = 0;
};


class LisEnrollmentGetFlowFromFaiCreResPosi : public EnrollmentListeners {
  public:
    LisEnrollmentGetFlowFromFaiCreResPosi(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};


class LisEnrollmentStartEnrollReq : public EnrollmentListeners {
  public:
    LisEnrollmentStartEnrollReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentStartEnrollRes : public EnrollmentListeners {
  public:
    LisEnrollmentStartEnrollRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentStopEnrollReq : public EnrollmentListeners {
  public:
    LisEnrollmentStopEnrollReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentStopEnrollRes : public EnrollmentListeners {
  public:
    LisEnrollmentStopEnrollRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentStopOperationReq : public EnrollmentListeners {
  public:
    LisEnrollmentStopOperationReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentStartOperationRes : public EnrollmentListeners {
  public:
    LisEnrollmentStartOperationRes(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentConResPosi : public EnrollmentListeners {
  public:
    LisEnrollmentConResPosi(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentConResNega : public EnrollmentListeners {
  public:
    LisEnrollmentConResNega(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};

class LisEnrollmentConReq : public EnrollmentListeners {
  public:
    LisEnrollmentConReq(Enrollment* nenrollment): EnrollmentListeners(nenrollment){};
  protected:
    void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj, cObject* detail) override;
};


#endif /* ENROLLMENTLISTENERS_H_ */
