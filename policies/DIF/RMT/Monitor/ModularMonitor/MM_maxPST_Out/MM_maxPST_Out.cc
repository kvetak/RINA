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

#include "DIF/RMT/Monitor/ModularMonitor/MM_maxPST_Out/MM_maxPST_Out.h"
#include "Common/Utils.h"

namespace MM_maxPST_Out {

Define_Module(MM_maxPST_Out);

void MM_maxPST_Out::initialize() {

    maxTH = par("maxTH").longValue();
    margin = par("margin").longValue();

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else {
        error("Error data not initialized!");
    }

    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing id missing!"); }
        if (!queue->getAttribute("th")) { error("Error parsing th missing!"); }
        if (!queue->getAttribute("p1")) { error("Error parsing p1 missing!"); }
        if (!queue->getAttribute("p2")) { error("Error parsing p2 missing!"); }

        string id = queue->getAttribute("id");
        int th = atoi(queue->getAttribute("th"));
        int p1 = atoi(queue->getAttribute("p1"));
        int p2 = atoi(queue->getAttribute("p2"));

        if(th < 0) { th = 0; }
        if(p1 < 0) { p1 = 0; }
        //Vesely: if(p2 < p2) -> if(p2 < p1)
        if(p2 < p1) { p2 = p1; }


        qName2Threshold[id] = th;
        qName2PrePrio[id] = p1;
        qName2PostPrio[id] = p2;
    }
}

MM_maxPST_Out::~MM_maxPST_Out(){}

void MM_maxPST_Out::finish() {}

void MM_maxPST_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueInTime[q].push_back(portTime[p]);
}

void MM_maxPST_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueInTime[q].pop_back();
}

void MM_maxPST_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_maxPST_Out::queueCreated(RMTQueue * q, RMTPort * p) {

    portQueues[p].insert(q);

    vector<string> qv = split(q->getName(), '_');

    int th = maxTH;
    if(qv.size() == 2 && qv[1] == "M") {
        if(qName2Threshold.find(qv[1]) != qName2Threshold.end()) {
            th = qName2Threshold[qv[1]];
        }
    } else  if(qv.size() == 3) {
        int h = stoi(qv[2].c_str());
        if(h <= 0) { h = 1; }
        if(qName2Threshold.find(qv[1]) != qName2Threshold.end()) {
            th = qName2Threshold[qv[1]];
        }
        th /= h;
    } else {
        cout  << "Queue : "<< q->getName() << endl;
        error("Queue name must be \"M\" or of the form \"in/outQ_QoS_distance\"");
    }

    th -= margin;
    if(th < 0) { th = 0; }

    qThreshold[q] = th;

    qPrePrio[q] = qName2PrePrio[qv[1]];
    qPostPrio[q] = qName2PostPrio[qv[1]];

    cout << "queue : " << q->getName() << " | Threshold " << th <<endl ;
}

RMTQueue * MM_maxPST_Out::getnextQueue(RMTPort * p) {
    RMTQueue * ret = NULL;
    long cT = portTime[p];

    double max = -1;
    int currP = -1;

//cout<<"Now " << cT << endl;
    for(auto & q : portQueues[p]) {
        if(!queueInTime[q].empty()) {
            int pst = cT - queueInTime[q].front();
            int th = qThreshold[q];
            int qP = pst < th ?  qPrePrio[q] : qPostPrio[q];

//if(!strcmp(q->getName(), "outQ_BE_3")) {
//            cout << qPrePrio[q]  << " " << qPostPrio[q]<<endl;
//cout<<q->getName() << " Prior " << qP << " pst " << pst << " th :" << th << endl;
//}
            if(qP > currP) {
                currP = qP;
                max = pst;
                if(th >0) { max /= th; }
                ret = q;
            } else if(qP == currP) {
                double temp = pst;
                if(th >0) { temp /= th; }

                if(temp > max) {
                    max = temp;
                    ret = q;
                }
            }
        }
    }

//cout << " result >>  " << ret->getName()  << " Prior " << currP << " maxDif " << max << endl;

    if(ret != NULL) {
        queueInTime[ret].pop_front();
        portTime[p]++;
    }
    return ret;
}

simtime_t  MM_maxPST_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
