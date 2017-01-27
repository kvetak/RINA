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

#ifndef APLISTENERS_H_
#define APLISTENERS_H_

#include <omnetpp.h>
#include "DAF/AP/AP.h"
#include "DAF/AP/APIResult.h"

class AP;
class APListeners : public cListener {
  public:
    APListeners(AP* nap);
    virtual ~APListeners();

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b, cObject *detail) {
        EV << "Signal to AP initiated by " << src->getFullPath() << endl;
    }
  protected:
    AP* ap;
};

class LisAPAllReqFromFai : public APListeners {
  public:
    LisAPAllReqFromFai(AP* nap) : APListeners(nap){};
    using APListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEAPAPI : public APListeners {
    using APListeners::receiveSignal;
  public:
    LisAEAPAPI(AP* nap) : APListeners(nap){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAPEnrolled : public APListeners {
  public:
    LisAPEnrolled(AP* nap) :  APListeners(nap){};
    using APListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, long obj, cObject *detail);
};


#endif /* APLISTENERS_H_ */
