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

#ifndef RALISTENERS_H_
#define RALISTENERS_H_


#include <omnetpp.h>
#include "DIF/RA/RABase.h"
#include "DIF/RA/NM1FlowTable.h"
#include "DIF/RA/NM1FlowTableItem.h"
#include "DIF/RMT/RMTQueue.h"

class RAListeners : public cListener
{
  public:
    RAListeners(RABase* nra);
    virtual ~RAListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, bool b, cObject *detail) {
            EV << "Signal to RA initiated by " << src->getFullPath() << endl;
        }
  protected:
    RABase* ra;
};

class LisRACreFlow : public RAListeners
{
    using RAListeners::receiveSignal;
  public:
    LisRACreFlow(RABase* nra) : RAListeners(nra){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRAAllocResPos : public RAListeners
{
  public:
    LisRAAllocResPos(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};


class LisRACreAllocResPos : public RAListeners
{
  public:
    LisRACreAllocResPos(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRACreResPosi : public RAListeners
{
  public:
    LisRACreResPosi(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRADelFlow : public RAListeners
{
  public:
    LisRADelFlow(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisEFCPStopSending : public RAListeners
{
  public:
    LisEFCPStopSending(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisEFCPStartSending : public RAListeners
{
  public:
    LisEFCPStartSending(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRMTSlowdownRequest : public RAListeners
{
  public:
    LisRMTSlowdownRequest(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

class LisRIBCongNotif : public RAListeners
{
  public:
    LisRIBCongNotif(RABase* nra) : RAListeners(nra){};
    using RAListeners::receiveSignal;
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};


#endif /* RALISTENERS_H_ */
