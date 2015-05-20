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

#include <RMTListeners.h>

RMTListeners::RMTListeners(RMTBase* rmt) : rmt(rmt)
{
}

RMTListeners::~RMTListeners()
{
    rmt = NULL;
}

void LisRMTQueuePDUPreRcvd::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->preQueueArrival(obj);
}

void LisRMTQueuePDUPostRcvd::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->postQueueArrival(obj);
}

void LisRMTQueuePDUPreSend::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->preQueueDeparture(obj);
}

void LisRMTQueuePDUSent::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->postQueueDeparture(obj);
}

void LisRMTPortReadyToServe::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->writeToPort(obj);
}


void LisRMTPortReadyForRead::receiveSignal(cComponent* src, simsignal_t id, cObject* obj)
{
    rmt->readFromPort(obj);
}
