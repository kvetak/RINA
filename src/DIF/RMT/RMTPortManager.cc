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

#include "RMTPortManager.h"

Define_Module(RMTPortManager);

void RMTPortManager::initialize()
{

}

void RMTPortManager::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

RMTPortManager::RMTPortManager()
{

}

RMTPortManager::~RMTPortManager()
{

}


RMTPort* RMTPortManager::getPort(ConnectionId conId)
{
    if (ports.count(conId))
    {
        return ports[conId];
    }
    else
    {
        return NULL;
    }
}


void RMTPortManager::addPort(ConnectionId conId)
{
    if (ports.count(conId))
    {
        return;
    }

    ports[conId] = new RMTPort;

    cModule* rmt = getParentModule()->getSubmodule("rmt");
    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << "efcpIo_" << conId.getSrcCepId();
    const char* gateName = gateName_str.str().c_str();


    rmt->addGate(gateName, cGate::INOUT, false);
    cGate* rmtIn = rmt->gateHalf(gateName, cGate::INPUT);
    cGate* rmtOut = rmt->gateHalf(gateName, cGate::OUTPUT);

    rmtModule->addGate(gateName, cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName, cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName, cGate::OUTPUT);

    rmtModuleIn->connectTo(rmtIn);
    rmtOut->connectTo(rmtModuleOut);

    ports[conId]->setEfcpiGate(rmtOut);

    // RMT<->EFCP interconnection shall be done by the FAI

//    EV << "rmtModuleOut: is connected outside: " << rmtModuleOut->isConnectedOutside() << endl;
//    EV << "rmtModuleOut: is connected inside: " << rmtModuleOut->isConnectedInside() << endl;
//
//    EV << "rmtModuleIn: is connected outside: " << rmtModuleIn->isConnectedOutside() << endl;
//    EV << "rmtModuleIn: is connected inside: " << rmtModuleIn->isConnectedInside() << endl;

}

void RMTPortManager::removePort(ConnectionId conId)
{
    if (!ports.count(conId))
    {
        return;
    }

    cModule* rmt = getParentModule()->getSubmodule("rmt");
    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << "efcpIo_" << conId.getSrcCepId();
    const char* gateName = gateName_str.str().c_str();

    cGate* rmtOut = rmt->gateHalf(gateName, cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName, cGate::INPUT);

    rmtOut->disconnect();
    rmtModuleIn->disconnect();

    rmt->deleteGate(gateName);
    rmtModule->deleteGate(gateName);

    delete ports[conId];
    ports.erase(conId);
}

RMTPortManager::iterator RMTPortManager::begin(){
    return this->ports.begin();
}

RMTPortManager::iterator RMTPortManager::end(){
    return this->ports.end();
}
