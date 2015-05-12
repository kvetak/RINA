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

Define_Module(DLMonitor);


dlCUInfo::dlCUInfo(){
    CUId = "";
    urgency = 0;
    threshold = 0;
}
dlCUInfo::dlCUInfo(std::string id){
    CUId = id;
    urgency = 0;
    threshold = 0;
}
dlCUInfo::dlCUInfo(std::string id, int urg, int thre){
    CUId = id;
    urgency = urg;
    threshold = thre;
}

void DLMonitor::onPolicyInit(){
    cXMLElement* cuXml = NULL;
    if (par("cuData").xmlValue() != NULL && par("cuData").xmlValue()->hasChildren())
        cuXml = par("cuData").xmlValue();
    else
        error("cuData parameter not initialized!");

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
            }
            else if ( !strcmp(n->getTagName(), "cherishThreshold") ) {
                inf.threshold = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.threshold < 0)
                    inf.threshold = 0;
            }
        }

        CUs[cu] = inf;
    }

}



void DLMonitor::onMessageArrival(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::INPUT){
        return;
    }

    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        count[port]++;
        std::string cu = Q2CU[queue];
        int urgency = CUs[cu].urgency;

        queues[port][urgency].push_back(queue);
        lastInsertedUrgency[port] = urgency;
    }
}

void DLMonitor::onMessageDeparture(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::INPUT){
        return;
    }

    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        count[port]--;
    }
}

void DLMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    if(queue->getType() == RMTQueue::INPUT){
        return;
    }

    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        count[port]--;
        queues[port][lastInsertedUrgency[port]].pop_back();
    }
}

void DLMonitor::postQueueCreation(RMTQueue* queue){
    std::string cu = queue->getName();
    if(CUs.find(cu) == CUs.end()){
        cu == "BE";
    }
    Q2CU[queue] = cu;
}


int DLMonitor::getPortCount(RMTPort* port){
    return count[port];
}

int DLMonitor::getThreshold(RMTQueue* queue){
    std::string cu = Q2CU[queue];
    return CUs[cu].threshold;
}

RMTQueue* DLMonitor::getNextUrgentQ(RMTPort * port){
    PriorityQueuesList * qs = & queues[port];
    for(PQListRIterator it = qs->rbegin(); it != qs->rend(); it++){
        if(!it->second.empty()){
            RMTQueue* q = it->second.front();
            it->second.pop_front();
            return q;
        }
    }
    return NULL;
}
