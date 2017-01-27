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

#ifndef FALISTENERS_H_
#define FALISTENERS_H_

#include <omnetpp.h>
#include "DIF/FA/FABase.h"

class FAListeners : public cListener {
  protected:
    FABase* fa;
  public:
    FAListeners(FABase* sfa){
        fa = sfa;
    };
    virtual ~FAListeners(){};

    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b, cObject *detail) {
        EV << "Signal to FA initiated by " << src->getFullPath() << endl;
    }

};

class LisFAAllocReq : public FAListeners
{
  public:
    LisFAAllocReq(FABase* sfa) : FAListeners(sfa){};
    using FAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFAAllocFinMgmt : public FAListeners
{
  public:
    LisFAAllocFinMgmt(FABase* sfa) : FAListeners(sfa){};
    using FAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};


class LisFACreFloPosi : public FAListeners
{
  public:
    LisFACreFloPosi(FABase* sfa) : FAListeners(sfa){};
    using FAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFADeallocReq : public FAListeners
{
  public:
    LisFADeallocReq(FABase* sfa) : FAListeners(sfa){};
    using FAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisFACreReq : public FAListeners
{
  public:
    LisFACreReq(FABase* sfa) : FAListeners(sfa){};
    using FAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};
/*
class LisFACreRes : public FAListeners
{
  public:
    LisFACreRes(FABase* sfa) : FAListeners(sfa){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};
*/
class LisFADelRes : public FAListeners
{
  public:
    LisFADelRes(FABase* sfa) : FAListeners(sfa){};
};

#endif /* FALISTENERS_H_ */
