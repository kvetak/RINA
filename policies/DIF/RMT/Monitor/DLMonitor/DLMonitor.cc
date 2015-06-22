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

#include <DLMonitor.h>

namespace DLMonitor {

Define_Module(DLMonitor);

dlCUInfo::dlCUInfo(){
    CUId = "";
    queue = "outQ_";
    urgency = 0;
    threshold = 0;
}
dlCUInfo::dlCUInfo(std::string id){
    CUId = id;
    queue = "outQ_";
    queue.append(CUId);
    urgency = 0;
    threshold = 0;
}
dlCUInfo::dlCUInfo(std::string id, std::string _queue, int urg, int thre){
    CUId = id;
    queue = _queue;
    urgency = urg;
    threshold = thre;
}

void DLMonitor::onPolicyInit(){

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
            }
        }

        CUs[cu] = inf;
    }
}

void DLMonitor::postPDUInsertion(RMTQueue* queue) {
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

void DLMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
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

void DLMonitor::postQueueCreation(RMTQueue* queue){
    std::string cu = "BE";

    for(cuRepoiterator it = CUs.begin(); it != CUs.end(); it++){
        if(it->second.queue == queue->getName()){
            cu = it->first;
        }
    }

    Q2CU[queue] = cu;
}

RMTQueue* DLMonitor::getNextInput(RMTPort* port){
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

RMTQueue* DLMonitor::getNextOutput(RMTPort* port){
    RMTQueue* q = NULL;

    PriorityQueuesList * qs = & outQs[port];
    for(PQListRIterator it = qs->rbegin(); it != qs->rend() && q == NULL; it++){
        if(!it->second.empty()){
            q = it->second.front();
            it->second.pop_front();
        }
    }

    if(q != NULL){
        outC[port]--;
    }

    return q;
}

double DLMonitor::getInDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return ( (int)inC[port] < queue->getMaxLength() )? 0 : 1;
}

double DLMonitor::getOutDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return ( (int)outC[port] < CUs[Q2CU[queue]].threshold )? 0 : 1;
}

}
