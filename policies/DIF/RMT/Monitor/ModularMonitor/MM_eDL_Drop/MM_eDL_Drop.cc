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

#include "DIF/RMT/Monitor/ModularMonitor/MM_eDL_Drop/MM_eDL_Drop.h"

namespace MM_eDL_Drop {

Define_Module(MM_eDL_Drop);

void MM_eDL_Drop::initialize() {

    defaultThreshold = par("defThreshold").longValue();
    if(defaultThreshold <= 0) { error("Error at DL_Drop. defThreshold must be >0!"); }

    defaultAbsThreshold = par("defAbsThreshold").longValue();
    if(defaultAbsThreshold <= 0) { error("Error at DL_Drop. defAbsThreshold must be >0!"); }

    defaultDropProb = par("defDropProb").doubleValue();
    if(defaultDropProb < 0.0 || defaultDropProb > 1.0) { error("Error at DL_Drop. defDropProb must be between [0,1]!"); }

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

        if (!queue->getAttribute("dropProb")) { error("Error parsing DL_Drop Queue. Its dropProb is missing!"); }
        double dropProb = atof(queue->getAttribute("dropProb"));
        if (dropProb<0 || dropProb > 1) { error("Error parsing DL_Drop Queue. Queue dropProb must be between [0,1]!"); }

        if (!queue->getAttribute("absThreshold")) { error("Error parsing DL_Drop Queue. Its absThreshold is missing!"); }
        int absThreshold = atoi(queue->getAttribute("absThreshold"));
        if (absThreshold<=0) { error("Error parsing DL_Drop Queue. Queue absThreshold must be >0!"); }

        queueName2Threshold[id] = threshold;
        queueName2DropProb[id] = dropProb;
        queueName2AbsThreshold[id] = absThreshold;
    }
}

MM_eDL_Drop::~MM_eDL_Drop(){
    portCount.clear();
}

void MM_eDL_Drop::pduInsertered(RMTQueue * q, RMTPort * p) {
    portCount[p]++;
}

void MM_eDL_Drop::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portCount[p]--;
}

void MM_eDL_Drop::pduReleased(RMTQueue * q, RMTPort * p) {
    portCount[p]--;
}

void MM_eDL_Drop::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queueName2Threshold.find(q->getName()) != queueName2Threshold.end()) {
        queueThreshold[q] = queueName2Threshold[q->getName()];
    } else {
        queueThreshold[q] = defaultThreshold;
    }

    if(queueName2DropProb.find(q->getName()) != queueName2DropProb.end()) {
        queueDropProb[q] = queueName2DropProb[q->getName()];
    } else {
        queueDropProb[q] = defaultDropProb;
    }

    if(queueName2AbsThreshold.find(q->getName()) != queueName2AbsThreshold.end()) {
        queueAbsThreshold[q] = queueName2AbsThreshold[q->getName()];
    } else {
        queueAbsThreshold[q] = defaultAbsThreshold;
    }

    portCount[p] = 0;
}

double MM_eDL_Drop::getDropProbability(RMTQueue * q, RMTPort * p) {
    int count = portCount[p];
    return (count > queueAbsThreshold[q])? 1.0 :
            (queueThreshold[q] < portCount[p])? queueDropProb[q] : 0.0;
}

}
