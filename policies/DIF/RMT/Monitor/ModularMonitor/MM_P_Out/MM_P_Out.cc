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

#include "DIF/RMT/Monitor/ModularMonitor/MM_P_Out/MM_P_Out.h"

namespace MM_P_Out {

Define_Module(MM_P_Out);

void MM_P_Out::initialize() {
    defaultPriority = par("defPriority").longValue();
    if(defaultPriority < 0) { error("Error at P_Out. defPriority must be >=0!"); }


    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else {
        return;
    }
    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing P_Out Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing P_Out Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("priority")) { error("Error parsing P_Out Queue. Its Priority is missing!"); }
        int priority = atoi(queue->getAttribute("priority"));
        if (priority<=0) { error("Error parsing P_Out Queue. Queue Priority must be >0!"); }

        queueName2Priority[id] = priority;
    }
}

MM_P_Out::~MM_P_Out(){}

void MM_P_Out::finish() {}

void MM_P_Out::pduInsertered(RMTQueue * q, RMTPort * p) {}

void MM_P_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {}

void MM_P_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_P_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queueName2Priority.find(q->getName()) != queueName2Priority.end()) {
        queuePriority[q] = queueName2Priority[q->getName()];
    } else {
        queuePriority[q] = defaultPriority;
    }
    portQueues[p].insert(q);
}

RMTQueue * MM_P_Out::getnextQueue(RMTPort * p) {
    int sumPrior = 0;
    for(auto pQ : portQueues[p]){
        if(pQ->getLength() > 0) {
            sumPrior += queuePriority[pQ];
        }
    }

    if(sumPrior<=0) { return NULL; }

    int until = omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, sumPrior);
    sumPrior = 0;
    RMTQueue * q = NULL;
    for(auto pQ : portQueues[p]){
        if(pQ->getLength() > 0) {
            q = pQ;
            sumPrior += queuePriority[pQ];
            if(sumPrior > until) { break; }
        }
    }

    return q;
}

simtime_t  MM_P_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
