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

#include "DIF/RMT/Monitor/ModularMonitor/MM_maxDelayLimited_Out/MM_maxDelayLimited_Out.h"

namespace MM_maxDelayLimited_Out {

Define_Module(MM_maxDelayLimited_Out);

void MM_maxDelayLimited_Out::initialize() {
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
        double delay = atof(queue->getAttribute("delay"));
        if (delay<0) { error("Error parsing DL_Out Queue. Queue delay must be >=0!"); }

        double multip = 1.0;
        if (queue->getAttribute("multip")) {
            multip = atof(queue->getAttribute("multip"));
            if (multip<=0) { error("Error parsing DL_Out Queue. Queue multip must be >0!"); }
        }

        double burstTime = 0.0;
        unsigned int burstSize = 1500;
        if (queue->getAttribute("burstTime")) {
            burstTime = atof(queue->getAttribute("burstTime"));
            if (burstTime<=0) { error("Error parsing DL_Out Queue. Queue burstTime must be >0!"); }

            if (queue->getAttribute("burstSize")) {
                burstSize = atoi(queue->getAttribute("burstSize"));
                if (burstSize<=0) { error("Error parsing DL_Out Queue. Queue burstSize must be >0!"); }
            } else { error("Error parsing DL_Out Queue. Queue burstSize must be initialized!"); }
        }


        queueName2Delay[id] = delay;
        queueName2Multip[id] = multip;
        queueName2BurstTime[id] = burstTime;
        queueName2BurstSize[id] = burstSize;
    }
}

MM_maxDelayLimited_Out::~MM_maxDelayLimited_Out(){}

void MM_maxDelayLimited_Out::finish() {}

void MM_maxDelayLimited_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueInTime[q].push_back(simTime());
}

void MM_maxDelayLimited_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueInTime[q].pop_back();
}

void MM_maxDelayLimited_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_maxDelayLimited_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    portQueues[p].insert(q);
    if(queueName2Delay.find(q->getName()) != queueName2Delay.end()) {
        queueDelay[q] = queueName2Delay[q->getName()];
    } else {
        queueDelay[q] = defaultMaxDel;
    }

    queueBurstCount[q];
    if(queueName2BurstTime.find(q->getName()) != queueName2BurstTime.end() && queueName2BurstSize.find(q->getName()) != queueName2BurstSize.end() ) {
        queueBurstCount[q].set(queueName2BurstTime[q->getName()], queueName2BurstSize[q->getName()]);
    }

}

RMTQueue * MM_maxDelayLimited_Out::getnextQueue(RMTPort * p) {
    RMTQueue * ret = NULL;
    simtime_t min = SimTime::getMaxTime();
    simtime_t now = simTime();

    double tic;//, toc = 50;


    for(auto & q : portQueues[p]) {
        if(!queueInTime[q].empty()) {
            tic = queueBurstCount[q].tic(q->getFirstPDU()->getByteLength());
            if(tic < 1.0) {
                simtime_t temp = queueDelay[q] - now + queueInTime[q].front();
                if(temp < 0) { temp *= queueMultip[q]; }
                if(temp < min) {
                    ret = q;
                    min = temp;
                  //  toc = tic;
                }
            }
        }
    }

    if(ret != NULL) {
        queueInTime[ret].pop_front();
        queueBurstCount[ret].in(ret->getFirstPDU()->getByteLength());
    }
    return ret;
}

simtime_t  MM_maxDelayLimited_Out::getnextTime(RMTPort * p) {
    simtime_t time = SimTime::getMaxTime();
    for(auto & q : portQueues[p]) {
        if(!queueInTime[q].empty()) {
            simtime_t t = queueBurstCount[q].getTime(q->getFirstPDU()->getByteLength());
            if(t < time) { time = t; }
        }
    }
    if(time < SimTime::getMaxTime()) {
        return time;
    } else {
        return 0.0;
    }
}

}
