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

#include "DIF/RMT/Monitor/ModularMonitor/MM_eDL_Out/MM_eDL_Out.h"

namespace MM_eDL_Out {

Define_Module(MM_eDL_Out);

void MM_eDL_Out::initialize() {
    defaultPriority = par("defPriority").longValue();
    if(defaultPriority < 0) { error("Error at eDL_Out. defPriority must be >=0!"); }

    maxPriority = defaultPriority;

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else {
        return;
    }
    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing eDL_Out Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing eDL_Out Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("priority")) { error("Error parsing eDL_Out Queue. Its Priority is missing!"); }
        int priority = atoi(queue->getAttribute("priority"));
        if (priority<0) { error("Error parsing eDL_Out Queue. Queue Priority must be >=0!"); }

        queueName2Priority[id] = priority;

        if(maxPriority<priority) { maxPriority = priority ; }
    }



    if (par("data2").xmlValue() != NULL && par("data2").xmlValue()->hasChildren()){
        Xml = par("data2").xmlValue();
    } else {
        return;
    }
    cXMLElementList priorities = Xml->getChildrenByTagName("priority");
    for(auto priority : priorities){
        if (!priority->getAttribute("val")) { error("Error parsing eDL_Out Priority. Its val is missing!"); }
        int id = atoi(priority->getAttribute("val"));
        if (id<=0) { error("Error parsing eDL_Out Priority. Priority val cannot be <=0!"); }

        if (!priority->getAttribute("prob")) { error("Error parsing eDL_Out Priority. Its prob is missing!"); }
        double prob = atof(priority->getAttribute("prob"));
        if (prob<0 || prob >1) { error("Error parsing eDL_Out Priority. Priority prob must be between 0 and 1!"); }

        prioritySkip[maxPriority-id] = prob;
    }
}

MM_eDL_Out::~MM_eDL_Out(){}

void MM_eDL_Out::finish() {}

void MM_eDL_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    portQueues[p][queuePriority[q]].push_back(q);
}

void MM_eDL_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portQueues[p][queuePriority[q]].pop_back();
}

void MM_eDL_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_eDL_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queueName2Priority.find(q->getName()) != queueName2Priority.end()) {
        queuePriority[q] = maxPriority-queueName2Priority[q->getName()];
    } else {
        queuePriority[q] = maxPriority-defaultPriority;
    }
}

RMTQueue * MM_eDL_Out::getnextQueue(RMTPort * p) {
    int selP = -1;

    for(auto &pQ : portQueues[p]) {
        if(!pQ.second.empty()) {
            selP = pQ.first;

       //     std::cout << selP << " => " << prioritySkip[selP] << endl;
            if(omnetpp::uniform(omnetpp::getEnvir()->getRNG(0), 0.0, 1.0) >= prioritySkip[selP]) { break; }
        }
    }

    if(selP < 0) { return NULL; }

    RMTQueue * q = portQueues[p][selP].front();
    portQueues[p][selP].pop_front();
    return q;
}

simtime_t  MM_eDL_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
