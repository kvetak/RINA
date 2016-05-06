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

#include "myListener.h"
#include "ModularMonitorSignals.h"

Define_Module(myListener);


void myListener::initialize() {
    getParentModule()->subscribe("PDUModularSignal", this);

}

void myListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    Enter_Method_Silent();
    //PDUInserted * o = dynamic_cast<PDUInserted*>(obj);
    //std::cout<< "Signal Received: Source:" << source->getFullPath() << ", MSG:" << o->eventName << std::endl;
    updateCount (source->getFullPath());
}

void myListener::updateCount (std::string nodeInfo)
{
    unsigned int c = nodes.count(nodeInfo);
    if (c == 0 )
    {
        //add new element into map
        nodes[nodeInfo] = 1;
    }
    else
    {
        // increment
        nodes[nodeInfo] += 1;
    }
}

void myListener::finish ()
{
    std::map<std::string, unsigned int>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        std::cout<<it->first<<": "<<it->second<<std::endl;
    }
    //nodes.clear();
}
