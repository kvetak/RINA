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

#include "DIF/RMT/MaxQueue/DumbMaxQ/DumbMaxQ.h"


Define_Module(DumbMaxQ);

void DumbMaxQ::onPolicyInit()
{
    monitor = dynamic_cast<SmartMonitor*>(qMonPolicy);
    if (monitor == NULL)
    {
        EV << "!!! DumbMaxQ has to be used in conjecture with SmartMonitor!" << endl;
    }
}

bool DumbMaxQ::run(RMTQueue* queue)
{
    bool drop = false;
    double dp;
    switch (queue->getType()) {
        case RMTQueue::INPUT: dp = monitor->getInDropProb(queue); break;
        case RMTQueue::OUTPUT: dp = monitor->getOutDropProb(queue); break;
    }

    if( dp <= 0 ) { drop = false; }
    if( dp >= 1 ) { drop = true; }
    else { drop = dp >= omnetpp::uniform(omnetpp::getEnvir()->getRNG(0), 0.0,1.0); }

    std::string qos = ((PDU*)queue->getLastPDU())->getConnId().getQoSId();
    if(drop) {
        if(queue->getType() == RMTQueue::INPUT){
            dropIn[qos]++;
            dDropIn[qos] += queue->getLastPDU()->getBitLength();

            dropIn["*"]++;
            dDropIn["*"] += queue->getLastPDU()->getBitLength();
        } else {
            dropOut[qos]++;
            dDropOut[qos] += queue->getLastPDU()->getBitLength();

            dropOut["*"]++;
            dDropOut["*"] += queue->getLastPDU()->getBitLength();
        }
    } else {
        if(queue->getType() == RMTQueue::INPUT){
            okIn[qos]++;
            dOkIn[qos] += queue->getLastPDU()->getBitLength();

            okIn["*"]++;
            dOkIn["*"] += queue->getLastPDU()->getBitLength();
        } else {
            okOut[qos]++;
            dOkOut[qos] += queue->getLastPDU()->getBitLength();

            okOut["*"]++;
            dOkOut["*"] += queue->getLastPDU()->getBitLength();
        }
    }

    return drop;
}


void  DumbMaxQ::finish(){
    if(par("printAtEnd").boolValue()) {
        EV << "--------"<< endl;
        EV << "At " << getFullPath()<< endl;
        std::map<std::string, unsigned int>::iterator it;

        EV << "On output:" <<endl;
        for(it = okOut.begin(); it!= okOut.end(); it++){
            EV << "QoS " << it->first << " - Processed " << okOut[it->first] <<"(" << dOkOut[it->first] << ")" << " - Dropped "<< dropOut[it->first] <<"(" << dDropOut[it->first] << ")" << endl;
        }
        EV << "--------"<< endl;
    }
}
