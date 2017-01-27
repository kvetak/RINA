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

#include "DIF/RMT/Monitor/ModularMonitor/MM_maxDelay_Out/MM_maxDelay_Out.h"

namespace MM_maxDelay_Out {

Define_Module(MM_maxDelay_Out);

void MM_maxDelay_Out::initialize() {
    defaultMaxDel = par("defDelay").longValue();
    if(defaultMaxDel < 0) { error("Error at DL_Out. defDelay must be >=0!"); }


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

        if (!queue->getAttribute("delay")) { error("Error parsing DL_Out Queue. Its delay is missing!"); }
        double delay = atof(queue->getAttribute("delay"))/1000.0;
        if (delay<0) { error("Error parsing DL_Out Queue. Queue delay must be >=0!"); }

        double multip = 1.0;

        if (queue->getAttribute("multip")) {
            multip = atof(queue->getAttribute("multip"));
            if (multip<=0) { error("Error parsing DL_Out Queue. Queue multip must be >0!"); }
        }

        queueName2Delay[id] = delay;
        queueName2Multip[id] = multip;
    }
}

MM_maxDelay_Out::~MM_maxDelay_Out(){}

void MM_maxDelay_Out::finish() {}

void MM_maxDelay_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueInTime[q].push_back(simTime());
}

void MM_maxDelay_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueInTime[q].pop_back();
}

void MM_maxDelay_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_maxDelay_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    portQueues[p].insert(q);
    if(queueName2Delay.find(q->getName()) != queueName2Delay.end()) {
        queueDelay[q] = queueName2Delay[q->getName()];
    } else {
        queueDelay[q] = defaultMaxDel;
    }
    if(queueName2Multip.find(q->getName()) != queueName2Multip.end()) {
        queueMultip[q] = queueName2Multip[q->getName()];
    } else {
        queueMultip[q] = 1.0;
    }
}

RMTQueue * MM_maxDelay_Out::getnextQueue(RMTPort * p) {
    RMTQueue * ret = NULL;
    simtime_t min = SimTime::getMaxTime();
    simtime_t now = simTime();

    for(auto & q : portQueues[p]) {
        if(!queueInTime[q].empty()) {
            simtime_t temp = queueDelay[q] - now + queueInTime[q].front();
            if(temp < 0) {
              //  std::cout << "From "<< temp;
                temp *= queueMultip[q];
              //  std::cout << " -> To "<< temp<< " --- Multiplier :: "<<queueMultip[q] <<endl;
            }
            if(temp < min) {
                ret = q;
                min = temp;
            }
        }
    }

    if(ret != NULL) {
        queueInTime[ret].pop_front();
    }
    return ret;
}

simtime_t  MM_maxDelay_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
