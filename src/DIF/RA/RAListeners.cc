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

#include "DIF/RA/RAListeners.h"


RAListeners::RAListeners(RABase* nra) : ra(nra)
{
}

RAListeners::~RAListeners()
{
    ra = nullptr;
}

void LisRACreFlow::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->createNM1FlowWithoutAllocate(flow);
    }
}

void LisRAAllocResPos::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow && !flow->isDdtFlag())
    {
        ra->postNFlowAllocation(flow);
    }
}

void LisRACreAllocResPos::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow && !flow->isDdtFlag())
    {
        ra->postNFlowAllocation(flow);
    }
}

void LisRACreResPosi::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    const APN& dstApn = flow->getDstApni().getApn();
    const std::string& qosId = flow->getConId().getQoSId();

    auto item = ra->getFlowTable()->findFlowByDstApni(dstApn.getName(), qosId);
    if (item != nullptr)
    {
        ra->postNM1FlowAllocation(item);
    }
}

void LisRADelFlow::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    const APN& dstApn = flow->getDstApni().getApn();
    const std::string& qosId = flow->getConId().getQoSId();

    auto item = ra->getFlowTable()->findFlowByDstApni(dstApn.getName(), qosId);
    if (item != nullptr)
    {
        ra->removeNM1FlowBindings(item);
    }
}

void LisEFCPStopSending::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    auto item = ra->getFlowTable()->lookup(flow);

    if (item)
    {
        ra->blockNM1PortOutput(item);
    }
}

void LisEFCPStartSending::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    auto item = ra->getFlowTable()->lookup(flow);

    if (item)
    {
        ra->unblockNM1PortOutput(item);
    }
}

void LisRMTSlowdownRequest::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    cPacket* pdu = dynamic_cast<cPacket*>(obj);
    if (pdu)
    {
        ra->signalizeSlowdownRequestToRIBd(pdu);
    }
}

void LisRIBCongNotif::receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail)
{
    ra->signalizeSlowdownRequestToEFCP(obj);
}

