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

#include <eDLMonitor.h>

namespace eDLMonitor {

Define_Module(eDLMonitor);

dlCUInfo::dlCUInfo(){
    CUId = "";
    queue = "outQ_";
    urgency = 0;
    threshold = 0;
    dropProb = 1;
    absThreshold = 0;
}
dlCUInfo::dlCUInfo(std::string id){
    CUId = id;
    queue = "outQ_";
    queue.append(CUId);
    urgency = 0;
    threshold = 0;
    dropProb = 1;
    absThreshold = 0;
}
dlCUInfo::dlCUInfo(std::string id, std::string _queue, int urg, int thre, double dropP, int absThre){
    CUId = id;
    queue = _queue;
    urgency = urg;
    threshold = thre;
    dropProb = dropP;
    absThreshold = absThre;
}

void eDLMonitor::onPolicyInit(){

    cXMLElement* cuXml = NULL;
    if (par("cuData").xmlValue() != NULL && par("cuData").xmlValue()->hasChildren()){
        cuXml = par("cuData").xmlValue();
    } else {
        error("cuData parameter not initialized!");
    }

    cXMLElementList cus = cuXml->getChildrenByTagName("CUItem");
    for (cXMLElementList::iterator it = cus.begin(); it != cus.end(); ++it) {
        cXMLElement* m = *it;
        if (!m->getAttribute("id")) {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }

        std::string cu = m->getAttribute("id");
        if (cu == "") {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }

        dlCUInfo inf = dlCUInfo(cu);

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), "urgency") ) {
                inf.urgency = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.urgency < 0)
                    inf.urgency = 0;
            } else if ( !strcmp(n->getTagName(), "cherishThreshold") ) {
                inf.threshold = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.threshold < 0)
                    inf.threshold = 0;
            } else if ( !strcmp(n->getTagName(), "cherishAbsThreshold") ) {
                inf.absThreshold = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.absThreshold < 0)
                    inf.absThreshold = 0;
            } else if ( !strcmp(n->getTagName(), "cherishDropProbability") ) {
                inf.dropProb = n->getNodeValue() ? atof(n->getNodeValue()) : 0.0;
                if (inf.dropProb < 0.0)
                    inf.dropProb = 0.0;
                else if (inf.dropProb > 1.0)
                    inf.dropProb = 1.0;
            }
        }

        if(inf.absThreshold < inf.threshold) { inf.absThreshold = inf.threshold; }

        CUs[cu] = inf;
    }


    cXMLElement* urgXml = NULL;
    if (par("urgData").xmlValue() != NULL && par("urgData").xmlValue()->hasChildren()){
        urgXml = par("urgData").xmlValue();
    } else {
        error("urgData parameter not initialized!");
    }

    cXMLElementList urgs = urgXml->getChildrenByTagName("urgency");
    for (cXMLElementList::iterator it = urgs.begin(); it != urgs.end(); ++it) {
        cXMLElement* m = *it;
        if (!m->getAttribute("val")) {
            EV << "Error parsing urgency. Its val is missing!" << endl;
            continue;
        }
        std::string valS = m->getAttribute("val");
        if (valS == "") {
            EV << "Error parsing urgency. Its val is missing!" << endl;
            continue;
        }

        if (!m->getAttribute("prob")) {
            EV << "Error parsing urgency. Its prob is missing!" << endl;
            continue;
        }
        std::string probS = m->getAttribute("prob");
        if (probS == "") {
            EV << "Error parsing urgency. Its prob is missing!" << endl;
            continue;
        }

        int val = atoi(valS.c_str());
        if(val<0) { val = 0; }

        double prob = atof(probS.c_str());
        if(prob<0) { prob = 0; }
        if(prob>1) { prob = 1; }

        probs[val] = prob;
    }
}

void eDLMonitor::postPDUInsertion(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] ++;
            inQ[port].push_back(queue);
        }
        if(queue->getType() == RMTQueue::OUTPUT){
            outC[port] ++;
            std::string cu = Q2CU[queue];
            int urgency = CUs[cu].urgency;
            outQs[port][urgency].push_back(queue);
            lastInsertedUrgency[port] = urgency;
        }
    }
}

void eDLMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] --;
            inQ[port].pop_back();
        } else {
            outC[port] --;
            outQs[port][lastInsertedUrgency[port]].pop_back();
        }
    }
}

void eDLMonitor::postQueueCreation(RMTQueue* queue){
    if(queue->getType() == RMTQueue::OUTPUT) {
        std::string cu = "BE";

        for(cuRepoiterator it = CUs.begin(); it != CUs.end(); it++){
            if(it->second.queue == queue->getName()){
                cu = it->first;
            }
        }
        Q2CU[queue] = cu;
    }
}


RMTQueue* eDLMonitor::getNextInput(RMTPort* port){
    RMTQueue* q = NULL;

    QueuesList* ql = &(inQ[port]);
    if(!ql->empty()) {
        q = ql->front();
        ql->pop_front();
    }

    if(q != NULL){
        inC[port]--;
    }

    return q;
}

RMTQueue* eDLMonitor::getNextOutput(RMTPort* port){
    RMTQueue* q = NULL;

    PriorityQueuesList * qs = & outQs[port];
    PQListRIterator tit = qs->rend();
    for(PQListRIterator it = qs->rbegin(); it != qs->rend() && q == NULL; it++){
        if(!it->second.empty()){
            tit = it;
            double tP = probs[it->first];
            if(tP <= 0 || tP < uniform(0,1) ){
                q = it->second.front();
                it->second.pop_front();
            }
        }
    }
    if(q == NULL && tit != qs->rend()){
        q = tit->second.front();
        tit->second.pop_front();
    }

    if(q != NULL){
        outC[port]--;
    } else {
        error("No queue found");
    }

    return q;
}


double eDLMonitor::getInDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return ( (int)inC[port] < queue->getMaxLength() )? 0 : 1;
}

double eDLMonitor::getOutDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    dlCUInfo din = CUs[Q2CU[queue]];
    int count = outC[port];

    return ( count < din.threshold )? 0 : ( ( count < din.absThreshold )? din.dropProb : 1) ;


}


}
