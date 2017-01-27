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

#ifndef RMTLISTENERS_H_
#define RMTLISTENERS_H_

#include <omnetpp.h>
#include "DIF/RMT/RMTBase.h"

class RMTListeners : public cListener
{
  public:
    RMTListeners(RMTBase* rmt);
    virtual ~RMTListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail)
    {
        EV << "Signal to RMT initiated by " << src->getFullPath() << endl;
    }
  protected:
    RMTBase* rmt;
};

class LisRMTQueuePDUPreRcvd : public RMTListeners
{
  public:
    LisRMTQueuePDUPreRcvd(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};

class LisRMTQueuePDUPostRcvd : public RMTListeners
{
  public:
    LisRMTQueuePDUPostRcvd(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};

class LisRMTQueuePDUPreSend : public RMTListeners
{
  public:
    LisRMTQueuePDUPreSend(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};

class LisRMTQueuePDUSent : public RMTListeners
{
  public:
    LisRMTQueuePDUSent(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};

class LisRMTPortReadyToServe : public RMTListeners
{
  public:
    LisRMTPortReadyToServe(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};

class LisRMTPortReadyForRead : public RMTListeners
{
  public:
    LisRMTPortReadyForRead(RMTBase* rmt) : RMTListeners(rmt){};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject* obj, cObject* detail);
};


#endif /* RMTLISTENERS_H_ */
