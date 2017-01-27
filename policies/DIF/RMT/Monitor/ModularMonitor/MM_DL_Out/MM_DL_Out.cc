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

#include "DIF/RMT/Monitor/ModularMonitor/MM_DL_Out/MM_DL_Out.h"

namespace MM_DL_Out {

Define_Module(MM_DL_Out);

void MM_DL_Out::initialize() {
    defaultPriority = par("defPriority").longValue();
    if(defaultPriority < 0) { error("Error at DL_Out. defPriority must be >=0!"); }

    maxPriority = defaultPriority;

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else {
        return;
    }
    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing DL_Out Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing DL_Out Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("priority")) { error("Error parsing DL_Out Queue. Its Priority is missing!"); }
        int priority = atoi(queue->getAttribute("priority"));
        if (priority<0) { error("Error parsing DL_Out Queue. Queue Priority must be >=0!"); }

        queueName2Priority[id] = priority;

        if(maxPriority<priority) { maxPriority = priority ; }
    }
}

MM_DL_Out::~MM_DL_Out(){}

void MM_DL_Out::finish() {}

void MM_DL_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    portQueues[p][queuePriority[q]].push_back(q);
}

void MM_DL_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portQueues[p][queuePriority[q]].pop_back();
}

void MM_DL_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_DL_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queueName2Priority.find(q->getName()) != queueName2Priority.end()) {
        queuePriority[q] = maxPriority-queueName2Priority[q->getName()];
    } else {
        queuePriority[q] = maxPriority-defaultPriority;
    }
}

RMTQueue * MM_DL_Out::getnextQueue(RMTPort * p) {
    for(auto & pQ : portQueues[p]){
        while(!pQ.second.empty()) {
            RMTQueue * q = pQ.second.front();
            pQ.second.pop_front();
            return q;
        }
    }
    return NULL;
}

simtime_t  MM_DL_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
