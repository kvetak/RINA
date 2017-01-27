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

#include "DIF/RMT/MaxQueue/RMTMaxQBase.h"

Define_Module(RMTMaxQBase);


void RMTMaxQBase::initialize()
{
    qMonPolicy = getRINAModule<RMTQMonitorBase*>(this, 1, {MOD_POL_RMT_QMONITOR});

    addrComparator = getRINAModule<AddressComparatorBase*>(this, 2, {MOD_RESALLOC, MOD_POL_RA_ADDRCOMPARATOR});

    rmtAllocator = getRINAModule<RMTModuleAllocator*>(this, 1, {MOD_RMTALLOC});

    // register slowdown signal for RA
    sigRMTSDReq = registerSignal(SIG_RMT_SlowdownRequest);

    setPolicyDisplayString(this);
    onPolicyInit();
}

void RMTMaxQBase::onPolicyInit()
{
}

void RMTMaxQBase::handleMessage(cMessage *msg)
{

}

bool RMTMaxQBase::run(RMTQueue* queue)
{
    return false;
}

void RMTMaxQBase::onQueueLengthDrop(RMTQueue* queue)
{
}

void RMTMaxQBase::notifySenderOfCongestion(const cPacket* pdu)
{
    emit(sigRMTSDReq, pdu);
}
