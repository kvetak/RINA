//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <RAListeners.h>

#include "RMTQueue.h"

RAListeners::RAListeners(RABase* nra) : ra(nra)
{
}

RAListeners::~RAListeners()
{
    ra = NULL;
}

void LisRACreFlow::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->createNM1FlowWithoutAllocate(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisRAAllocResPos::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->postNFlowAllocation(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }

}

void LisRACreAllocResPos::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->postNFlowAllocation(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisRACreResPosi::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->postNM1FlowAllocation(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisEFCPStopSending::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->blockNM1Port(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisEFCPStartSending::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    Flow* flow = dynamic_cast<Flow*>(obj);
    if (flow)
    {
        ra->unblockNM1Port(flow);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisRMTSlowdownRequest::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    cPacket* pdu = dynamic_cast<cPacket*>(obj);
    if (pdu)
    {
        ra->signalizeSlowdownRequestToRIBd(pdu);
    }
    else
    {
        EV << "RAListener received unknown object!" << endl;
    }
}

void LisRIBCongNotif::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
//    cPacket* pdu = dynamic_cast<cPacket*>(obj);
//    if (pdu)
//    {
        ra->signalizeSlowdownRequestToEFCP(obj);
//    }
//    else
//    {
//        EV << "RAListener received unknown object!" << endl;
//    }
}
