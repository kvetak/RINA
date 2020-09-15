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

#include "DIF/FA/FAIBase.h"

#include "Common/Flow.h"
#include "Common/RINASignals.h"

const simsignal_t FAIBase::allocateRequestSignal = registerSignal(SIG_FAI_AllocateRequest);
const simsignal_t FAIBase::deallocateRequestSignal = registerSignal(SIG_FAI_DeallocateRequest);
const simsignal_t FAIBase::deallocateResponseSignal = registerSignal(SIG_FAI_DeallocateResponse);
const simsignal_t FAIBase::allocateResponsePositiveSignal = registerSignal(SIG_FAI_AllocateResponsePositive);
const simsignal_t FAIBase::allocateResponseNegativeSignal = registerSignal(SIG_FAI_AllocateResponseNegative);
// Listened to by this IPCP's FANotifier
const simsignal_t FAIBase::createRequestSignal = registerSignal(SIG_FAI_CreateFlowRequest);
const simsignal_t FAIBase::deleteRequestSignal = registerSignal(SIG_FAI_DeleteFlowRequest);
const simsignal_t FAIBase::deleteResponseSignal = registerSignal(SIG_FAI_DeleteFlowResponse);
const simsignal_t FAIBase::createResponseNegativeSignal = registerSignal(SIG_FAI_CreateFlowResponseNegative);
const simsignal_t FAIBase::createResponsePositiveSignal = registerSignal(SIG_FAI_CreateFlowResponsePositive);

FAIBase::FAIBase() : flowObject(nullptr), degenerateDataTransfer(false)
{
}

FAIBase::~FAIBase() {}
