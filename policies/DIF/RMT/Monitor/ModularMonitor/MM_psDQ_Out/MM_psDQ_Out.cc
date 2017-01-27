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

#include "DIF/RMT/Monitor/ModularMonitor/MM_psDQ_Out/MM_psDQ_Out.h"

namespace MM_psDQ_Out {

Define_Module(MM_psDQ_Out);

UrgProb::UrgProb(double _prob, int _urg) {
    prob = _prob;
    urg = _urg;
}

DegradList::DegradList(double _s) {
    start = _s;
}

QueueConfig::QueueConfig(){
    id ="";
    defPriority = 0;
    rate = 0;
}

QueueConfig::QueueConfig(string _id, int _defPriority){
    id =_id;
    defPriority = _defPriority;
    rate = 0;
}

QueueData::QueueData(){
    count = 0;
    lastUrgency = -1;
}


void MM_psDQ_Out::initialize() {
    defaultPriority = par("defPriority").longValue();
    if(defaultPriority < 0) { error("Error at eDL_Out. defPriority must be >=0!"); }

    int rateUnit = par("rateUnit").longValue();
    if(defaultPriority < 0) { error("Error at eDL_Out. defPriority must be >=0!"); }

    maxPriority = defaultPriority;

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { return; }

    cXMLElementList queues = Xml->getChildrenByTagName("queue");
    for(auto queue : queues){
        if (!queue->getAttribute("id")) { error("Error parsing DQ_Out Queue. Its ID is missing!"); }
        std::string id = queue->getAttribute("id");
        if (id=="") { error("Error parsing DQ_Out Queue. Queue ID cannot be empty!"); }

        if (!queue->getAttribute("defPriority")) { error("Error parsing DQ_Out Queue. Its default Priority is missing!"); }
        int defPriority = atoi(queue->getAttribute("defPriority"));
        if (defPriority<0) { error("Error parsing DQ_Out Queue. Queue default Priority must be >=0!"); }
        if(maxPriority<defPriority) { maxPriority = defPriority ; }

        QueueConfig q(id, defPriority);

        if(queue->getAttribute("rate")) {
            double rate = atof(queue->getAttribute("rate"));
            if(rate <= 0) { error("Error parsing DQ_Out Queue. Queue Rate cannot be <= 0"); }
            rate *= rateUnit;

            q.rate = rate;
        }

        cXMLElementList degradLists = queue->getChildrenByTagName("degradList");
        for(auto degrad : degradLists){
            if (!degrad->getAttribute("s")) { error("Error parsing degradList. Its t is missing!"); }
            int s = atoi(degrad->getAttribute("s"));
            if (s<0) { error("Error parsing degradList. t cannot be <0!"); }

            DegradList dl(s);
            double sumProb = 0;
            cXMLElementList PPs = degrad->getChildrenByTagName("PP");

            if(PPs.size() <= 0) { error("Error parsing degradList. At least one PP must be defined!"); }
            for(auto PP : PPs){
                if(!PP->getAttribute("priority")) { error("Error parsing PP. priority must be defined!"); }
                int priority = atoi(PP->getAttribute("priority"));
                if(priority<0) { error("Error parsing PP. priority must be >=0!"); }
                if(maxPriority<priority) { maxPriority = priority ; }

                if(!PP->getAttribute("probability")) { error("Error parsing PP. probability must be defined!"); }
                double probability = atof(PP->getAttribute("probability"));
                if(probability<=0 || probability>1) { error("Error parsing PP. probability must be in (0,1]!"); }

                sumProb += probability;

                dl.urgList.push_back( UrgProb(sumProb, priority) );
            }

            if(sumProb > 1) { error("Error parsing degradList. probability of PPs cannot surpass 1!"); }

            q.degradLists.push_back(dl);
        }

        queuesConf[id] = q;
    }
}

MM_psDQ_Out::~MM_psDQ_Out(){}

void MM_psDQ_Out::finish() {
    /*
cout << "MM_psDQ_Out "<< endl;
    for(auto pq : portQueues) {

        cout << "\tPort: "<<pq.first->getFullPath()<< endl;
        for(RMTQueue *q : pq.second) {
            QueueData * qd  = &queueData[q];
            cout << "\t\tQueue: "<< q->getName() << endl;
            for(auto uc : qd->countUrgstats) {
                cout << "\t\t\tUrgency: "<< uc.first << " (" << uc.second <<")" << endl;
            }

        }
    }
*/
}

void MM_psDQ_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    QueueData * qd  = &queueData[q];
    QueueConfig * qc = queueConf[q];
    simtime_t t = simTime();

