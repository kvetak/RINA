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

#include "DIF/RMT/Monitor/ModularMonitor/MM_PDQ_Drop/MM_PDQ_Drop.h"

#include "Common/Utils.h"

namespace MM_PDQ_Drop {

Define_Module(MM_PDQ_Drop);

Threshold::Threshold(int _limit, double _prob) {
    limit = _limit;
    prob = _prob;
}


QueueConfig::QueueConfig(){
    id ="";
    absThreshold = 0;
}

QueueConfig::QueueConfig(string _id, int _absThreshold){
    id =_id;
    absThreshold = _absThreshold;
}

void MM_PDQ_Drop::initialize() {

    defaultThreshold = par("defaultThreshold").longValue();
    if(defaultThreshold < 0) { error("Error at DL_Drop. defThreshold must be >= 0!"); }

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { return; }

    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing DQ_Drop Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing DQ_Drop Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("absThreshold")) { error("Error parsing DQ_Drop Queue. Its absThreshold is missing!"); }
        int absThreshold = atoi(queue->getAttribute("absThreshold"));
        if (absThreshold<0) { error("Error parsing DQ_Drop Queue. Queue absThreshold must be >=0!"); }

        QueueConfig q(id, absThreshold);

        cXMLElementList THs = queue->getChildrenByTagName("TH");

        for(auto TH : THs){
            if(!TH->getAttribute("threshold")) { error("Error parsing TH. threshold must be defined!"); }
            int threshold = atoi(TH->getAttribute("threshold"));
            if(threshold<0) { error("Error parsing PP. threshold must be >=0!"); }
            if(absThreshold<=threshold) { continue; }

            if(!TH->getAttribute("dropProb")) { error("Error parsing TH. dropProb must be defined!"); }
            double dropProb = atof(TH->getAttribute("dropProb"));
            if(dropProb<=0 || dropProb>=1) { error("Error parsing TH. dropProb must be in (0,1)!"); }

            q.thresholdList.push_back(Threshold(threshold, dropProb));
        }

        queuesConf[id] = q;
    }
}

MM_PDQ_Drop::~MM_PDQ_Drop(){
    portCount.clear();
}

void MM_PDQ_Drop::pduInsertered(RMTQueue * q, RMTPort * p) {
    portCount[p]++;
}

void MM_PDQ_Drop::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portCount[p]--;
}

void MM_PDQ_Drop::pduReleased(RMTQueue * q, RMTPort * p) {
    portCount[p]--;
}

void MM_PDQ_Drop::queueCreated(RMTQueue * q, RMTPort * p) {

    vector<string> qv = split(q->getName(), '_');

    if(qv.size() < 2) {
        error("Queue name must be of the form in/outQ_QoS[_*]");
    }
    string qConf = join(qv, 2, '_');

    if(queuesConf.find(qConf) != queuesConf.end()) {
        queueConf[q] = &queuesConf[qConf];
    } else {
        queueConf[q] = NULL;
    }

    portQueues[p].insert(q);
}

double MM_PDQ_Drop::getDropProbability(RMTQueue * q, RMTPort * p) {
    int count = portCount[p];
    QueueConfig * qc = queueConf[q];

    if(count >= qc->absThreshold) {
        return 1.0;
    }

    double prob = 0.0;
    int nearTH = 0;
    for(Threshold & th : qc->thresholdList) {
        if(count >= th.limit && nearTH < th.limit) {
            nearTH = th.limit;
            prob = th.prob;
        }
    }

    return prob;
}


void MM_PDQ_Drop::finish() {
/*
    cout << "MM_PDQ_Drop "<< this->getFullPath()  << endl;
    for(auto qc : queueConf) {
        cout << "\tQueue " << qc.second->id << endl;
        cout << "\t\tAbsolute threshold " << qc.second->absThreshold<<endl;
        for(Threshold & th : qc.second->thresholdList) {
            cout << "\t\t-Threshold " << th.limit << " :: "<< th.prob <<endl;
        }

    }
*/
}

}
