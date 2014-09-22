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


RMTPort* RMTPortManager::getPort(int portId)
{
    if (ports.count(portId))
    {
        return ports[portId];
    }
    else
    {
        return NULL;
    }
}


void RMTPortManager::addPort(int portId)
{
    if (ports.count(portId))
    {
        return;
    }

    ports[portId] = new RMTPort;
}

void RMTPortManager::removePort(int portId)
{
    if (!ports.count(portId))
    {
        return;
    }


    delete ports[portId];
    ports.erase(portId);
}

RMTPortManager::iterator RMTPortManager::begin(){
    return this->ports.begin();
}

RMTPortManager::iterator RMTPortManager::end(){
    return this->ports.end();
}