    //Push insert pdu
    qd->count++;
    int pC = ++portCount[p];

    if (qc->rate > 0.0) {
        while(qd->cOutTimes.front() <= t ) { qd->cOutTimes.pop_front(); }
        if(!qd->cOutTimes.empty()) { t = qd->cOutTimes.front(); }

        qd->cOutTimes.push_back(t + exponential(q->getLastPDU()->getBitLength()/qc->rate));
    }

    if(!qc) {
        //if queue not configured, urgency = default
        qd->lastUrgency = maxPriority-defaultPriority;
    } else {
        //Get degradation list for current state
        DegradList * dl = NULL;
        for(DegradList & pdl : qc->degradLists) {
            if(pdl.start > pC) {
                if(dl == NULL) { dl = &pdl; }
                else if( dl->start < pdl.start) { dl = &pdl; }
            }
        }

        //Get urgency based on degradation list
        if(dl == NULL) {
            qd->lastUrgency = maxPriority-qc->defPriority;
        } else {
            int cPrio = qc->defPriority;
            double r = omnetpp::uniform(omnetpp::getEnvir()->getRNG(0), 0.0,1.0);

            for(UrgProb & ul : dl->urgList) {
                if(ul.prob < r) { cPrio = ul.urg; }
                else { continue; }
            }

            qd->lastUrgency = maxPriority-cPrio;
        }
    }

    //store queue urgency
    qd->countUrg[qd->lastUrgency]++;
    qd->countUrgstats[qd->lastUrgency]++;
}

void MM_psDQ_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    QueueData * qd  = &queueData[q];
    portCount[p]--;

    if(qd->count > 0) {
        qd->count--;
        if(!qd->cOutTimes.empty()) { qd->cOutTimes.pop_back(); }
    } else { error("PDU dropped from empty queue!??"); }

    if(qd->lastUrgency >=0) {
        qd->countUrg[qd->lastUrgency]--;
        qd->countUrgstats[qd->lastUrgency]--;
        qd->lastUrgency = -1;
    } else { error("Multiple PDUs dropped at same time!??"); }
}

void MM_psDQ_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_psDQ_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    if(queuesConf.find(q->getName()) != queuesConf.end()) {
        queueConf[q] = &queuesConf[q->getName()];
    } else {
        queueConf[q] = NULL;
    }
    queueData[q];

    portQueues[p].insert(q);
}

RMTQueue * MM_psDQ_Out::getnextQueue(RMTPort * p) {
    int mpriority = -1;
    bool shaped = false;
    simtime_t minT, now=simTime();
    RMTQueue * ret = NULL;

    //select next queue : min priority (saved inverse), min inTime
    for(RMTQueue *q : portQueues[p]) {
        QueueData * qd  = &queueData[q];
        if(qd->count <= 0) { continue; }

        int qP = maxPriority;
        for(auto & qpc : qd->countUrg) {
            if(qpc.second > 0 && qpc.first < qP) { qP = qpc.first; }
        }

        bool qShaped = ((int)qd->cOutTimes.size() < qd->count)
                        || (qd->cOutTimes.front() <= now);

        if(qShaped) {
            if(!shaped) {
                shaped = true;
                mpriority = qP;
                minT = qd->cOutTimes.front();
                ret = q;
            } else if(mpriority < 0 || mpriority > qP) {
                mpriority = qP;
                minT = qd->cOutTimes.front();
                ret = q;
            } else if(mpriority == qP && minT > qd->cOutTimes.front()) {
                minT = qd->cOutTimes.front();
                ret = q;
            }
        } else if(!shaped) {
            if(mpriority < 0 || mpriority > qP) {
                mpriority = qP;
                minT = qd->cOutTimes.front();
                ret = q;
            } else if(mpriority == qP && minT > qd->cOutTimes.front()) {
                minT = qd->cOutTimes.front();
                ret = q;
            }
        }
    }

    if(ret==NULL) { return NULL; }

    QueueData * qd  = &queueData[ret];
    qd->count--;
    qd->countUrg[mpriority]--;
    portCount[p]--;


    return ret;
}

simtime_t  MM_psDQ_Out::getnextTime(RMTPort * p) {
    return 0;
}

}
