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

#include "DIF/RMT/Monitor/ModularMonitor/MM_maxWP_Out/MM_maxWP_Out.h"
#include <limits.h>

namespace MM_maxWP_Out {

Define_Module(MM_maxWP_Out);

void MM_maxWP_Out::initialize() {
    defaultMaxWP = par("defWP").longValue();
    if(defaultMaxWP < 0) { error("Error at DL_Out. defWP must be >=0!"); }


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

        if (!queue->getAttribute("wp")) { error("Error parsing DL_Out Queue. Its wp is missing!"); }
        int wp = atoi(queue->getAttribute("wp"));
        if (wp<0) { error("Error parsing DL_Out Queue. Queue wp must be >=0!"); }

        double multip = 1.0;

        if (queue->getAttribute("multip")) {
            multip = atof(queue->getAttribute("multip"));
            if (multip<=0) { error("Error parsing DL_Out Queue. Queue multip must be >0!"); }
        }

        queueName2WP[id] = wp;
        queueName2Multip[id] = multip;
    }
}

MM_maxWP_Out::~MM_maxWP_Out(){}

void MM_maxWP_Out::finish() {}

void MM_maxWP_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueInS[q].push_back(portS[p]);

}

void MM_maxWP_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueInS[q].pop_back();
}

void MM_maxWP_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_maxWP_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    portQueues[p].insert(q);
    if(queueName2WP.find(q->getName()) != queueName2WP.end()) {
        queueWP[q] = queueName2WP[q->getName()];
    } else {
        queueWP[q] = defaultMaxWP;
    }
    if(queueName2Multip.find(q->getName()) != queueName2Multip.end()) {
        queueMultip[q] = queueName2Multip[q->getName()];
    } else {
        queueMultip[q] = 1.0;
    }
}

RMTQueue * MM_maxWP_Out::getnextQueue(RMTPort * p) {
    RMTQueue * ret = NULL;
    double min = DBL_MAX;
    int now = portS[p];

    for(auto & q : portQueues[p]) {
        if(!queueInS[q].empty()) {
            double temp = queueWP[q] - now + queueInS[q].front();
            if(temp <= 0) {
                temp *= queueMultip[q];
            }
            if(temp < min) {
                ret = q;
                min = temp;
            }
        }
    }

    if(ret != NULL) {
        queueInS[ret].pop_front();
        portS[p]++;
    }
    return ret;
}

simtime_t  MM_maxWP_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
