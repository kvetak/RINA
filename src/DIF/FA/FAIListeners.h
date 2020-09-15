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

#ifndef FAILISTENERS_H_
#define FAILISTENERS_H_

#include <omnetpp.h>

class FAI;
class FAIListeners : public cListener {
 public:
    FAIListeners(FAI* nfai);
    virtual ~FAIListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b, cObject *detail) {
        EV << "Signal to FAI initiated by " << src->getFullPath() << endl;
    }
 protected:
   FAI* fai;
};

class LisFAIAllocResPosi : public FAIListeners
{
  public:
    LisFAIAllocResPosi(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAIAllocResNega : public FAIListeners
{
  public:
    LisFAIAllocResNega(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAICreResPosi : public FAIListeners
{
  public:
    LisFAICreResPosi(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAICreResNega : public FAIListeners
{
  public:
    LisFAICreResNega(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAICreResPosiNminusOne : public FAIListeners
{
  public:
    LisFAICreResPosiNminusOne(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAICreResNegaNminusOne : public FAIListeners
{
  public:
    LisFAICreResNegaNminusOne(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAIDelRes : public FAIListeners
{
  public:
    LisFAIDelRes(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAIDelReq : public FAIListeners
{
  public:
    LisFAIDelReq(FAI* nfai) : FAIListeners(nfai){};
    using FAIListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};
#endif /* FAILISTENERS_H_ */
