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

#include "DIF/RMT/Monitor/ModularMonitor/MM_WFQ_Out/MM_WFQ_Out.h"

namespace MM_WFQ_Out {

Define_Module(MM_WFQ_Out);


QConfig::QConfig() :
    rTkBit(0), sTkBit(0), maxTk(0), priority(0) {}

Qinfo::Qinfo() :
    hasTk(false), priority(0) {}

Qinfo::Qinfo(const bool & _ht, const int & _pr) :
    hasTk(_ht), priority(_pr) {}

bool Qinfo::compare(const Qinfo & o) {
    if(hasTk) {
        if(o.hasTk) {
            return priority < o.priority;
        } else {
            return false;
        }
    } else {
        if(o.hasTk) {
            return true;
        } else {
            return priority < o.priority;
        }
    }
}

QData::QData() :
    tk(0), w(0), c(QConfig()) {}

void QData::addTk(const int & s) {
    tk += s*c.rTkBit;
    if(tk > c.maxTk) { tk = c.maxTk; }
}
void QData::remTk(const int & s) {
    tk -= s*c.sTkBit;
    if(tk < 0) { tk = 0; }
}

Qinfo QData::getInfo(const int & nextS) {
    return Qinfo(tk >= nextS * c.sTkBit, c.priority);
}


void MM_WFQ_Out::initialize() {
    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { return; }

    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing WFQ_OUT Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing WFQ_OUT Queue. Queue ID cannot be empty!"); }

        QConfig c;

        if (!queue->getAttribute("priority")) { error("Error parsing WFQ_OUT Queue. Its Priority is missing!"); }
        c.priority = atoi(queue->getAttribute("priority"));
        if (c.priority<0) { error("Error parsing WFQ_OUT Queue. Queue Priority must be >=0!"); }

        if (!queue->getAttribute("rTkBit")) { error("Error parsing WFQ_OUT Queue. Its Received tokens per byte is missing!"); }
        c.rTkBit = atoi(queue->getAttribute("rTkBit"));
        if (c.rTkBit<=0) { error("Error parsing WFQ_OUT Queue. Queue Received tokens per byte must be >=0!"); }

        if (!queue->getAttribute("sTkBit")) { error("Error parsing WFQ_OUT Queue. Its Required tokens per byte is missing!"); }
        c.sTkBit = atoi(queue->getAttribute("sTkBit"));
        if (c.sTkBit<0) { error("Error parsing WFQ_OUT Queue. Queue Required tokens per byte must be >=0!"); }

        if (!queue->getAttribute("maxTk")) { error("Error parsing WFQ_OUT Queue. Its Max Tokens is missing!"); }
        c.maxTk = atoi(queue->getAttribute("maxTk"));
        if (c.maxTk<=0) { error("Error parsing WFQ_OUT Queue. Queue Max Tokens must be >=0!"); }

        queueName2Config[id] = c;
    }
}

MM_WFQ_Out::~MM_WFQ_Out(){}

void MM_WFQ_Out::finish() {

}

void MM_WFQ_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueData[q].w++;
}

void MM_WFQ_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueData[q].w--;
}

void MM_WFQ_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_WFQ_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    QData qd;
    qd.c = queueName2Config[q->getName()];
    queueData[q] = qd;
    portQueues[p].push_back(q);
}

RMTQueue * MM_WFQ_Out::getnextQueue(RMTPort * p) {
    Qinfo ti;
    RMTQueue * retQ = NULL;

    for(auto & q : portQueues[p]){
        QData * qd = &queueData[q];

        if(qd->w > 0) {
            int nextS = q->getFirstPDU()->getByteLength();
            Qinfo i = qd->getInfo(nextS);
            if(ti.compare(i)) {
                ti = i;
                retQ = q;
            }
        }
    }

    if(retQ == NULL) {return NULL; }

    int nextS = retQ->getFirstPDU()->getByteLength();
    queueData[retQ].w--;
    queueData[retQ].remTk(nextS);
    for(auto & q : portQueues[p]){
        queueData[q].addTk(nextS);
    }

    return retQ;
}

simtime_t  MM_WFQ_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
