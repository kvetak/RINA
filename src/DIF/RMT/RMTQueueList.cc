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

#include "RMTQueueList.h"

Define_Module(RMTQueueList);

void RMTQueueList::initialize()
{

}

void RMTQueueList::handleMessage(cMessage *msg)
{

}

RMTQueueList::RMTQueueList()
{
//    EV << "creating queue list" << endl;

//    this->addQueue(3);
//    this->addQueue(4);
//    this->addQueue(5);
//    this->addQueue(6);
//    this->addQueue(7);
//    this->removeQueue(6);
}

RMTQueueList::~RMTQueueList()
{
//    EV << "destroying queue list" << endl;

    for(RMTQueues::iterator it = queueList.begin(); it != queueList.end(); ++it)
    {
        delete it->second;
    }

}

RMTQueue* RMTQueueList::getQueue(int portId)
{
    if (queueList.count(portId))
    {
        return queueList[portId];
    }
    else
    {
        return NULL;
    }
}


void RMTQueueList::addQueue(int portId)
{
    EV << "adding port " << portId << endl;

    queueList[portId] = new RMTQueue;

    // TODO: fix this mess and use gate vectors
//    std::ostringstream newgate;
//    newgate << "rmtPort" << portId;
//
//    std::ostringstream newgate2;
//    newgate2 << "southPort" << portId;
//
//    cModule* rmtModule = this->getParentModule();
//    cModule* southBorder = rmtModule->getParentModule();
//
//    rmtModule->addGate(newgate.str().c_str(), cGate::INOUT, false);
//    southBorder->addGate(newgate2.str().c_str(), cGate::INOUT, false);
//
//    cGate* rmtIn = rmtModule->gateHalf(newgate.str().c_str(), cGate::INPUT);
//    cGate* outerIn = southBorder->gateHalf(newgate2.str().c_str(), cGate::INPUT);
//
//    cGate* rmtOut = rmtModule->gateHalf(newgate.str().c_str(), cGate::OUTPUT);
//    cGate* outerOut = southBorder->gateHalf(newgate2.str().c_str(), cGate::OUTPUT);
//
//    outerIn->connectTo(rmtIn);
//    rmtOut->connectTo(outerOut);

}

void RMTQueueList::removeQueue(int portId)
{
    //EV << "destroying queue " << portId << endl;

    delete queueList[portId];
    queueList.erase(portId);

    // delete gates
//    if (portId == 5)
//    {
//        outerIn->disconnect();
//        outerOut->disconnect();
//        rmtIn->disconnect();
//        rmtOut->disconnect();
//        rmtModule->deleteGate(newgate.str().c_str());
//        southBorder->deleteGate(newgate.str().c_str());
//    }

}
