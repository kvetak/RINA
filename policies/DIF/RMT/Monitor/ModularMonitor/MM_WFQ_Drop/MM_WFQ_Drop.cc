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

#include "DIF/RMT/Monitor/ModularMonitor/MM_WFQ_Drop/MM_WFQ_Drop.h"

namespace MM_WFQ_Drop {

Define_Module(MM_WFQ_Drop);

void MM_WFQ_Drop::initialize() {

    defaultThreshold = par("defThreshold");
    if(defaultThreshold <= 0) { error("Error at DL_Drop. defThreshold must be >0!"); }

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else {
        return;
    }
    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing DL_Drop Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing DL_Drop Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("threshold")) { error("Error parsing DL_Drop Queue. Its Threshold is missing!"); }
        int threshold = atoi(queue->getAttribute("threshold"));
        if (threshold<=0) { error("Error parsing DL_Drop Queue. Queue Threshold must be >0!"); }
        queueName2Threshold[id] = threshold;
    }
}

MM_WFQ_Drop::~MM_WFQ_Drop(){
    queueCount.clear();
}

void MM_WFQ_Drop::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueCount[q]++;
}

void MM_WFQ_Drop::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueCount[q]--;
}

void MM_WFQ_Drop::pduReleased(RMTQueue * q, RMTPort * p) {
    queueCount[q]--;
}

void MM_WFQ_Drop::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queueName2Threshold.find(q->getName()) != queueName2Threshold.end()) {
        queueThreshold[q] = queueName2Threshold[q->getName()];
    } else {
        queueThreshold[q] = defaultThreshold;
    }
    queueCount[q] = 0;
}

double MM_WFQ_Drop::getDropProbability(RMTQueue * q, RMTPort * p) {
    return (queueThreshold[q] < queueCount[q])? 1.0 : 0.0;
}

}
