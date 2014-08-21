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

#include "RMTFlowManager.h"

Define_Module(RMTFlowManager);

void RMTFlowManager::initialize()
{
    ribFlow = new RMTFlow;
    // testing
    this->addFlow(1);
}

void RMTFlowManager::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

RMTFlowManager::RMTFlowManager()
{

}

RMTFlowManager::~RMTFlowManager()
{

}

RMTFlow* RMTFlowManager::getRibFlow()
{
    return ribFlow;
}


RMTFlow* RMTFlowManager::getFlow(int portId)
{
    if (flows.count(portId))
    {
        return flows[portId];
    }
    else
    {
        return NULL;
    }
}


void RMTFlowManager::addFlow(int portId)
{
    if (flows.count(portId))
    {
        return;
    }

    flows[portId] = new RMTFlow;

//    // either leave the potentially inconvenient module dependency here
//    // or move the gate creation to RMT
//    cModule *rmt = getParentModule()->getSubmodule("rmt");
//
//    // expand the gate vector
//    int rmtGateSize = rmt->gateSize("efcpIo");
//    rmt->setGateSize("efcpIo", ++rmtGateSize);
//
//    // bind the new subgates to the flow
//    cGate* newgate_in = rmt->gate("efcpIo$i", rmtGateSize-1);
//    cGate* newgate_out = rmt->gate("efcpIo$o", rmtGateSize-1);
//
//    flows[portId]->setEfcpiId(newgate_out->getId());
//
//    // compound rmtModule
//    cModule *rmtModule = getParentModule();
//
//    int compGateSize = rmtModule->gateSize("efcpIo");
//    rmtModule->setGateSize("efcpIo", ++compGateSize);
//
//    cGate* newgate2_in = rmtModule->gate("efcpIo$i", compGateSize-1);
//    cGate* newgate2_out = rmtModule->gate("efcpIo$o", compGateSize-1);

//    newgate_in->connectTo(newgate2_in);
//    newgate_out->connectTo(newgate2_out);


}

void RMTFlowManager::removeFlow(int portId)
{
    if (flows.count(portId))
    {
        delete flows[portId];
        flows.erase(portId);
    }

    // TODO: removal of gate from a vector requires shifting the indices
    // of the other gates; find out if this causes any problems

    //int gateSize = getParentModule()->gateSize("efcpIo");
    //getParentModule()->setGateSize("efcpIo", gateSize-1);

}

RMTFlowManager::iterator RMTFlowManager::begin(){
    return this->flows.begin();
}

RMTFlowManager::iterator RMTFlowManager::end(){
    return this->flows.end();
}
