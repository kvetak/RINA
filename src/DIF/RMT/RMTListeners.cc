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

#include "DIF/RMT/RMTListeners.h"

RMTListeners::RMTListeners(RMTBase* rmt) : rmt(rmt)
{
}

RMTListeners::~RMTListeners()
{
    rmt = nullptr;
}

void LisRMTQueuePDUPreRcvd::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->preQueueArrival(obj);
}

void LisRMTQueuePDUPostRcvd::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->postQueueArrival(obj);
}

void LisRMTQueuePDUPreSend::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->preQueueDeparture(obj);
}

void LisRMTQueuePDUSent::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->postQueueDeparture(obj);
}

void LisRMTPortReadyToServe::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->writeToPort(obj);
}


void LisRMTPortReadyForRead::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject* detail)
{
    rmt->readFromPort(obj);
}
