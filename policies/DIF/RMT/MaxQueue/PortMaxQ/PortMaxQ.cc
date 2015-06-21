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

#include <PortMaxQ.h>


Define_Module(PortMaxQ);

void PortMaxQ::onPolicyInit()
{
    monitor = dynamic_cast<SmartMonitor*>(qMonPolicy);
    if (monitor == NULL)
    {
        EV << "!!! PortMaxQ has to be used in conjecture with SmartMonitor!" << endl;
    }
}

bool PortMaxQ::run(RMTQueue* queue)
{
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    bool ret = true;
    if(port != NULL){
        if(queue->getType() == RMTQueue::INPUT){
            ret = monitor->getInCount(port) > monitor->getInThreshold(queue);
        } else {
            ret = monitor->getOutCount(port) > monitor->getOutThreshold(queue);
        }
    }
    if(ret) {
        std::string qos = ((PDU*)queue->getLastPDU())->getConnId().getQoSId();

        if(queue->getType() == RMTQueue::INPUT){
            dropIn[qos]++;
        } else {
            dropOut[qos]++;
        }
    }

    return ret;
}


void  PortMaxQ::finish(){
    if(!dropIn.empty() || !dropOut.empty()) {
        EV << "--------"<< endl;
        EV << "At " << getFullPath()<< endl;
        std::map<std::string, unsigned int>::iterator it;

        if(!dropIn.empty() ) {
            EV << "On input:" <<endl;
            for(it = dropIn.begin(); it!= dropIn.end(); it++){
                EV << "QoS " << it->first << " - Dropped "<< it->second << endl;
            }
        }

        if(!dropOut.empty() ) {
            EV << "On output:" <<endl;
            for(it = dropOut.begin(); it!= dropOut.end(); it++){
                EV << "QoS " << it->first << " - Dropped "<< it->second << endl;
            }
        }
        EV << "--------"<< endl;
    }
}
