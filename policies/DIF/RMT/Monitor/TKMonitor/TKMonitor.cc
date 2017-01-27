//
// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/RMT/Monitor/TKMonitor/TKMonitor.h"

namespace TKMonitor {

Define_Module(TKMonitor);

TKInfo::TKInfo(){
    id = "outQ_";
    tokensTic = 1;
    maxTokens = 5;
}
TKInfo::TKInfo(std::string _id){
    id = _id;
    tokensTic = 1;
    maxTokens = 5;
}
TKInfo::TKInfo(std::string _id, int _tokensTic, int _maxTokens) {
    id = _id;
    tokensTic = _tokensTic;
    maxTokens = _maxTokens;
}
QTKStatus::QTKStatus() {
    info = TKInfo();
    tokens = 0;
    count = 0;
}
QTKStatus::QTKStatus(TKInfo _info) {
    info = _info;
    tokens = 0;
    count = 0;
}

void TKMonitor::onPolicyInit(){

    cXMLElement* tkXml = NULL;
    if (par("tkData").xmlValue() != NULL && par("tkData").xmlValue()->hasChildren()){
        tkXml = par("tkData").xmlValue();
    } else {
        error("cuData parameter not initialized!");
    }

    cXMLElementList tks = tkXml->getChildrenByTagName("TKItem");
    for(cXMLElement * m : tks){
        if (!m->getAttribute("id")) {
            EV << "Error parsing TK. Its ID is missing!" << endl;
            continue;
        }

        TKInfo inf = TKInfo(m->getAttribute("id"));

        cXMLElementList attrs = m->getChildren();
        for(cXMLElement * n : attrs) {
            if ( !strcmp(n->getTagName(), "tokensTic") ) {
                inf.tokensTic = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.tokensTic <= 0) { inf.tokensTic = 1; }
            }

            if ( !strcmp(n->getTagName(), "maxTokens") ) {
                inf.maxTokens = n->getNodeValue() ? atoi(n->getNodeValue()) : 0;
                if (inf.maxTokens <= 0) { inf.maxTokens = 1; }
            }
        }

        TKs[inf.id] = inf;
    }

    tokensPDU = par("tokensPDU").longValue();
}

void TKMonitor::postPDUInsertion(RMTQueue* queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] ++;
            inQ[port].push_back(queue);
        }
        if(queue->getType() == RMTQueue::OUTPUT){
            outC[port] ++;
            Qs[queue].count++;
        }
    }
}

void TKMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            inC[port] --;
            inQ[port].pop_back();
        } else {
            outC[port] --;
            Qs[queue].count--;
        }
    }
}

void TKMonitor::postQueueCreation(RMTQueue* queue){
    if(queue->getType() == RMTQueue::OUTPUT) {
        TKInfo t = TKs["BE"];
        for(auto info : TKs) {
            if(queue->getName() == info.second.id) {
                t = info.second;
            }
        }
        Qs[queue].info = t;
        RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
        OutSet[port].insert(queue);
    }

}

RMTQueue* TKMonitor::getNextInput(RMTPort* port){
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

RMTQueue* TKMonitor::getNextOutput(RMTPort* port){
    RMTQueue* ret = NULL;

    int maxT = -1;
    int maxC = 0;
    for(RMTQueue * q : OutSet[port]) {
        QTKStatus * info = &Qs[q];

        if(info->count > 0) {
            if(info->tokens > maxT) {
                maxC = info->count;
                maxT = info->tokens;
                ret = q;
            } else if (info->tokens == maxT && info->count > maxC) {
                maxC = info->count;
                ret = q;
            }
        }
        info->tokens = min(info->info.tokensTic + info->tokens, info->info.maxTokens);

    }

    if(ret != NULL){
        outC[port]--;
        QTKStatus * info = &Qs[ret];
        info->count--;
        info->tokens = max(0, info->tokens-tokensPDU);
    }

    return ret;
}

double TKMonitor::getInDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return ( (int)inC[port] < queue->getMaxLength() )? 0 : 1;
}

double TKMonitor::getOutDropProb(RMTQueue * queue) {
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    if(port == NULL){ error("RMTPort for RMTQueue not found."); }

    return ( (int)outC[port] < queue->getMaxLength() )? 0 : 1;
}

}
