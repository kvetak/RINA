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

#ifndef INTROUTING_H_
#define INTROUTING_H_

#include <omnetpp.h>

#include <vector>
#include <string>
#include "Common/RINASignals.h"
#include "DIF/Routing/IntRoutingUpdate.h"
#include "Common/Address.h"
#include "DIF/RA/PDUFG/IntPDUFG.h"

class LisRoutingRecv;

class IntRouting  : public cSimpleModule {
public:
    //Destructor
    virtual void finish();

    void receiveUpdate(IntRoutingUpdate * update);

    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(IntRoutingUpdate * update) = 0;


protected:
    Address myAddress;

    // Initialize cons, signals, etc.
    void initialize();
    // Sends a Routing Update
    void sendUpdate(IntRoutingUpdate * update);

    // Called after initialize
    virtual void onPolicyInit() = 0;

private:
    LisRoutingRecv * listener;
    simsignal_t sigRoutingUpdate;
    IntPDUFG * fwdg;
};

/* Listener for routing updates.  */
class LisRoutingRecv : public cListener {
public:
    LisRoutingRecv(IntRouting * _module);
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details);
protected:
    IntRouting * module;
};

#endif /* INTROUTING_H_ */
