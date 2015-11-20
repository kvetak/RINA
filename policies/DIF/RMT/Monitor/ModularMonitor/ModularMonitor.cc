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

#include <ModularMonitor.h>
#include "ModularMonitorSignals.h"
#include "AEConstantMsgs.h"

namespace ModularMonitor {

Define_Module(ModularMonitor);

void ModularMonitor::onPolicyInit(){
     inOutModule  = check_and_cast<Int_MM_Out_Module*>  (getSubmodule("inputOutSubModule"));
     inDropModule = check_and_cast<Int_MM_Drop_Module*> (getSubmodule("inputDropSubModule"));
    outOutModule  = check_and_cast<Int_MM_Out_Module*>  (getSubmodule("outputOutSubModule"));
    outDropModule = check_and_cast<Int_MM_Drop_Module*> (getSubmodule("outputDropSubModule"));

    emitSignals = par("signal").boolValue();
    if(emitSignals) {
        signal = registerSignal("ModularSignal");
    }
}

void ModularMonitor::postPDUInsertion(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    switch(queue->getType()){
        case RMTQueue::INPUT:
            inOutModule->pduInsertered(queue, port);
            inDropModule->pduInsertered(queue, port);
            break;
        case RMTQueue::OUTPUT:
            outOutModule->pduInsertered(queue, port);
            outDropModule->pduInsertered(queue, port);
            break;
    }

    if(emitSignals) {
        const cPacket * pdu = queue->getLastPDU();
        if(inTime.find(pdu) == inTime.end()) {
            inTime[pdu] = simTime();
        }
    }
}

void ModularMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    switch(queue->getType()){
        case RMTQueue::INPUT:
            inOutModule->pduDropped(queue, pdu, port);
            inDropModule->pduDropped(queue, pdu, port);
            break;
        case RMTQueue::OUTPUT:
            outOutModule->pduDropped(queue, pdu, port);
            outDropModule->pduDropped(queue, pdu, port);
            break;
    }

    if(emitSignals) {
        if(const PDU * p = dynamic_cast<const PDU*>(pdu)) {
            emit(signal, new HopLossMsg(p->getConnId().getQoSId()));
        }
        inTime.erase(pdu);
    }
}

void ModularMonitor::prePDURelease(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    switch(queue->getType()){
        case RMTQueue::INPUT:
            inOutModule->pduReleased(queue, port);
            inDropModule->pduReleased(queue, port);
            break;
        case RMTQueue::OUTPUT:
            outOutModule->pduReleased(queue, port);
            outDropModule->pduReleased(queue, port);
            break;
    }

    if(emitSignals) {
        if(const PDU * pdu = dynamic_cast<const PDU*>(queue->getFirstPDU())) {
            if(inTime.find(pdu) != inTime.end()) {

                simtime_t hdel = simTime()-inTime[pdu];
                std::string qos = pdu->getConnId().getQoSId();
                inTime.erase(pdu);
                emit(signal, new HopDelayMsg(qos, hdel));
            }
        }
    }
}

void ModularMonitor::postQueueCreation(RMTQueue* queue){
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    switch(queue->getType()){
        case RMTQueue::INPUT:
            inOutModule->queueCreated(queue, port);
            inDropModule->queueCreated(queue, port);
            break;
        case RMTQueue::OUTPUT:
            outOutModule->queueCreated(queue, port);
            outDropModule->queueCreated(queue, port);
            break;
    }
}


double ModularMonitor::getInDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    return inDropModule->getDropProbability(queue, port);
}

double ModularMonitor::getOutDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    return outDropModule->getDropProbability(queue, port);
}


RMTQueue* ModularMonitor::getNextInput(RMTPort* port){
    return inOutModule->getnextQueue(port);
}

RMTQueue* ModularMonitor::getNextOutput(RMTPort* port){
    return outOutModule->getnextQueue(port);
}


simtime_t ModularMonitor::getInNextTime(RMTPort* port){
    return inOutModule->getnextTime(port);
}

simtime_t ModularMonitor::getOutNextTime(RMTPort* port){
    return outOutModule->getnextTime(port);
}


}
