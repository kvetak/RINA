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

#ifndef AELISTENERS_H_
#define AELISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/AE/AE.h"

class AE;
class AEListeners : public cListener {
  public:
    AEListeners(AE* nae);
    virtual ~AEListeners();

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b, cObject *detail) {
        EV << "Signal to AE initiated by " << src->getFullPath() << endl;
    }
  protected:
    AE* ae;
};

class LisAEReceiveData : public AEListeners {
  public:
    LisAEReceiveData(AE* nae) : AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail) override;
};

class LisAEAllReqFromFai : public AEListeners {
  public:
    LisAEAllReqFromFai(AE* nae) : AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEDeallReqFromFai : public AEListeners {
  public:
    LisAEDeallReqFromFai(AE* nae) : AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEAllResPosi : public AEListeners {
  public:
    LisAEAllResPosi(AE* nae) : AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEAllResNega : public AEListeners {
  public:
    LisAEAllResNega(AE* nae) : AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEConResPosi : public AEListeners {
  public:
    LisAEConResPosi(AE* nae) :  AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEConResNega : public AEListeners {
  public:
    LisAEConResNega(AE* nae) :  AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAERelRes : public AEListeners {
  public:
    LisAERelRes(AE* nae) :  AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisAEEnrolled : public AEListeners {
  public:
    LisAEEnrolled(AE* nae) :  AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, long obj, cObject *detail);
};

//API AP-AE Listeners
class LisAPAEAPI : public AEListeners {
  public:
    LisAPAEAPI(AE* nae) :  AEListeners(nae){};
    using AEListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

#endif /* AELISTENERS_H_ */
